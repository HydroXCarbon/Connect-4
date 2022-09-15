#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

int player , count_round;
char sym;
char slot[100][100];
int i , j , k;
int height, width , BoxSlot = 7, spaceX  , spaceY;
int move , x , y , x1 , y1 , y2;
int checktest;
bool move_y , gameover , endgame , user_continue , user_input;

//setup
void setup(){
    count_round = 0;
    user_continue = false;
    user_input = false;
    endgame=false;
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

//check game status
void check_gameover(){
    if( gameover == true ){
        gameover=false;
        endgame=true;
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
                y1=(20-i)/3;
                if((slot[x1][y1] == 'x' || slot[x1][y1] == 'o') 
                    && (j+3)%6 == 0 && (i+1)%3 == 0 ){
                    printf("%c",slot[x1][y1]);
                }
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("%d\n",checktest);
    printf("Round : %d\n", count_round);
}

//recive realtime input from keyboard 
void input(){
    //detect keyboard input
    if (kbhit()) {
        //recieve input and caculate
        switch (getch()) {
        case 'a': case '4':
            move = 1;
            break;
        case 's': case '5':
            move = 2;
            break;
        case 'd': case '6':
            move = 3;
            break;
        case '1':
            user_continue = true;
            user_input = true;
            break;
        case '2':
            user_continue = false;
            user_input = true;
            break;
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
    if( move_y == true ){
        y = -1;
        y+=3;
        while( y >= 1 ){
            x1=(3+x)/6;
            y1=(20-y)/3;
            y2=y1-1;
            if( slot[x1][spaceY] == 'x' || slot[x1][spaceY] == 'o'){
                y = -2;
               break;
            }
            if( slot[x1][y2] == 0 && y <= height-3){
                y+=3;
            }
            else{
                slot[x1][y1]=sym;
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
        }
    }
}
void reset_game(){
    for( i = 1 ; i <= spaceY ; i++){
        for( j = 1 ; j <= spaceX ; j++){
            slot[j][i] = 0;
        }
    } 
}

void check_user_continue(){
    printf("Continue ?\n");
    printf("1.Yes    2.No");
    do{
        input();
    }while(!user_input);
    user_input=false;
    if(user_continue){
        reset_game();
    }
}

//Main function
int main(){
    do{
        //setup game
        setup(); 
        //draw();
        //loop game
        while(!endgame){
            usleep(25000);
            check_player();
            draw();
            input();
            logic();
            check_gameover();
            check_Xposition();
            check_Yposition();
            check_result();
        }
        endgame=false;
        check_user_continue();
    }while(user_continue);
    return 0;
}