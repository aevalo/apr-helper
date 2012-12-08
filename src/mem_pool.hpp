#ifndef MEM_POOL_HPP_INCLUDED
#define MEM_POOL_HPP_INCLUDED

#include <apr_general.h>
#include <apr_status.hpp>
#include <non_copyable.hpp>
#include <apr_helper_config.hpp>

class APR_HELPER_API mem_pool : public non_copyable
{
  public:
    mem_pool();
    virtual ~mem_pool();
    
    apr_status create();
    apr_status create(const mem_pool& parent);
    
    void destroy(const char* file_line = NULL);
    
    inline operator apr_pool_t* () const { return mPool; }
    inline operator apr_pool_t* () { return mPool; }
    
  private:
    apr_pool_t* mPool;
};


#endif // MEM_POOL_HPP_INCLUDED
