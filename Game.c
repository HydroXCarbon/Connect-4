#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

void setup(), check_player(), choose_mode(), draw(), input(), logic(), reset_game(), loop(), random();
void check_Xposition(), check_Yposition(), check_user_continue(), check_round(), reset_game();
void loop(void(*looper)());
int check_result(char), check_around_1(char, int, int, int ,int, int , int, int, int);
int check_condition(int, int, int, int, int, int);
int player, count_round, round_max, user_continue;
char sym, player_win, count_route_sub, count_route_main;
char slot[9][8];
int i, j, k, i_temp, j_temp, count_check;
int height, width, BoxSlot = 9, spaceX , spaceY;
int move, x, y, x1, y2, ytemp;
int player1_score = 0, player2_score = 0;
int mode; 
bool move_y, gameover, endgame_1, endgame_2, user_input, wait_user, loopcheck = true;
struct position_check_1{
        int x0, y0;
        struct position_check_2{
            int route_x[30*3];
            int route_y[30*3];
            int vector[30];
            int priority[30];
            int result;
        }route[100];
}position[9][8][2];

//setup
void setup(){
    mode = 0;
    count_round = 0;
    count_route_main = 0;
    count_route_sub = 0;
    user_continue = 0;
    player_win = 'n';
    wait_user = false;
    user_input = false;
    endgame_1 = false;
    endgame_2 = false;
    gameover = false;
    move_y = false;
    spaceX = BoxSlot;
    spaceY =  BoxSlot-1;
    width = spaceX*6;
    height = spaceY*3;
    x = width/2;
    y = -2;
}

void loop(void(*looper)()){
    while(loopcheck){
        usleep(8000 * 2);
        looper();
        input();
    }
    loopcheck = true;
}

//check which player round
void check_player(){
    if(count_round%2 == 0){
        player = 1;
        sym = 'o';
    } 
    else{
        player = 2; 
        sym = 'x';
    }
}

//player selece mode
void choose_mode(){
    system("cls");
    printf("Choose mode\n");
    printf("1. easy (5x4) 2. normal (7x6) 3. Hard (9x8)");
    //check which mode player choose
    if( mode == 1 ){
        BoxSlot = 5;
        mode = 0;
        loopcheck = false;
        char slot[5][4];
        round_max = 20;
    }
    else if ( mode == 2){
        BoxSlot = 7;
        mode = 0;
        loopcheck = false;
        char slot[7][6];
        round_max = 42;
    }
    else if ( mode == 3){
        BoxSlot = 9;
        mode = 0;
        loopcheck = false;
        char slot[9][8];
        round_max = 72;
    }
}

//create boundary
void draw(){
    //clear old messsage
    system("cls");
    //generate prepare zone
    printf("\n");
    for( j = 1 ; j <= width ; j++ ){
        i = -2;
        if(i == y && j == x){
            printf(" %c",sym);
        }
        else{
            printf(" ");
        }
    }
    //generate box
    printf("\n\n");
    for ( i = 1 ; i <= height ; i++ ){
        for( j = 0 ; j <= width ; j++){
            if( j%6 == 0){
                printf("|");
            }
            else if( i%3 == 0){
                printf("_");
            }
            else{
                x1=(3+j)/6;
                ytemp=(1+i)/3;
                if((slot[x1][ytemp] == 'x' || slot[x1][ytemp] == 'o') 
                    && (j+3)%6 == 0 && (i+1)%3 == 0 ){
                    printf("%c",slot[x1][ytemp]);
                }
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Round : %d\n", count_round);
    printf("Score Player 1 : %d\n", player1_score);
    printf("Score Player 2 : %d\n", player2_score);
}

//random input(testing mode);
void random(){
    int lower = 4, upper = 6, num;
    switch (num = (rand() % (upper - lower + 1)) + lower) {
        case 4:
            if(!gameover){
                move = 1;
            }
            break;
        case 5:
            if(!gameover){
                move = 2;
            }
            break;
        case 6:
            if(!gameover){
                move = 3;
            }
    }
}

//recive realtime input from keyboard 
void input(){
    //detect keyboard input
    if (kbhit()) {
        //recieve input and caculate
        switch (getch()) {
            case 'a': case '4':
                if(!gameover){
                    move = 1;
                }
                break;
            case 's': case '5':
                if(!gameover){
                    move = 2;
                }
                break;
            case 'd': case '6':
                if(!gameover){
                    move = 3;
                }
                break;
            case '1':
                if(gameover){
                    user_continue = 1;
                    user_input = true;
                }
                else if(loopcheck){
                    mode = 1;
                }
                break;
            case '2':
                if(gameover){
                    user_continue = 2;
                    user_input = true;
                }
                else if(loopcheck){
                    mode = 2;
                }
                break;
            case '3':
                if(loopcheck){
                    mode = 3;
                }
        }
    }
}

//move X and Y axis
void logic(){
    sleep(0.01);
    switch (move) {
        case 1:
            x-=6;
            break;
        case 2:
            move_y = true;
            break;
        case 3:
            x+=6;
            break;
        default:
            break;
    }
    //reset move
    move = 0;
}

//reset x axis when go too far
void check_Xposition(){
    if( x > width )
        x = 3;
    else if( x < 3 )
        x = width - 3;
}

//check and reset y axis
void check_Yposition(){
    if( move_y ){
        y = -1;
        y+=3;
        while( y >= 1 ){
            x1=(3+x)/6;
            ytemp=(1+y)/3;
            y2=ytemp+1;
            if( slot[x1][1] == 'x' || slot[x1][1] == 'o'){
                y = -2;
               break;
            }
            if( slot[x1][y2] == 0 && y <= height-3){
                y+=3;
            }
            else{
                slot[x1][ytemp]=sym;
                count_round+=1;
                y = -2;
                break;
            }
        }
    }
    move_y=false;
}

void  check_round(){
    if(count_round == round_max){
        gameover = true;
        endgame_1 = true;
    }
}

//check player score
int check_result(char sym){
    int result = 0, temp_check = 0, posi;
    if( round_max != 72){
        for( i = 1 ; i <= spaceY ; i++ ){  
            for( j = 1 ; j <= spaceX ; j++ ){
                printf("|%c",slot[j][i]);
                if( slot[j][i] != sym ){
                    printf("=pass,");
                   continue;
                }
                if(sym == 'o')
                    posi = 0;
                else if(sym == 'x')   
                    posi = 1;
                position[j][i][posi].x0 = j;
                position[j][i][posi].y0 = i;
                temp_check = ((check_around_1(sym, i, j, posi, i, j, 0, 0, 100))*2)+1;
                printf("=check -> %d ",temp_check);
            }
            printf("|\n");
        }
    }
    return result;
}

//check around target slot
int check_around_1(char player_sym, int x0, int y0, int posi, int i, int j, int check_loop1, int check_loop2, int priority){
    int result = 0;
    if((j <= spaceX &&  j > 0 ) && (i <= spaceY && i > 0) && slot[j][i] == player_sym){
        //1. check left 
        if(slot[j][i] == slot[j-1][i] && slot[j][i] == slot[j-2][i] && (check_loop1 != 5  || check_loop2 == 1)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking left ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j-1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j-2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 4;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 5)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i, j-2, 1, z, priority-1);
            }
        } 
        //2. check top-left 
        else if(slot[j][i] == slot[j-1][i-1] && slot[j][i] == slot[j-2][i-2] && (check_loop1 != 6 || check_loop2 == 2)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking top-left ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j-1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i-1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j-2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i-2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 7;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 6)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i-2, j-2, 2, z, priority-1);
            }
        }
        //3. check top 
        else if(slot[j][i] == slot[j][i-1] && slot[j][i] == slot[j][i-2] && (check_loop1 != 7 || check_loop2 == 3)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking top ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i-1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i-2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 8;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 7)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i-2, j, 3, z, priority-1);
            }
        }
        //4. check top-right
        else if(slot[j][i] == slot[j+1][i-1] && slot[j][i] == slot[j+2][i-2] && (check_loop1 != 8 || check_loop2 == 4)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking top-right ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j+1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i-1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j+2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i-2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 9;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 8)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i-2, j+2, 4, z, priority-1);
            }
        }
        //5. check right 
        else if(slot[j][i] == slot[j+1][i] && slot[j][i] == slot[j+2][i] && (check_loop1 != 1 || check_loop2 == 5)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking right ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j+1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j+2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 6;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 1)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i, j+2, 5, z, priority-1);
            }
        }
        //6. check bottom-right
        else if(slot[j][i] == slot[j+1][i+1] && slot[j][i] == slot[j+2][i+2] && (check_loop1 != 2 || check_loop2 == 6)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking bottom-right ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j+1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i+1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j+2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i+2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 3;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 2)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i+2, j+2, 6, z, priority-1);
            }
        }
        //7. check bottom 
        else if(slot[j][i] == slot[j][i+1] && slot[j][i] == slot[j][i+2] && (check_loop1 != 3 || check_loop2 == 7)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking bottom ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i+1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i+2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 2;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 3)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i+2, j, 7, z, priority-1);
            }
        }
        //8. check bottom-left
        else if(slot[j][i] == slot[j-1][i+1] && slot[j][i] == slot[j-2][i+2] && (check_loop1 != 4 || check_loop2 == 8)){
            if( check_condition(x0, y0, posi, j, i, count_route_main) == 1)
                goto end;
            printf("(%d,%d)checking bottom-left ",j,i);
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j-1;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i+1;
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j-2;
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i+2;
            position[x0][y0][posi].route[count_route_main].priority[count_route_sub] = priority;
            position[x0][y0][posi].route[count_route_main].vector[count_route_sub] = 1;
            count_route_sub +=2;
            for(int z=1; z<=8; z++){
                if(z != 4)
                    position[x0][y0][posi].route[count_route_main].result += 1 + check_around_1( player_sym, x0, y0, posi, i+2, j-2, 8, z, priority-1);
            }
        }
        else
            end:
            result = 0;
            count_route_sub = 0;
            count_route_main++;
    }
    return result;
}

int check_condition(int x0, int y0, int posi, int j, int i, int route){
    int result
        if (position[x0][y0][posi].route[route].priority[count_route_sub]) ;
    return result
}

//initiate reset sequence game
void reset_game(){
    //set all array to 0
    endgame_1 = true;
    for( i = 1 ; i <= spaceY ; i++){
        for( j = 1 ; j <= spaceX ; j++){
            slot[j][i] = 0;
        }
    } 
    user_continue == 0;
    user_input = false;
    endgame_1 = false;
    gameover = false;
}

//check if user want to continue
void check_user_continue(){
    if(gameover){
        printf("Continue ?\n");
        printf("1.Yes    2.No");
        if(player_win == 'o'){
            player1_score ++;
            player_win = 'n';
        }
        else if(player_win == 'x'){
            player2_score ++;
            player_win = 'n';
        }
        if(user_input){
            if( user_continue == 1 ){
                loopcheck = false;
                endgame_2 = true;
                reset_game();
            }
            else if( user_continue == 2 ){
                loopcheck = false;
                endgame_2 = true;
            }
        }
    }
}

//Main function
int main(){
    do{
        //select mode
        loop(choose_mode);
        //setup game
        setup();
        //loop game
        while(!endgame_1){
            usleep(8000 * 2);
            check_player();
            draw();
            //input();
            random();
            logic();
            check_Xposition();
            check_Yposition();  
            check_round();       
        }
        check_result('o');
        user_continue = 2;
 /*       //check_result('x');
        while(!endgame_2){
            usleep(8000 * 2);
            draw();
            check_user_continue();
            input();
        }*/
    }while(user_continue !=2);
    return 0;
}
