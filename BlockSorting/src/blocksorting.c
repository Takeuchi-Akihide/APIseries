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
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "引数1: e(encode) or d(decode) or q(encode+decode)\n");
        fprintf(stderr, "引数2: 暗号化/復号化したい文字列\n");
        fprintf(stderr, "引数3: 復号化の場合のキー番号\n");
        return EXIT_FAILURE;
    }

    FILE *fp_read1;
    if ((fp_read1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "ファイルが開けません。\n");
		return EXIT_FAILURE;
    }
    
    char blockSortString[INPUT_MAX];
    int key;
    char input[INPUT_MAX];
    char pattern[3];

    key = file_read(fp_read1, input, pattern);
    if (key == -1) {
        fprintf(stderr, "ファイルの中身が適切ではありません\n");
        return EXIT_FAILURE;
    }

    if (pattern[0] == 'q' || pattern[0] == 'Q') {
        printf("pattern:\nq\n");
        key = encode(input, blockSortString);
        decode(blockSortString, key);
    } else if (pattern[0] == 'e' || pattern[0] == 'E') {
        printf("pattern:\nd\n");
        key = encode(input, blockSortString);
    } else if (pattern[0] == 'd' || pattern[0] == 'D') {
        printf("pattern:\ne\n");
        decode(input, key);
    }
    return EXIT_SUCCESS;
}

// ファイルを読み込んでpattern(encode/decode)、inputする文字列を渡し、keyを返す
int file_read(FILE *fp_read1, char *input, char *pattern) {
    char str[INPUT_MAX];
    int key;
    int i;

    // 1~2行目：pattern
    fgets(str, INPUT_MAX, fp_read1);
    if (strncmp(str, "pattern:", 8) != 0) {
        return -1;
    }
    fgets(str, INPUT_MAX, fp_read1);
    i = 0;
    while (str[i] != '\n') {
        pattern[i] = str[i];
        i++;
    }
    pattern[i] = '\0';

    // 3~4行目：input
    fgets(str, INPUT_MAX, fp_read1);
    if (strncmp(str, "code:", 5) != 0 && strncmp(str, "string:", 7) != 0) {
        return -1;
    }
    fgets(str, INPUT_MAX, fp_read1);
    i = 0;
    while (str[i] != '\n') {
        input[i] = str[i];
        i++;
    }
    input[i] = '\0';

    // 5~6行目：key
    if (pattern[0] == 'd') {
        fgets(str, INPUT_MAX, fp_read1);
        if (strncmp(str, "key:", 4) != 0) {
            return 0;
        }
        fgets(str, INPUT_MAX, fp_read1);
        key = strtol(str, NULL, 10);
    }
    
    return key;
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

    printf("string:\n%s\n", outputStr);
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
