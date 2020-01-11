#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
using namespace std;
ofstream oufile ("final.path");

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.

    ////////////method////////////
    //1. 當有可以gameover的點 優先引爆
    //2. 不下的話會被敵人吃掉很多
    //2. 搶角落
    //3. 如果我的角落旁邊有不同顏色而且2顆了->引爆角落

    //4. 分析主戰場: 
    //std::cout<<"HK";
    srand(time(NULL));
    static int round = 0;
    int row, col;
    int color = player.get_color();
    int enemy_color;
    int occupy = 0;
    int priority[5][6];
    int R = 0;//red numbers
    int B = 0;//green numbers

    memset(priority,0,sizeof(priority));

    Player *enemy; //判斷敵人下一步
    if(player.get_color() == RED){
        enemy = new Player(BLUE);
        enemy_color = BLUE;
    }
    else {
        enemy = new Player(RED);
        enemy_color = RED;
    }

    bool record0[5][6],record1[5][6],record2[5][6],record3[5][6],record4[5][6],record5[5][6],record6[5][6],record7[5][6],record8[5][6],record9[5][6];
    bool record10[5][6],record11[5][6],record12[5][6],record13[5][6],record14[5][6],record15[5][6],record16[5][6],record17[5][6],record18[5][6],record19[5][6];
    bool record20[5][6],record21[5][6],record22[5][6],record23[5][6],record24[5][6],record25[5][6],record26[5][6],record27[5][6],record28[5][6],record29[5][6];
    int record30[5][6] = {0}; //record occupy numbers
    
    for(int a = 0;a<5;a++){
        for(int b = 0;b<6;b++){
            record0[a][b] = false;
            record1[a][b] = false;
            record2[a][b] = false;
            record3[a][b] = false;
            record4[a][b] = false;
            record5[a][b] = false;
            record6[a][b] = false;
            record7[a][b] = false;
            record8[a][b] = false;
            record9[a][b] = false;
            record10[a][b] = false;
            record11[a][b] = false;
            record12[a][b] = false;
            record13[a][b] = false;
            record14[a][b] = false;
            record15[a][b] = false;
            record16[a][b] = false;
            record17[a][b] = false;
            record18[a][b] = false;
            record19[a][b] = false;
            record20[a][b] = false;
            record21[a][b] = false;
            record22[a][b] = false;
            record23[a][b] = false;
            record24[a][b] = false;
            record25[a][b] = false;
            record26[a][b] = false;
            record27[a][b] = false;
            record28[a][b] = false;
            record29[a][b] = false;
            record30[a][b] = 0;
            oufile<<record5[a][b];
        }
        
    }

    Board tmp = board;  //預判用
    Board cur = board;
    
    //check gameover and determine which one is best
    for(int i = 0;i<5;i++){
        for(int j =0;j<6;j++){
            tmp = board;
            if(tmp.get_cell_color(i,j) == color){
                oufile<<tmp.get_cell_color(i,j)<<i<<j<<endl;
                tmp.place_orb(i,j,&player); //假如我下這裡
                //check gameover
            
                for(int k =0;k<5;k++){
                    for(int l=0;l<6;l++){
                        if(tmp.get_orbs_num(k,l) != cur.get_orbs_num(k,l) || tmp.get_cell_color(k,l) != cur.get_cell_color(k,l))
                        {
                            if(tmp.get_cell_color(k,l) == 'r') R++;
                            if(tmp.get_cell_color(k,l) == 'b') B++;
                            occupy++; //共佔領幾個
                            int number = k*6+l; //被感染點
                            int ID = i*6+j; //引爆點
                            switch(number){
                                //record被感染點[引爆點]
                                case 0: record0[i][j] = 1; break;
                                case 1: record1[i][j] = 1; break;
                                case 2: record2[i][j] = 1; break;
                                case 3: record3[i][j] = 1; break;
                                case 4: record4[i][j] = 1; break;
                                case 5: record5[i][j] = 1; break;
                                case 6: record6[i][j] = 1; break;
                                case 7: record7[i][j] = 1; break;
                                case 8: record8[i][j] = 1; break;
                                case 9: record9[i][j] = 1; break;
                                case 10: record10[i][j] = 1; break;
                                case 11: record11[i][j] = 1; break;
                                case 12: record12[i][j] = 1; break;
                                case 13: record13[i][j] = 1; break;
                                case 14: record14[i][j] = 1; break;
                                case 15: record15[i][j] = 1; break;
                                case 16: record16[i][j] = 1; break;
                                case 17: record17[i][j] = 1; break;
                                case 18: record18[i][j] = 1; break;
                                case 19: record19[i][j] = 1; break;
                                case 20: record20[i][j] = 1; break;
                                case 21: record21[i][j] = 1; break;
                                case 22: record22[i][j] = 1; break;
                                case 23: record23[i][j] = 1; break;
                                case 24: record24[i][j] = 1; break;
                                case 25: record25[i][j] = 1; break;
                                case 26: record26[i][j] = 1; break;
                                case 27: record27[i][j] = 1; break;
                                case 28: record28[i][j] = 1; break;
                                case 29: record29[i][j] = 1; break;
                            }
                            record30[i][j] = occupy; //此record紀錄佔領幾個
                            occupy = 0;
                        }
                        int BLUe = 0;
                        for(int s = 0;s<5;s++){
                            for(int d = 0;d<6;d++){
                                if(tmp.get_cell_color(s,d) == enemy_color){
                                    BLUe++;
                                }
                            }
                        }
                        if(BLUe == 0 && round != 0 ){   //when I am win
                            oufile<<"rule1"<<"　"<<i<<" "<<j;
                            index[0] = i;
                            index[1] = j;
                            return;
                        }
                            
                    }
                    R = 0;
                    B = 0;
                        
                }
            }
           
        }
    }
    for(int i =0;i<5;i++){
        for(int j = 0;j<6;j++){
            if(board.get_cell_color(i,j) == color){
                index[0] = i;
                index[1] = j;
                break;
            }
            else{
                index[0] = 0;
                index[1] = 0;
            }

        }
    }   
            //防守
            //如果會被gameover 阻止她
            //如果一定會被吃　在他吃的極限邊緣準備ｆｕｌｌ的點　下次將這點引爆
    //std::cout<<index[0]<<" "<<index[1]<<" ";
    
    for(int i =0;i<5;i++){
        for(int j = 0;j<6;j++){
            tmp = board;
            if(tmp.get_cell_color(i,j) == enemy_color ){
                tmp.place_orb(i,j,enemy);
                //std::cout<<"QQ";
                if(tmp.win_the_game(*enemy)){
                    int ID = i*6+j;
                    /*選一個會炸到此格的並能吃掉最多的格子*/
                    for(int k = 0;k<5;k++){
                        for(int l = 0;l<6;l++){
                            switch(ID){
                                case 0: if(board.get_cell_color(k,l) == color && record0[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }   
                                case 1: if(board.get_cell_color(k,l) == color && record1[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 2: if(board.get_cell_color(k,l) == color && record2[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 3: if(board.get_cell_color(k,l) == color && record3[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 4: if(board.get_cell_color(k,l) == color&& record4[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 5: if(board.get_cell_color(k,l) == color && record5[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 6:if(board.get_cell_color(k,l) == color  && record6[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 7: if(board.get_cell_color(k,l) == color && record7[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 8: if(board.get_cell_color(k,l) == color  && record8[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 9: if(board.get_cell_color(k,l) == color && record9[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 10: if(board.get_cell_color(k,l) == color  && record10[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 11: if(board.get_cell_color(k,l) == color && record11[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 12: if(board.get_cell_color(k,l) == color && record12[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 13: if(board.get_cell_color(k,l) == color && record13[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 14: if(board.get_cell_color(k,l) == color && record14[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 15: if(board.get_cell_color(k,l) == color  && record15[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 16: if(board.get_cell_color(k,l) == color && record16[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 17: if(board.get_cell_color(k,l) == color && record17[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 18: if(board.get_cell_color(k,l) == color && record18[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 19: if(board.get_cell_color(k,l) == color && record19[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 20: if(board.get_cell_color(k,l) == color && record20[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 21: if(board.get_cell_color(k,l) == color && record21[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 22: if(board.get_cell_color(k,l) == color && record22[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 23: if(board.get_cell_color(k,l) == color && record23[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 24: if(board.get_cell_color(k,l) == color && record24[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 25: if(board.get_cell_color(k,l) == color && record25[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 26: if(board.get_cell_color(k,l) == color && record26[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 27: if(board.get_cell_color(k,l) == color && record27[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 28: if(board.get_cell_color(k,l) == color && record28[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                                case 29: if(board.get_cell_color(k,l) == color && record29[k][l] == 1 && record30[k][l] > record30[index[0]][index[1]]){
                                    index[0] = k;
                                    index[1] = l;
                                    break;
                                }
                            }
                        }
                            
                    }
                    //std::cout<<"MM";
                    if(index[0]*6+index[1] != ID){
                        oufile<<"rule2"<<" "<<index[0]<<" "<<index[1]<<endl;
                        return;
                    }
                    //std::cout<<"TT";
                }
            }
        }
    }

    tmp = board;

    //check whether the corner will be occupyied
    if(board.get_cell_color(0,0) == color){
        if(board.get_cell_color(0,1) == enemy_color){
            if(board.get_orbs_num(0,1) == 2){
                
                index[0] = 0;
                index[1] = 0;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
        else if(board.get_cell_color(1,0) == enemy_color){
            if(board.get_orbs_num(1,0) == 2){
               
                index[0] = 0;
                index[1] = 0;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
    }

    else if(board.get_cell_color(0,5) == color){
        if(board.get_cell_color(0,4) ==enemy_color){
            if(board.get_orbs_num(0,4) == 2){
                
                index[0] = 0;
                index[1] = 5;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
        else if(board.get_cell_color(1,5) ==enemy_color){
            if(board.get_orbs_num(1,5) == 2){
                
                index[0] = 0;
                index[1] = 5;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
    }

    else if(board.get_cell_color(4,0) == color){
        if(board.get_cell_color(3,0) == enemy_color){
            if(board.get_orbs_num(3,0) == 2){
                
                index[0] = 4;
                index[1] = 0;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
        else if(board.get_cell_color(4,1) ==enemy_color){
            if(board.get_orbs_num(4,1) == 2){
                
                index[0] = 4;
                index[1] = 0;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
    }

    else if(board.get_cell_color(4,5) == color){
        if(board.get_cell_color(3,5) == enemy_color){
            if(board.get_orbs_num(3,5) == 2){
                
                index[0] = 4;
                index[1] = 5;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
        else if(board.get_cell_color(4,4) == enemy_color){
            if(board.get_orbs_num(4,4) == 2){
                
                index[0] = 4;
                index[1] = 5;
                oufile<<"rule3"<<" "<<index[0]<<" "<<index[1]<<endl;
                return;
            }
        }
    }
    //搶角落
    if(board.get_cell_color(0,0) == 'w'){
        if(!((board.get_cell_color(0,1) == enemy_color && board.get_orbs_num(0,1) == 2) || (board.get_cell_color(1,0) ==enemy_color && board.get_orbs_num(1,0)== 2))){
            
            index[0] = 0;
            index[1] = 0;
            oufile<<"rule4"<<" "<<index[0]<<" "<<index[1]<<endl;
            return;
        }
    }
    else if(board.get_cell_color(0,5) == 'w'){
        if(!((board.get_cell_color(0,4) ==enemy_color && board.get_orbs_num(0,4) == 2) || (board.get_cell_color(1,5) ==enemy_color && board.get_orbs_num(1,5)== 2)) ){
            
            index[0] = 0;
            index[1] = 5;
            oufile<<"rule4"<<" "<<index[0]<<" "<<index[1]<<endl;
            return;
        }
    }
    else if(board.get_cell_color(4,0) == 'w'){
        if(!((board.get_cell_color(3,0) ==enemy_color && board.get_orbs_num(3,0) == 2) || (board.get_cell_color(4,1) ==enemy_color && board.get_orbs_num(4,1)== 2)) ){
            
            index[0] = 4;
            index[1] = 0;
            oufile<<"rule4"<<" "<<index[0]<<" "<<index[1]<<endl;
            return;
        }
    }
    else if(board.get_cell_color(4,5) == 'w'){
        if(!((board.get_cell_color(3,5) ==enemy_color && board.get_orbs_num(3,5) == 2) || (board.get_cell_color(4,4) ==enemy_color && board.get_orbs_num(4,4) == 2)) ){
            
            index[0] = 4;
            index[1] = 5;
            oufile<<"rule4"<<" "<<index[0]<<" "<<index[1]<<endl;
            return;
        }
    }

    //OO X
    //X  
    int max = 0;
    int max_row;
    int max_col;
    for(int m=0;m<5;m++){
        for(int n=0;n<6;n++){
            if(board.get_cell_color(m,n) == color){
                if(record0[m][n] == 1 && board.get_cell_color(0,0) == enemy_color) priority[m][n]+=2;
                if(record5[m][n] == 1 && board.get_cell_color(0,5) == enemy_color) priority[m][n]+=2;
                if(record24[m][n] == 1 && board.get_cell_color(4,0) == enemy_color) priority[m][n]+=2;
                if(record29[m][n] == 1 && board.get_cell_color(4,5) == enemy_color) priority[m][n]+=2;
                //if(record0[m][n] == 1 && record5[m][n] == 1 && record24[m][n] == 1 && record29[m][n] == 1) priority[m][n] +=5;
                if((record0[m][n] == 1 && board.get_cell_color(0,0) == enemy_color) || (record5[m][n] == 1 && board.get_cell_color(0,5) == enemy_color)|| (record24[m][n] == 1 && board.get_cell_color(4,0) == enemy_color)|| (record29[m][n] == 1 && board.get_cell_color(4,5) == enemy_color)){
                    priority[m][n]+=record30[m][n];
                    for(int f = 0;f<5;f++){
                        for(int g = 0;g<6;g++){
                            oufile<<record5[f][g];
                        }
                    }
                    if(priority[m][n] >= max){
                        index[0] = m;
                        index[1] = n;
                        oufile<<"rule~"<<" "<<index[0]<<" "<<index[1]<<endl;
                        return;
                    }
                }
                else{
                    priority[m][n]+=record30[m][n];
                    if(priority[m][n] >= max){
                        max = priority[m][n];
                        max_row = m;
                        max_col = n;
                    }
                    
                }
            }
            
        }
    }
    for(int m =0;m<5;m++){
        for(int n = 0;n<6;n++){
            tmp = board;
            if(tmp.get_cell_color(m,n) == enemy_color){
                tmp.place_orb(m,n,enemy);
                if(tmp.get_cell_color(max_row,max_col) == enemy_color){
                    index[0] = max_row;
                    index[1] = max_col;
                    oufile<<"rule5"<<" "<<index[0]<<" "<<index[1]<<endl;
                    return ;
                }
            }
            
        }
    }

    //XX XX
    //OO X
    if(board.get_orbs_num(4,4) == 2 && board.get_cell_color(4,4) == color && board.get_orbs_num(4,5)==1 && board.get_cell_color(4,5)==enemy_color){
        
        index[0] = 4;
        index[1] = 4;
        oufile<<"rule6"<<" "<<index[0]<<" "<<index[1]<<endl;
        return;
    }

    //X XX
    //OO X
    else if(board.get_orbs_num(1,0) == 2 && board.get_cell_color(1,0) == color && board.get_orbs_num(0,0)==1 && board.get_cell_color(0,0)==enemy_color){
        
        index[0] = 1;
        index[1] = 0;
        oufile<<"rule7"<<" "<<index[0]<<" "<<index[1]<<endl;
        return;
    }

    //OO X
    //XX X
    else if(board.get_orbs_num(0,4) == 2 && board.get_cell_color(0,4) == color && board.get_orbs_num(0,5)==1 && board.get_cell_color(0,5) == enemy_color){
        
        index[0] = 0;
        index[1] = 4;
        oufile<<"rule8"<<" "<<index[0]<<" "<<index[1]<<endl;
        return;
    }
    //OO XX
    //X  X
    else if(board.get_orbs_num(3,0) == 2 && board.get_cell_color(3,0) == color && board.get_orbs_num(4,0)==1 && board.get_cell_color(4,0) == enemy_color)
        //*1
    for(int i =0;i<5;i++){
        for(int j =0;j<6;j++){
            //full = 3
            if(board.get_orbs_num(i,j) == 2 && board.get_cell_color(i,j) == color){
                //X OO
                //XX XX
                //左邊是邊界
                if(i<4 && i!= 0 && j==1 && board.get_orbs_num(i,j-1) == 1 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1) == 2 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule91"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                    //XX  OO
                    //XXX XX   
                }
                else if(i<3 && j>1 && j<5 && board.get_orbs_num(i,j-1) == 2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1) == 3 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule92"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX  OO
                //XX  X
                else if(i==3 && j>1 && j<5 && board.get_orbs_num(i,j-1) == 2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1) == 2 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 1 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule93"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //OO  XX
                //XX XXX
                if(i<4 && j>1 && j<4 && board.get_orbs_num(i,j+1) == 2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1) == 3 && board.get_cell_color(i+1,j+1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule101"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //OO XX
                //X  XX
                else if(i==3 && j>1 && j<4 && board.get_orbs_num(i,j+1) == 2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1) == 2 && board.get_cell_color(i+1,j+1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 1 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule102"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //OO X
                //XX XX
                else if(i<4 && i!=0 && j==4 && board.get_orbs_num(i,j+1) == 1 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1) == 2 && board.get_cell_color(i+1,j+1) == enemy_color){
                        if(board.get_orbs_num(i+1,j) == 2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule103"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX XXX
                //OO XX
                if(i<4 && j>1 && j<4 && board.get_orbs_num(i,j+1) == 2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i-1,j+1) == 3 &&  board.get_cell_color(i-1,j+1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 2 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule111"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //X  XX
                //OO XX
                else if(i == 1 && j>1 && j<4 && board.get_orbs_num(i,j+1) == 2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i-1,j+1) == 2 && board.get_cell_color(i-1,j+1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 1 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule112"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX XX
                //OO X
                else if(i<4 && j == 4 && board.get_orbs_num(i,j+1) == 1 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i-1,j+1) == 2 && board.get_cell_color(i-1,j+1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 2 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule113"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }

                //X  X
                //OO X
                else if(i==1 && j == 4 && board.get_orbs_num(i,j+1) == 1 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i-1,j+1) == 1 && board.get_cell_color(i-1,j+1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 1 && board.get_cell_color(i-1,j) == enemy_color){
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule114"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }

                //XXX XX
                //XX OO
                if(i<4 && j>1 && j<4 && board.get_orbs_num(i,j-1) == 2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i-1,j-1) == 3 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 2 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule121"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                    //XX XX
                    //X  OO
                else if(i<4 && j==1 && board.get_orbs_num(i,j-1) == 1 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i-1,j-1) == 2 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 2 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule122"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                    //XX X
                    //XX OO   
                else if(i==1 && j>1 && j<4 && board.get_orbs_num(i,j-1) == 2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i-1,j-1) == 1 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 1 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule123"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }

                //X  X
                //X OO
                else if(i==1 && j == 1 && board.get_orbs_num(i,j-1) == 1 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i-1,j-1) == 1 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j) == 1 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule124"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }


                /*//XXX  
                else if(i+2<5 && board.get_cell_color(i+2,j) != color && board.get_cell_color(i+2,j)!= 'w'){
                        //邊界
                    if((j == 0 || j == 5) && board.get_orbs_num(i+2,j) == 2){
                        if(board.get_orbs_num(i+1,j) == 0){
                            index[0] = i;
                            index[1] = j;
                        }
                    }
                    else if(j>0 && j<5 && board.get_orbs_num(i+2,j) == 3){
                        if(board.get_orbs_num(i+1,j) == 0){
                            index[0] = i;
                            index[1] = j;
                        }
                    }
                }*/

            else if(board.get_orbs_num(i,j) == 1 && board.get_cell_color(i,j) == color){
                //O X
                //X X
                if(i == 3 && j == 4 && board.get_orbs_num(i,j+1)==1 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1)==1 && board.get_cell_color(i+1,j+1)== enemy_color ){
                        if(board.get_orbs_num(i+1,j)==1 && board.get_cell_color(i+1,j) == enemy_color ){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule131"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //O 
                //XX XX
                else if(i == 0 && j == 4 && board.get_orbs_num(i,j+1)==0 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1)==2 && board.get_cell_color(i+1,j+1) == enemy_color){
                        if(board.get_orbs_num(i+1,j)==2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule132"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //O XX
                //  XX
                else if(i == 3 && j == 0 && board.get_orbs_num(i,j+1)==2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i+1,j+1)==2 && board.get_cell_color(i+1,j+1) == enemy_color){
                        if(board.get_orbs_num(i+1,j)==0){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule133"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }

                //X   O
                //XX XX
                if(i == 1 && j == 1 && board.get_orbs_num(i,j-1)==1 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1)==2 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j)==2 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule141"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX O
                //XX
                else if(i == 3 && j == 5 && board.get_orbs_num(i,j-1)==2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1)==2 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j)==0){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule142"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //X  O
                //X  X
                else if(i == 3 && j == 1 && board.get_orbs_num(i,j-1)==1 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i+1,j-1)==1 && board.get_cell_color(i+1,j-1) == enemy_color){
                        if(board.get_orbs_num(i+1,j)==1 && board.get_cell_color(i+1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule143"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX  
                //XX  O
                if(i == 1 && j == 5 && board.get_orbs_num(i,j-1)==2 && board.get_cell_color(i,j-1) == enemy_color){
                    if(board.get_orbs_num(i-1,j-1)==1 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j)==0){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule151"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX X
                //  O
                else if(i == 4 && j == 1 && board.get_orbs_num(i,j-1)==0 && board.get_cell_color(i,j-1)==enemy_color){
                    if(board.get_orbs_num(i-1,j-1)==2 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j)==2 && board.get_cell_color(i-1,j) == enemy_color){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule152"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //   XX
                //O  XX
                if(i == 1 && j == 0 && board.get_orbs_num(i,j+1)==2 && board.get_cell_color(i,j+1) == enemy_color){
                    if(board.get_orbs_num(i-1,j+1)==2 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j)==0){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule161"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }
                //XX XX
                //O 
                else if(i == 4 && j == 4 && board.get_orbs_num(i,j+1)==0){
                    if(board.get_orbs_num(i-1,j+1)==2 && board.get_cell_color(i-1,j-1) == enemy_color){
                        if(board.get_orbs_num(i-1,j)==0){
                            
                            index[0] = i;
                            index[1] = j;
                            oufile<<"rule162"<<" "<<index[0]<<" "<<index[1]<<endl;
                            return;
                        }
                    }
                }

            }

            }
        }
    }
        //建主戰場
       /*|   |       |   |   |       |(O)    |   |    |
         |XX |OO(O)  |(O)|   |       |       |   |X   |
         |XXX|XX     |   |   |       |XX     |X  |O(O)|X
         |   |       |XXX|   |(O)    |       |   |X   |
         |   |       |   |   |       |       |   |    |*/
    bool random_choose = false;
    for(int i = 0;i<5;i++){
        for(int j = 0;j<6;j++){
            if(board.get_cell_color(i,j) == 'w' || (board.get_cell_color(i,j) == 1 && board.get_cell_color(i,j) == color)){
                random_choose = true;
                break;
            }
        }
    }
    if(!random_choose){
        index[0] = max_row;
        index[1] = max_col;
        oufile<<"rule_final"<<index[0]<<" "<<index[1]<<endl;
        return ;
    }
    while(1){
        //std:oufile<<"KK";
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == 'w' || (board.get_orbs_num(row,col) == 1 && board.get_cell_color(row,col)==color && (row!=0 && col!=0) && (row!=4 && col !=5) && (row!=4 && col !=0)&& (row!=0 && col !=5))){
                    //選未被戰的格子或　填滿某格。
            
            index[0] = row;
            index[1] = col;
            oufile<<"rule17"<<" "<<index[0]<<" "<<index[1]<<endl;
            return;
        }
        
    }
    

    /*
    |   |X  |   |   |X  |   |
    |X  |   |   |   |   |X  |
    |   |   |   |   |   |   |
    |X  |   |   |   |   |X  |
    |   |X  |   |   |X  |   |*/

    /*if(board.get_cell_color(0,0) == 'w') {
        if((board.get_cell_color(0,1) == color && board.get_orbs_num(0,1) == 1)|| (board.get_cell_color(1,0) == color && board.get_orbs_num(1,0) == 1));
        else if(board.get_cell_color(0,1) == 'w' && board.get_cell_color(1,0) == 'w');
        else ;
        index[0] = 0;
        index[1] = 0;
    } 
    
    else if(board.get_cell_color(5,0) == 'w' && (board.get_cell_color(5,1) == color || board.get_cell_color(4,0) == color)){
        index[0] = 5;
        index[1] = 0;
    }

    else if(board.get_cell_color(0,4) == 'w' && (board.get_cell_color(0,3) == color || board.get_cell_color(1,4) == color)){
        index[0] = 0;
        index[1] = 4;
    }

    else if(board.get_cell_color(5,4) == 'w' && (board.get_cell_color(4,4) == color || board.get_cell_color(5,3) == color)){
        index[0] = 5;
        index[1] = 4;
    }*/
    /*while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }*/
}