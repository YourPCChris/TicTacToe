
package main

import 
(
    "fmt"
)

func main() {
    fmt.Println("We Ball")

    board := getBoard()
    playerOne := getPlayer(1)
    playerTwo := getPlayer(2)

    //playerOne.getID()
    //playerTwo.getID()
    board.outputBoard()

    for !board.gameOver{
        board.takeTurn(&playerOne)
        if !board.gameOver{
            board.takeTurn(&playerTwo)
        }
    }

    fmt.Println("\n")
    fmt.Printf("\t***Winner : %d***\n", board.winner)
    fmt.Println("\n")
}


