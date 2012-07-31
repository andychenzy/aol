
#ifndef AOL_SYS_PROCESS_H_
#define AOL_SYS_PROCESS_H_

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "aol_log.h"

namespace aolsys {

  class cProcess {
    public:
      static int startDaemon(const char *szPidFile, const char *szLogFile);

      static int existPid(const char *szPidFile);

      static void writePidFile(const char *szPidFile);
  };

} // end of namespace aolsys

#endif

