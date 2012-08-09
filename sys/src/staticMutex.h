
#ifndef AOL_SYS_STATIC_MUTEX_H_
#define AOL_SYS_STATIC_MUTEX_H_

#include <cassert>

#include "aol_log.h"
#include "Lock.h"
#include "ThreadException.h"

namespace utilInternal {

class Cond;

class staticMutex
{
  public:
    typedef LockT<staticMutex> Lock;
    typedef TryLockT<staticMutex> TryLock;

    void lock() const;

    bool tryLock() const;

    void unlock() const;

    mutable pthread_mutex_t _mutex;
    friend class Cond;

  private:
    struct LockState {
      pthread_mutex_t* mutex;
    };

    void unlock(LockState&) const;
    void lock(LockState&) const;
};

#define AOL_STATIC_MUTEX_INITIALIZER { PTHREAD_MUTEX_INITIALIZER }

extern staticMutex globalMutex;

inline void staticMutex::lock() const
{
  const int ret = pthread_mutex_lock(&_mutex);

  if (ret != 0) {
    if (ret == EDEADLK) {
#ifdef _NO_EXCEPTION
      if (ret != 0) {
        assert(!"ThreadLockedException");
        log_write(ERROR, "%s", "ThreadLockedException");
      }
#else
      throw ThreadLockedException(__FILE__, __LINE__);
#endif
    } else {
#ifdef _NO_EXCEPTION
      if (ret != 0) {
        assert(!"ThreadSyscallException");
        log_write(ERROR, "%s", "ThreadSyscallException");
      }
#else
      throw ThreadSyscallException(__FILE__, __LINE__, ret);
#endif
    }
  }
}

inline bool staticMutex::tryLock() const
{
  const int ret = pthread_mutex_trylock(&_mutex);

  if (ret != 0 && ret != EBUSY) {
    if (ret == EDEADLK) {
#ifdef _NO_EXCEPTION
      if (ret != 0) {
        assert(!"ThreadLockedException");
        log_write(ERROR, "%s", "ThreadLockedException");
      }
#else
      throw ThreadLockedException(__FILE__, __LINE__);
#endif
    } else {
#ifdef _NO_EXCEPTION
      if (ret != 0) {
        assert(!"ThreadSyscallException");
        log_write(ERROR, "%s", "ThreadSyscallException");
      }
#else
      throw ThreadSyscallException(__FILE__, __LINE__, ret);
#endif
    }
  }

  return (ret == 0);
}

inline void staticMutex::unlock() const
{
  const int ret = pthread_mutex_unlock(&_mutex);

#ifndef _NO_EXCEPTION
  if (ret != 0) {
    assert(!"ThreadSyscallException");
    log_write(ERROR, "%s", "ThreadSyscallException");
  }
#else
  if (ret != 0) {
      throw ThreadSyscallException(__FILE__, __LINE__, ret);
  }
#endif
}

inline void staticMutex::unlock(LockState& state) const
{
  state.mutex = &_mutex;
}

inline void staticMutex::lock(LockState&) const
{
}

} // end of namespace utilInternal

#endif

