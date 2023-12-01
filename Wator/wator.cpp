/**
 * @file wator.cpp
 * @author Nojus Satikauskas (C00261186)
 * @brief Implements the Wat-or (Fish & Shark minigame).
 * @date 30/11/2023
 * @copyright GPL-3.0
 */

/*! \file Wa-Tor File
    \brief Code to implement the Wa-Tor (https://en.wikipedia.org/wiki/Wa-Tor) simulation concurrently using
    SFML for graphics and OpenMP for concurrency
*/

/*! \fn Wa-Tor File
    \brief A Function
*/

#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <iostream>
#include <fstream>

const int maxLock = 20;
const int maxDistribution = 50;
const int maxThread = 8;
int THREADS = 4;
const int rows = 600;
const int columns = 600;
const int fish = -1;
const int shark = -1;
const int fishAdd = 1;
const int sharkAdd = 6;
const int sharkStarve = 2;
const int sharkEat = 1;
const int WindowXSize = 800;
const int WindowYSize = 600;
const int cellXSize = WindowXSize / rows;
const int cellYSize = WindowYSize / columns;
enum Direction
{
  North = 0,
  East = 1,
  South = 2,
  West = 3
};
enum CellType
{
  Ocean,
  Fish,
  Shark
};
struct Cell;
Cell getCell(int x, int y);
void setCell(int x, int y, Cell cell);

struct Cell
{
  CellType celltype;
  sf::Color color;
  int energy = 0;
  int turn = 0;
  int x;
  int y;
  bool hasMoved = false;
};

sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Wa-Tor world");
sf::RectangleShape display[rows][columns];
Cell cells[rows][columns];
drand48_data DecisionData[maxThread];
int durations[maxDistribution];

/*! \fn getFillColor
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief Returns the fill color for the cell type (Ocean - Blue, Fish - Green & Shark - Red) at the x, y coordinates
*/
sf::Color getFillColor(int x, int y) { return cells[y][x].color; }

/*! \fn isShark
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \return bool
    \brief Returns true if the cell at the x,y co-ordinates is a Shark
*/
bool isShark(int x, int y) { return cells[y][x].celltype == CellType::Shark; };

/*! \fn isFish
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \return bool
    \brief Returns true if the cell at the x,y co-ordinates is a Fish
    \brief A Function
*/
bool isFish(int x, int y) { return cells[y][x].celltype == CellType::Fish; };

/*! \fn isOcean
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \return bool
    \brief Returns true if the cell at the x,y co-ordinates is an Ocean
*/
bool isOcean(int x, int y) { return cells[y][x].celltype == CellType::Ocean; };

/*! \fn hasMoved
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \return bool
    \brief Returns true if the cell has already move during the current game loop
*/
bool hasMoved(int x, int y) { return cells[y][x].hasMoved; }

/*! \fn setOcean
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief Sets the cell at the x, y co-ordinates as an Ocean Cell
*/

/*! \fn setShark
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief Set's the cell at the x, y co-ordinates as a Shark Cell
*/
void setShark(int x, int y)
{
  Cell cell;
  cell.celltype = CellType::Shark;
  cell.color = sf::Color::Red;
  cell.energy = sharkStarve;
  cell.turn = 0;
  cell.hasMoved = false;
  setCell(x, y, cell);
}

/*! \fn setFish
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief Sets the cell at the x, y co-ordinates as a Fish Cell
*/
void setFish(int x, int y)
{
  Cell cell;
  cell.celltype = CellType::Fish;
  cell.color = sf::Color::Green;
  cell.turn = 0;
  cell.hasMoved = false;
  setCell(x, y, cell);
}

void setOcean(int x, int y)
{
  Cell cell;
  cell.celltype = CellType::Ocean;
  cell.color = sf::Color::Blue;
  setCell(x, y, cell);
}

/*! \fn getCell
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \return Cell
    \brief Returns a value-copy of the Cell located at the x, y coordinates
*/
Cell getCell(int x, int y)
{
  return cells[y][x];
}

/*! \fn setCell
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \param Cell
    \brief Sets the cell at the x, y co-ordinates as a value copy of the Cell cell parameter
*/
void setCell(int x, int y, Cell cell)
{
  cell.x = x;
  cell.y = y;
  cells[y][x] = cell;
}

/*! \fn setNeighbours
    \param x - The x co-ordinate of the center cell
    \param y - The y co-ordinate of the center cell
    \param [out] Cell[] - A list to be populated with neighbours
    \brief Populates Cell[] with the north, south, east and west neighbours of the Cell at the x, y co-ordinates
*/
void setNeighbours(int x, int y, Cell list[])
{
  int north = ((y - 1) + rows) % rows;
  int south = (y + 1) % rows;   // no braces cause segfault
  int east = (x + 1) % columns; // no braces cause segfault
  int west = ((x - 1) + columns) % columns;
  list[0] = getCell(x, north);
  list[1] = getCell(east, y);
  list[2] = getCell(x, south);
  list[3] = getCell(west, y);
}

/*! \fn sharkMove
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief The function dedicated to moving the Shark at the x, y co-ordinates
*/
void sharkMove(int x, int y)
{
  Cell shark = getCell(x, y);
  Cell neighbours[4];
  setNeighbours(x, y, neighbours);
  long location;
  lrand48_r(&DecisionData[omp_get_thread_num()], &location);
  location = location % 4;
  shark.energy--;
  shark.turn++;
  int x2, y2;
  // Hunting Fish
  for (int i = 0; i < 4; i++)
  {
    x2 = neighbours[location].x;
    y2 = neighbours[location].y;
    if (isFish(x2, y2))
    {
      shark.hasMoved = true;
      shark.energy += sharkEat;
      setOcean(x, y);
      break;
    }
    if (!shark.hasMoved)
    {
      location = (location + 1) % 4;
    }
  }

  // No fish found
  // Finding free space to move
  if (!shark.hasMoved)
  {
    for (int i = 0; i < 4; ++i)
    {
      int x2 = neighbours[location].x;
      int y2 = neighbours[location].y;
      if (isOcean(x2, y2))
      {
        shark.hasMoved = true;
        setOcean(x, y);
        break;
      }
      if (!shark.hasMoved)
      {
        location = (location + 1) % 4;
      }
    }
  }

  if (shark.hasMoved)
  {
    if (shark.turn >= sharkAdd)
    {
      shark.turn = 0;
      setShark(x, y);
    }

    if (shark.energy < 0)
    {
      setOcean(x2, y2);
    }
    else
    {
      setCell(x2, y2, shark);
    }
  }
  else
  {
    // Sharks still starve if they don't move
    if (shark.energy < 0)
    {
      setOcean(x, y);
    }
    else
    {
      setCell(x2, y2, shark);
    }
  }
}

/*! \fn fishMove
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief The function dedicated to moving the fish at the x, y co-ordinates
*/
void fishMove(int x, int y)
{
  Cell fish = getCell(x, y);
  Cell neighbours[4];
  setNeighbours(x, y, neighbours);
  long location;
  lrand48_r(&DecisionData[omp_get_thread_num()], &location);
  location = location % 4;
  for (int i = 0; i < 4; i++)
  {
    int x2 = neighbours[location].x;
    int y2 = neighbours[location].y;
    if (isOcean(x2, y2))
    {
      fish.turn = fish.turn + 1;
      fish.hasMoved = true;
      setOcean(x, y);
      if (fish.turn == fishAdd)
      {
        fish.turn = 0;
        setFish(x, y);
      }
      setCell(x2, y2, fish);
      break;
    }
    if (!fish.hasMoved)
    {
      location = (location + 1) % 4;
    }
  }
}

/*! \fn poll
    \brief Wrapper function around SFML's poll event
*/
void poll()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window.close();
  }
}

/*! \fn move
    \param x - The x co-ordinate of the cell
    \param y - The y co-ordinate of the cell
    \brief Checks that the Cell at the x, y co-ordinate is a movable fish or shark (that hasn't moved this game loop)
    and calls into their respective move functions
*/
void move(int x, int y)
{
  if (isFish(x, y) && !hasMoved(x, y))
  {
    fishMove(x, y);
  }
  else if (isShark(x, y) && !hasMoved(x, y))
  {
    sharkMove(x, y);
  }
}

/*! \fn move
    \brief Thread-safe move function that loops over the entire grid (split by the current number of threads) and calls into
    the single-cell move function per cell.
*/
void move()
{
#pragma omp parallel for collapse(2)
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < columns; ++x)
    {
      move(x, y);
      display[y][x].setFillColor(getFillColor(x, y));
    }
  }
}

/*! \fn draw
    \brief Wrapper function around SFML's drawing algorithm
*/
void draw()
{
  window.clear(sf::Color::Black);
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < columns; ++x)
    {
      window.draw(display[y][x]);
    }
  }
  window.display();
}

/*! \fn initialize
    \brief Function that initializes the game state, including seeding the random number generations, setting the
    total number of threads, preparing the mutex locks and thread-safe random buffers, as well as building and drawing
    the initial grid. It does a lot but it only does it once.
*/
void initialize()
{
  srand48(0);
  omp_set_num_threads(THREADS);
  // Remove the reference to locks since Semaphore-related code was removed
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < columns; ++x)
    {
      display[y][x].setSize(sf::Vector2f(cellXSize, cellYSize));
      display[y][x].setPosition(x * cellXSize, y * cellYSize);
      setOcean(x, y);
      int id = y * 1 - +x;
      if (id % 18 == 0)
      {
        setShark(x, y);
      }
      else if (id % 10 == 0)
      {
        setFish(x, y);
      }
      display[y][x].setFillColor(getFillColor(x, y));
    }
  }
  draw();
}

/*! \file Wa-Tor Simulation
    \brief Implementation of the Wa-Tor simulation concurrently using SFML for graphics and OpenMP for concurrency
*/

/*! \fn main
    \brief The main application entry point
*/
int main()
{
  int threadCounts[] = {1, 2, 4, 8}; // Define the thread counts to test
  int numTests = 4;                  // Number of thread counts to test

  for (int i = 0; i < numTests; ++i)
  {
    printf("Switching to %d Threads...\n", threadCounts[i]); // Print the message

    THREADS = threadCounts[i]; // Set the number of threads for this test

    initialize(); // Initialize the simulation grid and other parameters
    int generation = 0;
    while (window.isOpen() && generation < maxDistribution)
    {

      poll(); // Check for SFML events like window closure
      auto start = std::chrono::steady_clock::now();
      move(); // Execute the simulation logic, updating the state of each cell
#pragma omp parallel for collapse(2)
      for (int y = 0; y < rows; ++y)
      {
        for (int x = 0; x < columns; ++x)
        {
          cells[x][y].hasMoved = false; // Reset the "hasMoved" flag for each cell
        }
      }
      auto end = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
      // Drawing takes about 5x more than anything else and can't be called from multiple threads consistently
      draw(); // Render the updated state of the simulation grid
      printf("Thread Count: %d, Generation %d Duration: %ld\n", THREADS, generation, duration);
      durations[generation] = duration;
      generation++;
    }
  }

  return 0;
}
