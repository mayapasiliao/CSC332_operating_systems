#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf1[100];
  char buf2[50];
  int fd_read = 1;
  int fd_open_source = open("source.txt", O_RDONLY);
  int fd_open1 = open("destination1.txt", O_WRONLY);
  int fd_open2 = open("destination2.txt", O_WRONLY);

  while(fd_read != 0) { // TODO: Fix so that read is processing exactly the right number fo chars
    fd_read = read(fd_open_source, buf1, 100);
    for(int i = 0; i < 100; i++) {
    }
    write(fd_open1, buf1, fd_read);

    fd_read = read(fd_open_source, buf2, 50);
    write(fd_open2, buf2, fd_read);
  }

  close(fd_open_source);
  close(fd_open1);
  close(fd_open2);

  return 0;
}