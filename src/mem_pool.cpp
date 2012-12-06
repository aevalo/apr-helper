#include "apr_status.hpp"
#include "mem_pool.hpp"


mem_pool::mem_pool()
 : non_copyable(), mPool(NULL)
{
}

mem_pool::~mem_pool()
{
  const char* debug_str = APR_POOL__FILE_LINE__;
  destroy(debug_str);
}

apr_status mem_pool::create()
{
  return apr_pool_create(&mPool, NULL);
}

apr_status mem_pool::create(const mem_pool& parent)
{
  return apr_pool_create(&mPool, parent.mPool);
}

void mem_pool::destroy(const char* file_line)
{
  if (mPool)
  {
#ifdef APR_POOL_DEBUG
    const char* debug_str = (file_line ? file_line : APR_POOL__FILE_LINE__);
    apr_pool_destroy_debug(mPool, debug_str);
#else
    apr_pool_destroy(mPool);
#endif
    mPool = NULL;
  }
}
