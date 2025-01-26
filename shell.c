#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include<sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> // For file control operations

char cmd[256];  // string holder for the commend
char *argv[16]; // array of commends and args

void getUsorCommend(void);      // This Function will take Usor commend
void convertCMD(void);          // This Function will preprocess Usor commend
void helpHandeler(void);        // This Function will handel HELP commend
void cdHandeler(void);          // This Function will handel CD commend
int outputRedirectHandel(void); // This Function will redirect output
int intputRedirectHandel(void); // This Function will redirect input

int main(void)
{
    // pid_t ppid = getppid();
    // pid_t pid = getpid();
    // printf("The Curent Process ID is : %d and Curent Parent Process ID is : %d\n",pid,ppid);      // Will SHow Parent and Curent Process's ID
    while (1)
    {
        getUsorCommend();

        if (strcmp("", cmd) == 0)
        {
            
            continue; // overlook blank commend
        }
        if (strcmp("exit", cmd) == 0 || strcmp("clear", cmd) == 0)
        { // Handel 'exit' & 'clear' here
            printf("Terminating Shell!....\n");
            break;
        }

        if (strcmp("help", cmd) == 0)
        {
            helpHandeler(); // Handel 'help' commend here
            continue;
        }

        convertCMD();

        if (strcmp("cd", cmd) == 0)
        {
            cdHandeler(); // Handel 'cd' commend here
            continue;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Fork failed!....\n");
            exit(1);
        }

        if (pid == 0) // Child process
        {
            outputRedirectHandel(); // Handel output redirection
            intputRedirectHandel(); // Handel input redirection
            // ppid = getppid();
            // pid = getpid();
            // printf("The Curent Process ID is : %d and Curent Parent Process ID is : %d\n",pid,ppid);
            // sleep(300);

            execvp(argv[0], argv);
            perror("Execvp syscall failed!.....\n");
            exit(1);
        }
        else
        {
            // ppid = getppid();
            // pid = getpid();
            // printf("The Curent Process ID is : %d and Curent Parent Process ID is : %d\n",pid,ppid);
            wait(NULL); // Parent process waits for child to finish
        }
    }

    return 0;
}

void cdHandeler(void) // Body for CD commend hanlder
{
    char *dir = argv[1];  // Will take directory path from the argument list
    if (dir == NULL)    // In case of no directory specified will fectch the HOME directory using getenv ()
    {
        dir = getenv("HOME");
        if (dir == NULL)
        {
            perror("HOME is not set!....\n");
            return;
        }
    }

    if (chdir(dir) == -1)   // In case of failore
    {
        perror("CD commend failed!.....\n");
    }
}

void helpHandeler(void) // Body for HELP commend hanlder
{
    char *args[] = {"man", "bash", NULL}; // "man bash" will do the job of help commend
    pid_t pid = fork();
    if (pid == 0)    // create child
    {
        execvp("man", args);
        perror("execvp commend failed!...\n");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        perror("Fork failed!.........\n");
        exit(1);
    }
}

int outputRedirectHandel(void) // Body for OUPUT redirect hanlder : will redirect output to the desired file
{
    int i = 0;
    while (argv[i] != NULL)
    {
        if (strcmp(argv[i], ">") == 0) // will retrun true if found output redirectionoperator ('>')
        {
            argv[i] = NULL; // will remove '>' from arguments

            char *filename = argv[i + 1]; // will get filename
            if (filename == NULL)         // will check whether a filename is given or not
            {
                fprintf(stderr, "Error: No file specified for redirection!.......... \n");
                return -1;
            }

            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // will open file in Write Only Mode , If not exits then create the file & Truncate the preiously written data
            if (fd == -1)                                                // If can't open the file
            {
                perror("Error opening file!..........\n");
                return -1;
            }

            if (dup2(fd, STDOUT_FILENO) == -1) // if duplicate the file descriptar to the standard output fail
            {
                perror("Error redirecting output!........\n");
                close(fd);
                return -1;
            }
            close(fd);
            return 0;
        }
        else
        {
            // printf("Ignore Tokens")      // Testing Code
        }
        i++;
    }
    return 0;
}

int intputRedirectHandel(void) // Body for INPUT redirect hanlder : will redirect input from the desired file
{
    int i = 0;
    while (argv[i] != NULL) // will check whether any cmnd line args paassed or not
    {
        if (strcmp(argv[i], "<") == 0)
        {                   // will Check for input redirection
            argv[i] = NULL; // will remove '<' from arguments

            char *filename = argv[i + 1]; // will get filename
            if (filename == NULL)
            {
                fprintf(stderr, "Error: No file specified for input redirection\n");
                return -1;
            }

            int fd = open(filename, O_RDONLY); // will open the file for reading only mood
            if (fd == -1)
            {
                perror("Error opening file");
                return -1;
            }

            if (dup2(fd, STDIN_FILENO) == -1) // If redirection fail
            {                                 // Redirect input
                perror("Error redirecting input");
                close(fd);
                return -1;
            }
            close(fd);
            return 0;
        }
        else
        {
            // printf("Ignore Tokens")      // Testing Code
        }
        i++;
    }
    return 0;
}

void convertCMD(void) // Body for commend conversion function
{
    char *commend = strtok(cmd, " "); // generate tokens based on space
    const char *customCommend[] = {"factorial", "mul", "add" , "strrev"}; // User-defined commands 

    int isCustomCommend = 0;    

    if (commend != NULL) {
        // Check if the commend is in the customCommend array
        for (int j = 0; j < 4; j++) {
            if (strcmp(customCommend[j], commend) == 0) {
                isCustomCommend = 1; // if commend matches with a custom commend
                break;
            }
        }
    }
    {
        // This code assums that all executable files are present in the subdirectory named 'ExecutableFiles' where the shell.c belongs to
        if (isCustomCommend == 1) // constrain check with our existed commend
        {
            static char completecommend[256];
            snprintf(completecommend, sizeof(completecommend), "./ExecutableFiles/%s", commend); // will geneate full path upto the executable files
            argv[0] = completecommend;
        }
        else
        {
            argv[0] = commend; // In case of Built in COmmneds
        }

        char *token;
        int i = 1;
        while ((token = strtok(NULL, " ")) != NULL && i < 16) // will parse argument from the rest of the code
        {
            argv[i] = token;
            i++;
        }
        argv[i] = NULL;
    }
}

void getUsorCommend(void)   // Body of User input function
{
    printf("GRS/Assignment/Assignment1$ ");     // SHell view
    fgets(cmd, 256, stdin);        
    if ((strlen(cmd) > 0) && (cmd[strlen(cmd) - 1] == '\n'))  
    {
        cmd[strlen(cmd) - 1] = '\0'; // will remove newlines
    }
}
