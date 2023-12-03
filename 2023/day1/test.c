
#include <stdio.h>
#include <string.h>

const char *digit_to_alpha[] = {
    "zero",  // 0
    "one",   // 1
    "two",   // 2
    "three", // 3
    "four",  // 4
    "five",  // 5
    "six",   // 6
    "seven", // 7
    "eight", // 8
    "nine"   // 9
};

void find_alpha_values(const char *input) {
    int length = strlen(input);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < 10; ++j) {
            const char *alpha_value = digit_to_alpha[j];
            int alpha_length = strlen(alpha_value);

            if (strncmp(input + i, alpha_value, alpha_length) == 0) {
                printf("Found \"%s\" at position %d\n", alpha_value, i);
                i += alpha_length - 1;  // Move the index to the end of the found alpha value
                break;
            }
        }
    }
}

int main() {
    const char *input_string = "two1nine";

    find_alpha_values(input_string);

    return 0;
}
