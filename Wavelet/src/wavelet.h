/* chain.h
 *  Created on: 2021/09/13
 *      Author: a_takeuchi
 */

#ifndef WAVELET_H_
#define WAVELET_H_

// #define MAX_SIZE    30
#define KEY_MAX     32
#define MAX_SIZE     sizeof(int) * 8

typedef struct Chara {
    char          p;
    unsigned int  bit;
    struct Chara  *next;
} Chara_T;

typedef struct Key_node {
    unsigned int    key;
    int             count;
    struct Key_node *next;
} Key_T;

typedef struct Node {
    Key_T           *key_node;
    int             cnt;
    struct Node     *left;
    struct Node     *right;
} Node_T;

int count_pnum(Node_T *node, int len, unsigned int bit, int depth);
void make_key(unsigned int bit, Node_T *node, int depth);
unsigned int count_key(Key_T *key_node, int i, unsigned int b);
void key_increment(Key_T *key_node, unsigned int key_bit);
unsigned int bit_check(Chara_T *chara_pointer, char p);
void new_node (Node_T *node, int depth);
int int_log2(unsigned int num);
void new_chara(Chara_T *chara_pointer, char str, unsigned int i);
void print_chara(Chara_T *chara_pointer);
void print_node(Node_T *node_pointer);
void print_key(Key_T *key_node, int cnt);

#endif /* WAVELET_H_ */
