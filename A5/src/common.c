#include "common.h"

#include <stdlib.h>

// DONE define global variables needed for your snake! (part 1A)
//int g_snake_row = 2;
//int g_snake_col = 2; // make way for the snakes linked list body (using snake t)

// Definition of global variables for game status.
int g_game_over;
int g_score;

char* g_name = "IvanOrtiz";
int g_name_len = 9;

enum input_key g_last_input = INPUT_RIGHT; // Start moving right



/** Sets the seed for random number generation.
 * Arguments:
 *  - `seed`: the seed.
 */
void set_seed(unsigned seed) {
    /* DO NOT MODIFY THIS FUNCTION */
    srand(seed);
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Returns a random index in [0, size)
 * Arguments:
 *  - `size`: the upper bound for the generated value (exclusive).
 */
unsigned generate_index(unsigned size) {
    /* DO NOT MODIFY THIS FUNCTION */
    return rand() % size;
    /* DO NOT MODIFY THIS FUNCTION */
}
