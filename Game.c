#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

int player , count_round , user_continue;
char sym , player_win;
char slot[100][100];
int i , j , k;
int height, width , BoxSlot = 9, spaceX  , spaceY;
int move , x , y , x1 , y2 , ytemp;
int player1_score , player2_score;
int mode ; 
int ytest , xtest , ytest1 , xtest1;
bool move_y , gameover , endgame , user_input , wait_user , c_mode = true;

//setup
void setup(){
    mode = 0;
    count_round = 0;
    user_continue = 0;
    player_win = 'n';
    c_mode = false;
    wait_user = false;
    user_input = false;
    endgame = false;
    gameover = false;
    move_y = false;
    spaceX = BoxSlot;
    spaceY =  BoxSlot-1;
    width = spaceX*6;
    height = spaceY*3;
    x = width/2;
    y = -2;
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
        c_mode = false;
    }
    else if ( mode == 2){
        BoxSlot = 7;
        mode = 0;
        c_mode = false;
    }
    else if ( mode == 3){
        BoxSlot = 9;
        mode = 0;
        c_mode = false;
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
    printf("%d %d\n",xtest,ytest);
    printf("%d %d",xtest1,ytest1);
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
            else if(c_mode){
                mode = 1;
            }
            break;
        case '2':
            if(gameover){
                user_continue = 2;
                user_input = true;
            }
            else if(c_mode){
                mode = 2;
            }
            break;
        case '3':
            if(c_mode){
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

//include all axis check
void check_result(){
    for( i = 1 ; i <= spaceY ; i++){
        for( j = 1 ; j <= spaceX ; j++){
            //check x axis result
            if((slot[j][i]==slot[j+1][i])&&
                (slot[j+1][i]==slot[j+2][i])&&
                (slot[j+2][i]==slot[j+3][i])&&
                (slot[j][i] != 0)){
                gameover=true;
            }
            //check y axis result
            else if((slot[j][i]==slot[j][i+1])&&
                (slot[j][i+1]==slot[j][i+2])&&
                (slot[j][i+2]==slot[j][i+3])&&
                (slot[j][i] != 0)){
                gameover=true;
            }
            //check diagonal (-slope) result
            else if((slot[j][i]==slot[j-1][i+1])&&
                (slot[j-1][i+1]==slot[j-2][i+2])&&
                (slot[j-2][i+2]==slot[j-3][i+3])&&
                (slot[j][i] != 0)){
                gameover=true;
            }
            //check diagonal (+slope) result
            else if((slot[j][i]==slot[j+1][i+1])&&
                (slot[j+1][i+1]==slot[j+2][i+2])&&
                (slot[j+2][i+2]==slot[j+3][i+3])&&
                (slot[j][i] != 0)){
                gameover=true;
            }
            if( gameover && !wait_user){
                player_win = slot[j][i];
                wait_user = true;
                break;
            }
        }
        if(gameover){
            break;
        }
    }
}

//initiate reset game
void reset_game(){
    //set all array to 0
    for( i = 1 ; i <= spaceY ; i++){
        for( j = 1 ; j <= spaceX ; j++){
            slot[j][i] = 0;
        }
    } 
    user_continue == 0;
    user_input=false;
}

//check if user want to continue
void check_user_continue(){
    if(gameover){
        printf("Continue ?\n");
        printf("1.Yes    2.No");
        if(player_win == 'o'){
            player1_score+=1;
            player_win = 'n';
        }
        else if(player_win == 'x'){
            player2_score+=1;
            player_win = 'n';
        }
        if(user_input){
            if( user_continue == 1 ){
                endgame = true;
                reset_game();
            }
            else if( user_continue == 2 ){
                endgame = true;
            }
        }
    }
}

//Main function
int main(){
    do{
        //select mode
        while(c_mode){
            usleep(8000 * 2);
            choose_mode();
            input();
        }
        //setup game
        setup();
        //loop game
        while(!endgame){
            usleep(8000 * 2);
            check_player();
            draw();
            input();
            logic();
            check_Xposition();
            check_Yposition();
            check_result();
            check_user_continue();
        }
        endgame=false;
    }while(user_continue !=2);
    return 0;
}