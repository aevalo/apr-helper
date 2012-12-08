#ifndef APR_ARRAY_HPP_INCLUDED
#define APR_ARRAY_HPP_INCLUDED

#include <stdexcept>
#include <apr_tables.h>


template<class T>
T apr_array_get(const apr_array_header_t* arr, int index)
{
  if (arr == NULL)
    throw std::invalid_argument("Array pointer given for array_element was NULL.");
  if (index < 0 || index >= arr->nelts)
    throw std::out_of_range("Index given for array_element was out of range.");
  return APR_ARRAY_IDX(arr, index, T);
}


#endif // APR_ARRAY_HPP_INCLUDED
