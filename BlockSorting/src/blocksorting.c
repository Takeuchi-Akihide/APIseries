/* knapsack.c
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 *  AP_sample_Problem4
 *  block sortingを用いた暗号化の問題
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocksorting.h"

int main(int argc, char **argv) {
    // 入力の受け付け
    if (argc <= 2 || argc > 4) {
        fprintf(stderr, "引数1: e(encode) or d(decode) or q(encode+decode)\n");
        fprintf(stderr, "引数2: 暗号化/復号化したい文字列\n");
        fprintf(stderr, "引数3: 復号化の場合のキー番号\n");
        return EXIT_FAILURE;
    }
    
    char blockSortString[INPUT_MAX+1];
    int key;

    if (strlen(argv[2]) > INPUT_MAX) {
        fprintf(stderr, "文字列は%d字以内で入力してください\n", INPUT_MAX);
        return EXIT_FAILURE;
    }
    if (argv[1][0] == 'q' || argv[1][0] == 'Q') {
        key = encode(argv[2], blockSortString);
        decode(blockSortString, key);
    } else if (argv[1][0] == 'e' || argv[1][0] == 'E') {
        key = encode(argv[2], blockSortString);
    } else if (argv[1][0] == 'd' || argv[1][0] == 'D') {
        if (argc == 4) {
            key = (int) strtol(argv[3], NULL, 10);
        }
        decode(argv[2], key);
    }
    return EXIT_SUCCESS;
}

int encode(char *inputStr, char *blockSortString) {
    int inputLen = strlen(inputStr);
    char rStr[inputLen*2 + 1];
    sprintf(rStr, "%s%s", inputStr, inputStr);
    int encodeArray[inputLen];
    int key;
    int i, j;

    for (i=0; i<inputLen; i++) {
        encodeArray[i] = i;
    }
    sort1(encodeArray, rStr, inputLen);

    for (i=0; i<inputLen; i++) {
        blockSortString[i] = rStr[encodeArray[i]+inputLen-1];
        if (encodeArray[i] == 0) {
            key = i;
        }
    }
    blockSortString[inputLen] = '\0';
    printf("code:\n%s\n", blockSortString);
    printf("key:\n%d\n", key);

    return key;
}

void decode(char *inputStr, int key) {
    int inputLen = strlen(inputStr);
    DecodeArray_T decodeArray[inputLen];
    char outputStr[inputLen+1];
    int i, n;

    for (i=0; i<inputLen; i++) {
        decodeArray[i].p = inputStr[i];
        decodeArray[i].num = i;
    }
    sort2(decodeArray, inputLen);
    outputStr[0] = decodeArray[key].p;
    n = decodeArray[key].num;
    for (i=1; i<inputLen; i++) {
        outputStr[i] = decodeArray[n].p;
        n = decodeArray[n].num;
    }
    outputStr[inputLen] = '\0';

    printf("outputStr:\n%s\n", outputStr);
}

void sort1(int *array, char *str, int n) {
    int i, j, k;
    char *str_i, *str_j;
    int tmp;
	
    for (i=0; i<n-1; i++) {
        for (j=i+1; j<n; j++) {
            str_i = str + array[i];
            str_j = str + array[j];
            if ((strncmp(str_j, str_i, n)) < 0) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
        // for (k=0; k<n; k++)            /* ソートの途中経過を表示 */
        //     printf("%s  ", str + array[k]);
        // printf("\n");
    }
}

void sort2(DecodeArray_T *str, int n) {
    int i, j, k;
    DecodeArray_T tmp;            /* 作業用ポインタ */
	
    for (i=0; i<n-1; i++) {
        for (j=i+1; j<n; j++) {
            if (str[j].p < str[i].p || (str[j].p == str[i].p) && str[j].num < str[i].num) {
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
        }
        // for (k=0; k<n; k++)            /* ソートの途中経過を表示 */
        //     printf("%s  ", str[k]);
        // printf("\n");
    }
}
