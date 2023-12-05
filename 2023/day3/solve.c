#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Position
{
    uint32_t x;
    uint32_t y;
};

typedef struct
{
    char symbol;
    struct Position pos;
    unsigned long adj_nums[64];
} symbol_t;

typedef struct
{
    unsigned long num;
    struct Position pos;
} number_t;


// Globals
symbol_t symbols[2048];
uint16_t symbols_index = 0;

number_t numbers[2048];
uint16_t numbers_index = 0;



int get_number_length(unsigned long number)
{
    return floor(log10((number))) + 1;
}


int get_x_pos_difference(number_t n, symbol_t s)
{
    return s.pos.x - n.pos.x;
}


int get_y_pos_difference(number_t n, symbol_t s)
{
    return s.pos.y - n.pos.y;
}


unsigned long part_one()
{
    unsigned long sum = 0;
    // If difference in x pos is -1 or the length of the number - 1 or - 2 then we are good.
    // If difference in y pos is -1 or 1 or 0 then we are good.
    for (uint16_t i = 0; i < numbers_index; i++)
    {
        number_t n = numbers[i];
        uint8_t num_length = get_number_length(n.num);

        for (uint16_t j = 0; j < symbols_index; j++)
        {
            symbol_t s = symbols[j];
            int x_pos_difference = get_x_pos_difference(n, s);
            int y_pos_difference = get_y_pos_difference(n, s);
            if ( (x_pos_difference == -1 || x_pos_difference == num_length || x_pos_difference == 0 ||
                x_pos_difference == num_length - 1 || x_pos_difference == num_length - 2) &&
                (y_pos_difference == -1 || y_pos_difference == 0 || y_pos_difference == 1) )
            {
                sum += n.num;
            }
        }
    }

    return sum;
}

unsigned long part_two()
{
    // Part 2 should be just looping through the symbols and if the symbol is a gear we find the advacent numbers for it and if they are 2 we multiply them
    unsigned long sum = 0;
    size_t prev_i = -1;

    for (size_t i = 0; i < symbols_index; i++) {

        symbol_t s = symbols[i];
        size_t adj_nums_index = 0;

        if (s.symbol == '*')
        {

            for (size_t j = 0; j < numbers_index; j++)
            {

                number_t n = numbers[j];
                uint8_t num_length = get_number_length(n.num);
                int x_pos_difference = get_x_pos_difference(n, s);
                int y_pos_difference = get_y_pos_difference(n, s);

                if ( (x_pos_difference == -1 || x_pos_difference == num_length || x_pos_difference == 0 ||
                    x_pos_difference == num_length - 1 || x_pos_difference == num_length - 2) &&
                    (y_pos_difference == -1 || y_pos_difference == 0 || y_pos_difference == 1) )
                {
                    s.adj_nums[adj_nums_index] = n.num;
                    if (i == prev_i) {
                        sum += s.adj_nums[adj_nums_index] * s.adj_nums[adj_nums_index - 1];
                    }
                    prev_i = i;
                    adj_nums_index++;
                }
            }

        }

    }


    return sum;
}


int main(int argc, char *argv[])
{

    char *filename = argv[1];
    if (filename == NULL || argc > 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *fs = fopen(filename, "r");
    char *line = {0};
    size_t line_size = 0;

    if (fs == NULL)
    {
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }

    uint32_t curr_line = 0;
    char symbol_chars[] = "*#+=$-&%@/";



    while (getline(&line, &line_size, fs) != -1)
    {

        for (uint16_t i = 0; i < strlen(line); i++)
        {

            // Find all symbols
            for (uint8_t j = 0; j < strlen(symbol_chars); j++)
            {
                if (line[i] == symbol_chars[j])
                {

                    symbol_t s = {
                        .symbol = line[i], .pos = {i, curr_line}, // x, y
                    };

                    symbols[symbols_index++] = s;
                }
            }
        }

        // Find all numbers
        /* I stole this code snippet from
           https://stackoverflow.com/questions/13399594/how-to-extract-numbers-from-string-in-c and modified a little */
        char *p = line;

        uint16_t x_pos = 0;
        for (uint16_t i = 0; *p; i++)
        {
            // printf("iteration %d: %s\n", i, p);
            if (isdigit(*p))
            {
                // Found a number
                unsigned long val = strtoul(p, &p, 10); // Read number
                number_t n = {
                    .num = val,
                    .pos = {x_pos, curr_line},
                };
                numbers[numbers_index++] = n;
                x_pos += get_number_length(val) - 1;
                // printf("%lu\n", val); // and print it.
            }
            else
            {
                // Otherwise, move on to the next character.
                p++;
            }
            x_pos++;
        }

        curr_line++;
    }


    printf("Part 1 answer: %lu\n", part_one());
    printf("Part 2 answer: %lu\n", part_two());

    fclose(fs);
    free(line);

    return EXIT_SUCCESS;
}
