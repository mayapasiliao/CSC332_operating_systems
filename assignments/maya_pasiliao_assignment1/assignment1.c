#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h> // FOR O_WRONLY

int main(int argc, char *argv[]) {
  int child1, child2, status;
  int fd[2]; // fd[0] is read end, fd[1] is write end

  // Check for errors
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
    int close_return1 = close(fd[0]); // Close read end
    int dup2_return1 = dup2(fd[1], 1);
    int execlp_return1 = execlp("ls", "ls", "-F", NULL);

    if(close_return1 == 0 || dup2_return1 == 0 || execlp_return1 == 0) {
      perror("error in child1");
      return -1;
    }
  }
  else {
    child2 = fork(); // Creating 2nd sibling

    // Check for errors
    if(child1 < 0) {
      perror("child2 fork");
      return -1;
    }
    // ----CHILD2 CODE----
    else if(child2 == 0) {
      int close_return2 = close(fd[1]); // Close write end
      int dup2_return2 = dup2(fd[0], 0);
      int execlp_return2 = execlp("nl", "nl", NULL);

      if(close_return2 == 0 || dup2_return2 == 0 || execlp_return2 == 0) {
        perror("error in child2");
        return -1;
      }
    }
    else {
      // ----PARENT CODE----
      // Check for errors
      if(close(fd[1]) < 0) {
        perror("close write end");
        return -1;
      }

      // Parent process waiting for both children to execute
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
  }
}
