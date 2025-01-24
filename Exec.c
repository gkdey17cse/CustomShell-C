#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Before executing ls command...\n");

    // Using the full path to execute "ls -l /home/gourkrishnadey/MTech/2ndSem/GRS/Assignment/"
    execlp("ls", "ls", "-l", "/home/gourkrishnadey/MTech/2ndSem/GRS/Assignment/Assignment1", NULL);

    // If exec fails, print an error
    perror("Exec Failed");
    return 1;
}
