#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;
#define height 5
#define width 6

typedef struct Pair{
    int BeOccupy = 0; //who is occupied by enemy
    int numbers = 0;  
    int eatnumber = 0;  //the next step enemy will eat cell
    int gameover = 0;
    
}Pair;

typedef struct WinPoint{
    bool occupy = false; //the next step enemy will win the game
    int numbers = 0;  
    int eatnumber = 0;  //the next step enemy will eat cell
    bool waste = false;
    bool gameover = false;
    
}WinPoint;

typedef struct playerinfo{
    int cost = 0;
    int eatenemy = 0;
    int score = 0;
    bool waste = false;
    int punish = 0;
    Pair point[height][width];
}playerinfo;

void algorithm_A2(Board board, Player player, int index[]){
    bool isgameover = false;
    static int firststep = 0;
    
    Board tmp;
    int enemy_color;
    int color;
    int gmaeoverNumbers = 0;
    WinPoint Enemy[height][width];
    playerinfo P[height][width];
    int boardconnect[height][width];

    Player *enemy; //敵人
    if(player.get_color() == RED){
        color = RED;
        enemy = new Player(BLUE);
        enemy_color = BLUE;
    }
    else {
        color = BLUE;
        enemy = new Player(RED);
        enemy_color = RED;
    }

    for(int i = 0 ;i<height;i++){
        for(int j = 0;j<width;j++){
            tmp = board;
            if(board.get_cell_color(i,j) != enemy_color){
                tmp.place_orb(i,j,&player);
                for(int k = 0;k<height;k++){
                   for(int h = 0 ;h<width;h++){
                        if(tmp.get_orbs_num(k,h) != board.get_orbs_num(k,h) || tmp.get_cell_color(i,j) != board.get_cell_color(i,j)){
                            boardconnect[k][h] = color;
                        }
                    }
                }
            }
        }
    }  


    //first: 判斷能不能贏
    for(int i = 0;i<height;i++){
        for(int j =0;j<width;j++){
            tmp = board;
            if(board.get_cell_color(i,j) != enemy_color){
                tmp.place_orb(i,j,&player);
                if(tmp.win_the_game(player) && firststep!=0){
                    index[0] = i;
                    index[1] = j;
                    return ;
                }
            }
        }
    }

    //second: 那些點會被gameover
    for(int i = 0;i<height;i++){
        for(int j =0;j<width;j++){
            tmp = board;
            if(board.get_cell_color(i,j) != color){
                tmp.place_orb(i,j,enemy);
                if(tmp.win_the_game(player)&& firststep!=0){
                    isgameover = true;
                    Enemy[i][j].occupy = true;
                }
            }
        }
    }
    firststep++;
    
    //////////////////game start////////////////
    tmp = board;
    //normal status
    if(!isgameover){
        int I,J;
        //cout<<firststep;
        if(firststep < 3){
            //cout<<board.get_orbs_num(0,0);
            if(board.get_orbs_num(0,0) == 0){

                index[0] = 0;
                index[1] = 0;
                return;
            }
            else if(board.get_orbs_num(0,5) == 0){
                //cout<<"BB";
                index[0] = 0;
                index[1] = 5;
                return;
            }
            else if(board.get_orbs_num(4,0) == 0){
                //cout<<"CC";
                index[0] = 4;
                index[1] = 0;
                return ;
            }
            else if(board.get_orbs_num(4,5) == 0){
                //cout<<"dd";
                index[0] = 4;
                index[1] = 5;
                return;
            }
        }
        for(int i = 0 ;i<height;i++){
            for(int j = 0;j<width;j++){
                tmp = board;
                if(board.get_cell_color(i,j) != enemy_color){
                    //cout<<board.get_cell_color(i,j)<<endl;
                    I = i;
                    J = j;
                    tmp.place_orb(i,j,&player);
                    Board tmp1 = tmp;
                    for(int k = 0;k<height;k++){
                        for(int h = 0;h<width;h++){
                            if(tmp.get_cell_color(k,h) == color){
                                P[i][j].eatenemy++;
                                /*if(board.get_orbs_num(k,h) == board.get_capacity(k,h)-1){
                                    P[i][j].score++;
                                }*/
                            }
                        }
                    }

                    //kill enemy beside
                    int kill_enemy = 4;
                    if(i+1<height &&  board.get_cell_color(i+1,j) == enemy_color){
                        int scare = board.get_capacity(i+1,j) - board.get_orbs_num(i+1,j);
                        if(scare < kill_enemy){
                            kill_enemy = scare;
                        }
                    } 
                    if(i-1>=0 && board.get_cell_color(i-1,j) == enemy_color){
                        int scare = board.get_capacity(i-1,j) - board.get_orbs_num(i-1,j);
                        if(scare < kill_enemy){
                            kill_enemy = scare;
                        }
                    }
                    if(j+1<width && board.get_cell_color(i,j+1) == enemy_color){
                       int scare = board.get_capacity(i,j+1) - board.get_orbs_num(i,j+1);
                        if(scare < kill_enemy){
                            kill_enemy = scare;
                        }
                    }
                    if(j-1>=0 && board.get_cell_color(i,j-1) == enemy_color){
                        int scare = board.get_capacity(i,j-1) - board.get_orbs_num(i,j-1);
                        if(scare < kill_enemy){
                            kill_enemy = scare ;
                        }
                    }
                    int my_power;
                    if(board.get_cell_color(i,j) == color){
                        my_power = board.get_capacity(i,j) - board.get_orbs_num(i,j);
                        if(my_power == kill_enemy){
                        
                            P[i][j].score +=3;
                        }
                    }
                    
                    //corn
                    if(i == 0 && j== 0){
                        if(board.get_orbs_num(i,j) == 0){
                            P[i][j].score+=2;
                        }
                    }
                    else if(i == 0 && j == width-1){
                        if(board.get_orbs_num(i,j) == 0){
                            P[i][j].score+=2;
                        }
                    }
                    else if(i == height-1 && j == 0){
                        if(board.get_orbs_num(i,j) == 0){
                            P[i][j].score+=2;
                        }
                    }
                    else if(i == height && j == width-1){
                        if(board.get_orbs_num(i,j) == 0){
                            P[i][j].score+=2;
                        }
                    }
                    
                    //side
                    if(i == 0 && (j<width-1 || j>0)){
                        if(board.get_cell_color(i,j) == 'w'){
                            
                            P[i][j].score++;
                        }
                    }
                    else if(i == height-1 && ( j<width-1 || j>0)){
                        if(board.get_cell_color(i,j) == 'w'){
                            
                            P[i][j].score ++;
                        }
                    }
                    else if(j == 0 && (i>0 || i<height-1)){
                        if(board.get_cell_color(i,j) == 'w'){
                            
                            P[i][j].score ++;
                        }
                    }
                    else if(j == width-1 && (i>0 || i<height-1)){
                        if(board.get_cell_color(i,j) == 'w'){
                           
                            P[i][j].score ++;
                        }
                    }
                    //tmp.print_current_boards();
                    
/////////////////////////enemy turn////////////////////////////////////
                    for(int k = 0;k<height;k++){
                        for(int h = 0;h<width;h++){
                            tmp = tmp1;
                            if(tmp.get_cell_color(k,h) != color){
                                tmp.place_orb(k,h,enemy);
                                if(tmp.win_the_game(*enemy)){
                                    Enemy[i][j].gameover = true;
                                }
                                //tmp.print_current_boards();
                                for(int a = 0;a<height;a++){
                                    for(int b = 0;b<width;b++){
                                        if(tmp.get_cell_color(a,b) == color){
                                            
                                            P[i][j].point[k][h].eatnumber++;
                                        }
                                        if(tmp.get_cell_color(a,b) != color && tmp1.get_cell_color(a,b) == color && tmp1.get_orbs_num(a,b) == tmp1.get_capacity(a,b)-1){
                                            P[i][j].point[k][h].numbers ++;
                                        }
                                        if(a == i && b == j && tmp.get_cell_color(a,b) != color){
                                            P[i][j].point[k][h].numbers++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    int max=0;
                    if(!Enemy[i][j].gameover){
                        for(int k = 0;k<height;k++){
                            for(int h = 0;h<width;h++){
                                int a = P[i][j].point[k][h].eatnumber - P[i][j].eatenemy - P[i][j].point[k][h].numbers*3 ;
                                if(a > max){
                                    P[i][j].punish  = a;
                                    max = a;
                                }
                            }
                        }
                    }
                }
                
            }
        }
        int max = P[I][J].score + P[I][J].punish;
        index[0] = I;
        index[1] = J;
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
                if(board.get_cell_color(i,j) != enemy_color){
                    if(!Enemy[i][j].gameover){
                        P[i][j].score -= P[i][j].punish;
                        if(P[i][j].score > max){
                            index[0] = i;
                            index[1] = j;
                            max = P[i][j].score;
                        }
                    }
                } 
            }
        }
        
        return;
    }
//////////////////////////////defend/////////////////////////////////
    
    else {
        tmp = board;
        ////////把不能清除所有被gameover的點清除
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
                tmp = board;
                if(board.get_cell_color(i,j) != enemy_color){
                    tmp.place_orb(i,j,&player);
                    //找能夠清除所有gameover的點
                    for(int k = 0;k<height;k++){
                        for(int h = 0 ;h<width;h++){
                            if(Enemy[k][h].occupy){
                                if(tmp.get_cell_color(k,h)!= color){
                                    P[i][j].score = -100;
                                }
                            }
                        }
                    }
                }
            }
        }
        int I,J;
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
                tmp = board;
                if(P[i][j].score > 0){
                    I = i;
                    J = j;
                    tmp.place_orb(i,j,&player);
                    if(tmp.get_cell_color(i,j) != board.get_cell_color(i,j)){
                        P[i][j].score ++;
                    }
                    Board tmp1 = tmp;
                    for(int k =0;k<height;k++){
                        for(int h = 0;h<width;h++){
                            tmp = tmp1;
                            if(tmp.get_cell_color(k,h) != color){
                                tmp.place_orb(k,j,enemy);
                                for(int a = 0;a<height;a++){
                                    for(int b = 0;b<width;b++){
                                        if(tmp.get_cell_color(a,b) != tmp1.get_cell_color(a,b) || tmp.get_orbs_num(a,b) != tmp1.get_orbs_num(a,b)){
                                            P[i][j].point[k][h].numbers ++;
                                        }
                                        if(tmp.get_cell_color(a,b) != tmp1.get_cell_color(a,b) && tmp1.get_orbs_num(a,b) == tmp.get_capacity(a,b)-1){
                                            P[i][j].point[k][h].eatnumber ++;
                                        }
                                        if(a == i && b == j && tmp.get_cell_color(a,b) != tmp1.get_cell_color(a,b)){
                                            P[i][j].point[k][h].BeOccupy = true;
                                            P[i][j].waste == true;
                                        }
                                    }
                                }

                                //下下次的ｇａｍｅｏｖｅｒ
                                for(int a =0;a<height;a++){
                                    for(int b = 0;b<width;b++){
                                        tmp.place_orb(i,j,enemy);
                                        if(tmp.win_the_game(*enemy)){
                                            P[i][j].point[k][h].gameover ++; 
                                        }
                                    }
                                }
                            }
                        }
                    }


                    int first = 0;
                    int max;
                    for(int k = 0;k<height;k++){
                        for(int h = 0;h<width;h++){
                            if(!P[i][j].point[k][h].BeOccupy){
                                int a = P[i][j].point[k][h].numbers - P[i][j].point[k][h].eatnumber *3 - P[i][j].point[k][h].gameover*10;
                                if(first == 0) max = a;
                                if(a<max){
                                    P[i][j].punish = a;
                                    max = a;
                                }
                                first ++;
                            }
                        }
                    }
                }
                for(int k =0;k<height;k++){
                    for(int h = 0;h<width;h++){
                        P[i][j].score += P[i][j].punish;
                    }
                }
            }
        }
        int max = P[I][J].score;
        index[0] = I;
        index[1] = J;
        for(int i= 0 ;i<height;i++){
            for(int j = 0;j<width;j++){
                if(!P[i][j].waste){
                    if(P[i][j].score> max){
                        max = P[i][j].score;
                        index[0] = i;
                        index[1] = j;
                    }
                }
            }
        }
        return;
    }
}    