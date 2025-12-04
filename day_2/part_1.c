#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static inline size_t consume_id(char** str) {
    size_t result = 0;
    while (isdigit(**str)) {
        result *= 10;
        result += **str - '0';
        (*str)++;
    }
    return result;
}

static inline size_t get_size_t_string_length(size_t value) {
    size_t length = 0;
    do {
        ++length;
        value /= 10;
    } while (value > 0);
    return length;
}

// for exp > 0
static inline size_t power(size_t base, size_t exp) {
    size_t result = 1;
    while (exp--) {
        result *= base;
    }
    return result;
}

static inline int is_repeated(const size_t number, const size_t nb_digits) {
    // 123456 
    const size_t mid_point = power(10, nb_digits / 2);
    const size_t first_half  = number / mid_point; // 123
    const size_t second_half = number % mid_point; // 456
    return first_half == second_half;
}


int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    size_t sum_of_invalid_ids = 0;

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fprintf(stderr, "error: failed to read from input\n");
        exit(EXIT_FAILURE);
    }

    char* scan = &buffer[0];
    
    do {
        size_t low = consume_id(&scan);
        scan++; // skip dash
        const size_t high = consume_id(&scan);

        while (low <= high) {
            size_t nb_digits = get_size_t_string_length(low);
            if (nb_digits % 2 != 0)  {
                low = power(10, nb_digits);
                continue;
            } else if (is_repeated(low, nb_digits)) {
                sum_of_invalid_ids += low;
            }
            low++;
        }    
    } while(*scan++!='\0'); // skip comma


    printf("The sum of invalid IDs is: %lld\n", sum_of_invalid_ids);

    fclose(file);
    return 0;
}
