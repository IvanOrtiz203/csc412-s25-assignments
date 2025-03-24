# Design Document - Assignment 5: Snake

## Introduction
This document outlines the approach for completing Assignment 5 - Snake. The goal 
is to use core C concepts like pointers, memory management, and data structures to
simulate the snake's movement, growth, food collection, and collisions. 

## Understanding
The game runs in the terminal and displays a grid where the snake moves in real-time. I will am responsible for managing the snake's body using a data structure. handling keyboard input for movement, spawning food randomly, and updating the game state until the player loses.

## Implementation

### 1.snake data stucure 
using a linked list to repesnet each segment of the snakes body.
Having this means it can grown and shrink with dynamicly 
Adding a new head or removing the tail is fast and efficient
when the sanke moves a new node will be added to the fornt and the tail will be removed unless it eats somthing 

### 2. Board Initialization
using initialize_default_board() to start with a 20x10 board
Mark the walls using FLAG_WALL and empty spaces with FLAG_PLAIN_CELL
snake will be placed on the bord with the use of FLAG_SNAKE

### 3. snake movement 
Updating the snake its position every tick by adding a new head segment in the direction while \
removing a its tail aswell.
this means it must calcualte the new head position amd create the new head node, check whats the next cell 
and update the bord

### 4. input handing 
using curses library to take in key inputs makeing sure the it changes into the right direction. The getch() function will be called every tick to check if the player has pressed a key. I will configure it to be no blocking using nodelay() so the game loop continues even when no input is given. Arrow key inputs like KEY_UP, KEY_DOWN, KEY_LEFT, and KEY_RIGHT will be mapped to the input_key values. getch() and keypad() will allow realtime movement control while the snake moves automatically in the background.

### 5. Food Spawning and Eating
Food will be spawned randomly on the board using the generate_index() function. I will use it to select random (row, col) positions until an empty cell (FLAG_PLAIN_CELL) is found and place food there by setting that cell to FLAG_FOOD. During each movement update if the snake’s head moves into a food cell the score (g_score) will increase by 1 and the snake will grow by not removing its tail node. After eating, the food flag will be cleared from that cell and a new piece of food will be spawned. Functions like spawn_food() and is_food_cell() will manage food placement and detection.

### 6. Collision Detection
Checking the cell that the snake's head is about to move into before actually updating its position. If that cell contains a wall FLAG_WALL or part of the snake LAG_SNAKE, that means a collision has occurred, and the game should end. Using bitflags, I can check the value of the next cell using bitwise operations like cell & FLAG_WALL. If a collision is detected, I will set g_game_over = 1 to end the game loop. This logic will be placed at the beginning of the snake's movement function, before inserting the new head.

### 7. Rendering
The rendering will use functions from the curses.h library such as mvaddch() and refresh() to draw the state of the game on the terminal. Each game tick the grid will be updated by checking each cell's bitflags and drawing the appropriate character. For example, `#` for walls, `O` for the snake, `*` for food, and a space or dot for empty cells. The refresh() function will be used to push all visual changes to the screen. At the end of the game, the render_game_over() function will display a message including the player’s name and final score.

### 8. Cleanup
When the game ends it will free all dynamically allocated memory to avoid memory leaks. Since the snake is stored as a linked list. I will create a function that traverses through each node of the list and frees the memory for each one. Freeing the board array cells that was allocated during initialization. This ensures the program exits cleanly which is important for programming in C. This logic will likely go at the end of the game loop or after render_game_over() is called.

## Timeline
Implement initialize_game() to set up board (March 24–26)
mplement movement logic (March 27–28)
mplement spawn_food() using generate_index() (March 29–30)
Check for wall or self collisions and rendering  (March 31–1)
creating test cases for the game (March 2-3)

## Expected Challenges & Solutions

### 1. Getting Lost in the Codebase
The project involves multiple `.c` and `.h` files with shared data structures and functions. It's easy to get overwhelmed or confused by where everything connects. To address this, I will read and map out the role of each file and write comments in my code as I go. Breaking each part into smaller tasks  will help me stay focused.

### 2. Git and Version Control
As I work through the assignment I want to make sure I’m pushing my progress regularly to GitHub. It’s easy to forget or make mistakes without using git consistently. I’ll get into the habit of using GitHub like a journal committing after finishing each feature and writing short messages about what I changed. This will also help me recover if something breaks.

### 3. Snake Movement and Memory Bugs
Implementing snake movement using a linked list could lead to segmentation faults or memory leaks if I forget to free nodes or manage pointers properly. To prevent this I will test small movements first and use `valgrind` or `gdb` to catch errors early.

### 4. Terminal Rendering Bugs
The `curses.h` functions only show changes after calling `refresh()` so if something isn’t showing up, it might not be a logic error just a rendering one. debuging with simple terminal printouts or temporarily show snake info directly on screen.

### 5. Running Out of Time
Since the project is due April 3rd it’s possible I’ll fall behind if I don’t pace myself. planing  and treat each section like a mini assignment. Even just working for 30–60 minutes daily will help me finish.

## Conclusion
This design document outlines my plan to implement the Snake game by breaking it into manageable parts like data structures, movement, input handling, rendering and cleanup. I’ve tried to fine possible challenges and created a timeline to complete everything by the due date. By following this structure and working steadily I’m confident I can finish the assignment and submit a clean, working game.