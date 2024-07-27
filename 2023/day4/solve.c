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
    size_t num_of_copies;
    size_t match_count;
} card_t;


// Globals
card_t all_cards[4096] = { 0 };
size_t all_cards_index = 0;
size_t total_cards = 0;


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

    c.num_of_copies = 1;

    // Gets the part before the ":"
    char *card_info = strtok(line, ":");
    sscanf(card_info, "Card %d", &c.id); 

    // Moving to the part after the ":"
    card_info = strtok(NULL, ":");

    // Getting winning numbers
    char *win_nums = strtok(card_info, "|");
    load_int_arr(win_nums, c.win_nums);

    // Getting our numbers 
    char *our_nums = strtok(NULL, "|");
    load_int_arr(our_nums, c.our_nums);

    return c;
}


int part_one() {
    int sum = 0;
    card_t card = {0};

    for (size_t i = 0; i < all_cards_index; i++) {

        card = all_cards[i];
        int curr_our_num = 0;
        for (int i = 0; (curr_our_num = card.our_nums[i]); i++) {

            int curr_win_num = 0;
            for (size_t j = 0; (curr_win_num = card.win_nums[j]); j++) {

                if (curr_win_num == curr_our_num) {
                    card.match_count++;
                    if (card.match_count == 1) {
                        card.points += 1;
                    } else {
                        card.points *= 2;
                    }
                }
            }

        }
        // printf("Card %d: points = %d\n", card.id, card.points);
        sum += card.points;

    }
    return sum;
}

int find_match_count(card_t *c) {

    int curr_our_num = 0;
    for (int i = 0; (curr_our_num = c->our_nums[i]); i++) {
        int curr_win_num = 0;
        for (size_t j = 0; (curr_win_num = c->win_nums[j]); j++) {
            if (curr_win_num == curr_our_num) {
                c->match_count++;
            }
        }
    }

    return EXIT_SUCCESS;
}

size_t part_two() {
    card_t *card;

    for (size_t i = 0; i < all_cards_index; i++) {

        card = &all_cards[i];   // Pointer to current card
        find_match_count(card);

        total_cards += card->num_of_copies;
        if (card->match_count) {

            // printf("Card %d has won copies of: ", card.id);
            for (size_t i = 0; i < card->match_count; i++) {
                card_t *c = &all_cards[card->id + i];    // Pointer to card(s) after
                c->num_of_copies += card->num_of_copies;
                // printf("%d ", c->id);
            }
            // printf("\n");

        }

    }

    return total_cards;
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

    while (getline(&line, &line_size, fs) != -1) {
        card = process_line(line);
        all_cards[all_cards_index++] = card;

    }

    printf("Part 1 answer = %d\n", part_one());
    printf("Part 2 answer = %lu\n", part_two());

    fclose(fs);
    free(line);

    return EXIT_SUCCESS;
}
