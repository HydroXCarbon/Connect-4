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
int gameover;
int checktest;
bool move_y;

//setup
void setup(){
    count_round = 0;
    gameover = 0;
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
                y1=y-1;
                if(slot[j][i] == 'x' || slot[j][i] == 'o'){
                    printf("%c",slot[j][i]);
                }
                else
                    printf(" ");
            }
            
        }
        printf("\n");
    }
    //printf("%d",checktest);
    printf("Round : %d", count_round);
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
            y1=y+3;
            if( slot[x][2] == 'x' || slot[x][2] == 'o'){
                //x = width/2;
                y = -2;
                break;
            }
            if( slot[x][y1] == 0 && y <= height-3){
                y+=3;
            }
            else{
                slot[x][y]=sym;
                count_round+=1;
                //x = width/2;
                y = -2;
                break;
            }
        }
    }
    move_y=false;
}

void check_result(){
    if(1){
        count_round+=1;
    }
}

int main(){
    //setup game
    setup(); 
    //draw();
    //loop game
    while(!gameover){
        usleep(25000);
        check_player();
        draw();
        input();
        logic();
        check_Xposition();
        check_Yposition();
        //check_result();
    }
    
    return 0;
}