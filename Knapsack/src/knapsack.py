# knapsack.py
#   Created on: 2021/09/11
#       Author: a_takeuchi
#   AP_H29Autumn_Problem4
#   ナップザック問題を解くアルゴリズム

MAX_SIZE  =  30

def main():
    print(__name__)
    maxvalue = []
    choice = []

    for k in range(MAX_SIZE+1):
        maxvalue.append(0)
        choice.append(-1)
    
    goods = make_list()
    goods_num = len(goods)

    # 動的計画法メイン
    for s in range(goods_num):
        t = goods[s].size
        while True:
            tmp_maxvalue = maxvalue[t-goods[s].size] + goods[s].value
            if tmp_maxvalue > maxvalue[t]:
                maxvalue[t] = tmp_maxvalue
                choice[t] = s
            if t == MAX_SIZE:
                break
            t += 1

    # 結果の出力
    k = MAX_SIZE
    while (choice[k] >= 0):
        goods[choice[k]].results += 1
        k = k - goods[choice[k]].size

    for k in range(goods_num):
        print(goods[k].name, ":\t", goods[k].results)
    print("totalvalue:\t", maxvalue[MAX_SIZE])

class GoodsItem:
    def __init__(self, name, size, value):
        self.name = name
        self.size = size
        self.value = value
        self.results = 0


def make_list():
    goods = []
    goods.append(GoodsItem("AMBRELLA", 5, 8))
    goods.append(GoodsItem("BEER",     3, 4))
    goods.append(GoodsItem("COKE",     2, 3))
    goods.append(GoodsItem("DESSERT",  4, 7))
    goods.append(GoodsItem("EEPROM",   1, 1))
    return goods

if __name__ == '__main__':
    main()

