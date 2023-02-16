// Nadeem Rashid
// Date: 06-JUN-2022
// Revision: 1.1 - 07-JUN-2022
// Description: This program will test out sodoku puzzles, and by using the created validity checks,
// we will be able to see if a given sodoku puzzle is valid or not.

#include "array_func.h"
#include <stdlib.h>
#include <time.h>

int checkSodoku(int row, int column, int array[][column]){
    // To check the entire sodoku puzzle, each check will be called
    int rowCheck = checkSodokuRow(row, column, array);
    int columnCheck = checkSodokuColumn(row, column, array);
    int boxCheck = checkSodokuBox(row, column, array);

    // If every check is 0, then the sodoku puzzle passed, otherwise it failed.
    if(rowCheck == 0 && columnCheck == 0 && boxCheck == 0)
        return 0;
    else
        return 1;
}

int checkSodokuRow(int row, int column, int array[][column]){
    // Used to keep track of duplicates
    int duplicateDetected = 0;
    // z is used for keeping track of the total sodoku rows
    int z = 0;

    //Depending on how many rows are in the array, the code will iterate through each one
    for(z = 0; z < row; z++) {
        int i = 0;
        int prevX = 1;
        int x = 1;

        // The explanation for this check can be found on main.c. The reason why it's located
        // where the user inputs their numbers, is to show where exactly the duplicates are
        for (i = 0; i < column; i++) {
            while (x < 9) {
                if (array[z][i] == array[z][x]) {
                    duplicateDetected += 1;
                }
                x++;
            }
            x = prevX + 1;
            prevX++;
        }
    }
    return duplicateDetected;
}

int checkSodokuColumn(int row, int column, int array[][column]){
    int duplicateDetected = 0;
    int z = 0;

    // Checking the duplicates for the column has the same idea as checking the rows, but now it's swapped
    for(z = 0; z < 9; z++) {
        int i = 0;
        int prevX = 1;
        int x = 1;

        for (i = 0; i < 9; i++) {
            while (x < 9) {
                // As you can see here, because the columns are being checked, we only need to use one at a time,
                // Hence the values of i/x and z being swapped, compared to the checkSodokuRows
                if (array[i][z] == array[x][z]) {
                    duplicateDetected += 1;
                }
                x++;
            }
            x = prevX + 1;
            prevX++;
        }
    }
    return duplicateDetected;
}

// Checking each sodoku box was a bit difficult. I decided to opt for this strategy:
// Iterate through the first three rows of the first box, place those values in a
// different array, and then submit the array to checkSodokuRow to see if there are
// any duplicate numbers. Then, move on to the next box, and repeat the same thing.
// I move on to the next box by adding 3 to the starting and ending number of columns.
// Once I reach the end of the first three rows (column 9), I shift downwards to the
// next set of boxes, which is by 3, and repeat the whole process again.
int checkSodokuBox(int row, int column, int array[][column]){
    int duplicateDetected = 0;
    int testArray[1][9] = {0};
    int counter = 0;

    int rowSet = 3;
    int columnSet = 3;

    // Iterating through the sodoku's rows, 3 at a time
    for(int z = 0; z < 3; z++){
        // Iterating through the sodoku's columns, 3 at a time
        for(int y = 0; y < 3; y++){
            // Iterating through the boxes' rows
            for(int i = -3 + rowSet; i < rowSet; i++){
                // Iterating through the boxes' columns
                for(int x = -3 + columnSet; x < columnSet; x++){
                    testArray[0][counter] = array[i][x];
                    // Once the counter reaches 9, the program will know that the entire box has been
                    // placed into an array, and will reset it afterwards.
                    counter++;
                }
            }
            duplicateDetected += checkSodokuRow(1,9,testArray);
            counter = 0;
            columnSet += 3;
        }
        columnSet = 3;
        rowSet += 3;
    }

    rowSet += 3;

    return duplicateDetected;
}

// Creating the random distinct numbers between 1 and 9 were a bit difficult too.
// I did it by creating a random number from 1 to 9, then while in a loop, check
// to see if that number exists in that row. If it does, then loop again and create
// a new random number, and check again. If there are no duplicates, the number will
// be placed into the array's row. Once the row is filled, then the program will
// move on to the next row(s).
void createRandomRows(int min, int row, int column, int array[][column]){
    int randomSame = 0;
    int randomNum;
    srand(time(NULL));

    // Iterating through each row
    for(int i = min; i < row; i++){
        // Iterating through the columns of the specified row
        for(int x = 0; x < column; x++) {
            // This loop will ensure a distinct random is placed, by brute force
            while(1){
                // Creating the random number, which will be reinitialized when it loops again
                randomNum = rand() % column + 1;
                // Iterating through the entire row to check for duplicates
                for(int z = 0; z < x; z++){
                    if(randomNum == array[i][z]) {
                        randomSame = 1;
                    }
                }
                // If there are no duplicates, break the loop.
                if(randomSame == 0){
                    break;
                }
                // Resetting this check for the next random number.
                randomSame = 0;
            }
            // When the loop is completed, the check is completed and the program
            // will put in the specific random number into the specified array index.
            array[i][x] = randomNum;
        }
    }
}