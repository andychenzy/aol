
#ifndef AOL_SYS_LOCK_H_
#define AOL_SYS_LOCK_H_

#include "ThreadException.h"

namespace utilInternal {

template <typename T>
class LockT
{
  public:
    LockT(const T& mutex) : _mutex(mutex)
    {
      _mutex.lock();
      _acquired = true;
    }
    
    ~LockT()
    {
      if (_acquired) {
        _mutex.unlock();
      }
    }

    void acquire() const
    {
      if (acquired) {
#ifdef _NO_EXCEPTION
        assert(!"ThreadLockedException");
#else
        throw ThreadLockedException(__FILE__, __LINE__);
#endif
      }
      _mutex.lock();
      _acquired = true;
    }

    bool tryAcquire() const
    {
      if (_acquired) {
#ifdef _NO_EXCEPTION
        assert(!"ThreadLockedException");
#else
        throw ThreadLockedException(__FILE__, __LINE__);
#endif
      }

      _acquired = _mutex.tryLock();
      return _acquired;
    }

    void release() const
    {
      if (!_acquired) {
#ifdef _NO_EXCEPTION
        assert("ThreadLockedException");
#else
        throw ThreadLockedException(__FILE__, __LINE__);
#endif
      }
        _mutex.unlock();
        _acquired = false;
    }

    bool acquired() const
    {
      return _acquired;
    }

  protected:
    LockT(const T& mutex, bool) : _mutex(mutex)
    {
      _acquired = _mutex.tryLock();
    }

  private:
    // non-copyable
    LockT(const LockT&);
    LockT operator=(const LockT&);

    const T& _mutex;
    mutable bool _acquired;
    friend class Cond;
};

template <typename T>
class TryLockT : public LockT<T>
{
  public:
    TryLockT(const T& mutex) : LockT<T>(mutex, true)
    {
    }
};

} // end of namespace utilInternal

#endif

