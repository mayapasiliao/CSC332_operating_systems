#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int child1, child2, status;

  // ----CHILD1 CODE----
  child1 = fork(); // Creating 1st sibling
  if(child1 < 0) {
    perror("child1 fork");
    return -1;
  }

  if(child1 == 0) {
    int child1_pid = getpid();
    if(child1 < 0) {
      perror("child1 fork");
      return -1;
    }

    printf("I am child one, my pid is: %d\n", child1_pid);
  }

  else {
    // ----CHILD2 CODE----
    child2 = fork(); // Creating 2nd sibling
    if(child2 < 0) {
      perror("child2 fork");
      return -1;
    }

    if(child2 == 0) {
      int child2_pid = getpid();
      printf("I am child two, my pid is: %d\n", child2_pid);
    }
  }

  // Wait for both child processes to terminate
  int wait_return = wait(&status);
  while(wait_return > 0) {
    if(wait_return < 0) {
      perror("wait");
      return -1;
    }
    wait_return = wait(&status);
  }

  return 0;
}