#include <iostream>
#include <vector>
using namespace std;
int stepCost(int move){
	switch(move){
		case 1 : return 1; //up
		case 2 : return 1; //down
		case 3 : return 1; //left
		case 4 : return 1; //right
		default: return 0;
	}
}

bool goalTest(char current_state[9][9], int n_rows, int n_cols){
	int n_pegs = 0;
	for(int i = 0; i < n_rows; i++)
		for(int j = 0; i < n_cols; j++)
			if(current_state[i][j] == '*')
				n_pegs++;	
	return (n_pegs == 1)? true : false;
}
bool successorFunction(char current_state[9][9], int n_rows, int n_cols, int peg_pos_row, int peg_pos_col, int move){
	if(move == 1 && peg_pos_row-2 >= 0 && current_state[peg_pos_row-1][peg_pos_col] == '*' && current_state[peg_pos_row-2][peg_pos_col] == 'O' ){
		current_state[peg_pos_row][peg_pos_col] == 'O';
		current_state[peg_pos_row-1][peg_pos_col] == 'O';
		current_state[peg_pos_row-2][peg_pos_col] == '*';
		return true;
	}
	
	else if(move == 2 && peg_pos_row + 2 <= n_rows && current_state[peg_pos_row+1][peg_pos_col] == '*' && current_state[peg_pos_row+2][peg_pos_col] == 'O' ){
		current_state[peg_pos_row][peg_pos_col] == 'O';
		current_state[peg_pos_row+1][peg_pos_col] == 'O';
		current_state[peg_pos_row+2][peg_pos_col] == '*';
		return true;
	}
	
	else if(move == 3 && peg_pos_col - 2 >= 0 && current_state[peg_pos_row][peg_pos_col-1] == '*' && current_state[peg_pos_row][peg_pos_col-2] == 'O' ){
		current_state[peg_pos_row][peg_pos_col] == 'O';
		current_state[peg_pos_row][peg_pos_col-1] == 'O';
		current_state[peg_pos_row][peg_pos_col-2] == '*';
		return true;
	}
	else if(move == 4 && peg_pos_col +2 <= n_cols && current_state[peg_pos_row][peg_pos_col+1] == '*' && current_state[peg_pos_row][peg_pos_col+2] == 'O' ){
		current_state[peg_pos_row][peg_pos_col] == 'O';
		current_state[peg_pos_row][peg_pos_col+1] == 'O';
		current_state[peg_pos_row][peg_pos_col+2] == '*';
		return true;
	}
	return false;
	
}
int main(int argc, char *argv[])
{
	int n_rows = 9,n_cols = 9;
	char current_state[9][9] = {
	{' ', ' ',' ','*','*','*',' ', ' ',' '},
	{' ', ' ',' ','*','*','*',' ', ' ',' '},
	{' ', ' ',' ','*','*','*',' ', ' ',' '},
	{'*','*','*','*','*','*','*','*','*'},
	{'*','*','*','*','O','*','*','*','*'},
	{'*','*','*','*','*','*','*','*','*'},
	{' ', ' ',' ','*','*','*',' ', ' ',' '},
	{' ', ' ',' ','*','*','*',' ', ' ',' '},
	{' ', ' ',' ','*','*','*',' ', ' ',' '}
};

	return 0;
}
