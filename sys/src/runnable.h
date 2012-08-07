
#ifndef AOL_SYS_RUNNABLE_H_
#define AOL_SYS_RUNNABLE_H_

namespace aolsys {
  
  class Runnable {
    public:
      virtual ~Runnable() { }

      virtual void run(cThread *thread, void *arg) = 0;
  };

} // end of namespace aolsys

#endif

