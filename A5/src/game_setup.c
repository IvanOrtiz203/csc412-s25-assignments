#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
    size_t* height_p, snake_t* snake_p,
    char* board_rep) {
enum board_init_status status;

if (board_rep != NULL) {
// If a custom board is provided, decompress it — this also sets the snake node
status = decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
} else {
// Otherwise, use the default board and manually set the snake
status = initialize_default_board(cells_p, width_p, height_p);

if (status != INIT_SUCCESS) {
return status;
}

// Allocate and initialize the snake's head node
snake_node_t* node = malloc(sizeof(snake_node_t));
if (node == NULL) {
return INIT_ERR_INCORRECT_DIMENSIONS;  // fallback for memory alloc failure
}

node->row = 2;
node->col = 2;
node->next = NULL;

snake_p->head = node;
snake_p->tail = node;
snake_p->length = 1;

// Place the snake on the board
int index = node->row * (*width_p) + node->col;
(*cells_p)[index] = FLAG_SNAKE;
}

// Only proceed if board setup was successful
if (status != INIT_SUCCESS) {
return status;
}

g_game_over = 0;
g_score = 0;

place_food(*cells_p, *width_p, *height_p);

return INIT_SUCCESS;
}


/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {


if (!compressed || compressed[0] != 'B') {
    return INIT_ERR_BAD_CHAR;
}

//step one height and width form the string 
int height = 0, width = 0;
char* rest = NULL;

if(height <= 0 || width <= 0){
    free(rest);
    return INIT_ERR_INCORRECT_DIMENSIONS;
}

*height_p = height;
*width_p = width;

//step two: allocate board memory 

int total_cells = height * width;
int* board = malloc(total_cells * sizeof(int));
if(!board){
    free(rest);
    return INIT_ERR_INCORRECT_DIMENSIONS;
}

//clear the board
for(int i = 0; i < total_cells; i++){
    board[i] = FLAG_PLAIN_CELL;
}

// Step 3: Decompress board rows
int current_cell = 0;
int snake_count = 0;

char* row_str = strtok(rest, "|");
int row_count = 0;

while (row_str && row_count < height) {
    char* ptr = row_str;

    while (*ptr != '\0') {
        char cell_type = *ptr++;

        if (cell_type != 'E' && cell_type != 'W' && cell_type != 'S') {
            free(rest);
            free(board);
            return INIT_ERR_BAD_CHAR;
        }

        // Read number
        int count = 0;
        while (*ptr >= '0' && *ptr <= '9') {
            count = count * 10 + (*ptr - '0');
            ptr++;
        }

        if (count <= 0) {
            free(rest);
            free(board);
            return INIT_ERR_INCORRECT_DIMENSIONS;
        }

        for (int i = 0; i < count; i++) {
            if (current_cell >= total_cells) {
                free(rest);
                free(board);
                return INIT_ERR_INCORRECT_DIMENSIONS;
            }

            if (cell_type == 'E') {
                board[current_cell++] = FLAG_PLAIN_CELL;
            } else if (cell_type == 'W') {
                board[current_cell++] = FLAG_WALL;
            } else if (cell_type == 'S') {
                if (snake_count >= 1) {
                    free(rest);
                    free(board);
                    return INIT_ERR_WRONG_SNAKE_NUM;
                }

                board[current_cell++] = FLAG_SNAKE;
                 // Calculate row and col
    int snake_row = row_count;
    int snake_col = current_cell % width;

    // Allocate and assign snake node
    snake_node_t* node = malloc(sizeof(snake_node_t));
    if (!node) {
        free(rest);
        free(board);
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }

    node->row = snake_row;
    node->col = snake_col;
    node->next = NULL;

    // Set snake pointers
    snake_p->head = node;
    snake_p->tail = node;
    snake_p->length = 1;

    snake_count++;
    current_cell++;
            }
        }
    }

    row_str = strtok(NULL, "|");
    row_count++;

}

free(rest);

if (row_count != height || current_cell != total_cells) {
    free(board);
    return INIT_ERR_INCORRECT_DIMENSIONS;
}

if (snake_count != 1) {
    free(board);
    return INIT_ERR_WRONG_SNAKE_NUM;
}

*cells_p = board;
    // TODO: implement!
return INIT_SUCCESS;
}// custom helper functions for loading diffrent bords (come back to this)
