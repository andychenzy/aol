
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#include <stdint.h>

#include "aol_string.h"

using namespace aolsys;

int main(int argc, char **argv)
{
  char s[100];

  for (int i = 0; i < 10; i++) {
    int len = sprintf(s, "test_%d", i);
    fprintf(stderr, "%s ==> %u\n", s, stringUtil::murmurHash(s, len));
  }

  uint64_t x = 1;
  for (int i = 0; i < 7; i++) {
    fprintf(stderr, "%ld ==> %s\n", x, stringUtil::formatByteSize(x).c_str());
    x *= 1022;
  }

  return 0;
}

