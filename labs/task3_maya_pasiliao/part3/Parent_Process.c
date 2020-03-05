// TODO?: Error checks

// Executes the Process_P1 and Process_P2 executable files.

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int child1 = fork();
  if(child1 == 0) {
    execl("Process_P1", NULL);
  }

  wait(NULL);

  int child2 = fork();
  if(child2 == 0) {
    execl("Process_P2", NULL);
  }

  wait(NULL);

  return 0;
}