#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int win_nums[64];
    int our_nums[128];
    int points;
} card_t;


int load_int_arr(char *source, int destination[]) {

    size_t index = 0;
    while (*source) {

         if (isdigit(*source)) {
            int num = strtol(source, &source, 10);
            destination[index++] = num;
         } else {
            source++;
        }

    }

    return EXIT_SUCCESS;
}


card_t process_line(char *line) {
    card_t c = { 0 };

    // Gets the part before the ":"
    char *card_info = strtok(line, ":");
    sscanf(card_info, "Card %d", &c.id); 

    // Moving to the part after the ":"
    card_info = strtok(NULL, ":");

    // Getting winning numbers
    char *win_nums = strtok(card_info, "|");
    load_int_arr(win_nums, c.win_nums);

    // printf("card winnin nums: %s\n", c.win_nums);

    // Getting our numbers 
    char *our_nums = strtok(NULL, "|");
    load_int_arr(our_nums, c.our_nums);
    // c.our_nums = our_nums;
    // printf("card our nums: %s", our_nums);

    return c;
}



int main(int argc, char *argv[]) {

    char *filename = argv[1];
    if (filename == NULL || argc > 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *fs = fopen(filename, "r");
    char *line = { 0 };
    size_t line_size = 0;

    if (fs == NULL) {
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }

    card_t card = { 0 };
    int sum = 0;

    while (getline(&line, &line_size, fs) != -1) {
        card = process_line(line);

        // int curr = 0;
        // for (int i = 0; (curr = card.our_nums[i]); i++) {
        //
        //     printf("%d ", curr);
        // 
        // }
        // printf("\n");

        int curr_our_num = 0;
        // printf("Card %d winning numbers -> ", card.id);
        int count = 0;
        for (int i = 0; (curr_our_num = card.our_nums[i]); i++) {

            // printf("curr our num --> %d\n", curr_our_num);

            int curr_win_num = 0;
            for (size_t j = 0; (curr_win_num = card.win_nums[j]); j++) {

                if (curr_win_num == curr_our_num) {
                    count++;
                    if (count == 1) {
                        card.points += 1;
                    } else {
                        card.points *= 2;
                    }
                }
            }

        }
        printf("Card %d: count = %d | points = %d\n", card.id, count, card.points);
        sum += card.points;
        // printf("Card: \n\tid: %d", card.id);
    }

    
    printf("Answer = %d\n", sum);


    fclose(fs);
    free(line);
    
    return EXIT_SUCCESS;
}
