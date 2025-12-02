#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    size_t window_size = 0;
    size_t pow10 = 1;

increase_window_size:
    while (window_size + 1 <= nb_digits / 2) {
        window_size++;
        pow10 *= 10;

        if (nb_digits % window_size != 0) {
            continue;
        }

        const size_t window = number % pow10;
        size_t shrink = number / pow10;
        while (shrink > 0) {
            if (window != shrink % pow10) {
                goto increase_window_size;
            }
            shrink /= pow10;
        };
        return 1;
    }
    return 0;
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
            if (is_repeated(low, nb_digits)) {
                sum_of_invalid_ids += low;
            }
            low++;
        }    
    } while(*scan++!='\0'); // skip comma


    printf("The sum of invalid IDs is: %lld\n", sum_of_invalid_ids);

    fclose(file);
    return 0;
}
