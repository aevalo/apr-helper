#ifndef APR_HELPER_CONFIG_HPP_INCLUDED
#define APR_HELPER_CONFIG_HPP_INCLUDED

#ifdef WIN32
# ifdef APR_HELPER_SHARED_LIB
#   ifdef APR_HELPER_EXPORTING
#     define APR_HELPER_API    __declspec(dllexport)
#   else
#     define APR_HELPER_API    __declspec(dllimport)
#   endif
# else
#   define APR_HELPER_API
# endif
#else
# define APR_HELPER_API
#endif

#endif // APR_HELPER_CONFIG_HPP_INCLUDED
