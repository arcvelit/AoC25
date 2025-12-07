#include <stdio.h>
#include <stdlib.h>

#define BANK_SIZE 100
#define CONCAT_CHARS(c1,c2) (((c1) - '0') * 10 + ((c2) - '0'))

// Iterative approach
static inline size_t get_maximum_bank_joltage(const char* const bank) {
    const char* const END = &bank[BANK_SIZE];

    char max  = *bank;
    char max2 = 0;
    
    const char* it;
    for (it = bank+1; it+1 < END; it++) {
        if (*it > max) {
            max2 = 0;
            max  = *it;
        } else if (max2 < *it) {
            max2 = *it;
        }
    }
    if (*it > max || *it > max2) {
        max2 = *it;
    }
    return CONCAT_CHARS(max, max2);
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
    printf("The maximum joltage possible is: %d\n", sum_of_maximum_joltages);

    fclose(file);
    return 0;
}
