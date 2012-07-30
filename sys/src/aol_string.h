
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#ifndef AOL_STRING_H_
#define AOL_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
#include <vector>

namespace aolsys {

class stringUtil {
  public:
    static int strToInt(const char* str, int d);
    static int isInt(const char* str);
    static char* strToLower(char* str);
    static char* strToUpper(char* str);
    static std::string trim(std::string& s);
    static int hashCode(const char* str);
    static int getPrimeHash(const char* str);
    static void split(char* str, const char* delim, std::vector<char *>& list);
    static char* urlDecode(const char* src, char* dest);
    static unsigned int murmurHash(const void* key, int len);
    static std::string formatByteSize(double bytes);
};

} // end namespace aol

#endif

