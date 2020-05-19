/*
    This program expects commands with one or no arguments..
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/wait.h> // For wait()
#include <unistd.h> // For fork() and getpid()
#include <stdlib.h>
#include <string.h>

void shell_loop();
char* read_line(void);
int execute(char *line);

int main(int argc, char *argv[]) {
    shell_loop();
    return 0;
}

void shell_loop() {
    char* line;
    char* tokens;
    int exit;

    do {
        printf("~ ");

        line = read_line();
        if(strncmp(line, "quit\n", 4) == 0) {
            exit = 1;
        }
        execute(line);

    } while(exit == 0);

    free(line);
}

char* read_line(void) {
    char* buf = NULL;

    size_t bufsize = 100;
    getline(&buf, &bufsize, stdin);

    return buf;
}

int execute(char *line) {
    char *token;
    char* tokens[3];

    token = strtok(line, " ");
    tokens[0] = token;
    int count = 1;
    while(token != NULL) {
        token = strtok(NULL, " ");
        tokens[count] = token;

        count++;
    }
    printf("count = %d\n", count);

    // Executing commands with arguments
    int pid = fork();

    if (pid == 0) {
        if(count == 3) {
            printf("tokens[1] = %s\n", tokens[1]);
            execlp(tokens[0], tokens[0], tokens[1], NULL);
        }
        else if (count == 2) {
            printf("tokens[0] = %s\n", tokens[0]);
            execlp(tokens[0], tokens[0], NULL);
        }
    }
    else {
        wait(NULL);
    }

    count = 0;

    return 0;
}