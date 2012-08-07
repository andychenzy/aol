
#include "aol_process.h"

namespace aolsys {

  int cProcess::startDaemon(const char *szPidFile, const char *szLogFile)
  {
    if (getppid() == 1)
      return 0;

    int pid = fork();
    // error
    if (pid < 0)
      return -1;
    // parent
    if (pid > 0)
      return pid;

    // child
    writePidFile(szPidFile);

    int fd = open("/dev/null", 0);
    if (fd != -1) {
      dup2(fd, 0);
      close(fd);
    }

    SYS_LOGGER.setFileName(szLogFile);

    return pid;
  }

  // write pid file
  void cProcess::writePidFile(const char *szPidFile)
  {
    char str[64];

    int fd = open(szPidFile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
      return;

    if (lockf(fd, F_TLOCK, 0) < 0) {
      fprintf(stderr, "Cannot open pid file: %s\n", szPidFile);
      return;
    }

    sprintf(str, "%d\n", getpid());
    ssize_t len = strlen(str);
    ssize_t ret = write(fd, str, len);
    if (ret != len) {
      fprintf(stderr, "Cannot write pid file: %s\n", szPidFile);
      return;
    }
    close(fd);
  }

  int cProcess::existPid(const char *szPidFile)
  {
    char buf[64];
    char *p;
    int otherpid = 0;
    int fd;

    fd = open(szPidFile, O_RDONLY, 0);
    if (fd >= 0) {
      read(fd, buf, 64);
      close(fd);
      buf[63] = '\0';
      p = strchr(buf, '\n');
      if (p != NULL)
        *p = '\0';
      otherpid = atoi(buf);
    }

    if (otherpid > 0) {
      if (kill(otherpid, 0) != 0) {
        otherpid = 0;
      }
    }

    return otherpid;
  }

} // end of namespace aolsys

