#include <stdio.h>
#include <sys/wait.h> // For wait()
#include <unistd.h> // For fork() and getpid()

int main(int argc, char *argv[]) {
  int child = fork();

  if (child == 0) {
    char* args[]={"ls", "-l", "-a", NULL};
    printf("child PID = %d\n", getpid());
    execvp("/bin/ls", "ls", "-l", "-a", &argv[0]);
  }

  wait(NULL);

  return 0;
}
