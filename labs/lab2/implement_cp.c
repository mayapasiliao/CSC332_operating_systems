// This program opens source.txt that is passed in as an argument and creates destination.txt to copy contents of source.txt into

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd_open, fd_close, fd_create, fd_read;
  size_t bytes;
  char buff[100];
  char* buf = malloc(10 * sizeof(char)); // buf changes size according to size of txt file
  char* filename = "destination.txt";

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

  // Read source.txt
  fd_read = read(fd_open, buf, 10000);
  if(fd_read < 0) {
    printf("read() failed");
    perror("read");
    return -1;
  }

  // Write contents of source.txt to destination.txt
  bytes = write(fd_create, buf, fd_read);
  if(bytes < 0) {
    perror("write");
    printf("write() failed\n");
    return -1;
  }

  // Close source.txt
  fd_close = close(fd_open);
  if(fd_close < 0) {
    perror("close");
    printf("close() failed\n");
    return -1;
  }

  free(buf); // Free dynamically allocated memory

  return 0;
}