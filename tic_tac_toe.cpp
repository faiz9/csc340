#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);
  // while (1) {. For testing
  //   makeAMove(board, 'X');
  //   cout << "----" << endl;
  //   displayBoard(board);
  //   if (isWon('X', board) == true)
  //     break;
  // }
  while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}
	return 0;
} 

void displayBoard(char board[][3]) {
	cout << "-------------" << endl;
	for (int i = 0; i < 3; i++) {   //row
		// Printing the row
		cout << "| ";
		for (int j = 0; j < 3; j++) {  //colounm
			cout <<  board[i][j] << " | ";
		}
		cout << endl;
    cout << "-------------" << endl;
	}
}

void makeAMove(char board[][3], char c) {
  int row, col;

  while(true) {
    cout << "Enter a row (0, 1, 2) for player " << c << "    : ";
    cin >> row;
    // Validate row value
    while(row < 0 || row > 2) {
      cout << "Invalid row value. Please try again" << endl;
      cout << "Enter a row (0, 1, 2) for player " << c << "  : ";
      cin >> row;    
    }

    cout << "Enter a column (0, 1, 2) for player "<< c << " : ";
    cin >> col;
    while(col < 0 || col > 2) {
      cout << "Invalid col value. Please try again" << endl;
      cout << "Enter a col (0, 1, 2) for player " << c << "  : ";
      cin >> col;    
    }
    // Check available board
    if (board[row][col] == ' ') {
      board[row][col] = c;
      break;
    } else {
       cout <<"This cell is already occupied. Try a different cell" << endl;   
    }
  }
}

bool isWon(char c, char board[][3]) {
    // Check winner by row
  for (int i = 0; i < 3; i++) {
    if (c == board[i][0] && c == board[i][1] && c == board[i][2])
      return true;
  }
  // Check winner by column
  for (int i = 0; i < 3; i++) {
    if (c == board[0][i] && c == board[1][i] && c == board[2][i])
    return true;
  }

  if (c == board[0][0] && c == board[1][1] && c == board[2][2]) {
    return true;
  }

  if (c == board[0][2] && c == board[1][1] && c == board[2][0]) {
    return true;
  }

  return false;
  
}

bool isDraw(char board[][3]) {
  int count = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        count += 1;
      }
      if (count > 1) {
        // Board has available space for player
        return false;
      }
    }
  }
  return true;
}
