# heapsort.py
#   Created on: 2021/10/06
#       Author: a_takeuchi
#
#   クイックソート

import sys, time
from statistics import median
sys.path.append("../Library/")
from makedata import make_data_random, print_by_10

def main():
    ### データ作成
    # hnum = random.randrange(20, 100)
    hnum = 10000
    data = make_data_random(hnum)
    start_time = time.perf_counter()

    ### プログラム実行
    res = quickSort(data)
    end_time = time.perf_counter()

    ### 出力
    print("data:", hnum)
    print_by_10(data)
    print("\nquick")
    print_by_10(res)
    print(end_time - start_time)

def quickSort(data):
    if len(data) <= 1:
        return data
    
    small, big, same = [], [], []
    dataset = [data[0], data[(0 + len(data)) // 2], data[-0]]
    pivot = median(dataset)

    # small = [i for i in data if i < pivot]
    # big   = [i for i in data if i > pivot]
    # same  = [i for i in data if i == pivot]

    for num in data:
        if num < pivot:
            small.append(num)
        elif num > pivot:
            big.append(num)
        else:
            same.append(num)

    small = quickSort(small)
    big = quickSort(big)
    return small + same + big


if __name__ == '__main__':
    main()
