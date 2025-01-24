#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if two arguments (numbers) are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    // Convert arguments from strings to integers
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // Perform multiplication and print the result
    printf("Multiplication of %d and %d is: %d\n", a, b, a * b);

    return 0;
}
