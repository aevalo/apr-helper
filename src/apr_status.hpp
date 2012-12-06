#ifndef APR_ERROR_HPP_INCLUDED
#define APR_ERROR_HPP_INCLUDED

#include <utility>
#include <string>
#include <apr_general.h>


class apr_status : protected std::pair<apr_status_t, std::string>
{
  public:
    apr_status(const apr_status& other);
    apr_status(apr_status_t status = APR_SUCCESS);
    ~apr_status();
    
    inline apr_status_t status() { return first; }
    inline const std::string& errorStr() { return second; }
    inline bool is_error() const { return (first != APR_SUCCESS); }

    apr_status& operator=(apr_status_t status);
    apr_status& operator=(const apr_status& rhs);
};



#endif // APR_ERROR_HPP_INCLUDED
