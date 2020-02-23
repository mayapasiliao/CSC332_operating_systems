// TODO: Make sure checking for errors everywhere

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h> // FOR O_WRONLY

int main(int argc, char *argv[]) {
  int child1, child2, status;
  int fd[2]; // fd[0] is read end, fd[1] is write end

  if(pipe(fd) < 0) {
    perror("pipe");
    return -1;
  }

  child1 = fork(); // Creating 1st sibling

  // Check for errors
  if(child1 < 0) {
    perror("child1 fork");
    return -1;
  }
  // ----CHILD1 CODE----
  else if(child1 == 0) {
    close(fd[0]);
    dup2(1, fd[1]);
    execlp("/bin/ls", "ls", "-F", NULL);
    pid_t child1_ppid = getppid();
    // printf("child1_ppid = %d\n", child1_ppid);
  }
  // ----PARENT CODE----
  else {
    child2 = fork(); // Creating 2nd sibling

    // Check for errors
    if(child1 < 0) {
      perror("child2 fork");
      return -1;
    }
    // ----CHILD2 CODE----
    else if(child2 == 0) {
      close(fd[1]);
      dup2(fd[0], 0);
      execlp("/bin/nl", "nl", NULL);
      pid_t child2_ppid = getppid();
      // printf("child2_ppid = %d\n", child2_ppid);
    }
    else {
      // printf("parent_pid = %d\n", getpid());
    }
  }

  close(fd[0]);
  close(fd[1]);

  // Parent process waiting for both children to execute
  while(wait(&status) > 0) {
    if(wait(NULL) < 0) {
      perror("wait");
      return -1;
    }
    printf("Child complete");
  }

  return 0;
}
