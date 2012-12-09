#include <iostream>
#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <direct.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_tables.h>
#include <pcre.h>
#include <string.hpp>
#include <regex.hpp>
#include <mem_pool.hpp>
#include <apr_array.hpp>
#include <apr_helper_init.hpp>


#ifdef WIN32
# define getcwd _getcwd
#endif


typedef std::pair<std::string, apr_table_t*> ini_section;
typedef std::vector<ini_section> ini_sections;

int main( int argc, char* argv[] )
{
#ifdef WIN32
  // Set console output code page to UTF-7
  SetConsoleOutputCP(65000);
  // Set console input code page to UTF-7
  SetConsoleCP(65000);
#endif

  mem_pool pool;
  apr_status rv;
  apr_file_t* iniFile;
  std::string file_name;
  
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <ini file>" << std::endl;
    //return 1;
    char buf[256];
    char* ret = getcwd(buf, sizeof(buf));
    if (ret)
    {
      std::string cwd(buf);
      if (cwd.find("bin") != std::string::npos)
      {
#ifdef WIN32
    file_name = "..\\test_data\\test.ini";
#else
    file_name = "../test_data/test.ini";
#endif
      }
      else
      {
#ifdef WIN32
    file_name = ".\\test_data\\test.ini";
#else
    file_name = "./test_data/test.ini";
#endif
      }
    }

  }
  else
  {
    file_name = argv[1];
  }
  
  apr_initialize();
  apr_helper_initialize();

  rv = pool.create();
  if (rv.is_error())
  {
    std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    pool.destroy(APR_POOL__FILE_LINE__);
    apr_terminate();
    return 1;
  }
  
  rv = apr_file_open(&iniFile, file_name.c_str(), APR_READ | APR_XTHREAD | APR_BUFFERED | APR_SHARELOCK, APR_OS_DEFAULT, pool);
  if (rv.is_error())
  {
    std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    pool.destroy(APR_POOL__FILE_LINE__);
    apr_terminate();
    return 1;
  }
  
  rv = apr_file_eof( iniFile );
  ini_section current("Default", apr_table_make(pool, 10));
  ini_sections sections;
  while(rv.status() != APR_EOF)
  {
    if (rv.is_error())
    {
        std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    }
    
    char line[ 256 ];
    rv = apr_file_gets(	line, sizeof( line ), iniFile );
    if (rv.status() != APR_EOF && rv.is_error())
    {
        std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    }
    try
    {
      char commentRegex[] = "^\\s*#\\s*(.+)\\s*$";
      char sectionRegex[] = "^\\s*\\[(.+)\\].*$";
      char keyvalRegex[] = "^\\s*(\\w+)\\s*=\\s*(.+)\\s*$";
      
      regex comment(commentRegex);
      regex section(sectionRegex);
      regex keyval(keyvalRegex);
      
      if (comment.match(line))
      {
        std::cout << "Skipping comment..." << std::endl;
      }
      else
      {
        std::vector<std::string> matches = section.match_sub(line);
        if (matches.size() > 0)
        {
          std::cout << "Found section " << matches.at(1) << std::endl;
          sections.push_back(current);
          current = ini_section(matches.at(1), apr_table_make(pool, 10));
        }
        
        matches = keyval.match_sub(line);
        if (matches.size() > 0)
        {
          std::cout << matches.at(1) << " (" << matches.at(1).length() << ")" << " => " << matches.at(2) << " (" << matches.at(2).length() << ")" << std::endl;
          const char* val = apr_table_get(current.second, matches.at(1).c_str());
          if (val)
          {
            apr_table_set(current.second, matches.at(1).c_str(), matches.at(2).c_str());
          }
          else
          {
            apr_table_add(current.second, matches.at(1).c_str(), matches.at(2).c_str());
          }
        }
      }
    }
    catch(pcre_exception& pcre)
    {
      std::cerr << "PCRE exception caught: " << pcre.what() << std::endl;
    }
    catch(std::exception& e)
    {
      std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    rv = apr_file_eof( iniFile );
    if (rv.status() == APR_EOF)
    {
      sections.push_back(current);
    }
  }


  
  std::cout << "Following sections and setting were found:" << std::endl;
  for (std::size_t i = 0; i < sections.size(); i++)
  {
    std::cout << "[" << sections.at(i).first << "]" << std::endl;
    const apr_array_header_t* keys = apr_table_elts(sections.at(i).second);
    for (int j = 0; j < keys->nelts; j++)
    {
      const char* key = apr_array_get<const char*>(keys, j);
      if (key)
      {
        const char* val = apr_table_get(sections.at(i).second, key);
        if (val)
        {
          std::cout << "  " << key << " = " << val << std::endl;
        }
      }
    }
  }
  rv = apr_file_close( iniFile );
  if (rv.is_error())
  {
      std::cerr << "Error occurred: " << rv.error_str() << std::endl;
      pool.destroy(APR_POOL__FILE_LINE__);
      apr_terminate();
      return 1;
  }

  pool.destroy(APR_POOL__FILE_LINE__);

  apr_terminate();
  apr_helper_terminate();

  return 0;
}
