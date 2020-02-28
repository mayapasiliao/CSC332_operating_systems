#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int a=10, b=25, fq=0, fr=0;
  fq=fork(); // fork a child - call it Process Q
  if(fq==0) { // Child successfully forked
    a=a+b; // print values of a, b, and process_id
    printf("1 a = %d, b = %d, pid = %d\n", a, b, getpid()); // 1
    fr=fork(); // fork another child - call it Process R
    printf("fr = %d\n", fr);
    if(fr!=0) {
      b=b+20; // print values of a, b, and process_id
      printf("2 a = %d, b = %d, pid = %d\n", a, b, getpid()); // 2
    }
    else {
      a=(a*b)+30; // print values of a, b, and process_id
      printf("3 a = %d, b = %d, pid = %d\n", a, b, getpid()); // 3
    }
  }
  else {
    b=a+b-5; // print values of a, b, and process_id
    printf("4 a = %d, b = %d, pid = %d\n", a, b, getpid()); // 4
  }
}
