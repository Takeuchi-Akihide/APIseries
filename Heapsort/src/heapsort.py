# heapsort.py
#   Created on: 2021/10/06
#       Author: a_takeuchi
#
#   ヒープソート

import random

def main():
    # hnum = random.randrange(20, 100)
    hnum = 1000
    data = make_data_random(hnum)
    heap = []
    makeHeap(data, heap, hnum)
    heapSort(heap, hnum)
    print("data:", hnum)
    print_by_10(data)
    print("\nheap")
    print_by_10(heap)

def swap(heap, i, j):
    tmp = heap[i]
    heap[i] = heap[j]
    heap[j] = tmp

def parent(i):
    return int((i - 1) / 2)

def lchild(i):
    return (2 * i + 1)

def rchild(i):
    return (2 * i + 2)

def make_data_random(hnum):
    data = []
    for i in range(hnum):
        data.append(random.randrange(0, hnum * 10))
        i += 1
    return data

def makeHeap(data, heap, hnum):
    for i in range(hnum):
        heap.append(data[i])
        k = i
        while k > 0:
            if heap[k] > heap[parent(k)]:
                swap(heap, k, parent(k))
                k = parent(k)
            else:
                break

def downHeap(heap, hlast):
    n = 0
    while lchild(n) <= hlast:
        tmp = lchild(n)
        if rchild(n) <= hlast:
            if heap[tmp] <= heap[rchild(n)]:
                tmp = rchild(n)
        if heap[tmp] > heap[n]:
            swap(heap, n, tmp)
        else:
            return
        n = tmp

def heapSort(heap, hnum):
    for last in reversed(range(hnum-1)):
        swap(heap, 0, last+1)
        downHeap(heap, last)

def getDigit(num):
    digit = 1
    num = int(num / 10)
    while num > 0:
        num = int(num / 10)
        digit += 1
    return digit

def print_by_10(data):
    num = len(data)
    line = int((num - 1) / 10) + 1
    digit = getDigit(max(data))
    for i in range(line):
        print(i, ":", end="\t")
        for j in range(10):
            dataNum = i * 10 + j
            if num > dataNum:
                for k in range(digit - getDigit(data[dataNum])):
                    print(" ", end="")
                    k += 1
                print(data[dataNum], end="  ")
        print()

if __name__ == '__main__':
    main()
