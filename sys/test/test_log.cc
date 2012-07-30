
/*
 * Author:
 *    Andy chen <andychenzy@gmail.com>
 */

#include "aol_log.h"

using namespace aolsys;

int main(int argc, char **argv)
{
  log_write(INFO, "test info %s:%d\n", "info", 1);
  log_write(ERROR, "test error %s:%d\n", "error", 2);

  SYS_LOGGER.setFileName("./testlog.txt");

  for (int i = 0; i < 50; i++) {
    log_write(ERROR, "test string %s:%d", "test error", i);
    getchar();
  }

  return 0;
}

