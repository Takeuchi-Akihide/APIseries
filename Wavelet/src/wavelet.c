/* wavelet.c
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
#include <time.h>
#include "wavelet.h"

/* グローバル変数 */
Wavelet_T wavelet;
Func_Interface_T func[MAX_FUNC] = {
    {   "help",         wavelet_help        },
    {   "access",       wavelet_access      },
    {   "rankall",      wavelet_rank_all    },
    {   "rank",         wavelet_rank        },
    {   "select",       wavelet_select      },
    {   "nodeprint",    print_node          },
    {   "charprint",    print_chara         },
};

int main(int argc, char **argv) {
    int i;
    char str[MAX_STR+1];

    // 引数の受け取り
    if (argc == 1) {
        srand((unsigned) time(NULL));
        for (i=0; i<MAX_STR; i++) {
            str[i] = 'A' + rand() % ALPHA_NUM;
        }
        str[MAX_STR] = '\0';
        printf("%s\n", str);
    } else if (argc == 2) {
        strncpy(str, argv[1], MAX_STR);
    } else {
        fprintf(stderr, "文字列を1つ入力してください\n");
        return EXIT_FAILURE;
    }

    // 文字の種類の数をカウント
    int str_len = 0;
    unsigned int cnt = 0;
    Chara_T *chara_start = calloc(1, sizeof(Chara_T));
    Chara_T *chara_pointer = chara_start;
    Chara_T *chara_last;

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

    // グローバル変数に登録
    wavelet.node_start = node_start;
    wavelet.chara_start = chara_start;
    wavelet.len = str_len;
    wavelet.depth = depth;

    while (1) {
        char input[32];
        printf("操作を入力してください。\n'help' -> 操作一覧を表示します\n");
        scanf("%31s", input);

        if (strncmp(input, "q", 32) == 0) {
            return 0;
        } else if (isdigit(input[0])) {
            int inputNum = (int) strtol(input, NULL, 10);
            if (inputNum >= 0 && inputNum < MAX_FUNC) {
                func[inputNum].Func1();
            }
        } else {
            for (i=0; i<MAX_FUNC; i++) {
                if (strncmp(input, func[i].FuncName, 32) == 0){
                    func[i].Func1();
                }
            }
        }
    }
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
            if (count_key(nodep->key_node, i, b)){
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

unsigned int count_key(Key_T *key_node, int i, unsigned int b) {
    Key_T *node = key_node;
    int times = i / KEY_MAX;
    i = i % KEY_MAX + 1;

    for (int j=0; j<times; j++) {
        node = node->next;
    }
    return b == ((node->key >> (node->count - i)) & 1);
}

void make_key(unsigned int bit, Node_T *node, int depth) {
    if (depth > 0) {
        unsigned int key_bit = (bit >> (depth - 1)) & 1;
        key_increment(node->key_node, key_bit);
        node->cnt++;
        if (key_bit) {
            make_key(bit, node->right, depth - 1);
        } else {
            make_key(bit, node->left, depth - 1);
        }
    }
}

// 1つ目のノードに0-31, 2つ目に32-63…が入る。
// 各ノードの中では、最上位ビットが0、最下位ビットが31を表す。
void key_increment(Key_T *key_node, unsigned int key_bit) {
    Key_T *node = key_node;
    while (node->next) {
        node = node->next;
    }
    node->key = (node->key << 1) + key_bit;
    node->count++;

    if (node->count == KEY_MAX) {
        node->next = calloc(1, sizeof(Key_T));
        node->next->prev = node;
        // key_prev->next = key_node;
        // key_node = key_prev;
    }
    // return key_node;
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
        Key_T *node_key = calloc(1, sizeof(Key_T));

        new_node(node_left, depth-1);
        new_node(node_right, depth-1);

        node->left = node_left;
        node->right = node_right;
        node->left->parent = node;
        node->right->parent = node;
        node->key_node = node_key;
    } else {
        node->key_node = calloc(1, sizeof(Key_T));
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

int print_chara(void) {
    Chara_T *pointer = wavelet.chara_start;
    while (pointer) {
        printf("pointer: %p\n", pointer);
        printf("p: %c\n", pointer->p);
        printf("bit: %d\n", pointer->bit);
        printf("next: %p\n", pointer->next);
        pointer = pointer->next;
    }
}

int print_node(void) {
    print_node_roop(wavelet.node_start);
}

void print_node_roop(Node_T *node_pointer) {
    if (node_pointer == NULL) {
        return;
    }
    Node_T *pointer = node_pointer;
    printf("pointer: %p\n", pointer);
    print_key(pointer->key_node, pointer->cnt);
    printf("parent: %p\n", pointer->parent);
    printf("left: %p\n", pointer->left);
    printf("right: %p\n", pointer->right);
    print_node_roop(pointer->left);
    print_node_roop(pointer->right);
}

void print_key(Key_T *key_node, int cnt) {
    int times = cnt / KEY_MAX;
    cnt = cnt % KEY_MAX;
    printf("key: ");
    for (int i=0; i<=times; i++) {
        if (i == times) {
            for (int j=cnt-1; j>=0; j--) {
                printf("%d", (key_node->key >> j) & 1);
            }
        } else {
            for (int j=KEY_MAX-1; j>0; j--) {
                printf("%d", (key_node->key >> j) & 1);
            }
            key_node = key_node->next;
        }
    }
    printf("\n");
}

int wavelet_help(void) {
    printf("You can use these commands\n");
    for (int i=0; i<MAX_FUNC; i++) {
        printf("%d / %s\n", i, func[i].FuncName);
    }
    printf("q -> exit\n");
}

int wavelet_access(void){
    char input[32];
    while (1) {
        printf("<<<access(i)>>>\n  i番目の値を返します。\n");
        printf("  1以上%d以下の数値を入力してください。\n  数値以外を入力したら終了します。\n->", wavelet.len);
        scanf("%31s", input);
        // printf("input: %s\n", input);
        int inputNum = (int) strtol(input, NULL, 10);
        if (inputNum >= 1 && inputNum <= wavelet.len) {
            // inputのビット番号を求める
            unsigned int bit = get_bitnum(wavelet.node_start, inputNum);

            // ビット番号から文字列を求める
            char c = get_chara(wavelet.chara_start, bit);
            printf("T[%d] = '%c'\n",inputNum, c);
        } else {
            printf("値が存在しません。終了します。\n");
            printf("----------------------------\n\n");
            return 0;
        }
        
    }
}

int wavelet_rank_all(void){
    char input[32];
    while (1) {
        printf("<<<RankAll(i)>>>\n  各文字が1からi番目までに出現する回数を返します。\n");
        printf("  iを1以上%d以下の数値で入力してください。\n  数値以外を入力したら終了します。\n->", wavelet.len);
        scanf("%31s", input);
        int inputNum = (int) strtol(input, NULL, 10);
        if (inputNum < 1 || inputNum > wavelet.len) {
            printf("値が存在しません。終了します。\n");
            printf("----------------------------\n\n");
            return 0;
        }

        Chara_T *chara_pointer = wavelet.chara_start;
        while (chara_pointer) {
            int num = count_pnum(wavelet.node_start, inputNum, chara_pointer->bit, wavelet.depth);
            printf("%c:\t%d\n", chara_pointer->p, num);        
            chara_pointer = chara_pointer->next;
        }
    }
}


int wavelet_rank(void) {
    char input[32];
    while (1) {
        printf("<<<Rank(c, i)>>>\n  1からi番目までにcが出現する回数を返します。\n");
        printf("  iを1以上%d以下の数値で入力してください。\n  数値以外を入力したら終了します。\n->", wavelet.len);
        scanf("%31s", input);
        int inputNum = (int) strtol(input, NULL, 10);
        if (inputNum < 1 || inputNum > wavelet.len) {
            printf("値が存在しません。終了します。\n");
            printf("----------------------------\n\n");
            return 0;
        }
        printf("検索したい文字を1文字入力してください。\n->");
        scanf("%1s", input);

        // 文字からビット番号を求める
        unsigned int bit;
        if ((bit = bit_check(wavelet.chara_start, input[0])) == 0xffffffff) {
            printf("文字が存在しません。数値入力からやり直してください。\n");
            printf("----------------------------\n\n");
            continue;
        }

        // 出現回数を求める
        int num = count_pnum(wavelet.node_start, inputNum, bit, wavelet.depth);
        printf("%c[1:%d] : %d\n", input[0], inputNum, num);
    }
    printf("wavelet_rank\n");
}

int wavelet_select(void){
    char inputStr;
    char input[32];
    while (1) {
        printf("<<<Select(i)>>>\n  指定した文字のn番目の出現位置を返します。\n");
        printf("  文字を1文字指定してください。\n  存在しない文字を入力したら終了します。\n->");
        scanf("%1s", &inputStr);

        // 文字からビット番号を求める
        unsigned int bit;
        if ((bit = bit_check(wavelet.chara_start, inputStr)) == 0xffffffff) {
            printf("文字が存在しません。終了します。\n");
            printf("----------------------------\n\n");
            return 0;
        }
        
        int num = count_pnum(wavelet.node_start, wavelet.len, bit, wavelet.depth);
        printf("  iを1以上%d以下の数値で入力してください。\n  数値以外を入力したら終了します。\n->", num);
        scanf("%31s", input);
        int inputNum = (int) strtol(input, NULL, 10);

        if (inputNum < 1 || inputNum > num) {
            printf("値が存在しません。終了します。\n");
            printf("----------------------------\n\n");
            return 0;
        }

        int position = select_pos(wavelet.node_start, bit, inputNum);
        printf("select[%c, %d] : %d\n", inputStr, inputNum, position);
    }
}

int select_pos(Node_T *node_start, unsigned int bit, int num) {
    int i;
    int depth = wavelet.depth;
    Node_T *node = node_start;
    for (i=depth-1; i>0; i--) {
        if ((bit >> i) & 1) {
            node = node->right;
        } else {
            node =node->left;
        }
    }

    int pos = select_from1Node(node, (bit & 1), num);
    return pos;
}

int select_from1Node(Node_T *node, int bit_now, int num) {
    int num_next = 0;
    int i;
    Key_T *keynode = node->key_node;

    // 取得したいビットがキーノードの何番目にあるか探す
    while (num > 0) {
        for (i=keynode->count-1; i>=0; i--) {
            num_next++;
            if (((keynode->key >> i) & 1) == bit_now) {
                num--;
                if (num == 0) {
                    break;
                }
            }
        }
        keynode = keynode->next;
    }

    // ノードがparentを持っている場合、繰り返す
    if (node->parent) {
        if (node->parent->left == node) {
            return select_from1Node(node->parent, 0, num_next);
        } else {
            return select_from1Node(node->parent, 1, num_next);
        }
    }
    return num_next;
}

unsigned int get_bitnum(Node_T *node_start, int num) {
    unsigned int bit = 0;
    roop_bitcount(node_start, num, &bit);
    return bit;
}

void roop_bitcount(Node_T *node, int num, unsigned int *bit) {
    int i, j;
    int count[2] = {0};     // 0,1の数をそれぞれ入れる
    int bit_now = 0;
    Key_T *keynode = node->key_node;
    num--;
    int times = num / KEY_MAX;
    num = num % KEY_MAX;
    
    for (i=0; i<=times; i++) {
        if (i == times) {
            for (j=1; j<=num+1; j++) {
                bit_now = (keynode->key >> (keynode->count - j)) & 1;
                count[bit_now]++;
            }
            break;
        } else {
            for (j=1; j<=KEY_MAX; j++) {
                bit_now = (keynode->key >> (keynode->count - j)) & 1;
                count[bit_now]++;
            }
        }
        keynode = keynode->next;
    }

    *bit = (*bit << 1) + bit_now;
    if (bit_now) {
        node = node->right;
    } else {
        node = node->left;
    }
    if (node) {
        roop_bitcount(node, count[bit_now], bit);
    }
}

// ビット番号から文字列を求める
char get_chara(Chara_T *chara_start, unsigned int bit) {
    int i;
    Chara_T *chara = chara_start;
    for (i=0; i<bit; i++) {
        chara = chara->next;
    }
    return chara->p;
}
