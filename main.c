// Nadeem Rashid
// Date: 07-JUN-2022
// Revision: 1.1 - 07-JUN-2022
// Description: This program will test out sodoku puzzles, and by using the created validity checks,
// we will be able to see if a given sodoku puzzle is valid or not.

#include <stdio.h>
#include "array_func.h"

int main() {
    int inpArr[9][9] = {0};
    // bool will be used for when the user inputs their numbers, and updated when its invalid
    int bool = 0;
    // counter will be used to fill in a singular row of the array
    int counter = 0;
    // counter1 will be used to repeat asking the user for input
    int counter1 = 0;
    char buffer[BUFF_SIZE];
    // a sudoku test grid, which has NO duplicate columns and rows
    int testGrid[ ][ 9 ] = {{5,3,4,6,7,8,9,1,2},
                            {6,7,2,1,9,5,3,4,8},
                            {1,9,8,3,4,2,5,6,7},
                            {8,5,9,7,6,1,4,2,3},
                            {4,2,6,8,5,3,7,9,1},
                            {7,1,3,9,2,4,8,5,6},
                            {9,6,1,5,3,7,2,8,4},
                            {2,8,7,4,1,9,6,3,5},
                            {3,4,5,2,8,6,1,7,9}};

    puts("--------Test Grid--------");
    for(int i = 0; i < 9; i++){
        for(int x = 0; x < 9; x++){
            printf("%d  ", testGrid[i][x]);
        }
        puts("");
    }
    // Calling the checkSodoku function, passing the testGrid as a baseline validity check
    printf("With 0 representing a pass, and 1 representing a fail, "
           "the Test Grid's result is: %d\n", checkSodoku(9,9,testGrid));

    // Counter will increase only once; starting value of 0 represents row 0, and an increment of 1 will represent row 1
    while(counter1 < 2) {
        // Counter will increase as user inputs the right amount of integers
        while (counter < 9) {
            int ch;
            puts("Please enter exactly 9 distinct integers that are within the range "
                 "of 1 - 9, inclusive, and separated by a Tab/Space:");
            fgets(buffer, sizeof(buffer), stdin);
            // I was trying to figure out a way to make this more compact, but with the validity checking for user
            // inputs, I found this way to be the best
            counter = sscanf(buffer, "%d%d%d%d%d%d%d%d%d %c", &inpArr[counter1][0],
                             &inpArr[counter1][1], &inpArr[counter1][2], &inpArr[counter1][3], &inpArr[counter1][4],
                             &inpArr[counter1][5], &inpArr[counter1][6], &inpArr[counter1][7], &inpArr[counter1][8], &ch);

            // If the total input is less than or greater than 9, reset and continue
            if (counter != 9 || counter > 9) {
                puts("Please enter EXACTLY 9 integers.");
                counter = 0;
                continue;
            }

            // If any of the user's inputs are out of bounds, reset and continue
            for (int i = 0; i < 9; i++) {
                if (inpArr[counter1][i] > 9 || inpArr[counter1][i] < 1) {
                    printf("%d is out of bounds.\n", inpArr[counter1][i]);
                    counter = 0;
                    continue;
                }
            }

            int i = 0;
            int prevX = 1;
            int x = 1;
            // I created this validity test to efficiently check if there are any duplicates;
            // The first values is picked, then compared to the rest of the values in the row.
            // Then, the second number is picked, but is only compared to the values after it,
            // and so on and so forth. This prevents the program from checking values that
            // have already been checked before.
            for (i = 0; i < 9; i++) {
                while (x < 9) {
                    if (inpArr[counter1][i] == inpArr[counter1][x]) {
                        printf("%d, %d ", inpArr[counter1][i], inpArr[counter1][x]);
                        puts("Duplicate Detected.");
                        bool = 1;
                    }
                    x++;
                }
                x = prevX + 1;
                prevX++;
            }

            // If the user enters a duplicate number, bool will be greater than 0 and they will
            // be prompted to enter the row again.
            if (bool >= 1) {
                counter = 0;
                bool = 0;
                continue;
            }
        }
        // Resetting the counter, as the user successfully entered a row
        counter = 0;
        counter1++;
        // Used for asthetic-purposes
        if(counter1 < 2) puts("Row 2:");
    }

    // Function called to create random rows that have distinct numbers from 1 through 9
    createRandomRows(2,9,9,inpArr);

    puts("Thank you for inputting values for the first two rows. Here's the result of the Sodoku grid:\n");
    puts("-------Sodoku Grid-------");
    for(int i = 0; i < 9; i++){
        for(int x = 0; x < 9; x++){
            printf("%d  ", inpArr[i][x]);
        }
        puts("");
    }
    printf("\nWith 0 representing a pass, and 1 representing a fail, "
           "the Sodoku Grid's result is: %d", checkSodoku(9,9,inpArr));
    return 0;
}
