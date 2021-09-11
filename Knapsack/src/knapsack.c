/* knapsack.c
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 *  AP_H29Autumn_Problem4
 *  ナップザック問題を解くアルゴリズム
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knapsack.h"

Goods_T goods[GOODS_NUM] = {
    {"AMBRELLA",   5,  8,   0},
    {"BEER",       3,  4,   0},
    {"COKE",       2,  3,   0},
    {"DESSERT",    4,  7,   0},
    {"EEPROM",     1,  1,   0},
};

int main(int argc, char **argv) {
    // 変数の初期化
    int maxvalue[MAX_SIZE + 1];
    int choice[MAX_SIZE + 1];
    int k, s, t;
    int tmp_maxvalue;

    for (k=0; k<=MAX_SIZE; k++) {
        maxvalue[k] = 0;
        choice[k] = -1;
    }

    // 動的計画法メイン
    for (s=0; s<GOODS_NUM; s++) {
        for (t=goods[s].size; t<=MAX_SIZE; t++) {
            tmp_maxvalue = maxvalue[t-goods[s].size] + goods[s].value;
            if (tmp_maxvalue > maxvalue[t]) {
                maxvalue[t] = tmp_maxvalue;
                choice[t] = s;
            }
        }
    }

    // 結果の出力
    k = MAX_SIZE;
    while (choice[k] >= 0) {
        goods[choice[k]].results++;
        k = k - goods[choice[k]].size;
    }
    for (k=0; k<GOODS_NUM; k++) {
        printf("%s:\t%d\n", goods[k].name, goods[k].results);
    }
    printf("\n");
    printf("totalvalue: %d\n", maxvalue[MAX_SIZE]);
}
