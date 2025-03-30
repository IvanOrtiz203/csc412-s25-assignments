# Understanding and Parsing the Custom Board String 

One difficult part I encountered was understanding how to correctly decompress the custom board string.
includes encoded information about wall (W), empty (E), and snake (S) cells, and each character is followed by 
a number that tells how many times that character should repeat. I had trouble figuring out how to Correctly extract
the board dimensions from the string. I had to spend a lot of time debugging off-by-one errors and making sure I was not
accessing invalid memory. Understanding how to tokenize the string and calculate the correct board cell positions was more 
complex than I expected.

# Implementing the Snake with a Linked List 

Another part I struggled with was converting the cells of the snake into growing using a linked list. I had experience with linked
lists before. Using them in C with manual memory management made it tricky. I had difficulty Managing memory correctly for each new 
node and Updating both the head and tail of the snake when it grows or moves. It was also confusing to figure out how to grow the 
snake only when it eats food, while keeping the logic clean and efficient. Since each part of the snake is stored as a node with row,
col, and next, I needed to be very careful about where and when I insert or remove nodes.

## Part 2: Real-World Examples / Analogies

I getting together a party but I am not sure how many people are going to show up. insteed of fining a fizx size room. I found a palce 
that allows me to add more chairs and tables if more people decied to come. with malloc its like calling the owner and asking to set up
10 more chairs. if for what ever reason fewer people show up the tables and chairs can be free up 

a conga line as some one in the fornt called the head and the people behind him holdine one antoher shoulders are the nodes. each one pointing
to the next one where ever the head goes the nodes follow. when the snake eats somthing its like someone else joined the end of the line. 



