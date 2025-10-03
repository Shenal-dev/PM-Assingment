#include<stdio.h>
#include<stdlib.h>
#include<time.h>



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
		printf("Player %c enter the row and the coloumn(0..%d)\nEnter as [row]'space'[coloumn]",current,N-1);
		scanf("%d %d",row,col);
		if (*row < 0||*row >= N|| *col< 0 || *col >= N || board[*row][*col]== 'X' || board[*row][*col]=='O'){
			printf("Invalid move\n");
                        continue;
                }else { 
                        break;
                }


	}
}
//check whether a user has won
int win_check(char current, int N, char board[N][N]) {
    int i, j;

    // check whether a user has won with a row match
    for (i = 0; i < N; i++) {
        int row_match =0 ;
        for (j = 0; j < N; j++) {
            if (board[i][j] == current){
                row_match++;
            }
	else {
		break;
	}
       }
        if (row_match == N) {
		return 1;
	}
    }

    //check whether a user has won with a coloumn match
    for(i=0;i<N;i++){
    	int col_match=0;
	for(j=0;j<N;j++){
		if(board[j][i]==current){
			col_match++;
		}
		else{
			break;
		}
	}
		if(col_match==N){
			return 1;
		}
	
    }
    // check whether a user has won with a diagonal match
    int dgn_win=1;
    for(i=0;i<N;i++){
    	if(board[i][i]!=current){
		dgn_win=0;
		break;
	}
    }
	if(dgn_win==1){
	       return 1;
	}	       

    // check whether a user has won with anti-diagonal match
    int Adgn_win =1;
    for(i=0;i<N;i++){
	    	if(board[i][N-i-1]!=current){
			Adgn_win=0;
			break;
		}
    }
	  
	 if(Adgn_win==1){
	        return 1;
	}
    	
    //No one has won
    
    return 0;
}
// Function to create random moves
void computer_move(int N,char board[N][N]){
	int row,col;
	do{
		row = rand()%N;
		col = rand()%N;
	}while(board[row][col]!=' ');
	board[row][col]='O';
	printf("The computer has played the move row %d and coloumn %d\n",row,col);
	print_board(N,board);
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
	printf("Mode 1 ==> User vs computer\n");
        printf("Mode 2 ==> User vs user\n");
        printf("Mode 3 ==> Mulit-Player (3 Users ) \n");
	printf("Enter the game mode: ");
	scanf("%d",&mode);
	initialize_game_board(N,board);
	print_board(N,board);
	for (int i=0;i<N*N; i++){
	 int row,col;
	 int turn;
         int winchk;	 
	     char player[3]={'X','O','Z'};
	     char current_player = player[turn % mode];
	           input_validation(current_player,&row,&col,N,board);
		   board[row][col] = current_player;
		   print_board(N,board);
		    if(win_check(current_player,N,board)==1){
		   	printf("player %c has won the game!",current_player);
                          return 0;
		    }
		    srand(time(NULL));
		    if (mode==1){
		    computer_move(N,board);
		    }
		   turn++;

	}
	printf("The game is a DRAW!\n");
        return 0;
 }
