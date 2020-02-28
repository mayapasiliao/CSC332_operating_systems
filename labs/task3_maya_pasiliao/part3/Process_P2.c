#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  char buf1[101];
  char buf2[51];
  int fd_read = 1;
  int fd_open_source = open("source.txt", O_RDONLY);
  int fd_open1 = open("destination1.txt", O_RDONLY);
  int fd_open2 = open("destination2.txt", O_RDONLY);

  // IDEA: Have variable to flag whether reading from destination1 or destination2.
  while(fd_read != 0){
    fd_read = read(fd_open_source, buf1);
    write(fd_open1, buf1, 100);

    fd_read = read(fd_open_source, buf2);
    write(fd_open2, buf2, 50);
  }

  close(fd_open_source);
  close(fd_open1);
  close(fd_open2);

  return 0;
}