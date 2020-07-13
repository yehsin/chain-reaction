# Chain Reaction Framework


# A very simple framework of chain reaction using C++ language. 

Apply the knowledge learned form the course of data structure and implement a competitive algorithm for the Critical Mass game.

## Compile Command:
* $g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_A.cpp algorithm_TA.cpp

## Execution: 
* Execute the output file(Mac: a.out, Windows: a.exe)

## Some simple actions that can make your development easier 

### Main program

*  The main data flow is in the chain_reaction.cpp. 
*  The following three lines of code are used to declare the variable board, red player and blue player.<br></br>

![Variable Declaration](/images/002.png)

*  Firstly, the program will call your function which "should" return a board index (i, j).
*  Then the program will call place_orb function to put your orb on the index that obtained from your algorithm.
*  If a players' placement is illegal, the program will terminate immediately and annouce the winner.
*  If a players' last placement dominate the hole board, the program will terminate immediately and annouce the winner.

![Player action](/images/001.png)

### Algorithm_A

*  The algorithm_A.cpp file is where you need to impliment your algorithm.
*  All the constrains and support funcitons is commented in the file, please check the [algorithm_A.cpp](/source/algorithm_A.cpp) for more information.

### Submit

*  All you need to do is complete the algorithm_A.cpp with correct return format.
*  Any other modifies "will not" be compiled in TA's computer.(except algorithm_A.cpp)
*  But we do not restrict you from modifying any part of the framwork. You can do whatever you want to speed up your developement.

### Project Objective:
Apply the knowledge learned from the course of data structures and implement a competitive algorithm for the Critical Mass game.

### Program Description
The gameplay takes place in a 5x6 board of squares. For each cell in the board, we define a critical mass. The critical mass is equal to the number of orthogonally adjacent cells. Therefore, that would be 4 for usual cells, 3 for cells in the edge and 2 for cells in the corner. All cells are initially empty. The Red and the Blue player take turns to place "orbs" of their corresponding colors. Each player can only place an orb of the chosen color either in an empty cell or a cell which already contains the same color orbs. When two or more orbs are placed in the same cell, they stack up. When a cell is loaded with a number of orbs equal to its critical mass, the stack immediately explodes. As a result of the explosion, the cell of explosion loses all orbs and becomes empty. At the same time, an orb is added to each of the orthogonally adjacent cells and all orbs of these orthogonally adjacent cells change color to the color of the orbs of explosion. The explosions might result in overloading of an adjacent cell and the chain reaction of explosion continues until every cell is stable. The winner is the one who eliminates every other player's orbs.
![](https://i.imgur.com/XMJF1Ui.png)
You are to design a competitive algorithm and TAs will integrate your code to act as one of the game players. Your code is evaluated based on whether their code plays the game correctly and how well it plays against predefined bots.

### Program description
1. *Program Flow Chart:*
![](https://i.imgur.com/sRjES7F.png)

2. *Detailed Description:*
分為會被gameover方法與不會被gameover方法一開始對棋盤做資料分析:
（１）有沒有能夠贏的點
（２）會不會被gameover
* 如果不會:
>> (1) 分析自己的分數: 角落額外+2、邊額外+1、能吃掉周遭敵人+3
>> (2) 分析敵人下法: 下完後自己剩的數量–被反吃(被反吃下這點就沒意義了)

* 如果會:
>> (1) 能 不 能 反 制 gameover
>>(2) 可 以 的 話 能 夠 吃 多 少 敵人
