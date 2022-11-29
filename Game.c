#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

void setup(), check_player(), choose_mode(), draw(), input(), logic(), loop(), random(), store_previous(int, int, int, int);
void check_Xposition(), check_Yposition(), check_user_continue(), check_round(), reset_game(), update_score(), record_data(struct tm tm);
void loop(void(*looper)()), store_data(int, int, int, int, int, int, int, int), check_result(char), clear_previous(int, int, int, int);
int check_around_1(char, int, int, int ,int, int , int, int, int), set_color(int, int, int, int);
int check_condition(int, int, int, int, int, int, int, int, int, int);
int player, count_round, round_max, user_continue;
char sym, count_route_sub, count_route_main;
char slot[10][9], best_posi_x[3], best_posi_o[3];
int i, j, k;
int count_checkl, check_count_route_main, check_print, check_count_main, count_game = 0;
int height, width, BoxSlot = 9, spaceX , spaceY;
int move, x, y, x1, y2, ytemp;
int player1_score = 0, player2_score = 0;
int mode, mode_in_file = 0;;
bool move_y, gameover, endgame_1, endgame_2, user_input, wait_user, loopcheck = true ;
FILE *p;
// dev mode !!
bool Debug_mode = false, auto_random = false, auto_run = false;
int auto_choose_mode = 0;
// dev mode !!
struct position_check_1{
        int x0, y0, conclude, best_route;
        struct position_check_2{
            int route_x[15*2];
            int route_y[15*2];
            int priority[15];
            int result, branch;
        }route[50];
}position[10][9][2];

//setup
void setup(){
    mode = 0;
    check_print = 0;
    count_round = 0;
    check_count_main = 0;
    count_route_main = 0;
    count_route_sub = 0;
    check_count_route_main = 0;
    user_continue = 0;
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
    best_posi_x[0] = 0;
    best_posi_o[0] = 0;
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
    if(count_game%2 == 1)
        if(count_round%2 == 0){
            player = 1;
            sym = 'o';
        }
        else{
            player = 2;
            sym = 'x';
    }
    else{
        if(count_round%2 == 1){
            player = 1;
            sym = 'o';
        }
        else{
            player = 2;
            sym = 'x';
        }
    }
}

//player selece mode
void choose_mode(){
        
                                                                                                               
    system("cls");
    printf(" _________  ________  ________         _____ ______   ________  ___          ___  ___  ________  ________                                         \n");
    printf("|\\___   ___\\   __  \\|\\   __  \\        |\\   _ \\  _   \\|\\   __  \\|\\  \\        |\\  \\|\\  \\|\\   __  \\|\\   ___ \\                     \n");
    printf("\\|___\\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\       \\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\_|\\ \\   \n");
    printf("    \\ \\  \\ \\ \\  \\\\\\  \\ \\   _  _\\       \\ \\  \\\\|__| \\  \\ \\   __  \\ \\  \\       \\ \\   __  \\ \\  \\\\\\  \\ \\  \\ \\\\ \\                \n");
    printf("     \\ \\  \\ \\ \\  \\\\\\  \\ \\\\  \\  \\|       \\ \\  \\    \\ \\  \\ \\  \\ \\  \\ \\  \\       \\ \\  \\ \\  \\ \\  \\\\\\  \\ \\  \\_\\\\ \\         \n");
    printf("      \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\        \\ \\__\\    \\ \\__\\ \\__\\ \\__\\ \\__\\       \\ \\__\\ \\__\\ \\_______\\ \\_______\\           \n");
    printf("       \\|__|  \\|_______|\\|__|\\|__|        \\|__|     \\|__|\\|__|\\|__|\\|__|        \\|__|\\|__|\\|_______|\\|_______|                           \nn");
    printf("-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n");
    printf("Select mode\n");
    printf("1. easy (5x4) \n2. normal (7x6) \n3. Hard (9x8)\n");
    //check which mode player choose
    if( mode == 1 || auto_choose_mode == 1){
        BoxSlot = 5;
        mode = 0;
        loopcheck = false;
        round_max = 20;
        mode_in_file = 1;
    }
    else if ( mode == 2 || auto_choose_mode == 2){
        BoxSlot = 7;
        mode = 0;
        loopcheck = false;
        round_max = 42;
        mode_in_file = 2;
    }
    else if ( mode == 3 || auto_choose_mode == 3){
        BoxSlot = 9;
        mode = 0;
        loopcheck = false;
        round_max = 72;
        mode_in_file = 3;
    }
}

//create boundary
void draw(){
    //generate prepare zone
    printf("\n");
    for(int j = 1, i = -2 ; j <= width ; j++ ){
        if(i == y && j == x)
            printf(" %c",sym);
        else
            printf(" ");
    }
    //generate box
    printf("\n\n");
    for ( int i = 1 ; i <= height ; i++ ){
        for( int j = 0 ; j <= width ; j++){
           if( j%6 == 0 )
                printf("|");
            else if( i%3 == 0 )
                printf("_");
            else{
                x1=(3+j)/6;
                ytemp=(1+i)/3;
                if((j+3)%6 == 0 && (i+1)%3 == 0){
                    if(set_color(x1, ytemp, i, j) == 1){
                    }
                    else if(slot[x1][ytemp] == 'x' || slot[x1][ytemp] == 'o'){
                        printf("%c",slot[x1][ytemp]);
                    }
                    else
                        printf(" ");
                }
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Round : %d\n", count_round);
    printf("Score Player 1 (o): %d\n", player1_score);
    printf("Score Player 2 (x): %d\n", player2_score);
    if(Debug_mode){
        printf("best posi x : (%d,%d) route : %d\n", best_posi_x[1],best_posi_x[2],position[best_posi_x[1]][best_posi_x[2]][1].best_route);
        printf("best posi o : (%d,%d) route : %d\n", best_posi_o[1],best_posi_o[2],position[best_posi_o[1]][best_posi_o[2]][0].best_route);
        printf("Prep stats x : %d\n", x);
    }
}

int set_color(int x1, int ytemp, int i, int j){
    int result = 0;
    for(int z = 0; z < 30 ; z++){
        if(slot[x1][ytemp]  == 'x' && (j+3)%6 == 0 && (i+1)%3 == 0  &&
                (x1 == position[best_posi_x[1]][best_posi_x[2]][1].route[(position[best_posi_x[1]][best_posi_x[2]][1].best_route)].route_x[z] &&
                ytemp == position[best_posi_x[1]][best_posi_x[2]][1].route[(position[best_posi_x[1]][best_posi_x[2]][1].best_route)].route_y[z]) ||
                (x1 == position[best_posi_x[1]][best_posi_x[2]][1].x0 &&
                ytemp == position[best_posi_x[1]][best_posi_x[2]][1].y0)){
            printf("\033[0;31m");
            printf("x");
            printf("\033[0m");
            result = 1;
            break;
        }
        else if(slot[x1][ytemp] == 'o' && (j+3)%6 == 0 && (i+1)%3 == 0  &&
                (x1 == position[best_posi_o[1]][best_posi_o[2]][0].route[(position[best_posi_o[1]][best_posi_o[2]][0].best_route)].route_x[z] &&
                ytemp == position[best_posi_o[1]][best_posi_o[2]][0].route[(position[best_posi_o[1]][best_posi_o[2]][0].best_route)].route_y[z]) ||
                (x1 == position[best_posi_o[1]][best_posi_o[2]][0].x0 &&
                ytemp == position[best_posi_o[1]][best_posi_o[2]][0].y0)){
            printf("\033[0;34m");
            printf("o");
            printf("\033[0m");
            result = 1;
            break;
        }
    }
    return result;
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
            break;
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
            if( slot[x1][y2] != 'x' && slot[x1][y2] != 'o' && y <= height-3){
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
void check_result(char sym){
    int posi;
    if(sym == 'o')
            posi = 0;
    else if(sym == 'x')
            posi = 1;
    //loop to check every slot
    for(int i = 1 ; i <= spaceY ; i++ ){
        for(int j = 1 ; j <= spaceX ; j++ ){
            if(Debug_mode){
                printf("\033[0;31m");
                printf("|");
                printf("\033[0m");
                printf("%c",slot[j][i]);
            }
            if( slot[j][i] != sym ){
                if(Debug_mode)
                    printf("=pass,");
                continue;
            }
            count_route_main = 0;
            count_route_sub = 0;
            position[j][i][posi].x0 = j;
            position[j][i][posi].y0 = i;
            for(int z = 0 ; z <= 25 ; z++)
                position[j][i][posi].route[z].result = 0;
            for(int z=1; z<=8; z++)
                check_around_1(sym, j, i, posi, i, j, 0, z, 100);
            for(int z=0; z < 25; z++)
                if(position[j][i][posi].route[z].result > position[j][i][posi].conclude){
                    position[j][i][posi].best_route = z;
                    position[j][i][posi].conclude = position[j][i][posi].route[z].result;
                }
            if(Debug_mode)
                printf("conclude -> %d best route = %d",position[j][i][posi].conclude,position[j][i][posi].best_route);
        }
        if(Debug_mode){
            printf("\033[0;31m");
            printf("|");
            printf("\033[0m");
            printf("\n");
        }
    }
    printf("\n");
    //find best route (priority top slot)
    for(int i = spaceY ; i >= 1 ; i-- ){
        for(int j = spaceX ; j >= 1 ; j-- ){
            if(position[j][i][1].conclude > best_posi_x[0]){
                best_posi_x[0] = position[j][i][1].conclude;
                best_posi_x[1] = j;
                best_posi_x[2] = i;
            }
            else if(position[j][i][0].conclude > best_posi_o[0]){
                best_posi_o[0] = position[j][i][0].conclude;
                best_posi_o[1] = j;
                best_posi_o[2] = i;
            }
        }
    }
}

//check around target slot
int check_around_1(char player_sym, int x0, int y0, int posi, int i, int j, int check_loop1, int check_loop2, int priority){
    if((j <= spaceX &&  j > 0) && (i <= spaceY && i > 0) && slot[j][i] == player_sym){
        //1. check left
        if(slot[j][i] == slot[j-1][i] && slot[j][i] == slot[j-2][i] && check_loop1 != 5 && check_loop2 == 1){
            if( check_condition(x0, y0, posi, j-1, i, j-2, i, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
               goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking left ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j-1, i, j-2, i, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 5)
                    check_around_1( player_sym, x0, y0, posi, i, j-2, 1, z, priority-1);
            }
        }
        //2. check top-left
        else if(slot[j][i] == slot[j-1][i-1] && slot[j][i] == slot[j-2][i-2] && check_loop1 != 6  && check_loop2 == 2){
            if( check_condition(x0, y0, posi, j-1, i-1, j-2, i-2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking top-left ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j-1, i-1, j-2, i-2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 6)
                    check_around_1( player_sym, x0, y0, posi, i-2, j-2, 2, z, priority-1);
            }
        }
        //3. check top
        else if(slot[j][i] == slot[j][i-1] && slot[j][i] == slot[j][i-2] && check_loop1 != 7 && check_loop2 == 3){
            if( check_condition(x0, y0, posi, j, i-1, j, i-2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking top ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j, i-1, j, i-2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 7)
                    check_around_1( player_sym, x0, y0, posi, i-2, j, 3, z, priority-1);
            }
        }
        //4. check top-right
        else if(slot[j][i] == slot[j+1][i-1] && slot[j][i] == slot[j+2][i-2] && check_loop1 != 8 && check_loop2 == 4){
            if( check_condition(x0, y0, posi, j+1, i-1, j+2, i-2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking top-right ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j+1, i-1, j+2, i-2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 8)
                    check_around_1( player_sym, x0, y0, posi, i-2, j+2, 4, z, priority-1);
            }
        }
        //5. check right
        else if(slot[j][i] == slot[j+1][i] && slot[j][i] == slot[j+2][i] && check_loop1 != 1 && check_loop2 == 5){
            if( check_condition(x0, y0, posi, j+1, i, j+2, i, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking right ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j+1, i, j+2, i, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 1)
                    check_around_1( player_sym, x0, y0, posi, i, j+2, 5, z, priority-1);
            }
        }
        //6. check bottom-right
        else if(slot[j][i] == slot[j+1][i+1] && slot[j][i] == slot[j+2][i+2] && check_loop1 != 2 && check_loop2 == 6){
            if( check_condition(x0, y0, posi, j+1, i+1, j+2, i+2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking bottom-right ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j+1, i+1, j+2, i+2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 2)
                    check_around_1( player_sym, x0, y0, posi, i+2, j+2, 6, z, priority-1);
            }
        }
        //7. check bottom
        else if(slot[j][i] == slot[j][i+1] && slot[j][i] == slot[j][i+2] && check_loop1 != 3 && check_loop2 == 7){
            if( check_condition(x0, y0, posi, j, i+1, j, i+2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking bottom ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j, i+1, j, i+2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 3)
                    check_around_1( player_sym, x0, y0, posi, i+2, j, 7, z, priority-1);
            }
        }
        //8. check bottom-left
        else if(slot[j][i] == slot[j-1][i+1] && slot[j][i] == slot[j-2][i+2] && check_loop1 != 4 && check_loop2 == 8){
            if( check_condition(x0, y0, posi, j-1, i+1, j-2, i+2, priority, check_loop1, check_loop2) == 1 && check_loop1 != 0)
                goto end;
            if(Debug_mode)
                printf("(%d,%d)(%d,%d)(%d,%d)checking bottom-left ",x0,y0,j,i,count_route_main,count_route_sub/2);
            store_data(x0, y0, posi, j-1, i+1, j-2, i+2, priority);
            position[x0][y0][posi].route[count_route_main].result ++;
            count_route_sub +=2;
            check_count_route_main = 1;
            for(int z=1; z<=8; z++){
                if(z != 4)
                    check_around_1( player_sym, x0, y0, posi, i+2, j-2, 8, z, priority-1);
            }
        }
        else if (check_loop2 == 8 || (check_loop1 == 4 && check_loop2 == 7)){
            end:
            if(check_loop2 == 8 || (check_loop1 == 4 && check_loop2 == 7)){
                if(check_count_route_main == 1){
                    if(Debug_mode)
                        printf("=check(%d,%d,%d) -> %d ",count_route_main,check_loop1,check_loop2,position[x0][y0][posi].route[count_route_main].result);
                    position[x0][y0][posi].route[count_route_main].branch = count_route_sub/2;
                    count_route_main++;
                    check_count_main = 1;
                    check_count_route_main = 0;
                }
                count_route_sub = 0;
            }
        }
    }
}
//clear previous unuse branch data
void clear_previous(int x0, int y0, int posi, int priority){
    while(count_route_sub > 0){
        position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = 0;
        position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = 0;
        position[x0][y0][posi].route[count_route_main].route_x[count_route_sub-1] = 0;
        position[x0][y0][posi].route[count_route_main].route_y[count_route_sub-1] = 0;
        position[x0][y0][posi].route[count_route_main].priority[count_route_sub/2] = 0;
        count_route_sub -= 2;
    }
    position[x0][y0][posi].route[count_route_main].result = 0;
    count_route_sub = 0;
}


//store previous branch data
void store_previous(int x0, int y0, int posi, int priority){
    // store previously branch
    if(check_count_main == 1 && count_route_main != 0){
        check_count_main = 0;
        for(int x = 100, z = 0; x > priority; x--, z++ ){
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = position[x0][y0][posi].route[count_route_main-1].route_x[count_route_sub];
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = position[x0][y0][posi].route[count_route_main-1].route_y[count_route_sub];
            position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = position[x0][y0][posi].route[count_route_main-1].route_x[count_route_sub+1];
            position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = position[x0][y0][posi].route[count_route_main-1].route_y[count_route_sub+1];
            position[x0][y0][posi].route[count_route_main].result ++;
            position[x0][y0][posi].route[count_route_main].priority[z] = x;
            count_route_sub += 2;
        }
    }
}

//store data from check_around_1
void store_data(int x0, int y0, int posi, int j1, int i1, int j2, int i2, int priority){
    position[x0][y0][posi].route[count_route_main].route_x[count_route_sub] = j1;
    position[x0][y0][posi].route[count_route_main].route_y[count_route_sub] = i1;
    position[x0][y0][posi].route[count_route_main].route_x[count_route_sub+1] = j2;
    position[x0][y0][posi].route[count_route_main].route_y[count_route_sub+1] = i2;
    position[x0][y0][posi].route[count_route_main].priority[count_route_sub/2] = priority;
}

//check if vector collaps( bigger vector only)
int check_condition(int x0, int y0, int posi, int j1, int i1, int j2, int i2, int priority, int check_loop1, int check_loop2){
    int result = 0;
    store_previous(x0, y0, posi, priority);;
    for(int z=count_route_sub-1; z >= 0; z--){
        if((j1 == position[x0][y0][posi].route[count_route_main].route_x[z] && i1 == position[x0][y0][posi].route[count_route_main].route_y[z] &&
            priority < position[x0][y0][posi].route[count_route_main].priority[z/2]) || (j1 == position[x0][y0][posi].x0 && i1 == position[x0][y0][posi].y0)){
                result = 1;
                if(Debug_mode){
                    printf("\033[0;33m");
                    printf("deflect->(%d,%d)",j1,i1);
                    printf("\033[0m");
                }
                //clear previous data(that not use)
                if(check_loop2 == 8 || (check_loop1 == 4 && check_loop2 == 7))
                    clear_previous(x0, y0, posi, priority);
                break;
        }
        else if((j2 == position[x0][y0][posi].route[count_route_main].route_x[z] && i2 == position[x0][y0][posi].route[count_route_main].route_y[z] &&
            priority < position[x0][y0][posi].route[count_route_main].priority[z/2]) || (j2 == position[x0][y0][posi].x0 && i2 == position[x0][y0][posi].y0)){
                result = 1;
                if(Debug_mode){
                    printf("\033[0;33m");
                    printf("deflect->(%d,%d)",j2,i2);
                    printf("\033[0m");
                }
                //clear previous data(that not use)
                if(check_loop2 == 8 || (check_loop1 == 4 && check_loop2 == 7))                   
                    clear_previous(x0, y0, posi, priority);
                break;
        }

    }
    return result;
}

//reset score counter
void update_score(){
    if(best_posi_o[0] > best_posi_x[0])
        player1_score ++;
    else if(best_posi_o[0] < best_posi_x[0])
        player2_score ++;
}

//initiate reset sequence game
void reset_game(){
    //set all array to 0
    endgame_1 = true;
    for( int i = 1 ; i <= spaceY ; i++){
        for( j = 1 ; j <= spaceX ; j++){
            slot[j][i] = 0;
        }
    }
    for( int i =0 ; i <= 2; i++ ){
        best_posi_x[i] = 0;
        best_posi_o[i] = 0;
    }
    for( int k =0 ; k <= 1; k++ ){
        for( int i = 1; i <= 9; i++ ){
            for( int j = 1; j <= 8; j++ ){
                position[i][j][k].x0 = 0;
                position[i][j][k].y0 = 0;
                position[i][j][k].conclude = 0;
                position[i][j][k].best_route = 0;
                for( int z = 0; z < 50; z++){
                    for( int s = 0; s < 30; s++){
                    position[i][j][k].route[z].route_x[s] = 0;
                    position[i][j][k].route[z].route_y[s] = 0;
                    position[i][j][k].route[z].route_x[s] = 0;
                    position[i][j][k].route[z].route_y[s] = 0;
                    }
                    for( int s = 0;s <= 15; s++){
                    position[i][j][k].route[z].priority[s] = 0;
                    }
                }
            }
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
        if(user_input || auto_run){
            if( user_continue == 1 || auto_run){
                endgame_2 = true;
                reset_game();
            }
            else if( user_continue == 2 ){
                endgame_2 = true;
            }
        }
    }
}

void record_data(struct tm tm){
    if(count_game == 0)
        fprintf(p,"%d-%02d-%02d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(p," Game %d Mode ",count_game+1);
    if( mode_in_file == 1)
        fprintf(p,"Easy(5x4)   ");
    else if ( mode_in_file == 2 )
        fprintf(p,"Normal(7x6) ");
    else if ( mode_in_file == 3 )
        fprintf(p,"Hard(9x8)   ");
    fprintf(p," Score : O Win %d , X win %d \n",player1_score,player2_score);
}

//Main function
int main(){
    srand(time(NULL));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    p = fopen("ScoreData.txt","a+");
    do{
         //select mode
        loop(choose_mode);
        //setup game
        setup();
        //loop game
        while(!endgame_1){
            usleep(8000 * 2);
            //clear old messsage
            system("cls");
            check_player();
            draw();
            if(auto_random)
                random();
            else
                input();
            logic();
            check_Xposition();
            check_Yposition();
            check_result('o');
            check_result('x');
            check_round();
        }
        update_score();
        while(!endgame_2){
            usleep(8000 * 2);
            //clear old messsage
            system("cls");
            draw();
            input();
            check_user_continue();
        }
        record_data(tm);
        count_game++;
    }while(user_continue !=2);
        fprintf(p,"--------------------------------------------------------------\n");
    fclose(p);
    return 0;
}
