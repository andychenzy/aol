
#ifndef AOL_SYS_THREAD_H_
#define AOL_SYS_THREAD_H_

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "runnable.h"

namespace aolsys {

  class cThread {
    public:
      cThread()
      {
        tid = 0;
        pid = 0;
      }

      void start(Runnable *r, void *a)
      {
        runnable = r;
        args = a;
        pthread_create(&tid, NULL, cThread::hook, this);
      }

      void join()
      {
        if (tid) {
          pthread_join(tid, NULL);
          tid = 0;
          pid = 0;
        }
      }

      Runnable *getRunnable()
      {
        return runnable;
      }

      void *getArgs()
      {
        return args;
      }

      int getpid()
      {
        return pid;
      }

      static void *hook(void *arg)
      {
        cThread *thread = (cThread *)arg;
        thread->pid = gettid();

        if (thread->getRunnable()) {
          thread->getRunnable()->run(thread, thread->getArgs());
        }

        return (void *)NULL;
      }

    private:
      #ifdef _syscall0
      static _syscall0(pid_t, getpid)
      #else
      static pid_t gettid()
      {
        return syscall(__NR_gettid);
      }
      #endif

    private:
      pthread_t tid;
      int pid;
      Runnable *runnable;
      void *args;
  };

} // end of namespace aolsys

#endif

