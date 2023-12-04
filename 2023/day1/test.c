
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


void replace(char *old, char *new) {

    // sq5fivetwothree1
    // sq55231

}

void find_alpha_values_and_replace(const char *input, char *output) {
    int length = strlen(input);
    int output_index = 0;

    for (int i = 0; i < length; i++) {
        int matched = 0;

        for (int j = 0; j < 10; j++) {
            const char *alpha_value = digit_to_alpha[j];
            int alpha_length = strlen(alpha_value);

            if (strncmp(input + i, alpha_value, alpha_length) == 0) {
                printf("Found \"%s\" at position %d\n", alpha_value, i);
                output[output_index++] = '0' + j;
                matched = 1;
                i += alpha_length - 1;  // Move the index to the end of the found alpha value
                break;

            }
        }
        // If the character is not part of any alpha value, copy it as is
        if (!matched) {
            output[output_index++] = input[i];
        }

    }
    // Null-terminate the output string
    output[output_index] = '\0';

}

int main() {
    const char *input_string = "sq5fivetwothree1";
    char output[100] = { 0 };
    find_alpha_values_and_replace(input_string, output);
    printf("%s\n%s\n", input_string, output);

    return 0;
}
