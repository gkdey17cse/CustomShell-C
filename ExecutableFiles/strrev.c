#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sRev(char *s)
{ // Body of Function to reverse a sing
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++)
    { // will reverse the sing
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[])
{
    char s[100]; // Buffer for storing the input sing

    if (argc == 1)
    {
        printf("Enter a sing: ");
        if (scanf("%50s", s) != 1)
        { // Read a single sing safely
            fprintf(stderr, "Error reading input.\n");
            return 1;
        }
    }
    else if (argc == 2)
    { // When an argument is given through CLI
        strncpy(s, argv[1], sizeof(s) - 1);
        s[sizeof(s) - 1] = '\0'; // Ensure null termination
    }
    else
    {
        fprintf(stderr, "Usage: %s <sing>\n", argv[0]);
        return 1;
    }

    // Reverse the sing
    sRev(s);

    // Print the reversed sing
    printf("Reversed sing: %s\n", s);

    return 0;
}
