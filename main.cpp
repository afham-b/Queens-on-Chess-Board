// 8-Queens Problem
#include <iostream>
#include <list> 
using namespace std;

// class Board - Represents the chess board and placement of queens
class Board {
public:
	static const int N = 8; // size of the board. 8x8 by default
protected:
	bool diags1[2 * N - 1]; // Diagonals in one direction
	bool diags2[2 * N - 1]; // Diagonals in the other direction
	int rows[N]; // Column numbers of where Queen is placed in each row
	void printDivider (int row);
	int diag1(int r, int c) { return r + c; } // Calculate diagonal 1 for row and column
	int diag2(int r, int c) { return N - r + c - 1; } // Calculate diagonal 2
public:
	Board();
	bool isQueen (int r, int c) { return rows[r] == c; }
	bool isSolved() const;
	bool placeQueen(int r, int c);
	void print ();
	void removeQueen(int r);
};

Board::Board() {
	for (int i = 0; i < N; i++)
		rows[i] = -1; // No Queen in any row
	// Mark all diagonals as unoccupied
	for (int i = 0; i < 2 * N - 1; i++)
		diags1[i] = diags2[i] = false;
}

// Prints the chess board
void Board::print () {
	for (int r = 0; r < N; r++) {
		printDivider(r);
		cout << "|";
		for (int c = 0; c < N; c++)
			cout << (isQueen(r, c) ? " Q " : "   ") << "|";
		cout << endl;
	}
	printDivider(N);
}

// Place a queen in the given row/column, if possible.
bool Board::placeQueen(int r, int c) {
	// Check the row
	if (rows[r] != -1 && rows[r] != c)
		return false;
	// Check the columns
	for (int i = 0; i < N; i++)
		if (rows[i] == c)
			return false;
	// Check to see if both diagonals are available
	if (diags1[diag1(r, c)] || diags2[diag2(r, c)])
		return false;
	// Place the queen
	rows[r] = c;
	diags1[diag1(r, c)] = true;
	diags2[diag2(r, c)] = true;
	return true;
}

// Helper function for printing the chess board
void Board::printDivider (int r) {
	if (!r || r == N)
		for (int i = 0; i < 4 * N + 1; i++)
			cout << "-";
	else {
		cout << "|";
		for (int i = 0; i < N; i++)
			cout << "---|";
	}
	cout << endl;
}

bool Board::isSolved() const {
	for (int i = 0; i < N; i++)
		if (rows[i] == -1)
			return false;
	return true;
}

void Board::removeQueen(int r) {
	diags1[diag1(r, rows[r])] = false;
	diags2[diag2(r, rows[r])] = false;
	rows[r] = -1;
}

void solve(Board& board, int row, list<Board>& solutions) {
	// Attempt to place a queen in the given row.
	if (row < Board::N) {
		for (int col = 0; col < Board::N; col++)
			if (board.placeQueen(row, col)) {
				solve(board, row + 1, solutions);
				if (board.isSolved())
					return;
				board.removeQueen(row);
			}
	}
  else 
    solutions.push_back(board); 
}

int main () {
	Board b;
  list<Board> solutions; 
	solve(b, 0, solutions);
	//b.print();   // <- print one solution 
  for( auto s: solutions)    // loop to print all solutions 
    s.print(); 
  cout << solutions.size() <<endl; 
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}