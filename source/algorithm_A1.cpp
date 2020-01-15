#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;
ofstream OUTfile ("final1.path");
#define height 5
#define width 6

typedef struct Pair{
    bool BeOccupy = false; //who is occupied by enemy
}Pair;

typedef struct WinPoint{
    bool occupy = false; //the next step enemy will win the game
    int numbers = 0;  
    int eatnumber = 0;  //the next step enemy will eat cell
    Pair point[height][width];
}WinPoint;


Board tmp;

int predict(Board tmp,Board original,Player enemy,int row,int col,int num){
    int Color = enemy.get_color();
    int attack = 0;
    for(int i = 0;i<height;i++){
        for(int j = 0; j<width;j++){
            if(tmp.get_cell_color(i,j) == Color){
                tmp.place_orb(i,j,&enemy);
                if(tmp.win_the_game(enemy)){
                    attack+=100;
                }
                if(tmp.get_cell_color(i,j) != original.get_cell_color(i,j) || tmp.get_orbs_num(i,j) != original.get_orbs_num(i,j)){
                    attack++;
                }
            }
        }
    }  
    return attack;
}

bool isMyCorner(Board board,Board tmp,Player player,Player enemy,int row,int col){
    if(board.get_cell_color(row,col) == enemy.get_color() && tmp.get_cell_color(row,col) == player.get_color()){
        return true;
    }
    
    return false;
}

void algorithm_A1(Board board, Player player, int index[]){
    static int firststep;
    int score[height][width];
    WinPoint Enemy[height][width];
    int color;
    int enemy_color;
    int initial_r = 0;
    int initial_c = 0;

    Player *enemy; //敵人
    if(player.get_color() == RED){
        enemy = new Player(BLUE);
        enemy_color = BLUE;
    }
    else {
        enemy = new Player(RED);
        enemy_color = RED;
    }

    color = player.get_color();


    //first: 判斷能不能贏
    for(int i = 0;i<height;i++){
        for(int j =0;j<width;j++){
            score[i][j] = 0;
            tmp = board;
            if(board.get_cell_color(i,j) != enemy_color){
                initial_r = i;
                initial_c = j;
                tmp.place_orb(i,j,&player);
                if(tmp.win_the_game(player) && firststep!=0){
                    OUTfile<<"rule1"<<endl;
                    index[0] = i;
                    index[1] = j;
                    return ;
                }
            }
        }
    }
    firststep++;
    //second: 那些點會被gameover
    for(int i = 0;i<height;i++){
        for(int j =0;j<width;j++){
            if(board.get_cell_color(i,j) == enemy_color){
                tmp = board;
                Enemy[i][j].numbers = board.get_orbs_num(i,j);
                tmp.place_orb(i,j,enemy);
                if(tmp.win_the_game(*enemy)){
                    Enemy[i][j].occupy = true;
                }
                for(int k = 0;k<height;k++){
                    for(int h = 0;h<width;h++){
                        if(tmp.get_orbs_num(k,h) != board.get_orbs_num(k,h) || tmp.get_cell_color(k,h) != board.get_cell_color(k,h)){
                            Enemy[i][j].point[k][h].BeOccupy = true;
                            Enemy[i][j].eatnumber++;
                        }
                    }
                }
            }
        }
    }

    /*third
    1. 能吃掉敵人重要棋子 (贏的點，會被大量吃掉的點,翻轉點)
    (1)如果下一步會被翻盤 -> 不考慮
    2. 搶角落
    3. 邊
    */
    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
            if(board.get_cell_color(i,j) == color){
                tmp = board;
                tmp.place_orb(i,j,&player);
                for(int k = 0;k<height;k++){
                    for(int h = 0;h<width;h++){
                        //佔領的點數量
                        if(tmp.get_orbs_num(k,h) != board.get_orbs_num(k,h) || tmp.get_cell_color(k,h)!= board.get_cell_color(k,h)){
                            score[i][j] ++;
                        }

                        //邊
                        /*
                        if(k>0 && k<height-1){
                            if(h==0 || h == 5){
                                score[i][j] ++;
                            }
                        }
                        if(h>0 && h<width-1){
                            if(k == 0 || k == 4){
                                score[i][j] ++;
                            }
                        }*/
                        

                        //角落佔領分數
                        if(k==0 &&  h==0 && isMyCorner(board,tmp,player,*enemy,0,0) && board.get_cell_color(0,0) == enemy_color){
                            score[i][j] += 5;
                        }
                        if(k == 0 && h == 5 && isMyCorner(board,tmp,player,*enemy,0,5) && board.get_cell_color(0,5) == enemy_color){
                            score[i][j] += 5;
                        }
                        if(k == 4 && h == 0 && isMyCorner(board,tmp,player,*enemy,4,0) && board.get_cell_color(5,0) == enemy_color){
                            score[i][j] += 5;
                        }
                        if(k == 4 && h == 5 && isMyCorner(board,tmp,player,*enemy,4,5) && board.get_cell_color(4,5) == enemy_color){
                            score[i][j] += 5;
                        }

                         //致命點佔領分數
                        if(board.get_cell_color(k,h) == color){
                            if(Enemy[k][h].occupy == true){
                                score[i][j] += 20;
                            }
                            else {
                                score[i][j] += Enemy[k][h].eatnumber;
                            }
                        }
                        //被翻盤點懲罰
                        score[i][j] -= predict(tmp,tmp,*enemy,i,j,score[i][j]);
                    }
                }
                        
                //搶角落
                if(i == 0 && j== 0 && tmp.get_cell_color(i,j) == 'w'){
                    if(!(tmp.get_cell_color(i,j+1) == enemy_color && tmp.get_orbs_num(i,j+1) == 2)){
                        if(!(tmp.get_cell_color(i+1,j) == enemy_color && tmp.get_orbs_num(i+1,j) == 2)){
                            score[i][j]+=5;
                        }
                    }
                }
                else if(i == 0 && j == 5 && tmp.get_cell_color(i,j) == 'w'){
                    if(!(tmp.get_cell_color(i+1,j) == enemy_color && tmp.get_orbs_num(i+1,j) == 2)){
                        if(!(tmp.get_cell_color(i+1,j-1) == enemy_color && tmp.get_orbs_num(i+1,j-1) == 2)){
                            score[i][j]+=5;
                        }
                    }
                }
                else if(i == 4 && j == 0 && tmp.get_cell_color(i,j) == 'w'){
                    if(!(tmp.get_cell_color(i-1,j) == enemy_color && tmp.get_orbs_num(i-1,j) == 2)){
                        if(!(tmp.get_cell_color(i,j+1) == enemy_color && tmp.get_orbs_num(i,j+1) == 2)){
                            score[i][j]+=5;
                        }
                    }
                }
                else if(i == 4 && j == 5 && tmp.get_cell_color(i,j) == 'w'){
                    if(!(tmp.get_cell_color(i-1,j) == enemy_color && tmp.get_orbs_num(i-1,j) == 2)){
                        if(!(tmp.get_cell_color(i,j-1) == enemy_color && tmp.get_orbs_num(i,j-1) == 2)){
                            score[i][j]+=5;
                        }
                    }
                }

                if(i>0 && i<height-1){
                    if(j==0 || j == 5){
                        score[i][j] += 2;
                    }
                }
                if(j>0 && j<width-1){
                    if(i == 0 || i == 4){
                        score[i][j] +=2;
                    }
                }

               
            }
        }
    }
    int max = score[initial_r][initial_r];
    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
            if(score[i][j] >max){
                //ofile<<"rule2"<<endl;
                index[0] = i;
                index[1] = j;
                OUTfile<<score[i][j]<<endl;
                return ;
            }
        }
    }
    index[0] = initial_r;
    index[1] = initial_c;
    return ;
}