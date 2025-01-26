#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num;

    if (argc == 1)
    {
        if (scanf("%d", &num) != 1)
        { // Read a number from stdin / File redirection
            fprintf(stderr, "Error: Please provide a number.\n");
            return 1;
        }
    }
    else if (argc == 2)
    {                        // while given through CLI
        num = atoi(argv[1]); // Convert argument from string to integer
    }
    else
    {
        fprintf(stderr, "Argument mismatch! The command should be: %s <num>\n", argv[0]);
        return 1;
    }

    // Core Logic
    if (num < 0)
    {
        printf("Factorial doesn't exist for %d\n", num);
    }
    else if (num == 0 || num == 1)
    {
        printf("Factorial of %d is: 1\n", num);
    }
    else
    {
        int fact = 1;
        for (int i = num; i > 0; i--)
        {
            fact = fact * i;
        }
        printf("Factorial of %d is: %d\n", num, fact);
    }

    return 0;
}
