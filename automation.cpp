#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


// Function to print the current state of the grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell ? "#" : " ") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to simulate one generation of the game
void simulateGeneration(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<int>> newGrid(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = 0;

            // Count the live neighbors of each cell
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) continue;
                    int ni = (i + x + rows) % rows;
                    int nj = (j + y + cols) % cols;
                    liveNeighbors += grid[ni][nj];
                }
            }

            // Apply the rules of the game
            if (grid[i][j]) {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    newGrid[i][j] = 0; // Cell dies due to underpopulation/overpopulation
                else
                    newGrid[i][j] = 1; // Cell survives to the next generation
            } else {
                if (liveNeighbors == 3)
                    newGrid[i][j] = 1; // Cell becomes alive due to reproduction
                else
                    newGrid[i][j] = 0; // Cell remains dead
            }
        }
    }

    // Update the original grid with the new generation
    grid = newGrid;
}


int main() {
  int rows = 72;
  int cols = 280;

    // Define the initial grid
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    int numAliveCells = rows * cols * 0.1;

    for (int i = 0; i < numAliveCells; ++i) {
      int randomRow = rand() % rows;
      int randomCol = rand() % cols;
      grid[randomRow][randomCol] = 1;
    }

    // Simulate and print each generation
    for (int generation = 1; generation <= 2500; ++generation) {
        std::cout << "Generation " << generation << ":" << std::endl;
        printGrid(grid);
        simulateGeneration(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }

    return 0;
}
