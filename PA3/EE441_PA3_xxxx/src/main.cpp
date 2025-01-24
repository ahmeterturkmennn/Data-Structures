#include <iostream>
#include "sudoku.hpp"
#include "memory.hpp"

void play(const char* filename)
{
    Sudoku sudoku;
    sudoku.set_clues(filename);
    if (sudoku.solve()) {
        sudoku.print();
    } else {
        std::cout << "No solution available!\n" << std::endl;
    }
}

int main()
{
    play("C:/Users/90551/Desktop/EE441PA3/project_template/data/s1.txt");
    play("C:/Users/90551/Desktop/EE441PA3/project_template/data/s2.txt");
    play("C:/Users/90551/Desktop/EE441PA3/project_template/data/s3.txt"); // No solution
}
