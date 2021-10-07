import random

def make_data_random(hnum):
    data = []
    for i in range(hnum):
        data.append(random.randrange(0, hnum * 10))
        i += 1
    return data

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