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
// Function to create random moves when mode=1
void computer_move_mode1(int N,char board[N][N],int*row,int *col){
	do{
		*row = rand()%N;
		*col = rand()%N;
	}while(board[*row][*col]!=' ');
	board[*row][*col]='O';
	printf("The computer has played the move row %d and coloumn %d\n",*row,*col);
	print_board(N,board);
}
//save the move to the log file
void save_move(int i,int row,int col,char current){
	FILE *F_ptr;
	F_ptr=fopen("game_history.txt","a");
	if(F_ptr==NULL){
		printf("Error occured opening the file");
	}
	else {
		fprintf(F_ptr,"%d. The player %c has played the move row %d and column %d for move number %d \n",i+1,current,row,col,i+1);
		fclose(F_ptr);
	}
}
// save the win status to the log file
void save_win(int i,char current,int T,int N){
	FILE *ptr;
	ptr=fopen("game_history.txt","a");
	if(ptr==NULL){
		printf("Error opening the file ");
	}
	else{
		if(T==N*N){
			fprintf(ptr,"The game is a Draw");
                fclose(ptr);
		}
		else{
		fprintf(ptr,"The player %c has won the game in the move number %d",current,i);
		fclose(ptr);
		}
	}
}
// function for computer to generate and store a move when mode ==3
void computer_move2(int N,char board[N][N],int*row,int *col,char current){
	do{
		*row = rand()%N;
		*col = rand()%N;
	}while(board[*row][*col]!=' ');
	board[*row][*col]=current;
	printf("the computer has played the move row %d and colomn %d\n",*row,*col);
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
	char player_type[3];
	if(mode==3){
		printf("Enter the player type\n");
		printf("H ==> Human, C ==> computer\n");
		int H_cnt;		// count the human players
		do{
		for(int i=0;i<3;i++){
			printf("Player type for plyer number %d:",i+1);
		        scanf(" %c",&player_type[i]);
				    }
		for(int j=0;j<3;j++){
			if( player_type[j]=='H'||player_type[j]=='h'){
				H_cnt++;
			}
			else {
				continue;
			}
		}
		if(H_cnt<1){
			printf("At least there must be one human player to play multi-player mode\n");
			printf("plase enter again");
		}
		}while(H_cnt<1); 	// since the human count should be at least one 

		printf("\n");
	}

	initialize_game_board(N,board);
	print_board(N,board);
	int turn=0;
	char current_player;
	if(mode==2||mode==1){
	for (int i=0;i<N*N; i++){
	 int row,col;
	 turn;
	     char player[2]={'X','O'};
	      current_player = player[turn % mode];
	           input_validation(current_player,&row,&col,N,board);
		   board[row][col] = current_player;
		   print_board(N,board);
		    if(win_check(current_player,N,board)==1){
		   	printf("player %c has won the game!",current_player);
			save_win(i,current_player,turn,N);

                          return 0;
		    }
		    save_move(i,row,col,current_player);
		    srand(time(NULL));
		    if (mode==1){
			    int temp_row,temp_col;
		    computer_move_mode1(N,board,&temp_row,&temp_col);
		    save_move(i+1,temp_row,temp_col,'O');
		    i++;
		    if(win_check('O',N,board)==1){
                        printf("The computer has won the game!");
                        save_win(i,'O',turn,N);

                          return 0;
                       }
		    }
		   turn++;

	}
	 printf("The game is a DRAW!\n");
         FILE *F_ptr = fopen("game_history.txt", "a");// saves the draw in log file
         if (F_ptr != NULL) {
                  fprintf(F_ptr, "The game ended in a DRAW!\n");
                                fclose(F_ptr);
              }
	}
	//If the mode is 3
	if(mode==3){
		int turn=0;
		char player[3]={'X','O','Z'};
		int i;
		for (i=0;i<N*N;i++){
			int row,col;
			char current = player[turn%3];
			char type = player_type[turn%3];
			if (type=='H'||type =='h'){
				input_validation(current,&row,&col,N,board);
				board[row][col]=current;
				save_move(i,row,col,current);
				if(win_check(current,N,board)==1){
					printf("player %c has won the game!",current);
					save_win(i,current,turn,N);
					return 0;
				}
			}
			if (type=='C'|| type=='c'){
				srand(time(NULL));
				computer_move2(N,board,&row,&col,current);
				save_move(i,row,col,current);
				if(win_check(current,N,board)==1){
					printf("The computer has won the game!");
					FILE *F_ptr = fopen("game_history.txt", "a");// saves the draw in log file
               		    		if (F_ptr != NULL) {
                  				fprintf(F_ptr, "The computer has won the game!\n");
                                		fclose(F_ptr);
                                	 		  }
					else{
						printf("Error opening the file ");
					}
					return 0;
				}
			}
			turn++;
		}
		 print_board(N,board);
		printf("The game is a DRAW!");
		FILE *F_ptr = fopen("game_history.txt", "a");// saves the draw in log file
         	if (F_ptr != NULL) {
                  fprintf(F_ptr, "The game ended in a DRAW!\n");
                                fclose(F_ptr);
             			 }
		else{
			printf("Error opening the file ");
		}
	}
        return 0;
    }
