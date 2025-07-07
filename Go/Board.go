package main

import 
(
    "fmt"
    "strconv"
)


type Board struct {
    row int
    col int
    winner int 
    gameOver bool
    board [][]string
    boardMap map[int]string
}

func getBoard() Board{
    var b Board
    b.gameOver = false
    b.winner = -1
    b.row = 3
    b.col = 3
    b.board = make([][]string, b.row)
    b.boardMap = make(map[int]string)
    
    //Making Board
    count := 1
    for i := range b.board{
        b.board[i] = make([]string, b.col)
        for j := range b.board[i]{
            b.board[i][j] = strconv.Itoa(count)
            b.boardMap[count] = strconv.Itoa(i)+strconv.Itoa(j)
            count ++
        }
    }

    /*
    for key, value := range b.boardMap { 
        fmt.Printf("%d : %s\n", key, value)
    }
    */

    return b
}
 
func (b *Board) outputBoard(){
    for _, v := range b.board{
        fmt.Println("\t", v)
    }
}

func (b *Board) takeTurn(p *Player) {
    var temp string
    var indexStr string 
    fmt.Printf("%d Take your turn(%s): \n", p.id, p.symbol)

    fmt.Scanln(&temp)

    nextMove, err := strconv.Atoi(temp)
    
    if err != nil {
        fmt.Println("Invalid Input -> Enter a number on the board")
        return
    }

    fmt.Println("You entered: ", nextMove)
    indexStr, there:= b.boardMap[nextMove]
    if !there{
        fmt.Println("Invlid Position")
        return 
    }

    row, err := strconv.Atoi(string(indexStr[0]))
    col, err := strconv.Atoi(string(indexStr[1]))
    b.board[row][col] = p.symbol
    b.winner = p.id
    b.outputBoard()

    b.checkForWin()
    if b.gameOver{
        b.winner = p.id
    }

    delete(b.boardMap, nextMove)
}
                    
func (b *Board) checkForWin() {
    board := b.board

    //Check for all columns
    if board[0][0] == board[0][1] && board[0][0] == board[0][2]{
        fmt.Println("Game Over")
        b.gameOver = true
    }else if board[1][0] == board[1][1] && board[1][0] == board[1][2]{
        fmt.Println("Game Over") 
        b.gameOver = true
    }else if board[2][0] == board[2][1] && board[2][0] == board[2][2]{
        fmt.Println("Game Over")
        b.gameOver = true 
    //Check for rows
    }else if board[0][0] == board[1][0] && board[0][0] == board[2][0]{
        fmt.Println("Game Over")
        b.gameOver = true
    }else if board[0][1] == board[1][1] && board[0][1] == board[2][1]{
        fmt.Println("Game Over")
        b.gameOver = true
    }else if board[0][2] == board[1][2] && board[0][2] == board[2][2]{
        fmt.Println("Game Over")
        b.gameOver = true
    //Check for Diagonals
    }else if board[0][0] == board[1][1] && board[0][0] == board[2][2]{
        fmt.Println("Game Over")
        b.gameOver = true
    }else if board[0][2] == board[1][1] && board[1][1] == board[2][0]{
        fmt.Println("Game Over")
        b.gameOver = true
    }
}
