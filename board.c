/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer
 */
boards_t * createBoard(char *initFileName){
  int cellCol = 0;
  int cellRow = 0;
  boards_t *newBoard = (boards_t *)malloc(sizeof(boards_t));

  FILE *file;
  if ((file = fopen(initFileName, "r")) == NULL){
    return NULL;
  }
    fscanf(file, "%d", &(*newBoard).numRows);
    fscanf(file, "%d", &(*newBoard).numCols);
    (*newBoard).bufferA = (belem*)malloc((*newBoard).numRows*(*newBoard).numCols);
    (*newBoard).bufferB = (belem*)malloc((*newBoard).numRows*(*newBoard).numCols);
    (*newBoard).currentBuffer = (*newBoard).bufferA;
    (*newBoard).nextBuffer = (*newBoard).bufferB;
    clearBoards(newBoard);
    while(fscanf(file, "%d %d", &cellRow, &cellCol) > 0){
      (*newBoard).bufferA[getIndex(newBoard, cellRow, cellCol)] = '1';
    }
    (*newBoard).gen = 0;
    fclose(file);
    return newBoard;
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  free((**bptrPtr).bufferA);
  free((**bptrPtr).bufferB);
  free((*bptrPtr));
  *bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  for (int i = 0; i < (*self).numRows; i++){
    for (int j = 0; j < (*self).numCols; j++){
      (*self).bufferA[getIndex(self,i,j)] = 0;
      (*self).bufferB[getIndex(self,i,j)] = 0;
    }
  }
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  belem *temp = (*self).currentBuffer;
  (*self).currentBuffer = (*self).nextBuffer;
  (*self).nextBuffer = temp;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
  int row2 = (*self).numRows;
  int col2 = (*self).numCols;
  int index = row * col2 + col;
  return index;
}
