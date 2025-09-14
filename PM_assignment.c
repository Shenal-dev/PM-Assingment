#include<stdio.h>
#include<stdlib.h>
# define max 10



// Initializing the game board
void initialize_game_board(int N,char board[N][N]){
	for(int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			board[i][j] = ' ';
		}
	}
}

// Printing the game board
void print_board(int N,char board[N][N]){
	for (int i=0;i<N;i++){
		printf("|");
		for (int j=0;j<N;j++){
			printf("%c",board[i][j]);
			if (j<N-1){
				printf("|");
			}
			else {printf("|\n");
			  }
		}


	   // Draw the line between two rows    
		if (i<N-1){
		      for (int j=0;j<N;j++){
			printf("--");
			   if (j==N-1){
				   printf("\n");
			   }
		     }
		}
	}
     	
}
// Get the user input and check input validation
void input_validation(char current, int *row , int *col ,int N, char board[N][N]){
	while(1){
		printf("Player %c enter the row and the coloumn(0..%d)",current,N-1);
		scanf("%d %d",row,col);
		if (*row < 0||*row >= N|| *col< 0 || *col >= N || board[*row][*col]== 'X' || board[*row][*col]=='O'){
			printf("Invalid move\n");
                        continue;
                }else { 
                        break;
                }


	}
}
//check whether a user has win
int win_check(char curent,char board[N][N]){
	while(1){
		int i;
		for (i=0;i<N;i++){
			for
		}
	}



int main(){
	int N;
	printf("Enter board size N( 3 <= N <= 10):\n");
	scanf("%d",&N);
	char board[N][N];
	 if (N<3 || N>10){
	       printf("Invalid input!\n");
         return 1;
	}       
	int mode;
	printf("Select the mode\n");
	printf("Mode 1 ==> Player vs Computer\n");
        printf("Mode 2 ==> Player vs Player\n");
        printf("Mode 3 ==> Mulit-Player (3 Users ) \n");
	printf("Enter the game mode: ");
	scanf("%d",&mode);
	initialize_game_board(N,board);
	print_board(N,board);
	for (int i=0;i<N*N; i++){
	 int row,col;
	 int turn;     
	     char player[3]={'X','O','Z'};
	     char current_player = player[turn % mode];
	           input_validation(current_player,&row,&col,N,board);
		   board[row][col] = current_player;
		   print_board(N,board);
		  while( win_check()){
			  printf("player %c won the game!",current_player);
			  return 0;
			  break;
		  }
		   turn++;

	}


        return 0;
 }
