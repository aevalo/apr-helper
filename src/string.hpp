#ifndef APR_HELPER_STRING_HPP_INCLUDED
#define APR_HELPER_STRING_HPP_INCLUDED

#include <apr_general.h>
#include <apr_helper_config.hpp>

namespace apr_helper {
  APR_HELPER_API bool line_starts_with(const char* str, const char c, bool skipws = false);
  APR_HELPER_API bool line_has_alphanum(const char* str);
  APR_HELPER_API char* ltrim(char* dst, const char* src);
  APR_HELPER_API char* rtrim(char* dst, const char* src);
  APR_HELPER_API char* trim(char* dst, const char* src);
  APR_HELPER_API apr_status_t apr_helper_file_gets(char* str, size_t size, apr_file_t* thefile);
}

#endif // APR_HELPER_STRING_HPP_INCLUDED
