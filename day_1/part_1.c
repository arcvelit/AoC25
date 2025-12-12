#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define dial_len 100
#define shift_dial(p, n) (((p + n) % dial_len + dial_len) % dial_len)
int dial = 50;

static inline int scan_int_endl(const char* str) {
    int result = 0;
    while (str && isdigit(*str)) {
        result = result * 10 + (*str++ - '0');
    }
    return result;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    size_t dial_to_zero_counter = 0;

    char buffer[8];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        const char* scan = &buffer[0];

        int direction;
        switch (*(scan++)) {
            case 'L': direction = -1; break;
            case 'R': direction =  1; break;
            default: fprintf(stderr, "error: bad input\n"); exit(EXIT_FAILURE);
        }
        const int magnitude = scan_int_endl(scan);

        dial = shift_dial(dial, direction * magnitude);
        if (dial == 0) {
            dial_to_zero_counter++;
        }
    }

    // easy clap
    printf("The password is: %d\n", dial_to_zero_counter);

    fclose(file);
    return 0;
}
