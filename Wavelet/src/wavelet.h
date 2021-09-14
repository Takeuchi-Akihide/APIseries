/* chain.h
 *  Created on: 2021/09/13
 *      Author: a_takeuchi
 */

#ifndef WAVELET_H_
#define WAVELET_H_

#define GOODS_NUM   5
#define MAX_SIZE    30

typedef struct Chara {
    char          p;
    unsigned int  bit;
    struct Chara  *next;
} Chara_T;

typedef struct Node {
    unsigned long long  key;
    int                 cnt;
    struct Node         *left;
    struct Node         *right;
} Node_T;

void make_key(unsigned int bit, Node_T *node, int depth);
unsigned int bit_check(Chara_T *chara_pointer, char p);
void new_node (Node_T *node, int depth);
int int_log2(unsigned int num);
void new_chara(Chara_T *chara_pointer, char str, unsigned int i);
void print_chara(Chara_T *chara_pointer);
void print_node(Node_T *node_pointer);
void print_key(unsigned long long key, int cnt);

#endif /* WAVELET_H_ */
