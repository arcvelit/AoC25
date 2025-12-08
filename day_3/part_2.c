#include <stdio.h>
#include <stdlib.h>

#define BANK_SIZE 100
#define STACK_CAP 12

static inline size_t scan_int(const char* str, size_t size) {
    size_t result = 0;
    while (size--) {
        result *= 10;
        result += *str++ - '0';
    }
    return result;
}

static inline size_t get_maximum_bank_joltage(const char* const bank) {
    char  stack[STACK_CAP] = { *bank };
    char* top = &stack[1];

    const char* const STACK_END = &stack[STACK_CAP];
    const char* const END = &bank[BANK_SIZE];

    for (const char* it = bank+1; it < END; it++) {
        while (*it > *(top - 1) && top - stack + END - it > STACK_CAP && top > stack)
            top--;
        if (top < STACK_END)
            *top++ = *it;
    }
    return scan_int(stack, STACK_CAP);
}

// Entry point
int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    size_t sum_of_maximum_joltages = 0;

    char buffer[BANK_SIZE + 2]; // account for \n AND \0 (took 24 hrs to realize it caused a bug)
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        sum_of_maximum_joltages += get_maximum_bank_joltage(buffer);
    }

    // easy clap
    printf("The maximum joltage possible is: %lu\n", sum_of_maximum_joltages);

    fclose(file);
    return 0;
}
