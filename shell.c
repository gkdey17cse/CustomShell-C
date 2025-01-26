#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>  // For file control operations

char cmd[256];          // string holder for the command
char *argv[16];        // array of commands and args 

void getUserCommand(void);
void convertCMD(void);
void handleHelp(void);
void handleCD(void);
int handleOutputRedirection(void);
int handleInputRedirection(void);  // Function for input redirection

int main(void) {
    // pid_t ppid = getppid();
    // pid_t pid = getpid();
    // printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
    while (1) {
        getUserCommand();

        if (strcmp("", cmd) == 0) {
            continue;   // overlook blank command
        }
        if (strcmp("exit", cmd) == 0 || strcmp("clear", cmd) == 0) { // Handle 'exit' here
            printf("Terminating Shell!....\n");
            break;
        }

        if (strcmp("help", cmd) == 0) {
            handleHelp();  // Handle 'help' command here
            continue;
        }

        convertCMD();

        if (strcmp("cd", cmd) == 0) {
            handleCD();  // Handle 'cd' command here
            continue;
        }

        int pidStat = fork();
        if (pidStat < 0) {
            perror("Fork failed!....\n");
            exit(1);
        }       

        if (pidStat == 0) {  // Child process
            handleInputRedirection();  // Handle input redirection
            handleOutputRedirection();  // Redirect output in the child
            // ppid = getppid();
            // pid = getpid();
            // printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
            sleep(300);

            execvp(argv[0], argv);  
            printf("Successful");
            perror("execvp failed!.....\n");  
            exit(1);
        } else {
            // ppid = getppid();
            // pid = getpid();
            // printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
            wait(NULL);  // Parent process waits for child to finish
        }
    }

    return 0;
}

void handleHelp(void) {
    char *args[] = {"man", "bash", NULL};  // "man bash" will do the job of help command 
    int pidStat = fork();
    if (pidStat == 0) {
        execvp("man", args);
        perror("execvp failed");
        exit(1);
    } else if (pidStat > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
        exit(1);
    }
}

void handleCD(void) {
    char *dir = argv[1];
    if (dir == NULL) {
        dir = getenv("HOME");
        if (dir == NULL) {
            perror("cd: HOME not set");
            return;
        }
    }

    if (chdir(dir) == -1) {
        perror("cd failed");
    }
}

int handleOutputRedirection(void) {
    int i = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], ">") == 0) {
            argv[i] = NULL;  // Remove '>' from arguments

            char *filename = argv[i + 1];  // Get filename
            if (filename == NULL) {
                fprintf(stderr, "Error: No file specified for redirection\n");
                return -1;
            }

            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);  
            if (fd == -1) {
                perror("Error opening file");
                return -1;
            }

            if (dup2(fd, STDOUT_FILENO) == -1) {  
                perror("Error redirecting output");
                close(fd);
                return -1;
            }
            close(fd);
            return 0;
        }
        i++;
    }
    return 0;
}

int handleInputRedirection(void) {
    int i = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], "<") == 0) {  // Check for input redirection
            argv[i] = NULL;  // Remove '<' from arguments

            char *filename = argv[i + 1];  // Get filename
            if (filename == NULL) {
                fprintf(stderr, "Error: No file specified for input redirection\n");
                return -1;
            }

            int fd = open(filename, O_RDONLY);  // Open the file for reading
            if (fd == -1) {
                perror("Error opening file");
                return -1;
            }

            if (dup2(fd, STDIN_FILENO) == -1) {  // Redirect input
                perror("Error redirecting input");
                close(fd);
                return -1;
            }
            close(fd);
            return 0;
        }
        i++;
    }
    return 0;
}

void convertCMD(void) {
    char *command = strtok(cmd, " ");
    if (command != NULL) {    // This code assums that all executable files are present in the subdirectory named 'ExecutableFiles' where the shell.c belongs to
        if (strcmp("factorial", command) == 0 || strcmp("mul", command) == 0 || strcmp("add", command) == 0) {
            static char completeCommand[256];  
            snprintf(completeCommand, sizeof(completeCommand), "./ExecutableFiles/%s", command);
            argv[0] = completeCommand;
        } else {
            argv[0] = command;
        }

        char *token;
        int i = 1;
        while ((token = strtok(NULL, " ")) != NULL && i < 16) {
            argv[i] = token;
            i++;
        }
        argv[i] = NULL;
    }
}

void getUserCommand(void) {
    printf("MTech/2ndSem/GRS/Assignment/Assignment1$ ");
    fgets(cmd, 256, stdin);
    if ((strlen(cmd) > 0) && (cmd[strlen(cmd) - 1] == '\n')) {
        cmd[strlen(cmd) - 1] = '\0';  // Remove newline
    }
}
