#ifndef APR_HELPER_STRING_HPP_INCLUDED
#define APR_HELPER_STRING_HPP_INCLUDED

#include <apr_general.h>

namespace apr_helper {
  bool line_starts_with(const char* str, const char c, bool skipws = false);
  bool line_has_alphanum(const char* str);
  char* ltrim(char* dst, const char* src);
  char* rtrim(char* dst, const char* src);
  char* trim(char* dst, const char* src);
  apr_status_t apr_helper_file_gets(char* str, size_t size, apr_file_t* thefile);
}

#endif // APR_HELPER_STRING_HPP_INCLUDED
