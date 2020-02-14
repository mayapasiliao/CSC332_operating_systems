#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
  int fd;
  if(2 != argc)
  {
    printf("\n Usage : \n");
    return 1;
  }
  errno = 0;
  fd = open(argv[1], O_RDONLY);
  if(-1 == fd)
  {
    printf("\n open() failed with error [%s]\n",strerror(errno));
    return 1;
  }
  else
  {
    printf("\n Open() Successful\n");
    /* open() succeeded, now one can do read operations on the
    file opened since we opened it in read-only mode. Also once done
    with processing, the file needs to be closed.*/

    // you can also do a bitwise OR with ​ O_CREAT ​ if you want thesystem to create the file if it doesn’t exist already (e.g., ​ O_RDONLY​ | ​ O_CREAT ​ creates and open in
    // read mode). The system call returns the file descriptor of the new file (or a negative number if there is
    // an error, placing the code into ​ errno​ ).


  }
  int fd2 = close(fd);
  if(fd2 < 0)
  {
    printf("\n close() failed\n");
  }
  else 
  {
    printf("\n close() successful\n");
  }
  return 0;
}