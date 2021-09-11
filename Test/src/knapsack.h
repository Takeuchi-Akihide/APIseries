/* knapsack.h
 *  Created on: 2021/09/11
 *      Author: a_takeuchi
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#define GOODS_NUM   5
#define MAX_SIZE    30

typedef struct Goods {
    // struct Goods  *next;
    char    *name;
    int     size;
    int     value;
    int     results;
} Goods_T;


#endif /* KNAPSACK_H_ */
