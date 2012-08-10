
#ifndef AOL_SYS_FILE_UTIL_H_
#define AOL_SYS_FILE_UTIL_H_

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

namespace aolsys {

#ifndef S_IRWXUGO
#define S_IRWXUGO (S_IRWXU | S_IRWXG | S_IRWXO)
#endif

class cFileUtil {
  public:
    static bool mkdirs(char *szDirPath);

    static bool isDir(const char *szDirPath);

    static bool isSymLink(const char *szDirPath);
};

} // end of namespace aolsys

#endif

