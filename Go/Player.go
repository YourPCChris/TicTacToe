
package main

import "fmt"


type Player struct {
    symbol string
    id int 
}

func getPlayer(id int) Player{
    var p Player
    p.id = id
    if id == 1{
        p.symbol = "O"
    }else if id == 2{
        p.symbol = "+"
    }else {
        fmt.Println("Invalid Player ID")
    }
    
    return p
}

func (p *Player) getID(){
    fmt.Printf("Player -> %d\n", p.id)
}


