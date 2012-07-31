
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#include "aol_config.h"

using namespace std;

namespace aolsys {

  static cConfig _config;

  cConfig::cConfig() { }

  cConfig::~cConfig()
  {
    for (STR_MAP_ITER iter = m_configMap.begin(); iter != m_configMap.end(); ++iter) {
      delete iter->second;
    }
  }

  cConfig& cConfig::getConfig()
  {
    return _config;
  }

  int cConfig::parseValue(char *str, char *key, char *val)
  {
    char *p, *p1, *name, *value;

    if (str == NULL)
      return -1;

    p = str;
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
      p++;

    p1 = p + strlen(p);
    while (p1 > p) {
      p1--;
      if (*p1 == ' ' || *p1 == '\t' || *p1 == '\r' || *p1 == '\n')
        continue;
      p1++;
      break;
    }
    *p1 = '\0';

    if (*p == '#' || *p == '\0')
      return -1;

    p1 = strchr(str, '=');
    if (p1 == NULL)
      return -2;
    name = p;
    value = p1 + 1;
    while (*(p1 -1) == ' ')
      p1--;
    *p1 = '\0';

    while (*value == ' ')
      value++;
    p = strchr(value, '#');
    if (p == NULL)
      p = value + strlen(value);
    while (*(p - 1) == ' ')
      p--;
    *p = '\0';
    if (name[0] == '\0')
      return -2;

    strcpy(key, name);
    strcpy(val, value);

    return 0;
  }

  char *cConfig::isSectionName(char *str)
  {
    if (str == NULL || strlen(str) < 3 || *str != '[')
      return NULL;

    char *p = str + strlen(str);
    while (*(p-1) == ' ' || *(p-1) == '\t' || *(p-1) == '\r' || *(p-1) == '\n')
      p--;
    if (*(p-1) != ']')
      return NULL;
    *(p-1) = '\0';

    p = str + 1;
    while (*p) {
      if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || (*p == '_')) {
      } else {
        return NULL;
      }
      p++;
    }

    return (str + 1);
  }

  int cConfig::load(const char *filename)
  {
    FILE *fp;
    char key[128], value[4096], data[4096];
    int ret, line = 0;

    if ((fp = fopen(filename, "rb")) == NULL) {
      log_write(ERROR, "Cannot open configure file: %s\n", filename);
      return EXIT_FAILURE;
    }

    STR_STR_MAP *m = NULL;
    while (fgets(data, 4096, fp)) {
      line++;
      char *sName = isSectionName(data);
      if (sName != NULL) {
        STR_MAP_ITER iter = m_configMap.find(sName);
        if (iter == m_configMap.end()) {
          m = new STR_STR_MAP();
          m_configMap.insert(STR_MAP::value_type(sName, m));
        } else {
          m = iter->second;
        }
        continue;
      }

      ret = parseValue(data, key, value);
      if (ret == -2) {
        log_write(ERROR, "Parse error, line: %d, %s\n", line, data);
        fclose(fp);
        return EXIT_FAILURE;
      }

      if (ret < 0)
        continue;
      if (m == NULL) {
        log_write(ERROR, "Not setting section for,  Line :%s, %s\n", line, data);
        fclose(fp);
        return EXIT_FAILURE;
      }

      STR_STR_MAP_ITER iter2 = m->find(key);
      if (iter2 != m->end()) {
        iter2->second += '\0';
        iter2->second += value;
      } else {
        m->insert(STR_STR_MAP::value_type(key, value));
      }
    }
    fclose(fp);
    return EXIT_SUCCESS;
  }

  const char *cConfig::getString(const char *section, const std::string& key, const char *d)
  {
    STR_MAP_ITER iter = m_configMap.find(section);
    if (iter == m_configMap.end())
      return d;

    STR_STR_MAP_ITER iter2 = iter->second->find(key);
    if (iter2 == iter->second->end()) {
      return d;
    }

    return iter2->second.c_str();
  }

  vector<const char *> cConfig::getStringList(const char *section, const string& key)
  {
    vector<const char*> ret;
    
    STR_MAP_ITER iter = m_configMap.find(section);
    if (iter == m_configMap.end()) {
      return ret;
    }

    STR_STR_MAP_ITER iter2 = iter->second->find(key);
    if (iter2 == iter->second->end()) {
      return ret;
    }

    const char *data = iter2->second.data();
    const char *p = data;
    for (int i = 0; i < (int)iter2->second.size(); i++) {
      if (data[i] == '\0') {
        ret.push_back(p);
        p = data + i + 1;
      }
    }
    ret.push_back(p);

    return ret;
  }

  int cConfig::getInt(const char *section, const string& key, int d)
  {
    const char *str = getString(section, key);

    return stringUtil::strToInt(str, d);
  }

  vector<int> cConfig::getIntList(const char *section, const string& key)
  {
    vector<int> ret;
    
    STR_MAP_ITER iter = m_configMap.find(section);
    if (iter == m_configMap.end()) {
      return ret;
    }
    
    STR_STR_MAP_ITER iter2 = iter->second->find(key);
    if (iter2 == iter->second->end()) {
      return ret;
    }

    const char *data = iter2->second.data();
    const char *p = data;
    for (int i = 0; i < (int)iter2->second.size(); i++) {
      if (data[i] == '\0') {
        ret.push_back(atoi(p));
        p = data + i + 1;
      }
    }

    ret.push_back(atoi(p));
    return ret;
  }

  int cConfig::getSectionKey(const char *section, vector<string> &keys)
  {
    STR_MAP_ITER iter = m_configMap.find(section);
    if (iter == m_configMap.end()) {
      return 0;
    }

    STR_STR_MAP_ITER iter2;
    for (iter2 = iter->second->begin(); iter2 != iter->second->end(); ++iter2) {
      keys.push_back(iter2->first);
    }

    return (int)keys.size();
  }

  int cConfig::getSectionName(vector<string>& sections)
  {
    STR_MAP_ITER iter;

    for (iter = m_configMap.begin(); iter != m_configMap.end(); ++iter) {
      sections.push_back(iter->first);
    }

    return (int)sections.size();
  }

  string cConfig::toString()
  {
    string result;
    STR_MAP_ITER iter1;
    STR_STR_MAP_ITER iter2;

    for (iter1 = m_configMap.begin(); iter1 != m_configMap.end(); ++iter1) {
      result += "[" + iter1->first + "]\n";
      for (iter2 = iter1->second->begin(); iter2 != iter1->second->end(); ++iter2) {
        string s = iter2->second.c_str();
        result += "   " + iter2->first + " = " + s + "\n";
        if (s.size() != iter2->second.size()) {
          char *data = (char *)iter2->second.data();
          char *p = NULL;
          for (int i = 0; i < iter2->second.size(); i++) {
            if (data[1] != '\0') 
              continue;
            if (p)
              result += "    " + iter2->first + " = " + p + "\n";
            p = data + i + 1;
          }
          if (p)
            result += "    " + iter2->first + " = " + p + "\n";
        }
      }
    }
    result += '\n';
   
    return result;
  }

} // end of namespace aolsys

