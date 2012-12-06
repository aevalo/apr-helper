#include <iostream>
#include <cctype>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <pcre.h>
#include <string.hpp>
#include <regex.hpp>
#include <mem_pool.hpp>


int main( int argc, char* argv[] )
{
  mem_pool pool;
  apr_status rv;
  apr_file_t* iniFile;
  
  if (argc < 2)
  {
      std::cerr << "Usage: " << argv[ 0 ] << " <ini file>" << std::endl;
      return 1;
  }
  
  apr_initialize();
  rv = pool.create();
  if (rv.is_error())
  {
      std::cerr << "Error occurred: " << rv.error_str() << std::endl;
      apr_terminate();
      return 1;
  }
  
  rv = apr_file_open( &iniFile, argv[ 1 ], APR_READ | APR_XTHREAD | APR_BUFFERED | APR_SHARELOCK, APR_OS_DEFAULT, pool );
  if (rv.is_error())
  {
      std::cerr << "Error occurred: " << rv.error_str() << std::endl;
      apr_terminate();
      return 1;
  }
  
  rv = apr_file_eof( iniFile );
  while(rv.status() != APR_EOF)
  {
    if (rv.is_error())
    {
        std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    }
    
    char line[ 256 ];
    rv = apr_file_gets(	line, sizeof( line ), iniFile );
    if (rv.is_error())
    {
        std::cerr << "Error occurred: " << rv.error_str() << std::endl;
    }
    try
    {
      char commentRegex[] = "^\\s*#\\s*(.+)\\s*$";
      //char commentRegex[] = "^\\s*?#";
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
        }
        
        matches = keyval.match_sub(line);
        if (matches.size() > 0)
        {
          std::cout << matches.at(1) << " (" << matches.at(1).length() << ")" << " => " << matches.at(2) << " (" << matches.at(2).length() << ")" << std::endl;
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
  }
  
  rv = apr_file_close( iniFile );
  if (rv.is_error())
  {
      std::cerr << "Error occurred: " << rv.error_str() << std::endl;
      apr_terminate();
      return 1;
  }
  pool.destroy(APR_POOL__FILE_LINE__);
  apr_terminate();
  
  return 0;
}
