#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "game_over.h"
#include "game_setup.h"
#include "mbstrings.h"
#include "render.h"

/** Gets the next input from the user, or returns INPUT_NONE if no input is
 * provided quickly enough. 

 */
enum input_key get_input() {
    /* DO NOT MODIFY THIS FUNCTION */
    int input = getch();

    if (input == KEY_UP) {
        return INPUT_UP;
    } else if (input == KEY_DOWN) {
        return INPUT_DOWN;
    } else if (input == KEY_LEFT) {
        return INPUT_LEFT;
    } else if (input == KEY_RIGHT) {
        return INPUT_RIGHT;
    } else {
        // if the input isn't an arrow key, we treat it as no input (could add
        // other keys in if we want other commands, like 'pause' or 'quit')
        return INPUT_NONE;
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Helper function that procs the GAME OVER screen and final key prompt.
 * `snake_p` is not needed until Part 2!
 */
void end_game(int* cells, size_t width, size_t height, snake_t* snake_p) {
    // Render final GAME OVER screen
    render_game_over(width, height);
    usleep(1000 * 1000);  // Pause for 1 second

    cbreak(); // Leave halfdelay mode
    getch();  // Wait for a key press

    // tell ncurses that we're done
    endwin();

    // Now free memory
    teardown(cells, snake_p);
}


int main(int argc, char** argv) {
    // Main program function — this is what gets called when you run the
    // generated executable file from the command line!

    // Board data
    size_t width;   // the width of the board.
    size_t height;  // the height of the board.
    int* cells;     // a pointer to the first integer in an array of integers
                    // representing each board cell.

    // snake data (only used in part 2!)
    snake_t snake;    // your snake struct. (not used until part 2!)
    int snake_grows;  // 1 if snake should grow, 0 otherwise.

    enum board_init_status status;

    // initialize board from command line arguments
    switch (argc) {
        case (2):
            snake_grows = atoi(argv[1]);
            if (snake_grows != 1 && snake_grows != 0) {
                printf(
                    "snake_grows must be either 1 (grows) or 0 (does not "
                    "grow)\n");
                return 0;
            }
            status = initialize_game(&cells, &width, &height, &snake, NULL);
            break;
        case (3):
            snake_grows = atoi(argv[1]);
            if (snake_grows != 1 && snake_grows != 0) {
                printf(
                    "snake_grows must be either 1 (grows) or 0 (does not "
                    "grow)\n");
                return 0;
            } else if (*argv[2] == '\0') {
                status = initialize_game(&cells, &width, &height, &snake, NULL);
                break;
            }
            status = initialize_game(&cells, &width, &height, &snake, argv[2]);
            break;
        case (1):
        default:
            printf("usage: snake <GROWS: 0|1> [BOARD STRING]\n");
            return 0;
    }

    // ----------- DO NOT MODIFY ANYTHING IN `main` ABOVE THIS LINE -----------

    // Check validity of the board before rendering!
    // DONE: Implement (in Part 1C)
    // if ( ? board is not valid ? ) { return EXIT_FAILURE; }

    // Read in the player's name & save its name and length
    // TODO: Implement (in Part 2B)
     char name_buffer[1000];
     read_name(name_buffer); //reads user inputs and stores their name
    //? save name_buffer ?
    // ? save mbslen(name_buffer) ?

    // DONE: Remove this message, uncomment the code below this message
    //       and implement Part 1A here.

if (status != INIT_SUCCESS) {
    switch (status) {
        case INIT_ERR_INCORRECT_DIMENSIONS:
            fprintf(stderr, "Error: Board dimensions do not match the compressed string.\n");
            break;
        case INIT_ERR_WRONG_SNAKE_NUM:
            fprintf(stderr, "Error: Board must contain exactly one snake cell.\n");
            break;
        case INIT_ERR_BAD_CHAR:
            fprintf(stderr, "Error: Compressed board string contains an invalid character.\n");
            break;
        default:
            fprintf(stderr, "Error: Unknown board initialization error.\n");
    }
    return EXIT_FAILURE;
}





    printf(
        "             ____   \n"
        "Hello       / . .\\ \n"
        "CSC412      \\  ---<\n"
        "student!     \\  /  \n"
        "   __________/ /    \n"
        "-=:___________/\n");

     initialize_window(width, height);

     

     while(!g_game_over){
            usleep(200000); //150ms between updates (speed)
            enum input_key input = get_input(); //repalce for input keys 
            if(input != INPUT_NONE){
                g_last_input = input;
            }
            update(cells, width, height, &snake, g_last_input, snake_grows); //snake update
            render_game(cells, width, height); //draw the board
     }

    // DONE: implement the game loop here (Part 1A)!
    end_game(cells, width, height, &snake);
}
