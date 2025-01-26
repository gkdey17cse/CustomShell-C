#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a, b;

    if (argc == 1) {
        if (scanf("%d %d", &a, &b) != 2) {  // Read two integers from stdin/input redirection
            fprintf(stderr, "Required two integers.\n");
            return 1;
        }
    }
    else if (argc == 3) {  // when arguments are given through CLI
        a = atoi(argv[1]);   // strings to integers conversion
        b = atoi(argv[2]);  // strings to integers conversion
    }
    else {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    printf("Addition of %d and %d is: %d\n", a, b, a * b);

    return 0;
}
