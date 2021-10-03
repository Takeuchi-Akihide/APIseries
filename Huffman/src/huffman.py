# huffman.py
#   Created on: 2021/10/03
#       Author: a_takeuchi
#  FE_H31Spring_Problem7
#  ハフマン符号化

import time

class Huffman:
    def __init__(self, name, freq):
        self.parent = -1
        self.left = -1
        self.right = -1
        self.name = name
        self.freq = freq


def main():
    input = "AAABBAACCABABABABABABABABBBBFFFFFCCCCCAAA"
    start_time = time.perf_counter()
    huffmanArray = make_huffman(input)
    print(input)
    Encode(huffmanArray, input)
    end_time = time.perf_counter()
    print(end_time - start_time)
    # print_huffman(huffmanArray)

def search_chara(c, huffmanArray):
    for n, i in enumerate(huffmanArray):
        if i.name == c:
            return n

def print_bit(n, huffmanArray):
    parent = huffmanArray[n].parent
    if (parent >= 0):
        print_bit(parent, huffmanArray)
        if huffmanArray[parent].left == n:
            print("0", end="")
        else:
            print("1", end="")

def Encode(huffmanArray, input):
    for c in input:
        n = search_chara(c, huffmanArray)
        print_bit(n, huffmanArray)
    print("")

def print_huffman(huffmanArray):
    for i, array in enumerate(huffmanArray):
        print("{0}".format(i), end='\t')
        print("name: {0}".format(array.name), end='\t')
        print("freq:  {0}".format(array.freq), end='\t')
        print("parent: {0}".format(array.parent), end='\t')
        print("left:  {0}".format(array.left), end='\t')
        print("right: {0}".format(array.right), end='\t')
        print("")

def check_appearNum(c, output):
    for num, i in enumerate(output):
        if i.name == c:
            return num
    return -1
    
def new_parent(output, min_freq, min_num):
    new = Huffman("", min_freq[0] + min_freq[1])
    new.left = min_num[0]
    new.right = min_num[1]
    output.append(new)
    output[min_num[0]].parent = len(output) - 1
    output[min_num[1]].parent = len(output) - 1
    return output
    

def make_huffman(input):
    output = []
    for c in input:
        arrayNum = check_appearNum(c, output)
        if arrayNum == -1:
            output.append(Huffman(c, 1))
        else:
            output[arrayNum].freq += 1

    while True:
        min_freq = [-1, -1]
        min_num = [-1, -1]
        for num, array in enumerate(output):
            if array.parent == -1:
                if (min_freq[0] == -1 or array.freq < min_freq[0]):
                    min_freq[1] = min_freq[0]
                    min_freq[0] = array.freq
                    min_num[1] = min_num[0]
                    min_num[0] = num
                elif (min_freq[1] == -1 or array.freq < min_freq[1]):
                    min_freq[1] = array.freq
                    min_num[1] = num
        if min_num[1] != -1:
            new_parent(output, min_freq, min_num)
        else:
            break

    return output

if __name__ == "__main__":
    main()