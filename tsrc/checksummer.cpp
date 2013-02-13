#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <apr.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_md5.h>
#include <apr_random.h>


void do_file_md5(const std::string& file_name)
{
  apr_size_t length;
  char * buffer;

  std::ifstream is;
  is.open(file_name.c_str(), std::ios::in);

  // get length of file:
  is.seekg (0, std::ios::end);
  length = is.tellg();
  is.seekg (0, std::ios::beg);

  // allocate memory:
  buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);

  is.close();
  unsigned char digest[APR_MD5_DIGESTSIZE + 1];
  apr_md5(digest, buffer, length);
  
  for(apr_size_t ind = 0; ind < APR_MD5_DIGESTSIZE; ind++)
  {
    unsigned short letter = digest[ind];
    std::cout << std::hex << std::setw(2) << std::setfill('0') << letter;
  }
  std::cout << "  " << file_name << std::endl;

  delete[] buffer;
}


void do_file_sha256(const std::string& file_name)
{
  apr_size_t length;
  char * buffer;

  std::ifstream is;
  is.open(file_name.c_str(), std::ios::in);

  // get length of file:
  is.seekg (0, std::ios::end);
  length = is.tellg();
  is.seekg (0, std::ios::beg);

  // allocate memory:
  buffer = new char [length];

  // read data as a block:
  is.read (buffer,length);

  is.close();
  
  apr_pool_t* sha_pool;
  apr_pool_create(&sha_pool, NULL);
  
  unsigned char result[256];
  
  apr_crypto_hash_t* sha_hash = apr_crypto_sha256_new(sha_pool);
  sha_hash->init(sha_hash);
  sha_hash->add(sha_hash, buffer, length);
  sha_hash->finish(sha_hash, result);
  
  for(apr_size_t ind = 0; ind < sha_hash->size; ind++)
  {
    unsigned short letter = result[ind];
    std::cout << std::hex << std::setw(2) << std::setfill('0') << letter;
  }
  std::cout << "  " << file_name << std::endl;
  
  delete[] buffer;

  apr_pool_destroy(sha_pool);
}



int main(int argc, const char *const *argv, const char *const *env)
{
  apr_status_t ret = apr_app_initialize(&argc, &argv, &env);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while initializing APR: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    return 1;
  }
  
  apr_pool_t* memPool;
  ret = apr_pool_create(&memPool, NULL);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while creating memory pool: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    apr_terminate();
    return 1;
  }
  
  if(argc < 2)
  {
    std::cerr << "No input file given...: " << std::endl;
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  /*apr_file_t* inputFile;
  ret = apr_file_open(&inputFile, argv[1], APR_READ, APR_OS_DEFAULT, memPool);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while opening input file \"" << argv[1] << "\": " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  apr_md5_ctx_t context;
  ret = apr_md5_init(&context);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while initializing MD5 context: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    apr_file_close(inputFile);
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  unsigned char inBuf[256];
  memset(inBuf, 0, sizeof(inBuf));
  unsigned char digest[APR_MD5_DIGESTSIZE + 1];
  memset(digest, 0, sizeof(digest));
  apr_size_t bytes_read;
  ret = apr_file_read_full(inputFile, inBuf, sizeof(inBuf), &bytes_read);
  if(ret != APR_SUCCESS && ret != APR_EOF)
  {
    char errStr[256];
    std::cerr << "Error while reading input file: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    apr_md5_final(digest, &context);
    apr_file_close(inputFile);
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  ret = apr_md5_update(&context, inBuf, bytes_read);
  while(ret != APR_SUCCESS)
  {
    memset(inBuf, 0, sizeof(inBuf));
    ret = apr_file_read_full(inputFile, inBuf, sizeof(inBuf), &bytes_read);
    if(ret != APR_SUCCESS)
    {
      char errStr[256];
      std::cerr << "Error while reading input file: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
      apr_md5_final(digest, &context);
      apr_file_close(inputFile);
      apr_pool_destroy(memPool);
      apr_terminate();
      return 1;
    }
    ret = apr_md5_update(&context, inBuf, bytes_read);
  }
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while updating MD5 context: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    apr_md5_final(digest, &context);
    apr_file_close(inputFile);
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  ret = apr_md5_final(digest, &context);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while finalizing MD5 context: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
  }
    
  ret = apr_file_close(inputFile);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while closing input file: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
  }
  
  for(apr_size_t ind = 0; ind < APR_MD5_DIGESTSIZE; ind++)
  {
    unsigned short letter = digest[ind];
    std::cout << std::hex << letter;
  }
  std::cout << "  " << argv[1] << std::endl;*/
  
  //do_file_md5(argv[1]);
  do_file_sha256(argv[1]);
  
  apr_pool_destroy(memPool);
  apr_terminate();
  return 0;
}

