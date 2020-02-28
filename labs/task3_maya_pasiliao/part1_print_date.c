#include <stdio.h>
#include <sys/wait.h> // For wait()
#include <unistd.h> // For fork() and getpid()

int main(int argc, char *argv[]) {
  int child = fork();

  if (child == 0) {
    printf("child PID = %d\n", getpid());
    execl("/bin/date", "date", NULL); // execl("location", "argument1", "argument2", ... , null pointer)
  }

  wait(NULL);

  return 0;
}
