/* chain.c
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 *  AP_H30Autumn_Problem3
 *  ウェーブレット木
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wavelet.h"


int main(int argc, char **argv) {

    // 引数の受け取り
    if (argc != 2) {
        fprintf(stderr, "文字列を1つ入力してください\n");
        return EXIT_FAILURE;
    }

    // 文字の種類の数をカウント
    char *str = argv[1];
    int str_len = 0;
    unsigned int cnt = 0;
    Chara_T *chara_start = calloc(1, sizeof(Chara_T));
    Chara_T *chara_pointer = chara_start;
    Chara_T *chara_last;
    int i;

    while (str[str_len] != '\0') {
        if (chara_start->p == '\0') {
            chara_start->p = str[str_len];
            chara_start->bit = cnt;
            cnt++;
        } else {
            while (chara_pointer) {
                if (str[str_len] == chara_pointer->p) {
                    break;
                }
                chara_last = chara_pointer;
                chara_pointer = chara_pointer->next;
            }
            if (chara_pointer == NULL) {
                new_chara(chara_last, str[str_len], cnt);
                cnt++;
            }
        }
        str_len++;
        chara_pointer = chara_start;
    }

    // ウェーブレット木の構築
    Node_T *node_start = calloc(1, sizeof(Node_T));
    int depth = int_log2(cnt);
    new_node(node_start, depth-1);

    for (i=0; i<str_len; i++) {
        // pのビット列を探索する
        unsigned int bit = bit_check(chara_start, str[i]);

        // ビット列に応じてノードを潜っていき、keyを更新する
        make_key(bit, node_start, depth);
    }

    // 出現回数をカウントしプリント
    while (chara_pointer) {
        int num = count_pnum(node_start, str_len, chara_pointer->bit, depth);
        printf("%c:\t%d\n", chara_pointer->p, num);        
        chara_pointer = chara_pointer->next;
    }

    // printf("depth=%d\n", depth);
    // print_chara(chara_start);
    // print_node(node_start);
}
int count_pnum(Node_T *node, int len, unsigned int bit, int depth) {
    Node_T *nodep = node;
    int d = 1;
    int n = len;
    unsigned int b;

    while (nodep) {
        int count = 0;
        b = (bit >> (depth - d) & 1);
        for (int i=0; i<n; i++) {
            if (b == (int) ((nodep->key >> i) & 1)) {
                count++;
            }
        }
        if (b == 1) {
            nodep = nodep->right;
        } else {
            nodep = nodep->left;
        }
        n = count;
        d++;
    }
    return n;
}

void make_key(unsigned int bit, Node_T *node, int depth) {
    if (depth > 0) {
        unsigned int key_bit = (bit >> (depth - 1)) & 1;
        node->key = (node->key << 1) + key_bit;
        node->cnt++;
        if (key_bit) {
            make_key(bit, node->right, depth - 1);
        } else {
            make_key(bit, node->left, depth - 1);
        }
    } else {
        // depth=0のときはkeyの更新だけ行う
        // node->key = (node->key << 1) + (bit & 1);
        // node->cnt++;
    }
}

unsigned int bit_check(Chara_T *chara_pointer, char p) {
    Chara_T *chara = chara_pointer;
    while (chara != NULL) {
        if (chara->p == p) {
            return chara->bit;
        }
        chara = chara->next;
    }
    return 0xffffffff;
}

void new_node (Node_T *node, int depth) {
    if (depth > 0) {
        Node_T *node_left = calloc(1, sizeof(Node_T));
        Node_T *node_right = calloc(1, sizeof(Node_T));

        new_node(node_left, depth-1);
        new_node(node_right, depth-1);

        node->left = node_left;
        node->right = node_right;
    }
}

int int_log2(unsigned int num) {
    int n = 0;
    while(num > 1) {
        num = num / 2 + num % 2;
        n++;
    }
    return n;
}

// 新しいノードを作成して後ろに付け加える
void new_chara(Chara_T *chara_pointer, char str, unsigned int i) {
    Chara_T *new = calloc(1, sizeof(Chara_T));
    new->p = str;
    new->bit = i;
    chara_pointer->next = new;
}

void print_chara(Chara_T *chara_pointer) {
    Chara_T *pointer = chara_pointer;
    while (pointer) {
        printf("pointer: %p\n", pointer);
        printf("p: %c\n", pointer->p);
        printf("bit: %d\n", pointer->bit);
        printf("next: %p\n", pointer->next);
        pointer = pointer->next;
    }
}

void print_node(Node_T *node_pointer) {
    if (node_pointer == NULL) {
        return;
    }
    Node_T *pointer = node_pointer;
    printf("pointer: %p\n", pointer);
    print_key(pointer->key, pointer->cnt);
    printf("left: %p\n", pointer->left);
    printf("right: %p\n", pointer->right);
    print_node(pointer->left);
    print_node(pointer->right);
}

void print_key(unsigned long long key, int cnt) {
    printf("key: ");
    for (int i=cnt-1; i>=0; i--) {
        printf("%lld", (key >> i) & 1);
    }
    printf("\n");
}
