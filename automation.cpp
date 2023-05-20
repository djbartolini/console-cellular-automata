#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Size of the grid
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 30;

// Number of generations
const int NUM_GENERATIONS = 500;

// Probability of a dead cell becoming alive during reproduction
constexpr double REPRODUCTION_PROBABILITY = 0.2;

// Function to update the grid based on the rules of the cellular automaton
void updateGrid(std::vector<std::vector<char>> &grid)
{
  std::vector<std::vector<char>> newGrid = grid;

  for (int y = 1; y < GRID_HEIGHT - 1; ++y)
  {
    for (int x = 1; x < GRID_WIDTH - 1; ++x)
    {
      // Get the count of live neighbors
      int liveNeighbors = 0;
      for (int i = -1; i <= 1; ++i)
      {
        for (int j = -1; j <= 1; ++j)
        {
          liveNeighbors += (grid[y + i][x + j] == '#');
        }
      }

      // Apply the rules of the cellular automaton
      if (grid[y][x] == '#')
      {
        // Cell is alive
        --liveNeighbors; // Exclude the cell itself from the count
        if (liveNeighbors < 2 || liveNeighbors > 3)
        {
          // Cell dies due to underpopulation or overpopulation
          newGrid[y][x] = ' ';
        }
      }
      else
      {
        // Cell is dead
        if (liveNeighbors == 3 || (liveNeighbors == 2 && (rand() / double(RAND_MAX) < REPRODUCTION_PROBABILITY)))
        {
          // Cell becomes alive due to reproduction
          newGrid[y][x] = '#';
        }
      }
    }
  }

  // Update the grid
  grid = std::move(newGrid);
}

// Function to draw the grid on the console
void drawGrid(const std::vector<std::vector<char>> &grid)
{
  for (const auto &row : grid)
  {
    for (char cell : row)
    {
      std::cout << cell;
    }
    std::cout << '\n';
  }
}

int main()
{
  // Initialize the grid
  std::vector<std::vector<char>> grid(GRID_HEIGHT, std::vector<char>(GRID_WIDTH, ' '));

  // Set the initial seed pattern (glider)
  grid[1][3] = '#';
  grid[2][1] = '#';
  grid[2][3] = '#';
  grid[3][2] = '#';
  grid[3][3] = '#';

  // Main loop
  for (int generation = 0; generation < NUM_GENERATIONS; ++generation)
  {
    // Clear the console
    std::cout << "\033[2J\033[1;1H";

    // Draw the grid
    drawGrid(grid);

    // Update the grid
    updateGrid(grid);

    // Sleep for a short time (optional)
    // This gives a visual delay between generations
    // You may need to include <thread> and <chrono> headers for this to work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
