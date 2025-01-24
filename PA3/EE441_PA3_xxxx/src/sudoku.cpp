#include <iostream>
#include "sudoku.hpp"
#include "memory.hpp"

#include "list.hpp"


Sudoku::Sudoku() {
    for (size_t id = 1; id <= 81; ++id) {
        add_vertex();
    }
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            size_t current = row * 9 + col + 1;

            for (size_t c = 0; c < 9; ++c) {
                if (c != col) {
                    connect(current, row * 9 + c + 1);
                }
            }

            for (size_t r = 0; r < 9; ++r) {
                if (r != row) {
                    connect(current, r * 9 + col + 1);
                }
            }

            size_t subgrid_row_start = (row / 3) * 3;
            size_t subgrid_col_start = (col / 3) * 3;
            for (size_t r = subgrid_row_start; r < subgrid_row_start + 3; ++r) {
                for (size_t c = subgrid_col_start; c < subgrid_col_start + 3; ++c) {
                    if (r != row || c != col) {
                        connect(current, r * 9 + c + 1);
                    }
                }
            }
        }
    }
}
Sudoku::~Sudoku() {
}

bool Sudoku::solve()
{
    return color();
}

void Sudoku::print() {
    int board[9][9] = {0};

    for (size_t id = 1; id <= 81; ++id) {
        Vertex* vertex = (*this)[id];
        int color = vertex->color();
        board[(id - 1) / 9][(id - 1) % 9] = color;
    }

  // Print the board with proper formatting
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Print the current number
            std::cout << board[row][col] << " ";

            // Print vertical separators for the 3x3 grid
            if ((col + 1) % 3 == 0 && col != 8) {
                std::cout << "| ";
            }
        }

        // Print the line separator after every 3 rows
        if ((row + 1) % 3 == 0 && row != 8) {
            std::cout << std::endl << "---------------------" << std::endl;
        }

        // Newline after each row
        std::cout << std::endl;
    }
}

int Sudoku::max_color() const {
    return 9;
}

