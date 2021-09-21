/* huffman.h
 *  Created on: 2021/09/13
 *      Author: a_takeuchi
 */

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

typedef struct Chara {
    char          p;
    unsigned int  bit;
    unsigned int  cnt;
    int           bit_num;
    struct Chara  *next;
    struct Chara  *parent;
    struct Chara  *left;
    struct Chara  *right;
} Chara_T;

void count_bit(Chara_T *pointer);
void new_chara_parent(Chara_T *pointer1, Chara_T *pointer2);
void new_chara(Chara_T *chara_pointer, char str);
void print_chara(Chara_T *pointer);
void print_huffman(Chara_T *chara);
void print_chara_bit(Chara_T *chara_start);
void print_bit (unsigned int bit, int num);
int print_charaToBit(Chara_T *pointer, char *str, int str_len);

#endif /* HUFFMAN_H_ */
