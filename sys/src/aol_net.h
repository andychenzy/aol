
#ifndef AOL_SYS_NET_H_
#define AOL_SYS_NET_H_

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#ifndef SHUT_RD
#define SHUT_RD 0
#endif

#ifndef SHUT_WR
#define SHUT_WR 1
#endif

#ifndef SHUT_RDWR
#define SHUT_RDWR 2
#endif

namespace utilInternal
{
  bool interrupted();

  int setBlock(int fd, bool block);

  int createPipe(int fds[2]);

  int closeSocketNoThrow(int fd);

} // end of namespace utilInternal

#endif

