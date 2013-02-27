#ifndef SHA1_CHECKSUM_HPP_INCLUDED
#define SHA1_CHECKSUM_HPP_INCLUDED

#include <string>
#include <apr_general.h>

apr_status_t sha1_file(const std::string& filename, std::string& checksum, bool binary, apr_pool_t* parentPool = NULL);

#endif // SHA1_CHECKSUM_HPP_INCLUDED
