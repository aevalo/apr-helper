#ifndef REGEX_HPP_INCLUDED
#define REGEX_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <pcre.h>
#include <non_copyable.hpp>



class pcre_exception : public std::runtime_error
{
  public:
    pcre_exception(const std::string& msg = "") : runtime_error(msg) {}
};


class regex : public non_copyable
{
  public:
    regex(const std::string& pattern);
    virtual ~regex();
    
    inline pcre* expression() { return mPattern.first; }
    inline pcre_extra* compiled_expression() { return mPattern.second; }
    
    bool match(const std::string& str);
    std::vector<std::string> match_sub(const std::string& str);
  
  private:
    std::pair<pcre*, pcre_extra*> mPattern;
};


#endif // REGEX_HPP_INCLUDED
