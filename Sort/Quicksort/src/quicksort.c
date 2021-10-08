/* quicksort.c
 *  Created on: 2021/10/08
 *      Author: a_takeuchi
 *  AP_H28Autumn_Problem3
 *  クイックソート
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quicksort.h"


int main(void) {
    // データ作成
    srand((unsigned) time(NULL));
    int hnum = 30000;
    int i;
    int data[hnum];
    make_data_random(data, hnum);
    printf("data: %d\n", hnum);
    print_by_10(data, hnum);
    clock_t start = clock();

    // プログラム実行
    quick_sort(data, hnum);
    clock_t end = clock();

    // 出力
    printf("\nquick\n");
    print_by_10(data, hnum);

    printf("\ntime: %.9f s\n", (float) (end-start) / CLOCKS_PER_SEC);
    
}

void print_by_10(int *data, int hnum) {
    int line = ((hnum - 1) / 10) + 1;
    int digit = getDigit(hnum * 10);
    int i, j, k;

    for (i=0; i<line; i++) {
        printf("%d:\t", i);
        for (j=0; j<10; j++) {
            int dataNum = i * 10 + j;
            if (hnum > dataNum) {
                for (k=0; k<(digit - getDigit(data[dataNum])); k++) {
                    printf(" ");
                }
                printf("%d  ", data[dataNum]);
            }
        }
        printf("\n");
    }
}

int getDigit(int num) {
    int digit = 1;
    num = num / 10;
    while (num) {
        num = num / 10;
        digit++;
    }
    return digit;
}

void make_data_random(int *data, int hnum) {
    int i;
    for (i=0; i<hnum; i++) {
        data[i] = rand() % (hnum * 10) + 1;
    }
}

void quick_sort(int *data, int hnum) {
    if (hnum <= 1) {
        return;
    }

    int small[hnum];
    int big[hnum];
    int pivot = data[0];
    int i, j;
    int smallNum = 0, bigNum = 0, sameNum = 0;

    for (i=0; i<hnum; i++) {
        if (data[i] < pivot) {
            small[smallNum] = data[i];
            smallNum++;
        } else if (data[i] > pivot) {
            big[bigNum] = data[i];
            bigNum++;
        } else {
            sameNum++;
        }
    }
    
    quick_sort(small, smallNum);
    quick_sort(big, bigNum);

    {
        i = 0;
        for (j=0; j<smallNum; j++) {
            data[i] = small[j];
            i++;
        }
        for (j=0; j<sameNum; j++) {
            data[i] = pivot;
            i++;
        }
        for (j=0; j<bigNum; j++) {
            data[i] = big[j];
            i++;
        }
    }

}
