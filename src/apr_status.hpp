#ifndef APR_ERROR_HPP_INCLUDED
#define APR_ERROR_HPP_INCLUDED

#include <string>
#include <apr_general.h>
#include <apr_helper_config.hpp>

// There is a bug in VS2010
// http://connect.microsoft.com/VisualStudio/feedback/details/696593/vc-10-vs-2010-basic-string-exports
// std::string, and other string related stuffs cannot be exported from DLL
//APR_HELPER_TEMPLATE template class APR_HELPER_API std::allocator<char>;
//APR_HELPER_TEMPLATE template class APR_HELPER_API std::basic_string<char>;

class APR_HELPER_API apr_status
{
  public:
    apr_status(const apr_status& other);
    apr_status(apr_status_t status = APR_SUCCESS);
    ~apr_status();
    
    apr_status_t status() { return mAprStatus; }
    //const std::string& error_str() { return mErrorStr; }
    const char* error_str() { return mErrorStr; }
    bool is_error() const { return (mAprStatus != APR_SUCCESS); }

    apr_status& operator=(apr_status_t status);
    apr_status& operator=(const apr_status& rhs);

  private:
    apr_status_t  mAprStatus;
    //std::string   mErrorStr;
    char          mErrorStr[256];
};



#endif // APR_ERROR_HPP_INCLUDED
