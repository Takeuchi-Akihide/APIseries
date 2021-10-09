# huffman.py
#   Created on: 2021/10/09
#       Author: a_takeuchi
#  AE_R3Spring_Problem3
#  K-means法

import time
import math, random



class P:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def data_dist(self, p_dist):
        return math.sqrt((self.x - p_dist.x) ** 2 + (self.y - p_dist.y) ** 2)

class Gravity:
    def __init__(self):
        self.length = 0
        self.x = 0
        self.y = 0
    # def grav_dist(self, p_dist):
    #     return math.sqrt((self.x - p_dist.x) ** 2 + (self.y - p_dist.y) ** 2)

def main():
    N = 20
    K = 3
    p = set_point_xy(N)
    clusters = clustering(p, N, K)

    for t in range(K):
        print("cluster ", t, ":", end="\t")
        for i, s in enumerate(clusters):
            if s == t:
                print(i, end=" ")
        print()

    for i in range(N):
        print(p[i].x, p[i].y)


def set_core_random(p, K):
    p_len = len(p)
    core = random.sample(range(p_len), K)
    return core

def min_index(data):
    min = -1
    for i, datanum in enumerate(data):
        if min == -1 or datanum < min:
            min = datanum
            id = i
    return id

def gravity_xy(p, t, clusters, result):
    count = 0
    x, y = 0, 0
    for num, i in enumerate(clusters):
        if i == t:
            x += p[num].x
            y += p[num].y
            count += 1
    result.x = x / count
    result.y = y / count

def clustering(p, N, K):
    MAX_COUNT = 100
    data_length = [0] * K
    grav_length = [0] * K
    clusters = [0] * N
    grav = []
    for i in range(K):
        grav.append(Gravity())

    core = set_core_random(p, K)
    print(core)
    for s in range(N):
        for t in range(K):
            data_length[t] = p[s].data_dist(p[core[t]])
        clusters[s] = min_index(data_length)

    for i in range(MAX_COUNT):
        print(clusters)
        if i == 0:
            for t in range(K):
                gravity_xy(p, t, clusters, grav[t])
        else:
            flag = False
            for t in range(K):
                grav_tmp = P(0, 0)
                gravity_xy(p, t, clusters, grav_tmp)
                if ((grav_tmp.x != grav[t].x) or (grav_tmp.y != grav[t].y)):
                    grav[t].x = grav_tmp.x
                    grav[t].y = grav_tmp.y
                    flag = True
            if flag == False:
                return clusters

        for s in range(N):
            for t in range(K):
                grav_length[t] = p[s].data_dist(grav[t])
            clusters[s] = min_index(grav_length)

    print("Error")
    return clusters

def set_point_xy(N):
    p = []
    for i in range(N):
        p_x = random.randrange(0, N * 5)
        p_y = random.randrange(0, N * 5)
        p.append(P(p_x, p_y))
    return p

if __name__ == "__main__":
    main()