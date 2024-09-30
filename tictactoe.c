/*
 * tictacttoe.c
 * Last Updated: 24-Sep-29, Alex Garcia
 */


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

#define BOARDSIZE 3


char p1 = 'x', p2 ='o';
char boardState[] = "---------";

//global variables for win validation
int rowX[3] = {0};
int colX[3] = {0};
int diagX = 0;
int antidiagX = 0;

int rowO[3] = {0};
int colO[3] = {0};
int diagO = 0;
int antidiagO = 0;


/*
 * Determines if player1 (X) has won the game
 * 
 * lastMove: the integer value of the players cell selection
 *
 * returns: bool value if the player has won
 * */
bool xWin(int lastMove){
    lastMove = lastMove - 49;
    int r = (lastMove) / BOARDSIZE;
    int c = (lastMove) % BOARDSIZE;
    rowX[r]++; 
    colX[c]++;
    if(r == c) diagX++;
    if(r+c+1 == BOARDSIZE) antidiagX++;
    bool playerWon = ( rowX[r] == BOARDSIZE ||
                 colX[r] == BOARDSIZE ||
                 diagX == BOARDSIZE ||
                 antidiagX == BOARDSIZE);
    return playerWon;
}


/*
 * Determines if player1 (O) has won the game
 * 
 * lastMove: the integer value of the players cell selection
 *
 * returns: bool value if the player has won
 * */
bool oWin(int lastMove){
    lastMove = lastMove - 49;
    int r = (lastMove) / BOARDSIZE;
    int c = (lastMove) % BOARDSIZE;
    rowO[r]++; 
    colO[c]++;
    if(r == c) diagO++;
    if(r+c+1 == BOARDSIZE) antidiagO++;
    bool playerWon = ( rowO[r] == BOARDSIZE ||
                 colO[r] == BOARDSIZE ||
                 diagO == BOARDSIZE ||
                 antidiagO == BOARDSIZE);
    return playerWon;
}


/*
 * Simple helper method, should be removed later on
 *
 * return:
 *      1: win
 *      0: draw
 *      -1:continue
 */
int validate(char currP, int lastMove){
    char* draw = strchr(boardState, '-');
    if(draw == NULL){
        return 0;
    }

    if(currP == p1){
        return (xWin(lastMove))? 1:-1;
    }else{
        return (oWin(lastMove))? 1:-1;
    }
}


/*
 * makes the players move by changing the state of the board
 *
 * currP: the current player
 * moveL the integer representation of the players selection
 */
void makeMove(char currP, int move ){
        if(move >= '0' && move <= '9'){
            int cell = move - 49;
            if(boardState[cell] == '-' ){
                boardState[cell] = currP;
            }
        }
}


/*
 * Prints the current state of the board
 */
void printBoard(){
    for(int row = 0; row < BOARDSIZE; row++){
            printf("\t\t\t|");
            for(int col = 0; col < BOARDSIZE; col++){
                int cell = (row*3) + col;
                if(boardState[cell] == '-'){
                    printf(" ");
                }else{
                    printf("%c", boardState[cell]);
                }
                printf("|");
            }
            printf("\n");
    }
}


/*
 * prints the game instructions to the player
 */
void showInstructions(){
    char op;
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("Choose Opponent:\n1: Player\n2: Computer\n");
   if(scanf("%c", &op) != 1 ){
        printf("Error!\n");
        return;
    }

    #ifdef _WIN32
        system("clear");
    #endif

    #ifdef linux
        system("clear");
    #endif

    #ifdef __APPLE__
        system("clear");
    #endif

    while(op != '1' && op != '2'){
        printf("Please choose a valid Opponent\n1: Player\n2: Computer\n");
        if(scanf(" %c", &op) != 1 ){
            printf("Error!\n");
            return;
    }
        #ifdef _WIN32
            system("clear");
        #endif

        #ifdef linux
            system("clear");
        #endif

        #ifdef __APPLE__
            system("clear");
        #endif
        printf("");
    }

    printf("In order to make a selection choose one of the available squares(1-9)\n");
    printf("\t\t\t|1|2|3|\n\t\t\t|4|5|6|\n\t\t\t|7|8|9|\n");
    printf("The game will start in 1 second\n");
    //sleep(1);
    #ifdef _WIN32
        system("clear");
    #endif

    #ifdef linux
        system("clear");
    #endif

    #ifdef __APPLE__
        system("clear");
    #endif
}


/*
 * main game loop and overall game logic is held here
 */
void playGame(){
    system("clear");
    showInstructions();
    char currP = p2;
    while(1){
        //the next thing we want to do is change the board state every turn
        #ifdef _WIN32
            system("clear");
        #endif

        #ifdef linux
            system("clear");
        #endif

        #ifdef __APPLE__
            system("clear");
        #endif
        printf("Choose a number from 1-9(0 to quit the game)\n");
        printBoard();
        int input;
        while ((getchar()) != '\n');
        input = getchar();

        if(input == '0'){
            break;

        }else{
            currP = (currP == p2)? p1:p2 ;
            makeMove(currP, input);
            int res = validate(currP, input);

            if(res == 1) {
                system("clear");
                printBoard();
                printf("%c WINS!!!\n", currP);
                break;

            }else if(res == 0){
                system("clear");
                printBoard();
                printf("DRAW!!\n");
                break;

            }
        }
    }
}


int main(){
    playGame();
    return 0;
}

