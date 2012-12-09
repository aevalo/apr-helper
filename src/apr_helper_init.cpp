#include "apr_helper_init.hpp"


apr_status_t apr_helper_initialize()
{
  apr_status_t ret = APR_SUCCESS;
#ifdef APR_HELPER_SHARED_LIB
  // Only shared build needs its own initialization for APR.
  ret = apr_initialize();
#endif
  return ret;
}

void apr_helper_terminate()
{
#ifdef APR_HELPER_SHARED_LIB
  // Only shared build needs its own deinitialization for APR.
  apr_terminate();
#endif
}

