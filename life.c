/* Game of Life
life.c -- Hunter Trautz, hctrautz
 */

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"					
#include <string.h>

/**  Returns the contents of the desired cell 
 * @param  totalRows 	 the totalNumber of rows on the board
 * @param  totalColumns  totalNumber of columns on the board
 * @param  rowNUM   	 the row number of the cell you want to know what it contains 
 * @param  columnNUM  	 the column number of the cell you want to know what it contains 
 * @param  board 		 Array of pointers to integers representing whether a cell is dead or alive 
 * @return the desired cell's contents, 0 if the row or the column is empty/not on the board
 */
int cellContains(int totalRows, int totalColumns, int rowNUM, int columnNUM, int **board){
	//if the user entered a negative (invalid) row coordinate mark the cell as empty 
	if(rowNUM < 0){
		return 0;
	}

	//if the user enetered a row coordinate that would cause the array containing the board to overflow, mark the cell as empty
	if(rowNUM >= totalRows){
		return 0;
	}

	//if the user enetered a column coordinate that would cause the array containing the board to overflow, mark the cell as empty
	if(columnNUM >= totalColumns){
		return 0;
	}

	//if the user entered a negative (invalid) column coordinate mark the cell as empty 
	if(columnNUM < 0){
		return 0;
	}

	return board[rowNUM][columnNUM];
}

/** Returns an integer represnting the total number of surrounding alive cells for the desired cell 
 * @param  totalRows  		the totalNumber of rows on the board
 * @param  totalColumns  	the totalNumber of columns on the board
 * @param  rowNUM  			the row number of the cell you want to know how many total surroding alive cells there are 
 * @param  columnNUM  		the column number of the cell you want to know how many total surroding alive cells there are 
 * @param  board  			Array of pointers to integers representing whether a cell is dead or alive 
 * @return an integer represnting the total number of surrounding alive cells for the desired cell  
 */
int totalSurroundingAliveCells(int totalRows, int totalColumns, int rowNUM, int columnNUM, int **board){
	int numberOfAliveCells = 0;

	//cell directly to the left 
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM-1, columnNUM, board);
	//cell directly to the right
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM+1, columnNUM, board);

	//cells directly on top, to the top right, and to the top left
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM, columnNUM-1, board);
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM+1, columnNUM-1, board);
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM-1, columnNUM-1, board);
	
	//cells directly on the bottom, to the bottom left, and to the bottom right
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM-1, columnNUM+1, board);
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM+1, columnNUM+1, board);
	numberOfAliveCells = numberOfAliveCells + cellContains(totalRows, totalColumns, rowNUM, columnNUM+1, board);
	

	return numberOfAliveCells;
}

/** Prints "The Game of Life" board based off of the 2D array of integers passed in, 
 *  1 represents a cell that is alive or "x", and 0 represents a dead cell or "o"
 * @param totalRows  	the totalNumber of rows on the board
 * @param totalColumns  the totalNumber of columns on the board
 * @param board 		Array of pointers to integers representing whether a cell is dead or alive 
 */
void printBoard(int totalRows, int totalColumns, int **board){
    //INVARIANT #1: The loop will continue to evaluate as long as the rowNUM is less than the total amount of rows on the board. 0 < rowNUM < totalRows
	for(int rowNUM = 0; rowNUM < totalRows; rowNUM++){
        //INVARIANT #2: The loop will continue to evaluate as long as the columnNUM is less than the total amount of columns on the board. 0 < columnNUM < totalColumns
		for(int columnNUM = 0; columnNUM < totalColumns; columnNUM++){
			//if the cell is alive (the element of the array is 1) 
			if(board[rowNUM][columnNUM]){
				printf("x");
			} /* otherwise the array holds 0 so mark the cell as dead */ else {
				printf(" ");
			}
		}
		printf("\n"); //space so that the next board is not connected to this board
	}
}

/** Plays one round or one generation of "The Game of Life" by cycling the previous generation through the rules 
 *  with the knowledge of the surronding cells of each cell and creating a new array of ints 
 *  representing the next generation. Returns 1 if there was change between the 
 *  the previous generation and the next generation, and returns 0 if there was no change
 * @param totalRows  	the totalNumber of rows on the board
 * @param totalColumns  the totalNumber of columns on the board
 * @param generationNUM the number of the generations played so far
 * @param genX  		Array of pointers to integers representing whether a cell is dead or alive 
 * @param genY  		Array of pointers to integers representing whether a cell is dead or alive
 * @param genZ  		Array of pointers to integers representing whether a cell is dead or alive  
 * @param doPrint 		holds whether the program should print out each generation  
 */
int playOne(int totalRows, int totalColumns, int generationNUM, int **genX, int **genY, int **genZ, int doPrint){
    //INVARIANT #3: The loop will continue to evaluate as long as the rowNUM is less than 
    //the total amount of rows on the board. 0 < rowNUM < totalRows
	for(int rowNUM = 0; rowNUM < totalRows; rowNUM++){
        //INVARIANT #4: The loop will continue to evaluate as long as the columnNUM is less 
        //than the total amount of columns on the board. 0 < columnNUM < totalColumns
		for(int columnNUM = 0; columnNUM < totalColumns; columnNUM++){

			int surroundingCells = totalSurroundingAliveCells(totalRows, totalColumns, rowNUM, columnNUM, genY);

			//if the cell was dead in the previous generation, and surrounded 
            //by 3 living cells, mark it as alive in the next generation
			if(genY[rowNUM][columnNUM] == 0 && surroundingCells == 3){
				//mark cell as alive
				genZ[rowNUM][columnNUM] = 1;
			}

			//if the cell was alive in the previous generation, and is surrounded by more than 
            //3 living cells (overcrowding), mark it as dead in the next generation
			if(genY[rowNUM][columnNUM] == 1 && surroundingCells > 3){
				//mark cell as dead
				genZ[rowNUM][columnNUM] = 0;
			}

			//if the cell was alive in the previous generation, and is surrounded by 2 or 3 living cells,
            //mark it as alive in the next generation
			if(genY[rowNUM][columnNUM] == 1 && surroundingCells < 4 && surroundingCells >= 2){
				//mark cell as alive
				genZ[rowNUM][columnNUM] = 1;
			}	
			
			//if the cell was alive in the previous generation, and is surrounded by less than 2 living cells (dies of lonliness) 
            //mark it as dead in the next generation
			if(genY[rowNUM][columnNUM] == 1 && surroundingCells < 2){
				//mark cell as dead
				genZ[rowNUM][columnNUM] = 0;
			}
		}
	}

	//prints the board if the user entered 'y' or 1 for the doPrint argument
	if(doPrint){
		printBoard(totalRows, totalColumns, genZ);
	}

	int oscillate = 1; //1 if the game oscillates, 0 if it does not 
	int repeat = 1; //1 if the game repeats, 0 if it does not

	//INVARIANT #5: The loop will continue to evaluate as long as the rowNUM is less than the total amount
    //of rows on the board. 0 < rowNUM < totalRows
	for(int rowNUM = 0; rowNUM < totalRows; rowNUM++){
		//INVARIANT #6: The loop will continue to evaluate as long as the columnNUM is less 
        //than the total amount of columns on the board. 0 < columnNUM < totalColumns
		for(int columnNUM = 0; columnNUM < totalColumns; columnNUM++){

			//Compares the next(new) generation to the generation from 2 generations back to check if they are the same. 
            //If they aren't, mark it as oscillate as false
			if(genZ[rowNUM][columnNUM] != genX[rowNUM][columnNUM]){
				//false
				oscillate = 0;
			}

			//Compares the two most recent generations, changes 
			if(genY[rowNUM][columnNUM] != genZ[rowNUM][columnNUM]){
				//Turn off the repeat flag.
				repeat = 0;
			}
		}
	}

	//If the board contains is the same thing two times in sucession, and it is not genZero,
    //print an error specifiying this and return 1 for reference in Life().
	if(repeat == 1 && generationNUM != 0){
		printf("\nGame Ending: No Change in Board on Generation #%d\n", generationNUM);
		return 1;
	}

    //If the current board at the time is equal to the board from two generations ago, 
    //and it is not generation 0 or generation 1, print an error specifiying this and return 1 for reference in Life().
	if(oscillate == 1 && generationNUM != 0 && generationNUM != 1){
		printf("\nGame Ending: Oscillation on Generation #%d\n", generationNUM);
		return 1;
	}

	//Return 0 if there were no errors
	return 0;
}

/**  Plays "The Game of Life"
 * @param  totalRows  	the totalNumber of rows
 * @param  totalColumns the totalNumber of columns
 * @param  totalGens  	the total number of generations
 * @param  doPrint  	holds whether or not to print out the board after each generation is calcualted
 * @param  doPause  	holds whether or not whether to pause before printing the next generation.
 * @param  board  		gen0, the starting board from the txt file
 */
void Life(int totalRows, int totalColumns, int totalGens, int doPrint, int doPause, int **board){
	int **A = make2Dint(totalRows, totalColumns);
	int **B = make2Dint(totalRows, totalColumns);
	int **C = make2Dint(totalRows, totalColumns);

	//sets Array A equal to the inputed array so it can be edited/used
	//INVARIANT #7: The loop will continue to evaluate as long as the rowNUM is less than the total amount
    //of rows on the board. 0 < rowNUM < totalRows
	for(int rowNUM = 0; rowNUM < totalRows; rowNUM++){
		//INVARIANT #8: The loop will continue to evaluate as long as the columnNUM is less 
        //than the total amount of columns on the board. 0 < columnNUM < totalColumns
		for(int columnNUM = 0; columnNUM < totalColumns; columnNUM++){
			A[rowNUM][columnNUM] = board[rowNUM][columnNUM];
		}
	}

	int boardCounter = 1; //stores which number board contains the current generation  
	int error = 0; //stores if the playOne function produces an error while running, 1 if error 0 if sucesful

	//INVARIANT #9: The loop will continue to evaluate as long as the generationNUM is less 
    //than the total amount of generations. 0 < generationNUM < totalGens
	for(int generationNUM = 0; generationNUM < totalGens; generationNUM++){

		int ***genX = &C; //2 generation beheind the current generation
		int ***genY = &A; //The previous generation
		int ***genZ = &B; //The current generation, the one to be printed out

		//If printing is enabled, print out the generation label.
		if(doPrint){
			printf("\nGeneration #%d\n", generationNUM);
		}

		if(generationNUM > 0){
				
			//Whenever boardCounter is one use Array B as the current generation, Array A as the previous generation, and Array C as 2 gens back
			if(boardCounter == 1){
				genX = &C;
				genY = &A;
				genZ = &B;
			}

			//Whenever boardCounter is two use Array C as the current generation, Array B as the previous generation, and Array A as 2 gens back
			else if(boardCounter == 2){
				genX = &A;
				genY = &B;
				genZ = &C;
			}

			//Whenever boardCounter is three use Array A as the current generation, Array C as the previous generation, and Array B as 2 gens back
			else{
				genX = &B;
				genY = &C;
				genZ = &A;
			}

			//If the generationNUM is equal to the max gen number, print out the final config and break the loop. 
			if(generationNUM == totalGens){
				printf("\nFinal Configuration:\n");
				printBoard(totalRows, totalColumns, *genZ);
			}

			//If processRound() returns one, there was an error, print the final config and break the loop. 
			if(playOne(totalRows, totalColumns, generationNUM, *genX, *genY, *genZ, doPrint)){
				error = 1;
				printf("\nFinal Configuration:\n");
				printBoard(totalRows, totalColumns, *genZ);
				break;
			}

			//Move to the next board
			if(boardCounter == 1 || boardCounter == 2){
				boardCounter++;
			} else {
			//Reset the board counter back to 1
				boardCounter = 1;
			}

		} else {
			printBoard(totalRows, totalColumns, board);
		}

		//Enables the pause function with getchar()
		if(doPause){
			printf("\nPress Enter to Continute.");
			getchar();
		}
	}

	//If there was no error, return the end game statement 
	if(error == 0){
		printf("\nGame Ending: Generation Limit Reached on Generation #%d\n", totalGens);
	}
}

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 */
int main(int argc, char **argv){
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input = NULL; // Stream descriptor for file containing initial grid
	int totalRows = 0; // Number of rows in the grid
	int totalColumns = 0; // Number of columns in the grid
	int gens = 0; //Number of generations to produce
	int doPrint = 0; // 1 if user wants to print each generation, 0 if not
	int doPause = 0; // 1 if user wants to pause after each generation, 0 if not
	int didError = 0; // 1 is there was an error that occured with the input of arguments, of if not 

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	//only print if there are 5 or more arguments
	if (argv[5][0] == 'y' && (argc >= 6)){
		doPrint = 1;
	}

	//only print if there are 6 or more arguments
	if(argv[6][0] == 'y' && argc == 7){
		doPause = 1;
	}

	//if negative produce exit the program 
	if(gens < 0){
		didError = 1;
	}

	//if negative produce exit the program 
	if(!input){
		didError = 1;
	}

	//if negative produce exit the program 
	if(totalColumns < 0){
		didError = 1;
	}

	//if negative produce exit the program 
	if(totalRows < 0){
		didError = 1;
	}

	//if negative produce exit the program 
	if(!didError){
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	totalRows = atoi(argv[1]); // Convert from character string to integer.
	totalColumns = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];

	/* Eventually, need to try to open the input file. */
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}

	//Allocate memory to read each line of the input file.
	char *InputFileLine = malloc(500);
	//Holds the files total number of rows in the input file
	int inputRowTotal = 0; 
	//Holds the total number of columns in the input file
	int inputColumnTotal = 0; 
	//Holds the 1st row of the input file 
	int inputRow = 0; 
	//Holds the 1st column of the input file 
	int inputColumn = 0; 

	//INVARIANT #10: The loop will continue to evaluate as long as the InputFileLine is less 
    //than the total amount of lines in the file. 0 < InputFileLine < inputRowTotal
	while(fgets(InputFileLine, 500, input) != NULL) {
		if(strlen(InputFileLine)-1 == 0){
			continue;
		}
		
		if(strlen(InputFileLine)-1 > inputColumnTotal){
			inputColumnTotal = strlen(InputFileLine)-1;
		}
		inputRowTotal++;
	}

	//Rewind to parse the file once more 
	rewind(input);
	//Makes a 2D array of integers made up of the file
	int **file = make2Dint(inputRowTotal, inputColumnTotal);
	//Allocate memory to read the current line of the file.
	char *tempInputLine = malloc(500);
	//Stores the current line number of the file
	int currentLine = 0;

	//INVARIANT #11: The loop will continue to evaluate as long as the InputFileLine is less 
    //than the total amount of lines in the file. 0 < InputFileLine < inputRowTotal
	while(fgets(tempInputLine, 500, input) != NULL) {

		//INVARIANT #12: The loop will continue to evaluate as long as the tempInputLine is less 
   		//than the total amount of lines in the file. 0 < i < tempInputLine
		for(int i=0;i<strlen(tempInputLine)+1;i++){
			
			//If the character is x, set the filemap for this position to 1 (organism)
			if(tempInputLine[i] == 'x'){
				file[currentLine][i] = 1;
			}else{ //Otherwise set it to 0, empty space.
				file[currentLine][i] = 0;
			}
			
		}
		currentLine++;
	}

	inputRow = (totalRows/2)-(inputRowTotal/2); //Set the start of the file to the max number of rows divided by 2, and subtract by 1/2 of the total rows in the file
	inputColumn = (totalColumns/2)-(inputColumnTotal/2); //Set the start of the file to the max number of columns divided by 2, and subtract by 1/2 of the total columns in the file

	//Make a 2nd array of integers which will hold the centered version of the board
	int **parse = make2Dint(totalRows, totalColumns);

	//INVARIANT #13: The loop will continue to evaluate as long as the rowNUM is less than the total amount
    //of rows on the board. 0 < rowNUM < totalRows
	for(int rowNUM = 0; rowNUM < totalRows; rowNUM++){

		//INVARIANT #14: The loop will continue to evaluate as long as the columnNUM is less 
        //than the total amount of columns on the board. 0 < columnNUM < totalColumns
		for(int columnNUM=0; columnNUM<totalColumns; columnNUM++){

			//set each element of the new array to the contents of the file except centered in the middle of the new array
			if(rowNUM > inputRow-1 && columnNUM > inputColumn-1 && rowNUM <= inputRow+inputRowTotal-1 && columnNUM <= inputColumn+inputColumnTotal-1){
				parse[rowNUM][columnNUM] = file[rowNUM-inputRow][columnNUM-inputColumn];
			}else{
				//if not in the file mark the cell as empty
				parse[rowNUM][columnNUM] = 0;
			}
		}
	}

	//Run the game 
	Life(totalRows, totalColumns, gens, doPrint, doPause, parse);

	//Sucess.
	return EXIT_SUCCESS;
	
}
