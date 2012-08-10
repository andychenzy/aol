
#include "fileUtil.h"

namespace aolsys {

  bool cFileUtil::mkdirs(char *szDirPath)
  {
    struct stat stats;

    if (lstat(szDirPath, &stats) == 0 && S_ISDIR(stats.st_mode))
      return true;

    mode_t umask_value = umask(0);
    umask(umask_value);
    mode_t mode = (S_IRWXUGO & (~umask_value)) | S_IWUSR | S_IXUSR;

    char *slash = szDirPath;
    // remove prefix '//'
    while (*slash == '/')
      slash++;

    while (1) {
      slash = strchr(slash, '/');
      if (slash == NULL)
        break;

      *slash = '\0';
      int ret = mkdir(szDirPath, mode);
      *slash++ = '/';
      if (ret != 0 && errno != EEXIST)
        return false;

      while (*slash == '/')
        slash++;
    }

    if (mkdir(szDirPath, mode))
      return false;
  }

  bool cFileUtil::isDir(const char *szDirPath)
  {
    struct stat stats;

    if (lstat(szDirPath, &stats) == 0 && S_ISDIR(stats.st_mode))
      return true;
  
    return false;
  }

  bool cFileUtil::isSymLink(const char *szDirPath)
  {
    struct stat stats;

    if (lstat(szDirPath, &stats) == 0 && S_ISLNK(stats.st_mode))
      return true;

    return false;
  }

}

