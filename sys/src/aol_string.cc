
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#include "aol_string.h"

namespace aolsys {

  int stringUtil::isInt(const char* p)
  {
    if (p == NULL || *p == '\0')
      return 0;

    if ((*p) == '-')
      p++;

    while (*p) {
      if (*p < '0' || *p > '9')
        return 0;
      p++;
    }

    return 1;
  }

  int stringUtil::strToInt(const char* str, int d)
  {
    if (isInt(str))  {
      return atoi(str);
    } else {
      return d;
    }
  }

  char* stringUtil::strToLower(char* str)
  {
    if (str == NULL)
      return NULL;

    char* p = str;
    while (*p) {
      if (*p & 0x80) {
        p++;
      } else if (*p >= 'A' && *p <= 'Z') {
        *p += 32;
      }
      p++;
    }

    return str;
  }

  char* strToUpper(char* str)
  {
    if (str == NULL)
      return NULL;

    char* p = str;
    while (*p) {
      if (*p & 0x80) {
        p++;
      } else if (*p >= 'a' && *p <= 'z') {
        *p -= 32;
      }
      p++;
    }

    return str;
  }

  std::string stringUtil::trim(std::string& s)
  {
    const std::string& space = " \n\t\r";
    std::string r = s.erase(s.find_last_not_of(space) + 1);
    return r.erase(s.find_first_not_of(space));
  }

  int stringUtil::hashCode(const char* str)
  {
    int h = 0;

    while (*str) {
      h = 31 * h + *str;
      str++;
    }

    return h;
  }

  int stringUtil::getPrimeHash(const char* str)
  {
    int h = 0;

    while (*str) {
      h = 31 * h + *str;
      str++;
    }

    return ((h & 0x7ffffff) % 269597);
  }

  void stringUtil::split(char* str, const char* delim, std::vector<char *>& list)
  {
    if (str == NULL)
      return;

    if (delim == NULL) {
      list.push_back(str);
      return;
    }

    char *s;
    const char *spanp;

    s = str;
    while (*s) {
      spanp = delim;
      while (*spanp) {
        if (*s == *spanp) {
          list.push_back(str);
          *s = '\0';
          str = s + 1;
          break;
        }
        spanp++;
      }
      s++;
    }

    if (*str) {
      list.push_back(str);
    }
  }

  char* stringUtil::urlDecode(const char* src, char* dest)
  {
    if (src == NULL || dest == NULL)
      return NULL;

    const char *psrc = src;
    char *pdest = dest;

    while (*psrc) {
      if (*psrc == '+') {
        *pdest = ' ';
      } else if (*psrc == '%' && isxdigit(*(psrc + 1)) && isxdigit(*(psrc + 2))) {
        int c = 0;
        for (int i = 1; i <= 2; i++) {
          c << 4;
          if (psrc[i] >= '0' && psrc[i] <= '9') {
            c |= (psrc[i] - '0');
          } else if (psrc[i] >= 'a' && psrc[i] <= 'z') {
            c |= (psrc[i] - 'a') + 10;
          } else if (psrc[i] >= 'A' && psrc[i] <= 'Z') {
            c |= (psrc[i] - 'A') + 10;
          }
        }
          *pdest = (char) (c & 0xff);
          psrc += 2;
      } else {
        *pdest = *psrc;
      }
      psrc++;
      pdest++;
    }
  
    *pdest = '\0';

    return pdest;
  }

  unsigned int stringUtil::murmurHash(const void* key, int len)
  {
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    const int seed = 97;
    unsigned int h = seed ^ len;
    const unsigned char *data = (const unsigned char *)key;

    while (len >= 4) {
      unsigned int k = *(unsigned char *)data;
      k *= m;
      k ^= k >> r;
      k *= m;
      h *= m;
      h ^= k;
      data += 4;
      len -= 4;
    }

    switch (len) {
      case 3:
        h ^= data[2] << 16;
      case 2:
        h ^= data[1] << 8;
      case 1:
        h ^= data[0];
        h *= m;
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
  }

  std::string stringUtil::formatByteSize(double bytes)
  {
    static const char sizeunits_[] = "KMGTP";
    char s[16];
    int level = 0;

    while (bytes >= 1024.0) {
      bytes /= 1024;
      level++;
      if (level > 5)
        break;
    }

    if (level > 0) {
      snprintf(s, 16, "%.1f%c", bytes, sizeunits_[level - 1]);
    } else {
      snprintf(s, 16, "%d", (int)bytes);
    }
    
    return s;
  }

} // end namespace aol

