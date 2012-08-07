
#ifndef AOL_SYS_H_
#define AOL_SYS_H_

#include <errno.h>


namespace aolsys {
  
  class Runnable;
  class cThread;
}

#if defined(__BCPLUSPLUS__) || defined(_MSC_VER)
#define T_INT64(n) n##i64
#elif defined(TNET_64)
#define T_INT64(n) n##L
#else
#define T_INT64(n) n##LL
#endif

inline int getSystemErrno()
{
  return errno;
}


#include "aol_thread.h"
#include "runnable.h"


#endif

