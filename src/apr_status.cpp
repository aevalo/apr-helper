#include <exception>
#include "apr_status.hpp"



apr_status::apr_status(const apr_status& other)
{
  this->first = other.first;
  this->second = other.second;
}

apr_status::apr_status(apr_status_t status)
{
  first = status;
  if (first != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(first, buf, sizeof(buf));
    if (ret)
    {
      second = buf;
    }
  }
}

apr_status::~apr_status()
{
  // Nothing to do
}

apr_status& apr_status::operator=(apr_status_t status)
{
  first = status;
  second = "";
  if (first != APR_SUCCESS)
  {
    char buf[256];
    memset(buf, 0, 256);
    char* ret = apr_strerror(first, buf, sizeof(buf));
    if (ret)
    {
      second = buf;
    }
  }
  return *this;
}

apr_status& apr_status::operator=(const apr_status& rhs)
{
  this->first = rhs.first;
  this->second = rhs.second;
  return *this;
}
