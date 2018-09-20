/* Game of Life
README.txt -- Hunter Trautz, hctrautz
 */

RULES OF THE GAME: 
The game is played on a rectangular grid of cells, so that each cell has eight neighbors (adjacent cells). Each cell is either occupied by an organism (it is marked alive) or not (dead). A pattern of occupied and unoccupied cells in the grid is called a generation. The rules for deriving a new generation from the previous generation are these:–

1. Death. If an occupied cell has 0, 1, 4, 5, 6, 7, or 8 occupied neighbors, the organism dies (0 or 1 of loneliness; 4 thru 8 of overcrowding).

2. Survival. If an occupied cell has two or three neighbors, the organism survives to the next generation.

3. Birth. If an unoccupied cell has precisely three occupied neighbors, it becomes occupied by a new organism.

INSTRUCTIONS FOR RUNNING THE PROGRAM: 
The program can be run by first navigating, in terminal, to the folder where you unzipped the contents of the program and then simply typing the command "make", which will compile the program. Next, navigate in terminal again to the same folder as before, and use the following command to play the game: "./life rows columns generations inputFile [print] [pause]". Where rows is the total number of rows on the board, columns is the total number of columns on the board, generation is the total number of generation the game will be played for, inputFile is the .txt file where the original board state will be read from, print is 'y' if you want to print out each individual generation or 'n' if not, and finally pause is 'y' if you want the game to pause after printing each individual generation or 'n' if not. 

Problems that Arose:
During the entirety of the making of this project, there were many big problems that came up. Some major problems included parsing the input file to make the inital generation, centering the board when given board dimensions that were too big, and creating multiple multi-dimensonal arrays to be able to cycle through and acess three generations at once. 

Loop Invariants: 
INVARIANT #1: The loop will continue to evaluate as long as the rowNUM is less than the total amount of rows on the board. 0 < rowNUM < totalRows

INVARIANT #2: The loop will continue to evaluate as long as the columnNUM is less than the total amount of columns on the board. 0 < columnNUM < totalColumns

INVARIANT #3: The loop will continue to evaluate as long as the rowNUM is less than the total amount of rows on the board. 0 < rowNUM < totalRows

INVARIANT #4: The loop will continue to evaluate as long as the columnNUM is less 
than the total amount of columns on the board. 0 < columnNUM < totalColumns

INVARIANT #5: The loop will continue to evaluate as long as the rowNUM is less than the total amount
of rows on the board. 0 < rowNUM < totalRows

INVARIANT #6: The loop will continue to evaluate as long as the columnNUM is less 
than the total amount of columns on the board. 0 < columnNUM < totalColumns

INVARIANT #7: The loop will continue to evaluate as long as the rowNUM is less than the total amount
of rows on the board. 0 < rowNUM < totalRows

INVARIANT #8: The loop will continue to evaluate as long as the columnNUM is less 
than the total amount of columns on the board. 0 < columnNUM < totalColumns

INVARIANT #9: The loop will continue to evaluate as long as the generationNUM is less 
than the total amount of generations. 0 < generationNUM < totalGens

INVARIANT #10: The loop will continue to evaluate as long as the InputFileLine is less 
than the total amount of lines in the file. 0 < InputFileLine < inputRowTotal

INVARIANT #11: The loop will continue to evaluate as long as the InputFileLine is less 
than the total amount of lines in the file. 0 < InputFileLine < inputRowTotal

INVARIANT #12: The loop will continue to evaluate as long as the tempInputLine is less 
than the total amount of lines in the file. 0 < i < tempInputLine

INVARIANT #13: The loop will continue to evaluate as long as the rowNUM is less than the total amount
of rows on the board. 0 < rowNUM < totalRows

INVARIANT #14: The loop will continue to evaluate as long as the columnNUM is less 
than the total amount of columns on the board. 0 < columnNUM < totalColumns

EXAMPLE TEST CASES: 
./life 3 3 10 blinker.txt y y , The game ended due to oscillation on generation 2
./life 3 9 30 diehard.txt y y , The game ends due to reaching the generation limit on generation #30
