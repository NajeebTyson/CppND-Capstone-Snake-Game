#include "BonusFood.h"

void BonusFood::Update() {

}

void BonusFood::UpdatePosition(int x_, int y_) {
    m_x = static_cast<float>(x_);
    m_y = static_cast<float>(y_);
    m_food_body = PointToFoodBody(x_, y_);
}

bool BonusFood::isEaten() const {
    return m_eaten;
}

void BonusFood::Eaten(bool eaten_) {
    m_eaten = eaten_;
}

bool BonusFood::FoodCell(int x, int y) const {
    for (auto &point: m_food_body) {
        if (point.x == x and point.y == y) {
            return true;
        }
    }
    return false;
}

std::vector<SDL_Point> BonusFood::PointToFoodBody(int x, int y) {
    std::vector<SDL_Point> body(4);
    body[0] = {x, y};
    body[1] = {x + 1, y};
    body[2] = {x, y + 1};
    body[3] = {x + 1, y + 1};
    return body;
}



