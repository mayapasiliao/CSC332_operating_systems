#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int fd;

  if(2 != argc) {
    printf('\n Usage : \n');
    return 1;
  }

  errno = 0;
  fd = open(argv[1], O_RDONLY|O_CREAT);
  if(fd < 0) {
    perror('open');
    return;
  }
  else {
    printf('\n Open() Successful\n');
  }

  int fd2 = close(fd);
  if(fd2 < 0) {
    printf('\n close() failed\n');
  }
  else  {
    printf('\n close() successful\n');
  }

  return 0;
}