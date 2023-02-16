// Nadeem Rashid
// Date: 06-JUN-2022
// Revision: 1.1 - 07-JUN-2022
// Description: This program will test out sodoku puzzles, and by using the created validity checks,
// we will be able to see if a given sodoku puzzle is valid or not.

#ifndef NADEEMRASHIDASSIGN1_ARRAY_FUNC_H
#define NADEEMRASHIDASSIGN1_ARRAY_FUNC_H

#endif //NADEEMRASHIDASSIGN1_ARRAY_FUNC_H

#define BUFF_SIZE 100

int checkSodoku(int row, int column, int array[][column]);
int checkSodokuRow(int row, int column, int array[][column]);
int checkSodokuColumn(int row, int column, int array[][column]);
int checkSodokuBox(int row, int column, int array[][column]);
void createRandomRows(int min, int row, int column, int array[][column]);