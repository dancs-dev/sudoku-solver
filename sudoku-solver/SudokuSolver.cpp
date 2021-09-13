#include <cmath>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> int2d;
typedef std::vector<std::vector<std::vector<int>>> int3d;
typedef std::vector<std::vector<int>> sudoku;
typedef std::vector<int> line;

line getRow(const sudoku& sudoku, const int& rowNum);
line getCol(const sudoku& sudoku, const int& colNum);
line getSquare(const sudoku& sudoku, const int& rowNum, const int& colNum);
bool check(const line& nineNumList);
bool checkAllComplete(const sudoku& sudoku);

class SudokuSolver;

std::ostream& operator<<(std::ostream& os, const line& input);
std::ostream& operator<<(std::ostream& os, const sudoku& input);

sudoku hard = { {2, 5, 0, 0, 8, 9, 0, 0, 0},
				{0, 0, 0, 3, 0, 0, 0, 4, 0},
				{0, 6, 0, 0, 2, 0, 0, 0, 0},
				{0, 0, 9, 2, 0, 0, 7, 1, 0},
				{5, 0, 0, 0, 0, 0, 0, 0, 8},
				{0, 7, 2, 0, 0, 8, 5, 0, 0},
				{0, 0, 0, 0, 1, 0, 0, 2, 0},
				{0, 2, 0, 0, 0, 6, 0, 0, 0},
				{0, 0, 0, 4, 3, 0, 0, 7, 1} };

sudoku hardSolution = { {2, 5, 4, 1, 8, 9, 3, 6, 7},
						{9, 1, 7, 3, 6, 5, 8, 4, 2},
						{3, 6, 8, 7, 2, 4, 1, 5, 9},
						{6, 8, 9, 2, 5, 3, 7, 1, 4},
						{5, 4, 3, 6, 7, 1, 2, 9, 8},
						{1, 7, 2, 9, 4, 8, 5, 3, 6},
						{4, 3, 6, 8, 1, 7, 9, 2, 5},
						{7, 2, 1, 5, 9, 6, 4, 8, 3},
						{8, 9, 5, 4, 3, 2, 6, 7, 1} };

sudoku easy = { {2, 5, 4, 1, 8, 9, 3, 0, 7},
				{9, 1, 7, 3, 6, 5, 8, 4, 2},
				{3, 6, 8, 7, 2, 4, 1, 5, 9},
				{6, 8, 9, 2, 5, 0, 7, 0, 4},
				{5, 0, 3, 6, 0, 0, 2, 9, 8},
				{1, 7, 2, 9, 4, 8, 5, 3, 6},
				{4, 3, 6, 8, 1, 7, 9, 2, 5},
				{7, 0, 1, 5, 9, 6, 4, 8, 3},
				{8, 9, 5, 4, 0, 2, 6, 7, 1} };

line getRow(const sudoku& sudoku, const int& rowNum) {
	return sudoku[rowNum];
}

line getCol(const sudoku& sudoku, const int& colNum) {
	line col = {};
	for (line row : sudoku) {
		col.push_back(row[colNum]);
	}
	return col;
}

line getSquare(const sudoku& sudoku, const int& rowNum, const int& colNum) {
	int accessRow = rowNum * 3;
	int accessCol = colNum * 3;

	line square = {};

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			square.push_back(sudoku[accessRow + row][accessCol + col]);
		}
	}

	return square;
}

bool check(const line& nineNumList) {
	line done = {};
	for (int num : nineNumList) {
		if (num == 0) return false;
	}
	for (int num : nineNumList) {
		for (int dupe : done) {
			if (num == dupe) return false;
		}
		done.push_back(num);
	}
	return true;
}

bool checkAllComplete(const sudoku& sudoku) {
	int row, col;
	for (int i = 0; i < 9; i++) {
		if (!(check(getRow(sudoku, i)))) return false;
		if (!(check(getCol(sudoku, i)))) return false;
	}
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (!(check(getSquare(sudoku, row, col)))) return false;
		}
	}
	return true;
}

line filter(const line& lineA, const line& lineB) {
	line filtered = {};
	for (int a : lineA) {
		bool ok = true;
		for (int b : lineB) {
			if (a == b) ok = false;
		}
		if (ok) {
			filtered.push_back(a);
		}
	}
	return filtered;
}

line filterCandidates(const sudoku& sudoku, const int& rowNum, const int& colNum) {
	line candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	line row = getRow(sudoku, rowNum);
	line col = getCol(sudoku, colNum);
	line square = getSquare(sudoku, std::floor(rowNum / 3), std::floor(colNum / 3));
	candidates = filter(candidates, row);
	candidates = filter(candidates, col);
	candidates = filter(candidates, square);

	return candidates;
}

class SudokuSolver {
public:
	sudoku result = { {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
					  {-1, -1, -1, -1, -1, -1, -1, -1, -1} };
	sudoku challenge;
	sudoku expected;
	std::string name;
	sudoku solve();
private:
	sudoku solver(sudoku sudoku);
};

sudoku SudokuSolver::solve() {
	solver(challenge);
	return result;
}

sudoku SudokuSolver::solver(sudoku sudoku) {
	line candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i, ii;
	for (int n = 0; n < 81; n++) {
		i = std::floor(n / 9);
		ii = n % 9;
		if (sudoku[i][ii] == 0) {
			for (int elem : filterCandidates(sudoku, i, ii)) {
				sudoku[i][ii] = elem;

				if (checkAllComplete(sudoku)) {
					result = sudoku;
					return sudoku;
				}
				else {
					if (checkAllComplete(solver(sudoku))) {
						return sudoku;
					}
				}
			}
			break;
		}
	}
	sudoku[i][ii] = 0;
	return sudoku;
}

int main() {
	SudokuSolver s;
	s.challenge = hard;
	std::cout << s.solve() << std::endl;
	return 0;
}
std::ostream& operator<<(std::ostream& os, const line& input)
{
	for (auto const& i : input) {
		os << i << " ";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const sudoku& input)
{
	for (auto const& i : input) {
		os << i << "\n";
	}
	return os;
}