
#include <errno.h>
#include <cstdlib>

#include "aol_sys.h"
#include "aol_net.h"
#include "Exception.h"

namespace utilInternal
{
  
  bool interrupted()
  {
    return errno == EINTR;
  }

  int setBlock(int fd, bool block)
  {
    if (block) {
      int flags = fcntl(fd, F_GETFL);

      flags &= ~O_NONBLOCK;
      if (fcntl(fd, F_SETFL, flags) == SOCKET_ERROR) {
#ifdef _NO_EXCEPTION
        closeSocketNoThrow(fd);
        return errno;
#else
        closeSocketNoThrow(fd);
#endif
      }
    } else {
      int flags = fcntl(fd, F_GETFL);
      flags |= O_NONBLOCK;
      if (fcntl(fd, F_SETFL, flags) == SOCKET_ERROR) {
#ifndef _NO_EXCEPTION
        closeSocketNoThrow(fd);
        return errno;
#else
        closeSocketNoThrow(fd);
#endif
      }
    }

    return EXIT_SUCCESS;
  }

  int createPipe(int fds[2])
  {
    if (::pipe(fds) != 0) {
#ifdef _NO_EXCEPTION
      return -1;
#else
      utilInternal::SyscallException ex(__FILE__, __LINE__);
      ex._error = getSystemErrno();
      throw ex;
#endif
    }

#ifdef _NO_EXCEPTION
    const int ret = setBlock(fds[0], true);
    if (ret != 0)
      return ret;

    const int ret2 = setBlock(fds[0], true);
    if (ret2 != 0)
      return ret2;
#else
    try {
      setBlock(fds[0], true);
    } catch (...) {
      closeSocketNoThrow(fds[0]);
      throw;
    }

    try {
      setBlock(fds[1], true);
    } catch (...) {
      closeSocketNoThrow(fds[1]);
      throw;
    }
#endif

    return EXIT_SUCCESS;
  }

  int closeSocketNoThrow(int fd)
  {
    const int error = errno;

    close(fd);
    errno = error;
    return errno;
  }

}

