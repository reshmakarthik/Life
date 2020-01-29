/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
  int aliveCount = 0;
  while(srcStart != srcEnd){
    if (*(srcStart-1) == '1'){
      aliveCount++;
    }
    if (*(srcStart+1) == '1'){
      aliveCount++;
    }
    if (*(srcStart-cols) == '1'){
      aliveCount++;
    }
    if (*(srcStart+cols) == '1'){
      aliveCount++;
    }
    if (*(srcStart-cols+1) == '1'){
      aliveCount++;
    }
    if (*(srcStart-cols-1) == '1'){
      aliveCount++;
    }
    if (*(srcStart+cols+1) == '1'){
      aliveCount++;
    }
    if (*(srcStart+cols-1) == '1'){
      aliveCount++;
    }

    if (*srcStart == '1' && (aliveCount < 2 || aliveCount > 3)){
      (*dest) = 0;
    }
    if (*srcStart == '1' && (aliveCount == 2 || aliveCount == 3)) {
      (*dest) = '1';
    }
    if (*srcStart == 0 && aliveCount == 3) {
      (*dest) = '1';
    }
    if (*srcStart == 0 && aliveCount != 3){
	    (*dest)=0;
    }
    (dest)++;
    srcStart++;
    aliveCount = 0;
  }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
  int j = 0;
  while (j < steps){
    ((*self).gen)++;
    for (int i = 1; i < (*self).numRows-1; i++){
      belem *destPtr = &((*self).nextBuffer[getIndex(self,i,1)]);
      belem *srcPtr = &((*self).currentBuffer[getIndex(self,i,1)]);
      belem *srcPtr2 = &((*self).currentBuffer[getIndex(self,i,(*self).numCols-1)]);
      doRow(destPtr,srcPtr, srcPtr2,(*self).numCols);
    }
    j++;
    swapBuffers(self);
  }
}
