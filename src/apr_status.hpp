#ifndef APR_ERROR_HPP_INCLUDED
#define APR_ERROR_HPP_INCLUDED

#include <string>
#include <apr_general.h>
#include <apr_helper_config.hpp>


class APR_HELPER_API apr_status
{
  public:
    apr_status(const apr_status& other);
    apr_status(apr_status_t status = APR_SUCCESS);
    ~apr_status();
    
    apr_status_t status() { return mAprStatus; }
    const std::string& error_str() { return mErrorStr; }
    bool is_error() const { return (mAprStatus != APR_SUCCESS); }

    apr_status& operator=(apr_status_t status);
    apr_status& operator=(const apr_status& rhs);

  private:
    apr_status_t  mAprStatus;
    std::string   mErrorStr;
};



#endif // APR_ERROR_HPP_INCLUDED
