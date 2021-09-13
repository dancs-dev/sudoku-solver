#include <iostream>

#include "SudokuSolver.h"

SudokuSolver::sudoku hard = { {2, 5, 0, 0, 8, 9, 0, 0, 0},
                {0, 0, 0, 3, 0, 0, 0, 4, 0},
                {0, 6, 0, 0, 2, 0, 0, 0, 0},
                {0, 0, 9, 2, 0, 0, 7, 1, 0},
                {5, 0, 0, 0, 0, 0, 0, 0, 8},
                {0, 7, 2, 0, 0, 8, 5, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 2, 0},
                {0, 2, 0, 0, 0, 6, 0, 0, 0},
                {0, 0, 0, 4, 3, 0, 0, 7, 1} };

SudokuSolver::sudoku hardSolution = { {2, 5, 4, 1, 8, 9, 3, 6, 7},
                        {9, 1, 7, 3, 6, 5, 8, 4, 2},
                        {3, 6, 8, 7, 2, 4, 1, 5, 9},
                        {6, 8, 9, 2, 5, 3, 7, 1, 4},
                        {5, 4, 3, 6, 7, 1, 2, 9, 8},
                        {1, 7, 2, 9, 4, 8, 5, 3, 6},
                        {4, 3, 6, 8, 1, 7, 9, 2, 5},
                        {7, 2, 1, 5, 9, 6, 4, 8, 3},
                        {8, 9, 5, 4, 3, 2, 6, 7, 1} };

SudokuSolver::sudoku easy = { {2, 5, 4, 1, 8, 9, 3, 0, 7},
                {9, 1, 7, 3, 6, 5, 8, 4, 2},
                {3, 6, 8, 7, 2, 4, 1, 5, 9},
                {6, 8, 9, 2, 5, 0, 7, 0, 4},
                {5, 0, 3, 6, 0, 0, 2, 9, 8},
                {1, 7, 2, 9, 4, 8, 5, 3, 6},
                {4, 3, 6, 8, 1, 7, 9, 2, 5},
                {7, 0, 1, 5, 9, 6, 4, 8, 3},
                {8, 9, 5, 4, 0, 2, 6, 7, 1} };

void sudokuSolver(SudokuSolver::sudoku sudoku, SudokuSolver::sudoku solution, std::string name) {
    SudokuSolver s(sudoku, solution, name);
    std::cout << "Solving: " << s.getName() << std::endl;
    std::cout << std::endl << "Calculated solution:" << std::endl << s.solve() << std::endl;
    std::cout << "Solution matches expected: " << (s.asExpected() ? "Yes" : "No") << std::endl;
}

int main() {
    sudokuSolver(hard, hardSolution, "Hard");

    return 0;
}
