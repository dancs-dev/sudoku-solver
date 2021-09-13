#include <cmath>
#include <iostream>

#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(sudoku challenge,
    sudoku expected,
    std::string name)
    :
    challenge(challenge),
    expected(expected),
    name(name) {
    result = { {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1},
               {-1, -1, -1, -1, -1, -1, -1, -1, -1} };
}

SudokuSolver::line SudokuSolver::getRow(const sudoku& sudoku, const int& rowNum) {
    return sudoku[rowNum];
}

SudokuSolver::line SudokuSolver::getCol(const sudoku& sudoku, const int& colNum) {
    line col = {};
    for (line row : sudoku) {
        col.push_back(row[colNum]);
    }
    return col;
}

SudokuSolver::line SudokuSolver::getSquare(const sudoku& sudoku, const int& rowNum, const int& colNum) {
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

bool SudokuSolver::check(const line& nineNumList) {
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

bool SudokuSolver::checkAllComplete(const sudoku& sudoku) {
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

SudokuSolver::line SudokuSolver::filter(const line& lineA, const line& lineB) {
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

SudokuSolver::line SudokuSolver::filterCandidates(const sudoku& sudoku, const int& rowNum, const int& colNum) {
    line candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    line row = getRow(sudoku, rowNum);
    line col = getCol(sudoku, colNum);
    line square = getSquare(sudoku, std::floor(rowNum / 3), std::floor(colNum / 3));
    candidates = filter(candidates, row);
    candidates = filter(candidates, col);
    candidates = filter(candidates, square);

    return candidates;
}

SudokuSolver::sudoku SudokuSolver::solve() {
    solver(challenge);
    return result;
}

SudokuSolver::sudoku SudokuSolver::solver(sudoku sudoku) {
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

bool SudokuSolver::asExpected() {
    return result == expected;
}

std::string SudokuSolver::getName() {
    return name;
}

std::ostream& operator<<(std::ostream& os, const SudokuSolver::line& input)
{
    for (auto const& i : input) {
        os << i << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SudokuSolver::sudoku& input)
{
    for (auto const& i : input) {
        os << i << "\n";
    }
    return os;
}
