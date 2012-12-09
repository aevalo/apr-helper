#ifndef APR_HELPER_CONFIG_HPP_INCLUDED
#define APR_HELPER_CONFIG_HPP_INCLUDED

#ifdef APR_HELPER_SHARED_LIB
# ifdef APR_HELPER_EXPORTING
#   ifdef WIN32
#     define APR_HELPER_API    __declspec(dllexport)
#   else
#     define APR_HELPER_API
#   endif
#   define APR_HELPER_TEMPLATE
# else
#   ifdef WIN32
#     define APR_HELPER_API    __declspec(dllimport)
#   else
#     define APR_HELPER_API
#   endif
#   define APR_HELPER_TEMPLATE extern
# endif
#else
# define APR_HELPER_API
# define APR_HELPER_TEMPLATE
#endif

#endif // APR_HELPER_CONFIG_HPP_INCLUDED
