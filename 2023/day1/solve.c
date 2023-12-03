#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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


int get_first_int(char *string, char *c, int reverse) {

    for (int i = 0; i < strlen(string); i++) {
        char curr_char;
        if (reverse == 1) {
            curr_char = string[strlen(string) - i - 1];
        } else {
            curr_char = string[i];
        }

        if (isdigit(curr_char)) {
            *c = curr_char;
            break;
        }
    }

    return EXIT_SUCCESS;
}


int get_calibration_value(char *string) {

    char calibration_value[3] = { 0 };

    get_first_int(string, &calibration_value[0], 0);
    get_first_int(string, &calibration_value[1], 1);

    return atoi(calibration_value);
}


int main(int argc, char *argv[])
{
    FILE *fs   = fopen("./input.txt", "r");
    char *buff = { 0 };
    size_t buff_size = 0;

    if (fs == NULL) {
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }

    int calibration_value = 0;
    int sum = 0;

    while (getline(&buff, &buff_size, fs) != -1) {
        calibration_value = get_calibration_value(buff);
        sum += calibration_value;
    }

    printf("Sum of calibration values is: %d\n", sum);


    free(buff);
    fclose(fs);

    return EXIT_SUCCESS;
}
