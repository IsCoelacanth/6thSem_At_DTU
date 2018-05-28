from collections import deque
class Node:
    def __init__(self, id, c):
        self.id = id
        self.cost = c
        self.par = None
        self.or_list = []
        self.and_list = []
    def __gt__(self, other):
        return self.cost > other.cost

def input_graph():
    q = deque()
    Id = input("Enter node id : ")
    tmpcost = int(input("Enter cost : "))
    root = Node(Id, tmpcost)
    q.append(root)
    pathcost = 0
    while(len(q) > 0):
        tmp = q.popleft()
        andnum = int(input("Enter num of nodes in and arc : "))
        for i in range(andnum):
            Id = input("Enter node id : ")
            tmpcost = int(input("Enter cost : "))
            pthcst = int(input("Enter path cost : "))
            nn = Node(Id, tmpcost)
            nn.par = tmp
            tmp.and_list.append((nn, pthcst))
            q.append(nn)

        ornum = int(input("Enter num of nodes in or : "))
        for i in range(ornum):
            Id = input("Enter node id : ")
            tmpcost = int(input("Enter cost : "))
            pthcst = int(input("Enter path cost : "))
            nn = Node(Id, tmpcost)
            nn.par = tmp
            tmp.or_list.append((nn, pthcst))
            q.append(nn)
    return root

def isLeaf(curr):
    return len(curr.and_list) == 0 and len(curr.or_list) == 0

def propagate(curr, dif):
    if dif == 0:
        return
    while(curr.par is not None):
        curr = curr.par
        cur.cost += dif

def main():
    root = input_graph()
    curr = []
    print("Graph : ")
    curr.append((root.cost, root))
    it = 0
    while(len(curr)>0):
        tmp = curr[0][1]
        c = curr[0][0]
        curr = curr[1:]
        # print(len(curr))
        print(tmp.id, ' ', c)
        if len(tmp.and_list) > 0 :
            s = len(tmp.and_list)
            # print('len and ', s)
            cc = 0
            for i in range(s):
                nxt = tmp.and_list[i][0]
                ed_et = tmp.and_list[i][1]
                cc += ed_et
                cc += nxt.cost
                curr.append((nxt.cost, nxt))
            propagate(tmp, cc - tmp.cost)
            tmp.cost = cc
        if len(tmp.or_list) > 0 :
            s = len(tmp.or_list)
            cc = 9999999999999999999
            tpush = Node
            for i in range(s):
                nxt = tmp.or_list[i][0]
                ed_et = tmp.or_list[i][1]
                t_wt = ed_et
                t_wt += nxt.cost
                if t_wt < cc:
                    cc = t_wt
                    tpush = nxt
            curr.append((tpush.cost, tpush))
            propagate(tmp, cc - tmp.cost)
            tmp.cost = cc
        curr = sorted(curr)
    print ('final cost : ', root.cost)

            
main()

    