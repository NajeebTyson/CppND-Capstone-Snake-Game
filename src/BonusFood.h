#ifndef SDL2TEST_BONUSFOOD_H
#define SDL2TEST_BONUSFOOD_H

#include <SDL.h>
#include <vector>
#include "GameObject.h"

class BonusFood: public GameObject {
public:
    BonusFood() = default;

    void Update() override;

    void Eaten(bool eaten_);

    bool isEaten() const;

    void UpdatePosition(int x_, int y_);

    bool FoodCell(int x, int y) const;

    static std::vector<SDL_Point> PointToFoodBody(int x, int y);

    std::vector<SDL_Point> m_food_body{4};
private:
    bool m_eaten{true};
};


#endif //SDL2TEST_BONUSFOOD_H
