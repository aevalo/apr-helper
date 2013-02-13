#include <iostream>
#include <cstdlib>
#include <apr.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_random.h>


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
  
  apr_size_t byte_count = atoi(argv[1]);
  unsigned char* buf = new unsigned char[byte_count];
  ret = apr_generate_random_bytes(buf, byte_count);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while generating random bytes: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    delete[] buf;
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  apr_file_t* outFile;
  if(argc < 3)
  {
    ret = apr_file_open_stdout(&outFile, memPool);
  }
  else
  {
    ret = apr_file_open(&outFile, argv[2], APR_WRITE | APR_BINARY | APR_CREATE | APR_TRUNCATE, APR_OS_DEFAULT, memPool);
  }
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while opening input file \"" << argv[2] << "\": " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    delete[] buf;
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  
  ret = apr_file_write(outFile, buf, &byte_count);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while writing random bytes: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
    delete[] buf;
    apr_pool_destroy(memPool);
    apr_terminate();
    return 1;
  }
  delete[] buf;
  
  ret = apr_file_close(outFile);
  if(ret != APR_SUCCESS)
  {
    char errStr[256];
    std::cerr << "Error while closing input file: " << apr_strerror(ret, errStr, sizeof(errStr)) << std::endl;
  }
  
  apr_pool_destroy(memPool);
  apr_terminate();
  return 0;
}

