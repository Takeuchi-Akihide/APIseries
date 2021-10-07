# heapsort.py
#   Created on: 2021/10/06
#       Author: a_takeuchi
#
#   マージソート

import sys, time
sys.path.append("../Library/")
from makedata import make_data_random, print_by_10

def main():
    ### データ作成
    # hnum = random.randrange(20, 100)
    hnum = 10000
    data = make_data_random(hnum)
    start_time = time.perf_counter()

    ### プログラム実行
    res = mergeSort(data)
    end_time = time.perf_counter()

    ### 出力
    print("data:", hnum)
    print_by_10(data)
    print("\nmerge")
    print_by_10(res)
    print(end_time - start_time)

def merge(left, right):
    result = []
    i, j = 0, 0
    while(i < len(left)) and (j < len(right)):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    if i < len(left):
        result.extend(left[i:])
    if j < len(right):
        result.extend(right[j:])
    return result

def mergeSort(data):
    if len(data) <= 1:
        return data

    mid = len(data) // 2
    left = mergeSort(data[:mid])
    right = mergeSort(data[mid:])
    return merge(left, right)

if __name__ == '__main__':
    main()
