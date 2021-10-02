/* magicsquare.c
 *  Created on: 2021/09/25
 *      Author: a_takeuchi
 *  AP_H28Autumn_Problem3
 *  N*Nの魔法陣を作るプログラム
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magicsquare.h"

int square[N][N];

int main(int argc, char **argv) {
    // 変数の初期化
    int x, y;
    for (y=0; y<N; y++) {
        for (x=0; x<N; x++) {
            square[y][x] = 0;
        }
    }

    make_square();
    print_square();
    
}

void make_square(void) {
    int y = N - 1;
    int x = (N+1)/2 - 1;
    int num = 1;
    square[y][x] = 1;

    while(num < N*N) {
        int yb = y;
        int xb = x;

        if (++y >= N) {
            y = 0;
        }
        if (++x >= N) {
            x = 0;
        }

        if (square[y][x] != 0) {
            y = yb - 1;
            x = xb;
        }

        square[y][x] = ++num;
    }
}

void print_square(void) {
    int x, y;
    for (y=0; y<N; y++) {
        for (x=0; x<N; x++) {
            printf("%d ", square[y][x]);
            if (square[y][x] < 10) {
                printf(" ");
            }
            printf("| ");
        }
        printf("\n");
        for (x=0; x<N; x++) {
            printf("-----");
        }
        printf("\n");
    }
}