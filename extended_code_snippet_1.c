#include <stdio.h>
#include <unistd.h>
#include <errno.h>

// argc is filepath
int main (int argc, char* argv[])
{
  char* filepath = argv[1];
  int returnval;

  // Check file existence
  returnval = access (filepath, F_OK);
  if (returnval == 0)
    printf ("\n %s exists\n", filepath);
  else
  {
    if (errno == ENOENT)
    printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
    printf ("%s is not accessible\n", filepath);
    return 0;
  }

  // Checking read access and write access
  int check_read_access = access(filepath, R_OK);
  int check_write_access = access(filepath, W_OK);
  if (check_read_access != 0)
    printf ("There was a read error!");
  if (check_write_access != 0)
    printf ("There was a write error!");
  return 0;
}
