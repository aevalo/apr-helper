#include <sstream>
#include <iomanip>
#include <apr.h>
#include <apr_sha1.h>
#include <apr_file_io.h>

#include "sha1_checksum.hpp"


apr_status_t sha1_file(const std::string& filename, std::string& checksum, bool binary, apr_pool_t* parentPool)
{
  apr_status_t ret = APR_SUCCESS;

  apr_pool_t* pool = NULL;
  ret = apr_pool_create(&pool, parentPool);
  if(ret == APR_SUCCESS)
  {
    apr_file_t* in = NULL;
    apr_int32_t flags = (binary ? APR_READ | APR_BINARY : APR_READ);

    ret = apr_file_open(&in, filename.c_str(), flags, APR_OS_DEFAULT, pool);
    if(ret == APR_SUCCESS)
    {
      unsigned char digest[APR_SHA1_DIGESTSIZE + 1];
      memset(digest, 0, APR_SHA1_DIGESTSIZE + 1);

      apr_sha1_ctx_t context;
      apr_sha1_init(&context);

      unsigned char buffer[512];
      memset(buffer, 0, sizeof(buffer));

      apr_size_t bytes_read = 0;
      ret = apr_file_read_full(in, buffer, sizeof(buffer) - 1, &bytes_read);

      if(ret == APR_SUCCESS || ret == APR_EOF)
      {
        if(binary) apr_sha1_update_binary(&context, buffer, bytes_read);
        else apr_sha1_update(&context, (const char*)buffer, bytes_read);
      }

      while(ret == APR_SUCCESS)
      {
        ret = apr_file_read_full(in, buffer, sizeof(buffer) - 1, &bytes_read);
        if(ret == APR_SUCCESS || ret == APR_EOF)
        {
          if(binary) apr_sha1_update_binary(&context, buffer, bytes_read);
          else apr_sha1_update(&context, (const char*)buffer, bytes_read);
        }
      }

      apr_sha1_final(digest, &context);

      if(ret == APR_EOF)
      {
        std::ostringstream oss;
        for(int i = 0; i < APR_SHA1_DIGESTSIZE; i++)
        {
          unsigned short letter = digest[i];
          oss << std::hex << std::setw(2) << std::setfill('0') << letter;
        }
        checksum = oss.str();
        ret = APR_SUCCESS;
      }
      apr_file_close(in);
    }
    apr_pool_destroy(pool);
  }
  
  return ret;
}
