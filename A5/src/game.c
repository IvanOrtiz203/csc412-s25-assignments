#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 * 
 * 
 */

 //moves the snake to the right
void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
                 
 //making sure the snake exits before the game is over
if (g_game_over) {
    return;
}

if (!snake_p || !snake_p->head) {
fflush(stdout);

    g_game_over = 1;
    return;
}

 // Get current head position
 int old_row = snake_p->head->row;
 int old_col = snake_p->head->col;

   // Compute new position
   int new_row = old_row;
   int new_col = old_col;

    //debugging the game end when  I run ./snake 1 
    fflush(stdout); // Ensure it prints immediately


// Clear the old snake cell
//cells[g_snake_row * width + g_snake_col] = FLAG_PLAIN_CELL; // this has to go

// Compute the new position - default move is to the RIGHT
//int new_row = g_snake_row; // this has to go
//int new_col = g_snake_col;  // this has to go

switch (input) {
    case INPUT_UP:
        new_row -= 1;
        break;
    case INPUT_DOWN:
        new_row += 1;
        break;
    case INPUT_LEFT:
        new_col -= 1;
        break;
    case INPUT_RIGHT:
        new_col += 1;
        break;
    default: break;
}


    int new_index = new_row * width + new_col;

    // Check collision with self
    if (cells[new_index] & FLAG_WALL || cells[new_index] & FLAG_SNAKE) {
        g_game_over = 1;
        return;
    }

    // Check collision with self


    // Check if food is eaten
    int ate_food = 0;
    if (cells[new_index] & FLAG_FOOD) {
        g_score++;
        ate_food = 1;
        place_food(cells, width, height);
    }

    // Add new head to the front of the snake
    snake_node_t* new_head = malloc(sizeof(snake_node_t));
    new_head->row = new_row;
    new_head->col = new_col;
    new_head->next = snake_p->head;
    snake_p->head = new_head;
    snake_p->length++;

    // Mark new head position on the board
    cells[new_index] = FLAG_SNAKE;

    // Remove tail if not growing and didn’t eat food
    //
    if (!growing && !ate_food) {
        snake_node_t* curr = snake_p->head;
        snake_node_t* prev = NULL;

        // Traverse to second-to-last node
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }

        // Clear the tail from the board
        int tail_index = curr->row * width + curr->col;
        cells[tail_index] = FLAG_PLAIN_CELL;

        // Remove tail node
        free(curr);

        if (prev != NULL) {
            prev->next = NULL;
            snake_p->tail = prev;
        } else {
            // Snake became empty
            snake_p->head = NULL;
            snake_p->tail = NULL;
        }

        snake_p->length--;
    } 
}


/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your
    // implementation)
    strcpy(write_into, "placeholder");
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    // Done(03/30 2:30pm): implement!
    // free board
    if(cells != NULL){
        free(cells);

    }

    //free snake linked list 
    snake_node_t* current = snake_p ->head;
    while (current != NULL){
        snake_node_t* temp = current;
        current = current ->next;
        free(temp);  
      }

    
}
