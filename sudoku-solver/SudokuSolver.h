#pragma once

#include <string>
#include <vector>


class SudokuSolver {
public:
    typedef std::vector<std::vector<int>> sudoku;
    typedef std::vector<int> line;
    SudokuSolver(sudoku challenge,
                 sudoku expected, 
                 std::string name);
    SudokuSolver::sudoku solve();
    bool asExpected();
    std::string getName();

private:
    sudoku result;
    sudoku challenge;
    sudoku expected;
    std::string name;

    line getRow(const sudoku& sudoku, const int& rowNum);
    line getCol(const sudoku& sudoku, const int& colNum);
    line getSquare(const sudoku& sudoku, const int& rowNum, const int& colNum);
    line filter(const line& lineA, const line& lineB);
    line filterCandidates(const sudoku& sudoku, const int& rowNum, const int& colNum);
    bool check(const line& nineNumList);
    bool checkAllComplete(const sudoku& sudoku);
    sudoku solver(sudoku sudoku);
};

std::ostream& operator<<(std::ostream& os, const SudokuSolver::line& input);
std::ostream& operator<<(std::ostream& os, const SudokuSolver::sudoku& input);
