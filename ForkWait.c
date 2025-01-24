#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void){
    pid_t ppid = getppid();
    pid_t pid = getpid();
    printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
    pid_t forkStatus = fork();
    if(forkStatus<0){
        perror("Error! Can't generate child process\n");
    }else if(forkStatus==0){
        printf("-------- Child Processs --------\n");
        ppid = getppid();
        pid = getpid();
        printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
    }else{
        printf("-------- Parent Processs --------\n");
        ppid = getppid();
        pid = getpid();
        printf("The Current Process ID is : %d and CUrrent Parent Process ID is : %d\n",pid,ppid);
        wait(NULL);
    }
}