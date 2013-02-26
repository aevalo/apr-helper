#ifndef SHA1_CHECKSUM_HPP_INCLUDED
#define SHA1_CHECKSUM_HPP_INCLUDED

#include <string>

int sha1_file(const std::string& filename, std::string& checksum, bool binary);

#endif // SHA1_CHECKSUM_HPP_INCLUDED
