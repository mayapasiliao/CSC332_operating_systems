#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd;
  int sz;
  char buff[100];
  char* buf = malloc(10 * sizeof(char)); // buf changes size according to size of txt file

  // Open file
  fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    printf("open() failed\n");
    perror("open");
    return -1;
  }
  
  // Read text file then write to terminal
  sz = read(fd, buf, 10000); // I wish I could set the third parameter according to the size of the txt file being passed in but I don't know how to do it without a whole other fopen.
  if(sz < 0) {
    printf("read() failed");
    perror("read");
  }
  
  write(1, buf, sz);

  // Close file
  int fd2 = close(fd);
  if(fd2 < 0) {
    perror("close");
    printf("close() failed\n");
  }

  // Free allocated dynamically allocated memory
  free(buf);

  return 0;
}