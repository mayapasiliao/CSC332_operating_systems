#include <stdio.h>
#include <fcntl.h> // for mode constants and create()

int main(int argc, char *argv[]) {
  int fd1 = creat("destination1.txt", S_IRWXU);
  if(fd1 < 0) {
    perror("creat1");
  }

  int fd2 = creat("destination2.txt", S_IRWXU);
  if(fd2 < 0) {
    perror("creat2");
  }

  return 0;
}