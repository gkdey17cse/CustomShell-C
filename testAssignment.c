#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

int main(void) {
    char input[MAX_INPUT];
    char *args[4];  // The maximum expected number of arguments for "mul" command

    while (1) {
        // Display the shell prompt
        printf("$ ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit on EOF (Ctrl+D)
        }

        // Remove newline at the end
        input[strcspn(input, "\n")] = 0;

        // Simple command parsing: "mul 10 20"
        if (strncmp(input, "mul", 3) == 0) {
            // Tokenize the input into command arguments
            args[0] = "./mul";  // Command name
            char *token = strtok(input + 4, " ");  // Skip "mul" and get the arguments

            // Parse the two arguments
            int i = 1;
            while (token != NULL && i < 3) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL;  // Null-terminate the argument list

            // Fork a child process to execute the command
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(1);
            }

            if (pid == 0) {
                // In the child process, execute the "mul" program
                execvp(args[0], args);  // Execute the mul command
                // If exec fails
                perror("execvp failed");
                exit(1);
            } else {
                // In the parent process, wait for the child to finish
                wait(NULL);
            }
        } else {
            printf("Command not recognized.\n");
        }
    }

    return 0;
}
