#include <stdio.h>

int main() {
    int i = 0;

    printf("Initial value of i: %d\n", i);
    printf("Result of !i++: %d\n", !i++);
    printf("Value of i after !i++: %d\n", i);

    i = 1;

    printf("Initial value of i: %d\n", i);
    printf("Result of !i++: %d\n", !i++);
    printf("Value of i after !i++: %d\n", i);

    return 0;
}
