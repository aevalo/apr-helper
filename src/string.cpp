#include <cstring>
#include <stdexcept>
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include "string.hpp"

namespace {
  // New line
  const char LFCR[] = "\n\r"; // Microsoft Windows, DEC TOPS-10, RT-11...
  const char CRLF[] = "\r\n"; // Acorn BBC and RISC OS spooled text output.
  const char LF[] = "\n";      // Multics, Unix and Unix-like systems.
}

namespace apr_helper {
  
  bool line_starts_with(const char* str, const char c, bool skipws)
  {
    size_t str_len = strlen(str);
    size_t str_iter = 0;
    if (skipws)
    {
      while (str_iter < str_len && isspace(str[str_iter]) != 0)
        str_iter++;
    }
    return (str[str_iter] == c);
  }
  
  bool line_has_alphanum(const char* str)
  {
    static char alphanums[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return (strpbrk(str, alphanums) != NULL);
  }
  
  char* ltrim(char* dst, const char* src)
  {
    size_t src_len = strlen(src);
    size_t str_off = 0;
    while (str_off <= src_len && isspace(src[str_off]) != 0)
      str_off++;
    return apr_cpystrn(dst, src + str_off, src_len - str_off + 1);
  }
  
  char* rtrim(char* dst, const char* src)
  {
    size_t src_len = strlen(src);
    size_t str_off = src_len;
    while (str_off >= 0 && isspace(src[str_off]) != 0)
      str_off--;
    return apr_cpystrn(dst, src, str_off + 1);
  }
  
  char* trim(char* dst, const char* src)
  {
    size_t src_len = strlen(src);
    size_t str_beg = 0;
    size_t str_end = src_len - 1;
    while (str_beg <= src_len && isspace(src[str_beg]) != 0)
      str_beg++;
    while (str_end >= 0 && isspace(src[str_end]) != 0)
      str_end--;
    char* ret = NULL;
    if ((strlen(src + str_beg) > (str_end - str_beg)) > 0)
      ret = strncpy(dst, src + str_beg, (str_end - str_beg) + 1);
    dst[(str_end - str_beg) + 1] = '\0';
    return ret;
  }
  
  // Same as apr_helper_file_gets, but new line is stripped from line end
  apr_status_t apr_helper_file_gets(char* str, size_t size, apr_file_t* thefile)
  {
    apr_status_t rv = APR_INCOMPLETE;
    static char buf[1024];
    memset(buf, 0, 1024);
    try {
      rv = apr_file_gets(buf, 1024, thefile);
      if (rv == APR_SUCCESS)
      {
        size_t str_len = strlen(buf);
        size_t dst_len = str_len + 1;
        if ((strstr(buf, LFCR) != NULL) || (strstr(buf, CRLF) != NULL))
        {
          dst_len -= 2;
        }
        else if (strstr(buf, LF) != NULL)
        {
          dst_len -= 1;
        }
        if (dst_len > size)
        {
          dst_len = size;
        }
        apr_cpystrn(str, buf, dst_len);
        rv = APR_SUCCESS;
      }
      else
      {
        rv = APR_EGENERAL;
      }
   }
    catch (std::bad_alloc&) {
      rv = APR_EGENERAL;
    }
    return rv;
  }
  
}
