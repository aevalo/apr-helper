#include <sstream>
#include "regex.hpp"


regex::regex(const std::string& pattern)
 : non_copyable(), mPattern(static_cast<pcre*>(NULL), static_cast<pcre_extra*>(NULL))
{
  const char *pcreErrorStr = NULL;
  int pcreErrorOffset = 0;
  
  // pcre_compile returns NULL on error, and sets pcreErrorOffset & pcreErrorStr
  mPattern.first = pcre_compile(pattern.c_str(), 0, &pcreErrorStr, &pcreErrorOffset, NULL);
  if (mPattern.first == NULL)
  {
    std::ostringstream oss;
    oss << "ERROR: Could not compile '" << pattern << "': " << pcreErrorStr << std::ends;
    throw pcre_exception(oss.str());
  }
  
  // Optimize the regex
  mPattern.second = pcre_study(mPattern.first, 0, &pcreErrorStr);
  if (pcreErrorStr != NULL)
  {
    std::ostringstream oss;
    oss << "ERROR: Could not study '" << pattern << "': " << pcreErrorStr << std::ends;
    throw pcre_exception(oss.str());
  }
}

regex::~regex()
{
    // Free up the EXTRA PCRE value (may be NULL at this point)
    if (mPattern.second != NULL)
    {
      pcre_free(mPattern.second);
    }
    // Free up the regular expression.
    pcre_free(mPattern.first);
}

bool regex::match(const std::string& str)
{
  bool ret = false;
  int pcreExecRet = pcre_exec(mPattern.first, mPattern.second,
                              str.c_str(), str.length(), 0, 0, NULL, 0);
  if (pcreExecRet < 0)
  {
    if (pcreExecRet == PCRE_ERROR_NOMATCH)
    {
      ret = false;
    }
    else
    {
      switch (pcreExecRet)
      {
        case PCRE_ERROR_NULL:
          throw pcre_exception(std::string("Something was null."));
          break;
        case PCRE_ERROR_BADOPTION:
          throw pcre_exception(std::string("A bad option was passed."));
          break;
        case PCRE_ERROR_BADMAGIC:
          throw pcre_exception(std::string("Magic number bad (compiled re corrupt?)."));
          break;
        case PCRE_ERROR_UNKNOWN_NODE:
          throw pcre_exception(std::string("Something kooky in the compiled regex."));
          break;
        case PCRE_ERROR_NOMEMORY:
          throw pcre_exception(std::string("Ran out of memory."));
          break;
        default:
          throw pcre_exception(std::string("Unknown error."));
          break;
      }
    }
  }
  else
  {
    ret = true;
  }
  return ret;
}

std::vector<std::string> regex::match_sub(const std::string& str)
{
  int pcreExecRet;
  int subStrVec[30];

  std::vector<std::string> matches;
  
  // Try to find the regex in aLineToMatch, and report results.
  pcreExecRet = pcre_exec(mPattern.first, mPattern.second,
                          str.c_str(), str.length(), 0, 0,
                          subStrVec, 30);
  
  // Report what happened in the pcre_exec call..
  if (pcreExecRet < 0)
  {
    if (pcreExecRet == PCRE_ERROR_NOMATCH)
    {
      return matches;
    }
    else
    {
      switch (pcreExecRet)
      {
        case PCRE_ERROR_NULL:
          throw pcre_exception(std::string("Something was null."));
          break;
        case PCRE_ERROR_BADOPTION:
          throw pcre_exception(std::string("A bad option was passed."));
          break;
        case PCRE_ERROR_BADMAGIC:
          throw pcre_exception(std::string("Magic number bad (compiled re corrupt?)."));
          break;
        case PCRE_ERROR_UNKNOWN_NODE:
          throw pcre_exception(std::string("Something kooky in the compiled regex."));
          break;
        case PCRE_ERROR_NOMEMORY:
          throw pcre_exception(std::string("Ran out of memory."));
          break;
        default:
          throw pcre_exception(std::string("Unknown error."));
          break;
      }
    }
  }
  else
  {
    // At this point, rc contains the number of substring matches found...
    if (pcreExecRet == 0)
    {
      throw pcre_exception(std::string("But too many substrings were found to fit in subStrVec!"));
    }
    else
    {
      const char *psubStrMatchStr = NULL;
      for (int j = 0; j < pcreExecRet; j++)
      {
        pcre_get_substring(str.c_str(), subStrVec, pcreExecRet, j, &(psubStrMatchStr));
        matches.push_back(psubStrMatchStr);
      }
      // Free up the substring
      pcre_free_substring(psubStrMatchStr);
    }
  }
  
  return matches;
}

