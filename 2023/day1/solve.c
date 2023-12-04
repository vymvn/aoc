#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PART_ONE 0
#define PART_TWO 1

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


void find_alpha_values_and_replace(const char *input, char *output) {
    int length = strlen(input);
    int output_index = 0;

    for (int i = 0; i < length; i++) {
        int matched = 0;

        for (int j = 0; j < 10; j++) {
            const char *alpha_value = digit_to_alpha[j];
            int alpha_length = strlen(alpha_value);

            if (strncmp(input + i, alpha_value, alpha_length) == 0) {
                // printf("Found \"%s\" at position %d\n", alpha_value, i);
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


int get_calibration_value(char *line, int8_t *left, int8_t *right) {

    *left  = -1;
    *right = -1;

    for (uint16_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
        
            if (*left == -1) {
                *left  = line[i] - 0x30;
                *right = line[i] - 0x30;
            } else {
                *right = atoi(&line[i]);
            }

        }
    }

    return EXIT_SUCCESS;
}

// int get_first_int(char *string, char *c, int reverse) {
//
//     for (int i = 0; i < strlen(string); i++) {
//         char curr_char;
//         if (reverse == 1) {
//             curr_char = string[strlen(string) - i - 1];
//         } else {
//             curr_char = string[i];
//         }
//
//         if (isdigit(curr_char)) {
//             *c = curr_char;
//             break;
//         }
//     }
//
//     return EXIT_SUCCESS;
// }
//
//
// int get_calibration_value(char *string) {
//
//     char calibration_value[3] = { 0 };
//
//     get_first_int(string, &calibration_value[0], 0);
//     get_first_int(string, &calibration_value[1], 1);
//
//     return atoi(calibration_value);
// }


int main(int argc, char *argv[])
{
    char *filename = "./input.txt";
    FILE *fs   = fopen(filename, "r");
    char *line = { 0 };
    size_t buff_size = 0;

    if (fs == NULL) {
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }

    uint8_t calibration_value = 0;
    uint32_t sum = 0;
    char fixed_line[200] = { 0 };
    int8_t left;
    int8_t right;

    while (getline(&line, &buff_size, fs) != -1) {

        if (PART_ONE) {

            // calibration_value = get_calibration_value(line);
            // sum += calibration_value;

        } else if (PART_TWO) {

            line[strcspn(line, "\n")] = 0;
            find_alpha_values_and_replace(line, fixed_line);
            printf("%s\n", fixed_line);
            // calibration_value = get_calibration_value(fixed_line);
            get_calibration_value(fixed_line, &left, &right);
            uint32_t total = left * 10 + right;
            sum += total;

        }
    }

    printf("Answer from file \"%s\": %d\n", filename, sum);


    free(line);
    fclose(fs);

    return EXIT_SUCCESS;
}
