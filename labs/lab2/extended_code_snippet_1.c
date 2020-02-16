#include <stdio.h>
#include <unistd.h>
#include <errno.h>

// argc is filepath
int main(int argc, char* argv[]) {
  // argv[1] is pointer to first command line argument supplied, argv[0] holds name of program itself 
  char* filepath = argv[1];
  int returnval;

  // Check file existence
  returnval = access (filepath, F_OK);
  if(returnval == 0) {
    printf("\n %s exists\n", filepath);
  }
  else {
    if (errno == ENOENT)
    printf("%s does not exist\n", filepath);
    else if (errno == EACCES)
    printf("%s is not accessible\n", filepath);
    return 0;
  }

  // Checking read access and write access
  int check_read_access = access(filepath, R_OK);
  if(check_read_access == 0) {
    printf("You have read access\n");
  }
  else {
    printf("You don't have read access\n");
  }

  int check_write_access = access(filepath, W_OK);
  if(check_write_access == 0) {
    printf("You have write access\n");
  }
  else {
    printf("You don't have write access\n");
  }
  
  return 0;
}
