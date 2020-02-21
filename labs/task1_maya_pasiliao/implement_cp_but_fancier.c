// This program opens source.txt that is passed in as an argument and creates destination.txt to modify and copy
// contents of source.txt into.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd_open, fd_close, fd_create, fd_read = 1;
  size_t bytes;
  char buf[101];
  char* filename = "destination.txt";
  char xyz[3] = {'X', 'Y', 'Z'};

  // Open source.txt
  fd_open = open(argv[1], O_RDONLY);
  if(fd_open < 0) {
    printf("open() failed\n");
    perror("open");
    return -1;
  }

  // Create destination.txt
  fd_create = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if(fd_create < 0) {
    perror("create");
    printf("create() failed\n");
    return -1;
  }

  int counter = 0;
  while(fd_read != 0) {
    // Read source.txt
    fd_read = read(fd_open, buf /* buffer to read data from */, 101 /* bytes to read before truncating data */);
    if(fd_read < 0) {
      printf("read() failed");
      perror("read");
      return -1;
    }

    printf("%d right after read\n", fd_read);

    for(int count = 0; count < 102; count++) {
      if(buf[count] == '1') {
        buf[count] = 'A';
      }
    }

    // Write contents of source.txt to destination.txt
    bytes = write(fd_create, buf, fd_read);
    if(bytes < 0) {
      perror("write");
      printf("write() failed\n");
      return -1;
    }

    bytes = write(fd_create, xyz, 3);

    printf("%d right before next call\n", fd_read);

    counter++;
  }

  printf("%d count\n", counter);

  // Close source.txt
  fd_close = close(fd_open);
  if(fd_close < 0) {
    perror("close");
    printf("close() failed\n");
    return -1;
  }

  return 0;
}
