#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "GameObject.h"

class Snake: public GameObject {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        GameObject(grid_width / 2, grid_height / 2),
        head_x(m_x), head_y(m_y) {}

  void Update() override;

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float &head_x;
  float &head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif