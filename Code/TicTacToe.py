# -*- coding: utf-8 -*-
"""
Created on Sun Oct 20 06:03:00 2024

@author: Christopher Bennett
Tic Tac Toe
"""
import time


class square:
    def __init__(self, x, y, content):
        self.x = x
        self.y = y
        self.content = content
    
    
def main():
    keepGoing = True
    print("Tic Tac Toe")
    grid = [[None, None, None], [None, None, None], [None, None, None]]
    
    
    make_grid(grid)
    
    #main game loop
    while (keepGoing == True):
        print("Player One")
        turn = player_one_turn(grid)
        if (turn == 909):
            keepGoing = False
        elif (turn == 0):
            print("Player Two")
            turn = player_two_turn(grid)
            if (turn == 909):
                keepGoing = False

    time.sleep(5)            
    
    return 0


def make_grid(grid):
    print ("Making Grid ...")
    
    for i in range (3):
        for j in range (3):
            gridSquare = square(i, j, "empty")
            grid[i][j] = gridSquare
            #print(i, j)
            
            
   
    output_grid(grid)

    """
    for i in range (3):
        for j in range(3):
            print(grid[i][j].content)
            #print(grid[i][j].x, grid[i][j].y)
            #print(i, j)
            """
            
def output_grid(grid):
    print("Outputing grid...")
    for i in range (3):
        print("\n")
        for j in range (3):
            temp = grid[i][j]
            
            if (temp == None): print("None", end=" ")
            else:
                print("{:^5}".format(temp.content), end=" ")
           #print(i, j)
           
    print("\n")
    
def player_one_turn(grid):
    index = int(input("Enter a number from '0' to '9': "))
    print ("Index: ", index)
    edit_grid(index, 1, grid)
    
    if (check_for_win(grid, 1) == 909):
        print("Player One Has Won!!")
        return 909
    return 0
    
def player_two_turn(grid):
    turnMade = False
    
    while(turnMade == False):
        index = int(input("Enter a number from '0' to '9': "))
        print ("index: ", index)
        if (index < 10 and index > 0): turnMade = True
        
    edit_grid(index, 2, grid)
    
    if (check_for_win(grid, 2) == 909):
        print("Player Two Has Won!!!")
        return 909
    
    return 0
    
def edit_grid(index, player, grid):

    if (index >= 1 and index <= 9):
        if (player == 1): symbol = "O"
        elif (player == 2): symbol = "+"
            
        if (index == 1):
            grid[0][0].content = symbol
        if (index == 2):
            grid[0][1].content = symbol
        if (index == 3):
            grid[0][2].content = symbol
        if (index == 4):
            grid[1][0].content = symbol
        if (index == 5):
            grid[1][1].content = symbol
        if (index == 6):
            grid[1][2].content = symbol
        if (index == 7):
            grid[2][0].content = symbol
        if (index == 8):
            grid[2][1].content = symbol
        if (index == 9):
            grid[2][2].content = symbol   
            

                    
    
    output_grid(grid)
    
def check_for_win(grid, player):
    if (player == 1): symbol = "O"
    if (player == 2): symbol = "+"
    
    #diagonal check
    if (grid[0][0].content == symbol and grid[1][1].content == symbol and grid[2][2].content == symbol):
        return 909
    if (grid[0][2].content == symbol and grid[1][1].content == symbol and grid[2][0].content == symbol):
        return 909
    
    #Horazontal check
    if (grid[0][0].content == symbol and grid[0][1].content == symbol and grid[0][2].content == symbol):
        return 909
    if (grid[1][0].content == symbol and grid[1][1].content == symbol and grid[1][2].content == symbol):
        return 909
    if (grid[2][0].content == symbol and grid[2][1].content == symbol and grid[2][2].content == symbol):
        return 909
    
    #vertical check
    if (grid[0][0].content == symbol and grid[1][0].content == symbol and grid[2][0].content == symbol):
        return 909
    if (grid[0][1].content == symbol and grid[1][1].content == symbol and grid[2][1].content == symbol):
        return 909
    if (grid[0][2].content == symbol and grid[1][2].content == symbol and grid[2][2].content == symbol):
        return 909
    
    return 0
    

    
main()


