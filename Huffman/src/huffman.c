/* huffman.c
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 *  FE_H31Spring_Problem7
 *  ハフマン符号化
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "huffman.h"


int main(int argc, char **argv) {

    // 引数の受け取り
    if (argc != 2) {
        fprintf(stderr, "文字列を入力してください\n");
        return EXIT_FAILURE;
    }

    char *str = argv[1];
    int str_len = 0;
    int str_kind = 0;
    Chara_T *chara_start = calloc(1, sizeof(Chara_T));
    Chara_T *chara_pointer = chara_start;
    Chara_T *chara_last;
    int i;
    clock_t start = clock();

    while (str[str_len] != '\0') {
        if (chara_start->p == '\0') {
            chara_start->p = str[str_len];
            chara_start->cnt++;
            str_kind++;
        } else {
            while (chara_pointer) {
                if (str[str_len] == chara_pointer->p) {
                    chara_pointer->cnt++;
                    break;
                }
                chara_last = chara_pointer;
                chara_pointer = chara_pointer->next;
            }
            if (chara_pointer == NULL) {
                str_kind++;
                new_chara(chara_last, str[str_len]);
            }
        }
        str_len++;
        chara_pointer = chara_start;
    }

    Chara_T *chara_parent;

    while (1) {
        Chara_T *min[2] = { NULL, NULL };
        chara_pointer = chara_start;
        while (chara_pointer) {
            if (chara_pointer->parent == NULL) {
                if (min[0] == NULL || (chara_pointer->cnt < min[0]->cnt)) {
                    min[1] = min[0];
                    min[0] = chara_pointer;
                } else if (min[1] == NULL || (chara_pointer->cnt < min[1]->cnt)) {
                    min[1] = chara_pointer;
                }
            }
            chara_pointer = chara_pointer->next;
        }
        if (min[1] != NULL) {
            new_chara_parent(min[0], min[1]);
        } else {
            chara_parent = min[0];
            break;
        }
    }

    count_bit(chara_parent);
    print_chara_bit(chara_start);
    int bitcount = print_charaToBit(chara_start, str, str_len);
    clock_t end = clock();
    printf("time: %.9f s\n", (float) (end-start) / CLOCKS_PER_SEC);
    float efficiency = (float) bitcount / (float) str_len;
    printf("%d種類、%d文字の文字列が%dビットで表せました。\n1文字あたり%.2fビットです。\n", str_kind, str_len, bitcount, efficiency);
    // print_chara(chara_start);
    // print_huffman(chara_parent);

}

void count_bit(Chara_T *pointer) {
    if (pointer == NULL) {
        return;
    }
    if (pointer->parent != NULL) {
        Chara_T *parent = pointer->parent;
        if (pointer == parent->left) {
            pointer->bit = parent->bit << 1;
        } else {
            pointer->bit = (parent->bit << 1) + 1;
        }
        pointer->bit_num = parent->bit_num + 1;
    }
    count_bit(pointer->left);
    count_bit(pointer->right);
}

// 新しいノードを作成して間に付け加える
void new_chara_parent(Chara_T *pointer1, Chara_T *pointer2) {
    Chara_T *parent = calloc(1, sizeof(Chara_T));
    pointer1->parent = parent;
    pointer2->parent = parent;
    parent->left = pointer1;
    parent->right = pointer2;
    parent->cnt = pointer1->cnt + pointer2->cnt;
    
    parent->next = pointer1->next;
    pointer1->next = parent;
}

// 新しいノードを作成して後ろに付け加える
void new_chara(Chara_T *chara_pointer, char str) {
    Chara_T *new = calloc(1, sizeof(Chara_T));
    new->p = str;
    new->cnt = 1;
    chara_pointer->next = new;
}

void print_chara(Chara_T *pointer) {
    while (pointer) {
        printf("pointer: %p\n", pointer);
        printf("p: %c\n", pointer->p);
        printf("cnt: %d\n", pointer->cnt);
        printf("next: %p\n", pointer->next);
        printf("parent: %p\n", pointer->parent);
        pointer = pointer->next;
    }
}

void print_huffman(Chara_T *chara) {
    if (chara == NULL) {
        return;
    }
    Chara_T *pointer = chara;
    printf("pointer: %p\n", pointer);
    printf("cnt: %d\n", pointer->cnt);
    printf("p: %c\n", pointer->p);
    printf("parent: %p\n", pointer->parent);
    printf("left: %p\n", pointer->left);
    printf("right: %p\n", pointer->right);
    print_huffman(pointer->left);
    print_huffman(pointer->right);
}

void print_chara_bit(Chara_T *chara_start) {
    Chara_T *pointer = chara_start;
    while(pointer) {
        if (pointer->p) {
            printf("%c:\t", pointer->p);
            print_bit(pointer->bit, pointer->bit_num);
            printf("\n");
        }
        pointer = pointer->next;
    }
}

void print_bit (unsigned int bit, int num) {
    int i;
    for (i=num-1; i>=0; i--) {
        printf("%d", (bit >> i) & 1);
    }
}

int print_charaToBit(Chara_T *chara, char *str, int str_len) {
    Chara_T *pointer;
    int cnt = 0;
    int i;
    for (i=0; i<str_len; i++) {
        pointer = chara;
        while(pointer) {
            if (pointer->p == str[i]) {
                print_bit(pointer->bit, pointer->bit_num);
                cnt += pointer->bit_num;
            }
            pointer = pointer->next;
        }
    }
    printf("\n");
    return cnt;
}