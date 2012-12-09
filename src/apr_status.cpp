#include <exception>
#include <cstdio>
#include "apr_status.hpp"

#ifdef WIN32
# define snprintf _snprintf
#endif



apr_status::apr_status(const apr_status& other)
  : mAprStatus(other.mAprStatus)
{
  snprintf(mErrorStr, 256, "%s", other.mErrorStr);
}

apr_status::apr_status(apr_status_t status)
  : mAprStatus(status)
{
  memset(mErrorStr, 0, 256);
  if (mAprStatus != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(mAprStatus, buf, sizeof(buf));
    if (ret)
    {
      //mErrorStr = buf;
      snprintf(mErrorStr, 256, "%s", buf);
    }
  }
}

apr_status::~apr_status()
{
  // Nothing to do
}


apr_status& apr_status::operator=(apr_status_t status)
{
  mAprStatus = status;
  //mErrorStr.clear();
  memset(mErrorStr, 0, 256);
  if (mAprStatus != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(mAprStatus, buf, sizeof(buf));
    if (ret)
    {
      //mErrorStr = buf;
      snprintf(mErrorStr, 256, "%s", buf);
    }
  }
  return *this;
}

apr_status& apr_status::operator=(const apr_status& rhs)
{
  this->mAprStatus = rhs.mAprStatus;
  snprintf(mErrorStr, 256, "%s", rhs.mErrorStr);
  return *this;
}
