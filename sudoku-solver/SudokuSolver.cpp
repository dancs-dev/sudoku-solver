#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> sudoku;
typedef std::vector<int> line;

line getRow(const sudoku& sudoku, int rowNum);
line getCol(const sudoku& sudoku, int colNum);
line getSquare(const sudoku& sudoku, int rowNum, int colNum);
bool check(const line& nineNumList);
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

int main() {
	std::cout << check({9, 8, 1, 2, 3, 5, 4, 6, 7}) << std::endl;
	return 0;
}

line getRow(const sudoku& sudoku, int rowNum) {
	return sudoku[rowNum];
}

line getCol(const sudoku& sudoku, int colNum) {
	line col = {};
	for (line row : sudoku) {
		col.push_back(row[colNum]);
	}
	return col;
}

line getSquare(const sudoku& sudoku, int rowNum, int colNum) {
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