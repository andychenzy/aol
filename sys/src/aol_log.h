
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#ifndef AOL_LOG_H_
#define AOL_LOG_H_

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <deque>
#include <string>
#include <pthread.h>

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN  1
#define LOG_LEVEL_INFO  2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL(level) LOG_LEVEL_##level, __FILE__, __LINE__, __func__
#define SYS_LOGGER aolsys::logger::_logger
#define log_write(level, ...) SYS_LOGGER.logMessage(LOG_LEVEL(level), __VA_ARGS__)


namespace aolsys {

using std::deque;
using std::string;

class logger {
  public:
    logger();
    ~logger();

    void rotateLog(const char *filename, const char *fmt = NULL);
    
    void logMessage(int level, const char *file, int line, const char *func, const char *fmt, ...);
    
    // @level DEBUG | WARN | INFO | ERROR
    void setLogLevel(const char *level);
    
    void setFileName(const char *filename, bool flag = false);
    
    void checkFile();
    
    void setCheck(int v)
    {
      _check = v;
    }

    void setMaxFileSize(int64_t maxFileSize = 0x40000000);

    void setMaxFileIndex(int maxFileIndex = 0x0f);

    static inline struct timeval getCurTv()
    {
      struct timeval tv;
      gettimeofday(&tv, NULL);
    
      return tv;
    }

  private:
    int _fd;
    char *_name;
    int _check;
    int64_t _maxFileSize;
    size_t _maxFileIndex;
    bool _flag;

  public:
    static logger _logger;
    int _level;

  private:
    std::deque<std::string> _fileList;
    static const char *const _errstr[];
    pthread_mutex_t _fileSizeMutex;
    pthread_mutex_t _fileIndexMutex;
};

} // end of namespace aolsys

#endif

