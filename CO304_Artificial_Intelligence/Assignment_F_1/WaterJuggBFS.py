from collections import deque

class state(object):
    def __init__(self, a = None, b = None ):
        self._x = a
        self._y = b

    @property 
    def x(self):
        return self._x 

    @x.setter
    def x(self, X):
        self._x = X

    @property 
    def y(self):
        return self._y

    @y.setter
    def y(self, Y):
        self._y = Y

    def __gt__(self, other):
        return self.x < other.x if self.x != other.x else self.y < other.y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    
    def __hash__(self):
        return hash(self.x+self.y)

    def __str__(self):
        out_x = "X : " + str(self.x)
        out_y = "Y : " + str(self.y)
        return out_x + '\n' + out_y 


# The container i.e Jug capacities :
vol_x = 0; vol_y = 0; goal = 0

def BFS(start, path):
    q = deque()

    # Defing Goal state flag
    G = state(-1, -1)
    # Keep the chain form source to dest to find The shortest path.
    parent_of = {}
    q.append(start)
    parent_of[start] = (start, 0)
    while len(q) > 0:
        top = q.popleft()
        if top.x == goal or top.y == goal:
            G = top
            # print ("Goal Found") # For debugging
            break

        # Rule 1 
        '''
            completly fill J1 
            j1 = (x, y) --> (5, y)
        '''
        if top.x < vol_x :
            child = state(vol_x, top.y)
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 1)
                # print ("Rule used : 1") # For debugging

        # Rule 2
        '''
            completly fill J2
            j2 = (x, y) --> (x, 3)
        '''
        if top.y < vol_y :
            child = state(top.x, vol_y)
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 2)
                # print ("Rule used : 2") # For debugging

        # Rule 3
        '''
            completly empty J1
            j1 = (x, y) --> (0, y)
        '''
        if top.x > 0:
            child = state(0, top.y)
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 3)
                # print ("Rule used : 3") # For debugging

        # Rule 4
        '''
            completly empty J2
            j2 = (x, y) --> (x, 0)
        '''
        if top.y > 0:
            child = state(top.x , 0)
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 4)
                # print ("Rule used : 4") # For debugging

        # Rule 5
        '''
            Add water from J2 to J1 
            j1 = (x, y) --> ( min(5, x+y) , max(0, x + y - 5))
        '''
        if top.y > 0:
            child = state(min(top.x + top.y, vol_x), max(0, top.x + top.y - vol_x))
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 5)
                # print ("Rule used : 5") # For debugging

        # Rule 6
        '''
            Add water from J1 to J2
            j2 = (x, y) --> ( max(0, x+y-3) , min(4, x + y))
        '''
        if top.x > 0:
            child = state(max(0, top.x + top.y - vol_y), min(top.x + top.y, vol_y))
            if child not in parent_of.keys():
                q.append(child)
                parent_of[child] = (top, 6)
                # print ("Rule used : 6") # For debugging
    if G.x == -1 or G.y == -1 :
        return 

    # Retracting the path
    path.append((G,0))
    while parent_of[path[-1][0]][1] != 0 :
        path.append(parent_of[path[-1][0]])

def main():
    global vol_x, vol_y, goal
    vol_x, vol_y = map(int, input("Enter the vols of jugs 1 and 2 : ").split())
    goal = int(input("Enter the target volume : "))
    path = []
    BFS(state(0,0),path)

    if len (path)  == 0:
        print ("No path found to goal state")

    else:
        print ("A path was found of lenth {} :\n".format(len(path)))
        print('-----------------------------------------------------------')
        while len(path) > 0:
            val = path.pop()
            top = val[0]
            rule = val[1]

            if rule == 0 :
                print ("state : {},{}\t|\tGOAL STATE".format(top.x, top.y))
                print('-----------------------------------------------------------')
                continue
            if rule == 1 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Fill JUG 1")
                print('-----------------------------------------------------------')
                continue
            if rule == 2 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Fill JUG 2")
                print('-----------------------------------------------------------')
                continue
            if rule == 3 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Empty JUG 1")
                print('-----------------------------------------------------------')
                continue
            if rule == 4 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Empty JUG 2")
                print('-----------------------------------------------------------')
                continue
            if rule == 5 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Water from JUG 2 to JUG 1")
                print('-----------------------------------------------------------')
                continue
            if rule == 6 :
                print ("state : {},{}\t|\t".format(top.x, top.y), end='')
                print ("Action : Water from JUG 1 to JUG 2")
                print('-----------------------------------------------------------')
                continue

if __name__ == '__main__':
    main()




