#include <exception>
#include "apr_status.hpp"



apr_status::apr_status(const apr_status& other)
  : mAprStatus(other.mAprStatus), mErrorStr(other.mErrorStr)
{
}

apr_status::apr_status(apr_status_t status)
  : mAprStatus(status), mErrorStr("")
{
  if (mAprStatus != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(mAprStatus, buf, sizeof(buf));
    if (ret)
    {
      mErrorStr = buf;
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
  mErrorStr.clear();
  if (mAprStatus != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(mAprStatus, buf, sizeof(buf));
    if (ret)
    {
      mErrorStr = buf;
    }
  }
  return *this;
}

apr_status& apr_status::operator=(const apr_status& rhs)
{
  this->mAprStatus = rhs.mAprStatus;
  this->mErrorStr = rhs.mErrorStr;
  return *this;
}
