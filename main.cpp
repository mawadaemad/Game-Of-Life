#include<iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Universe {
private:
    const int rows = 20;
    const int cols = 20;
    vector<vector<int>> grid;


public:

    Universe() : grid(rows, vector<int>(cols, 0)) {}

    void reset() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = 0;
            }
        }
    }
    void display_with_numbers() const {
        cout << "Grid Numbers:" << endl;
        int number = 1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if(grid[i][j]!=1)
                {
                    printf("%3d ", number++);
                }
                else {
                    printf("%3d ", 1);
                    number++;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    void setcells() {
        reset();
        int cell_number;
        cout << "Enter the cell numbers that you want alive (from [1,400]) enter 0 to stop:" << endl;
        while (true) {
            cout << "Enter cell number: ";
            cin >> cell_number;



            if (cell_number == 0) {
                break;
            }


            if (cell_number >= 1 && cell_number <= 400) {
                int row = (cell_number - 1) / cols;
                int col = (cell_number - 1) % cols;
                grid[row][col] = 1;
            }
            else {
                cout << "Error, Please enter a number within the range" << endl;
            }
            display_with_numbers();
            system("cls");
            display_with_numbers();

        }

    }


    int count_n(int row, int col) {
        int count = 0;

        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) {
                    continue;
                }
                int nr = row + dr, nc = col + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    count += grid[nr][nc];
                }
            }
        }
        return count;
    }

    void next_generation() {
        vector<vector<int>> new_grid = grid;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int neighbors = count_n(i, j);

                if (grid[i][j] == 1) {
                    // Underpopulation
                    if (neighbors < 2) {
                        new_grid[i][j] = 0;
                    }
                    //  any live cell with two or three live neighbors lives on to the next generation
                    else if (neighbors == 2 || neighbors == 3) {
                        new_grid[i][j] = 1;
                    }
                    // Overpopulation
                    else if (neighbors > 3) {
                        new_grid[i][j] = 0;
                    }
                }
                else {
                    // Reproduction
                    if (neighbors == 3) {
                        new_grid[i][j] = 1;
                    }
                }
            }
        }
        grid = new_grid;
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (grid[i][j] ? "O" : " ") << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void run(int generations, int delay = 500) {
        for (int gen = 0; gen < generations; ++gen) {
            display();
            this_thread::sleep_for(chrono::milliseconds(500));

            next_generation();
            system("cls");
        }
    }
};


int main() {
    Universe universe;
    universe.display_with_numbers();
    universe.setcells();
    int generations;
    cout << "enter the number of generations to simulate: ";
    cin >> generations;
    universe.run(generations);

    return 0;
}