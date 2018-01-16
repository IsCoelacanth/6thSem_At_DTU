import random #for randomly selecting a non corner/ empty cell

#Board Class/Data structure
#Hold the board and the printer function
class Board(object):
    def __init__(self):
        self.board = [[2,2,2,],[2,2,2],[2,2,2]]
        self.empty = [1,2,3,4,5,6,7,8,9]
        self.noncorner = [2,4,6,8]

    def DispBoard(self):
        print()
        for i in range(3):
            for j in range(3):
                if (self.board[i][j] == 3):
                    ch = 'X'
                elif (self.board[i][j] == 5):
                    ch = 'O'
                else:
                    ch = '-'
                print('| {} |'.format(ch),end='')
            print()
            if(i<2):
                print(' - - - - - - - ')
        print()

#The function class
#contains all functions involved in the AI Technique
class Algos(Board):
    def __init__(self):
        Board.__init__(self)
    
    #Makes blank at n = 3 is turn is odd otherwise 5
    def Go(self, n, turn):
        if(n<0 or n>9):
            print('Invalid index')
        else:
            if(n/3 <= 1):
                self.board[0][(n-1)%3] = 3 if turn%2 != 0 else 5                
            elif(n/3>1 and n/3<=2):
                self.board[1][(n-1)%3] = 3 if turn%2 != 0 else 5
            else:
                self.board[2][(n-1)%3] = 3 if turn%2 != 0 else 5
            self.empty.remove(n)
            if n in self.noncorner:
                self.noncorner.remove(n)

    #returns 5 if center is blank otherwise returns one 
    #of the non corner squares that are empty
    def make2(self):
        if self.board[1][1] == 2:
            return 5
        else:
            sel = random.choice(self.noncorner)
            return sel
    
    #Utility funtion that returns a column 
    def column(self,i):
        return [col[i] for col in self.board]

    #Checks if X/O can win in this turn, if yes 
    #returns the winning position otherwise 0
    def poswin(self, turn):
        prod = 1

        #Check Rows
        for i in range(3):
            prod = 1
            for j in range(3):
                prod *= self.board[i][j];
            try:
                IndTwo = self.board[i].index(2)
                if(turn%2 == 0 and prod == 50):
                    return (i*3+IndTwo+1)
                elif(turn%2 == 1 and prod == 18):
                    return (i*3+IndTwo+1)
            except:
                pass

        #Check Columns
        for i in range(3):
            prod = 1;
            for j in range(3):
                prod *= self.board[j][i];
            col = self.column(i)
            try:
                IndTwo = col.index(2)
                if(turn%2 == 0 and prod == 50):
                    return (i+IndTwo*3+1)
                elif(turn%2 == 1 and prod == 18):
                    return (i+IndTwo*3+1)
            except:
                pass

        #Check Diagonal 1
        prod = 1
        diag1 = [self.board[0][0],self.board[1][1],self.board[2][2]]
        for i in range(3):
            prod *= diag1[i] 
        try:
            IndTwo = diag1.index(2)
            if(turn%2 == 0 and prod == 50):
                return (IndTwo*4+1)
            elif(turn%2 == 1 and prod == 18):
                return (IndTwo*4+1)
        except:
            pass

        #Check Diagonal 2
        prod = 1
        diag2 = [self.board[0][2],self.board[1][1],self.board[2][0]]
        for i in range(3):
            prod *= diag2[i] 
        try:
            IndTwo = diag2.index(2)
            if(turn%2 == 0 and prod == 50):
                return (IndTwo*2+3)
            elif(turn%2 == 1 and prod == 18):
                return (IndTwo*2+3)
        except:
            pass

        return 0


class Game(Algos):
    def __init__(self):
        Algos.__init__(self)
        self.blnk = []

    def CheckWin(self,turn):
        prod = 1

        #Check Rows
        for i in range(3):
            prod = 1
            for j in range(3):
                prod *= self.board[i][j];
            if(turn%2 == 0 and prod == 125):
                return -1
            elif(turn%2 == 1 and prod == 27):
                return -1

        #Check Columns
        for i in range(3):
            prod = 1;
            for j in range(3):
                prod *= self.board[j][i];
            if(turn%2 == 0 and prod == 125):
                return -1
            elif(turn%2 == 1 and prod == 27):
                return -1

        #Check Diagonal 1
        prod = 1
        diag1 = [self.board[0][0],self.board[1][1],self.board[2][2]]
        for i in range(3):
            prod *= diag1[i] 
        if(turn%2 == 0 and prod == 125):
            return -1
        elif(turn%2 == 1 and prod == 27):
            return -1

        #Check Diagonal 2
        prod = 1
        diag2 = [self.board[0][2],self.board[1][1],self.board[2][0]]
        for i in range(3):
            prod *= diag2[i] 
        if(turn%2 == 0 and prod == 125):
            return -1
        elif(turn%2 == 1 and prod == 27):
            return -1
        return 1

    #User Funtion:
    #Checks if users move is valid and calls Go()
    def MakeMove(self, n,turn):
        if n in self.empty:
            self.Go(n,turn)
        else:
            print("Invalid move play again")
            print("Valid available moves : {}".format(self.empty))
            m = int(input("select an empty cell [1-9] : "))
            self.MakeMove(m, turn)          
                            
    #Game Function:
    #Plays the game
    def PlayGame(self,turn):
        
        #Step 1
        if (turn == 1):
            turn = (turn)%2
            
            self.Go(1, turn)
            self.DispBoard()

        #Step 2
        elif (turn == 2):
            turn = (turn)%2
            
            if (self.make2() == 5):
                self.Go(self.make2(),turn)
            else:
                self.Go(1,turn)
            self.DispBoard()

        #Step 3
        elif (turn == 3):
            turn = (turn)%2
            
            if(self.board[2][2] == 2):
                self.Go(9,turn)
            else:
                self.Go(3,turn)
            self.DispBoard()

        #Step 4
        elif (turn == 4):
            turn = (turn)%2
            
            if(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(self.make2(),turn)
            self.DispBoard()

        #Step 5
        elif (turn == 5):
            turn = (turn)%2
            
            if(self.poswin(turn) != 0):
                self.Go(self.poswin(turn),turn)
                return -1
            elif(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(3,turn)
            self.DispBoard()

        #Step 6
        elif(turn == 6):
            turn = (turn)%2
            
            if(self.poswin(turn) != 0):
                self.Go(self.poswin(turn),turn)
                return -1
            elif(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(self.make2(),turn)
            self.DispBoard()
        

        #Step 7
        elif (turn == 7):
            turn = (turn)%2
            
            if(self.poswin(turn) != 0):
                self.Go(self.poswin(turn),turn)
                return -1
            elif(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(random.choice(self.empty),turn)
            self.DispBoard()

        #Step 8
        elif (turn == 8):
            turn = (turn)%2
            
            if(self.poswin(turn) != 0):
                self.Go(self.poswin(turn),turn)
                return -1
            elif(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(random.choice(self.empty),turn)
            self.DispBoard()

        #Step 9
        elif (turn == 9):
            turn = (turn)%2
            
            if(self.poswin(turn) != 0):
                self.Go(self.poswin(turn),turn)
                return -1
            elif(self.poswin(turn+1) != 0):
                self.Go(self.poswin(turn+1),turn)
            else:
                self.Go(random.choice(self.empty),turn)
            self.DispBoard()
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
        G.DispBoard()
        input("Press enter to continue")
    else:
        print("AI Goes first!")
        win = G.PlayGame(1)
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
                    G.DispBoard()
                    break
                G.DispBoard()
                input("Press enter to continue")
            else:
                print("AI's Turn")
                win = G.PlayGame(i+1)
                if (win == -1):
                    print("The AI beat you!")
                    G.DispBoard()
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
                    G.DispBoard()
                    break
                G.DispBoard()
                input("Press enter to continue")
            else:
                print("AI's turn")
                win = G.PlayGame(i+1)
                if (win == -1):
                    print("The AI beat you")
                    G.DispBoard()
                    break
                input("Press enter to continue")
            
if __name__ == '__main__':
    main()
