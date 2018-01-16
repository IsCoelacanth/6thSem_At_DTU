import random

class Board(object):

    def __init__(self):
        self.board = [[8, 3, 4], [1, 5, 9], [6, 7, 2]]
        self.moves = { 'x' : [], 'o' : [],}
        self.empty = [1,2,3,4,5,6,7,8,9]
        self.values = { 1:8, 2:3, 3:4,
                        4:1, 5:5, 6:9,
                        7:6, 8:7, 9:2,}
        self.NonCorner = [2,4,6,8]

    def DisplayBoard(self):
        print()
        for i in range(3):
            for j in range(3):
                if ((i*3+j+1) in self.moves['x']):
                    ch = 'X'
                elif ((i*3+j+1) in self.moves['o']):
                    ch = 'O'
                else:
                    ch = ' '
                print("| {} |".format(ch), end='')
            print()
            if(i<2):
                print(' - - - - - - - ')
        print()
    
    def GetKey(self,n):
        for ky, val in self.values.items():
            if val == n:
                return ky

class Rules(Board):
    def __init__(self):
        Board.__init__(self)
    
    def Go(self, N, turn):
        if(N<1 and N>9):
            print("Invalid index!")
        else:
            if(turn%2 == 0):
                self.moves['o'].append(N)
                if N in self.NonCorner:
                    self.NonCorner.remove(N)
                self.empty.remove(N)
            else:
                self.moves['x'].append(N)
                if N in self.NonCorner:
                    self.NonCorner.remove(N)
                self.empty.remove(N)

    def make2(self):
        
        if(5 not in self.moves['x'] and 5 not in self.moves['o']):
            return 5
        else:
            sel = random.choice(self.NonCorner)
            return sel
    
    def PossWin(self,turn):
        
        if(turn%2 == 0):
            check = self.moves['o']
            for i in range(len(check)):
                for j in range(i+1, len(check)):
                    t_sum = self.values[check[i]] + self.values[check[j]]
                    t_diff = 15 - t_sum
                    if(t_diff < 0 or t_diff > 9):
                        continue
                    else:
                        if self.GetKey(t_diff) in self.empty:
                            return self.GetKey(t_diff)
                        else:
                            continue
        else:
            check = self.moves['x']
            for i in range(len(check)):
                for j in range(i+1, len(check)):
                    t_sum = self.values[check[i]] + self.values[check[j]]
                    t_diff = 15 - t_sum
                    if(t_diff < 0 or t_diff > 9):
                        continue
                    else:
                        if self.GetKey(t_diff) in self.empty:
                            return self.GetKey(t_diff)
                        else:
                            continue
        return 0
    
    def CheckWin(self, turn):
        
        if (turn%2 == 0):
            check = self.moves['o']
            for i in range(len(check)):
                for j in range(i+1,len(check)):
                    for k in range(j+1, len(check)):
                        t_s = self.values[check[i]] + self.values[check[j]] + self.values[check[k]]
                        if (t_s == 15):
                            return -1
        if (turn%2 != 0):
            check = self.moves['x']
            for i in range(len(check)):
                for j in range(i+1,len(check)):
                    for k in range(j+1, len(check)):
                        t_s = self.values[check[i]] + self.values[check[j]] + self.values[check[k]]
                        if (t_s == 15):
                            return -1
        return 1
    
class Game(Rules):
    def __init__(self):
        Rules.__init__(self)
    
    def MakeMove(self,N,turn):
        if(N in self.empty):
            self.Go(N,turn)
    
    def PlayGame(self, turn):

        #Turn 1 
        if (turn == 1):
            turn = turn%2
            self.Go(1,turn)
            self.DisplayBoard()
        
        #Step 2
        elif (turn == 2):
            turn = (turn)%2            
            if (5 in self.empty):
                self.Go(5,turn)
            else:
                self.Go(1,turn)
            self.DisplayBoard()

        #Step 3
        elif (turn == 3):
            turn = (turn)%2            
            if(9 in self.empty):
                self.Go(9,turn)
            else:
                self.Go(3,turn)
            self.DisplayBoard()

        #Step 4
        elif (turn == 4):
            turn = (turn)%2            
            if(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                self.Go(self.make2(),turn)
            self.DisplayBoard()

        #Step 5
        elif (turn == 5):
            turn = (turn)%2
            if(self.PossWin(turn) != 0):
                self.Go(self.PossWin(turn),turn)
                return -1
            elif(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                self.Go(3,turn)
            self.DisplayBoard()

        #Step 6
        elif(turn == 6):
            turn = (turn)%2
            
            if(self.PossWin(turn) != 0):
                self.Go(self.PossWin(turn),turn)
                return -1
            elif(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                try:
                    self.Go(self.make2(),turn)
                except:
                    self.Go(random.choice(self.empty),turn)
            self.DisplayBoard()
        

        #Step 7
        elif (turn == 7):
            turn = (turn)%2
            if(self.PossWin(turn) != 0):
                self.Go(self.PossWin(turn),turn)
                return -1
            elif(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                bnk = random.choice(self.empty)
                self.Go(bnk, turn)
            self.DisplayBoard()

        #Step 8
        elif (turn == 8):
            turn = (turn)%2
            
            if(self.PossWin(turn) != 0):
                self.Go(self.PossWin(turn),turn)
                return -1
            elif(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                bnk = random.choice(self.empty)
                self.Go(bnk, turn)
            self.DisplayBoard()

        #Step 9
        elif (turn == 9):
            turn = (turn)%2
            print("Pos win : ",self.PossWin(turn))
            
            if(self.PossWin(turn) != 0):
                self.Go(self.PossWin(turn),turn)
                return -1
            elif(self.PossWin(turn+1) != 0):
                self.Go(self.PossWin(turn+1),turn)
            else:
                bnk = random.choice(self.empty)
                self.Go(bnk, turn)
            self.DisplayBoard()
        return 1

def main():
    print("Welcome to tic-tac-toe!\n")
    x_o = input("\nSelect your sign x/o : ")
    G = Game()
    if x_o == 'o':
        x_o = 0
    else:
        x_o = 1
    print()
    if(x_o == 1):
        print("You go first!")
        move = int(input("Select a cell [1-9] : "))
        G.MakeMove(move,1)
        G.DisplayBoard()
        input("Press enter to continue")
    else:
        print("AI Goes first!")
        win = G.PlayGame(1)
        print()
        input("Press enter to continue")
    
    for i in range(1,9):
        print("Turn {}".format(i+1))
        if (x_o == 1):
            if((i+1)%2 != 0):
                print("Your move!")
                move = int(input("Select a cell [1-9] : "))
                G.MakeMove(move,x_o)
                win = G.CheckWin(x_o)
                if (win == -1):
                    print("You've Beat the AI! congrats!")
                    G.DisplayBoard()
                    break
                G.DisplayBoard()
                input("Press enter to continue")
            else:
                print("AI's Turn")
                win = G.PlayGame(i+1)
                if (win == -1):
                    print("The AI beat you!")
                    G.DisplayBoard()
                    break
                input("Press enter to continue")
        elif(x_o == 0):
            if((i+1)%2 == 0):
                print("Your move!")
                move = int(input("Select a cell [1-9] : "))
                G.MakeMove(move,x_o)
                win = G.CheckWin(x_o)
                if (win == -1):
                    print("You've Beat the AI! congrats!")
                    G.DisplayBoard()
                    break
                G.DisplayBoard()
                input("Press enter to continue")
            else:
                print("AI's turn")
                win = G.PlayGame(i+1)
                if (win == -1):
                    print("The AI beat you")
                    G.DisplayBoard()
                    break
                input("Press enter to continue")
            
if __name__ == '__main__':
    main()