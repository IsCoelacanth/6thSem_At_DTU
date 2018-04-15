from queue import PriorityQueue
goal = []
id = 0

def print_as_state(a):
    e = a[0:3]
    b = a[3:6]
    c = a[6:9]
    print(e)
    print(b)
    print(c)
    print()
class Board:
    def __init__(self, state):
        global id
        self.state = state
        self.id = id
        id += 1
    def __hash__(self):
        return self.id 
    def __str__(self):
        a = self.state[0:3]
        b = self.state[3:6]
        c = self.state[6:9]
        o1 = "state = \n" + str(a) + '\n' + str(b) + '\n' + str(c) + '\n'
        o2 = "Cost : " + str(self.cost()) + " ID : " + str(self.id) + '\n'
        return o1 + o2 + '\n'
    
    def cost(self):
        cst = 0
        for i in range(9):
            if self.state[i] != goal[i]:
                cst += 1 
            else:
                cst -= 1
        return cst
    
    def __gt__(self, other):
        # Cost function used : L2 distance
        return self.cost() > other.cost()
    
    def __eq__(self, other):
        for i in range(9):
            if self.state[i] != other.state[i]:
                return False
        return True
    def copy(self):
        cp = Board(self.state)
        cp.id = self.id
        return cp

    def can_move_up(self):
        if self.state.index(0) not in [0,1,2]:
            return True
        return False
    def can_move_down(self):
        if self.state.index(0) not in [6,7,8]:
            return True
        return False
    def can_move_left(self):
        if self.state.index(0) not in [0,3,6]:
            return True
        return False
    def can_move_right(self):
        if self.state.index(0) not in [2,5,8]:
            return True
        return False

    def getmoves(self):
        ind_0 = self.state.index(0)
        move = []
        if self.can_move_up():
            tm = self.state.copy()
            tm[ind_0], tm[ind_0-3] = tm[ind_0-3], tm[ind_0]
            move.append(tm)
        if self.can_move_down():
            tm = self.state.copy()
            tm[ind_0], tm[ind_0+3] = tm[ind_0+3], tm[ind_0]
            move.append(tm)
        if self.can_move_left():
            tm = self.state.copy()
            tm[ind_0], tm[ind_0-1] = tm[ind_0-1], tm[ind_0]
            move.append(tm)
        if self.can_move_right():
            tm = self.state.copy()
            tm[ind_0], tm[ind_0+1] = tm[ind_0+1], tm[ind_0]
            move.append(tm)
        return move
    
    def is_goal(self):
        return self.cost() == -9

def BestFS(start):
    k = 0
    q = PriorityQueue()               
    q.put(start)
    parent_of = {}
    parent_of[tuple(start.state)] = tuple(start.state)
    seen = []
    G = Board([-1,-1,-1,-1,-1,-1,-1,-1,0])
    while not q.empty():
        # k += 1
        top = q.get()
        if top in seen:
            print('looping')
            break
        seen.append(top)
        # print_as_state(top.state)
        if top.is_goal():
            G = top.copy()
            break
        moves = top.getmoves()
        # print(moves)
        # print([i for i in seen])
        for i in moves:
            if Board(i) not in seen and Board(i) not in q.queue:
                q.put(Board(i))
                parent_of[tuple(Board(i).state)] = tuple(top.state)
    if not G.is_goal():
        print("Goal not found")
        return 
    else:
        print("Solution found : ")
        G = tuple(G.state)
        while (1):
            print_as_state(G)
            G = parent_of[G]
            if parent_of[G] == tuple(start.state):
                print_as_state(G)
                break
        print_as_state(tuple(start.state))
    
def main():
    print("Enter the start state : ")
    start = list(map(int, input().split()))
    start = Board(start)
    print("Enter the goal state : ")
    global goal
    goal = list(map(int, input().split()))
    BestFS(start)

main()

