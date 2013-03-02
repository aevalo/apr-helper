#include "apr_helper_init.hpp"


apr_status_t apr_helper_initialize()
{
  apr_status_t ret = APR_SUCCESS;
  ret = apr_initialize();
  return ret;
}

void apr_helper_terminate()
{
  apr_terminate();
}

