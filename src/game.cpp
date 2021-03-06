#include <iostream>

#include "SDL.h"
#include "game.h"
#include "utils.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  unsigned int highest_score = read_score();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, bonus_food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, highest_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  if (score > highest_score) {
      write_score(score);
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item or bonus food item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
        if (!bonus_food.isEaten() && bonus_food.FoodCell(x, y)) {
            continue;
        }
        food.x = x;
        food.y = y;
//        std::cout << "Placing food: (" << y <<", "<<x <<")\n";
        return;
    }
  }
}

void Game::PlaceBonusFood() {
    // we want to generate new bonus food after every five foods m_eaten
    // TODO: make it 5
    if (food_eaten%3 != 0 or food_eaten < 2) {
        return;
    }
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);

        // check that the location is not occupied by snake or food
        bool place_food{true};
        for (auto &point: BonusFood::PointToFoodBody(x, y)) {
            if ((food.x == point.x && food.y == point.y) || snake.SnakeCell(point.x, point.y)) {
                place_food = false;
            }
        }
        if (place_food) {
            bonus_food.UpdatePosition(x, y);
            bonus_food.Eaten(false);
            return;
        }
    }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    food_eaten++;
    PlaceFood();
    PlaceBonusFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if there's bonus food over here
  if (!bonus_food.isEaten() && bonus_food.FoodCell(new_x, new_y)) {
      bonus_food.Eaten(true);
      score += 5;
      snake.GrowBody();
  }

  bonus_food.Update();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
