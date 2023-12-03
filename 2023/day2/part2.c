
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int PART_ONE = 0;
const int PART_TWO = 1;


const int MAX_RED   = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE  = 14;



struct Game {
    int id;
    int max_red_cubes;
    int max_green_cubes;
    int max_blue_cubes;
};



void update_cube_count(char *cube_info, struct Game *game) {

    int curr_num = atoi(cube_info);

    if (strstr(cube_info, "red")) {

        if ( curr_num > game->max_red_cubes) {
            game->max_red_cubes = curr_num;
        }

    } else if (strstr(cube_info, "green")) {

        if ( curr_num > game->max_green_cubes) {
            game->max_green_cubes = curr_num;
        }

    } else if (strstr(cube_info, "blue")) {

        if ( curr_num > game->max_blue_cubes) {
            game->max_blue_cubes = curr_num;
        }

    }

}



struct Game process_line(char *line) {
    struct Game game = {};

    // Gets the part before the ":"
    char *game_info = strtok(line, ":");
    sscanf(game_info, "Game %d", &game.id); 

    // Moving to the part after the ":"
    game_info = strtok(NULL, ":");

    // The first cube in the round
    char *curr_cube = strtok(game_info, ";,");
    update_cube_count(curr_cube, &game);


    // The rest of the cubes in the round
    while ((curr_cube = strtok(NULL, ";,")) != NULL) {
        update_cube_count(curr_cube, &game);
    }

    return game;
}



int main(int argc, char *argv[])
{

    char filename[] = "./input2.txt";
    FILE *fs   = fopen(filename, "r");
    char *line = { 0 };
    size_t line_size = 0;

    if (fs == NULL) {
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }

    struct Game game = { 0 };

    int sum = 0;

    while (getline(&line, &line_size, fs) != -1) {
        game = process_line(line);

        if (PART_ONE) {

            if (game.max_red_cubes <= MAX_RED && game.max_green_cubes <= MAX_GREEN && game.max_blue_cubes <= MAX_BLUE) {
                printf("game:\n\tid = %d\n\tred = %d\n\tgreen = %d\n\tblue = %d\n", game.id, game.max_red_cubes, game.max_green_cubes, game.max_blue_cubes);
                sum += game.id;
            }


        } else if (PART_TWO) {

            sum += game.max_red_cubes * game.max_blue_cubes * game.max_green_cubes;

        }


    }

    printf("Answer = %d\n", sum);


    fclose(fs);
    free(line);
    
    return EXIT_SUCCESS;
}
