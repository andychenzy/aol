
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#ifndef AOL_CONFIG_H_
#define AOL_CONFIG_H_

#include <string>
#include <ext/hash_map>

#include "aol_string.h"
#include "aol_log.h"

namespace aolsys {

struct str_hash
{
  size_t operator()(const std::string& str) const {
    return __gnu_cxx::__stl_hash_string(str.c_str());
  }
};

struct char_equal
{
  bool operator()(const char* s1, const char* s2) const {
    return (strcmp(s1, s2) == 0);
  }
};

typedef __gnu_cxx::hash_map<std::string, std::string, str_hash> STR_STR_MAP;
typedef STR_STR_MAP::iterator STR_STR_MAP_ITER;
typedef __gnu_cxx::hash_map<std::string, STR_STR_MAP*, str_hash> STR_MAP;
typedef STR_MAP::iterator STR_MAP_ITER;

#define AOL_CONFIG aolsys::cConfig::getConfig()

class cConfig {
  public:
    cConfig();
    ~cConfig();

    int load(const char *filename);
    // get a match string
    const char *getString(const char *section, const std::string& key, const char *d = NULL);
    // get a match string list
    std::vector<const char *> getStringList(const char *section, const std::string& key);
    // get a match int
    int getInt(const char *section, const std::string& key, int d = 0);
    // get a match int list
    std::vector<int> getIntList(const char *section, const std::string& key);
    // get key by the section
    int getSectionKey(const char *section, std::vector<std::string> &keys);
    // get all section name
    int getSectionName(std::vector<std::string>& sections);

    std::string toString();

    static cConfig& getConfig();

  private:
    STR_MAP m_configMap;
    int parseValue(char *str, char *key, char *val);
    char *isSectionName(char *str);
};

} // end of namespace aolsys

#endif

