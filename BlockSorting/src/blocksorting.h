/* knapsack.h
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 */

#ifndef BLOCKSORTING_H_
#define BLOCKSORTING_H_

#define INPUT_MAX    100


typedef struct DecodeArray {
    char p;
    int  num;
} DecodeArray_T;

int encode(char *inputStr, char *blockSortString);
void decode(char *inputStr, int key);
void sort1(int *array, char *str, int n);
void sort2(DecodeArray_T *str, int n);

#endif // BLOCKSORTING_H_
