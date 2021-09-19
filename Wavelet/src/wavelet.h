/* wavelet.h
 *  Created on: 2021/09/13
 *      Author: a_takeuchi
 */

#ifndef WAVELET_H_
#define WAVELET_H_

// #define MAX_SIZE    30
#define KEY_MAX     32
#define MAX_SIZE     sizeof(int) * 8
// #define MAX_FUNC    10
#define MAX_STR     1000
#define ALPHA_NUM   26

typedef enum {
    HELP,       
    ACCESS,
    RANKALL,
    RANK,
    SELECT,
    NODEPRINT,
    CHARAPRINT,
    MAX_FUNC,
} FUNC_T;

typedef struct Chara_T {
    char            p;
    unsigned int    bit;
    struct Chara_T  *next;
} Chara_T;

typedef struct Key_node {
    unsigned int    key;
    int             count;
    struct Key_node *next;
    struct Key_node *prev;
} Key_T;

typedef struct Node_T {
    Key_T           *key_node;
    int             cnt;
    struct Node_T   *parent;
    struct Node_T   *left;
    struct Node_T   *right;
} Node_T;

typedef struct Wavelet {
    Node_T      *node_start;
    Chara_T     *chara_start;
    int         len;
    int         depth;
} Wavelet_T;

typedef struct Func_Interface {
    char        *FuncName;
    int (*Func1) (void);
} Func_Interface_T;

/* 関数宣言 */

int count_pnum(Node_T *node, int len, unsigned int bit, int depth);
void make_key(unsigned int bit, Node_T *node, int depth);
unsigned int count_key(Key_T *key_node, int i, unsigned int b);
void key_increment(Key_T *key_node, unsigned int key_bit);
unsigned int bit_check(Chara_T *chara_pointer, char p);
void new_node (Node_T *node, int depth);
int int_log2(unsigned int num);
void new_chara(Chara_T *chara_pointer, char str, unsigned int i);
void print_key(Key_T *key_node, int cnt);
void print_node_roop(Node_T *node_pointer);

/* ウェーブレット木操作用の関数 */
int print_chara(void);
int print_node(void);
int wavelet_help(void);
int wavelet_access(void);
int wavelet_rank_all(void);
int wavelet_rank(void);
int wavelet_select(void);
unsigned int get_bitnum(Node_T *node_start, int num);
void roop_bitcount(Node_T *node, int num, unsigned int *bit);
char get_chara(Chara_T *chara_start, unsigned int bit);
int select_pos(Node_T *node_start, unsigned int bit, int num);
int select_from1Node(Node_T *node, int bit_now, int num);

#endif /* WAVELET_H_ */
