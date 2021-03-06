#ifndef SDL2TEST_BONUSFOOD_H
#define SDL2TEST_BONUSFOOD_H

#include <SDL.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include "GameObject.h"

class BonusFood: public GameObject {
public:
    BonusFood() = default;

    void Update() override;

    void Eaten(bool eaten_);

    bool isEaten() const;

    float GetRemainingTime() const;

    void UpdatePosition(int x_, int y_);

    bool FoodCell(int x, int y) const;

    static std::vector<SDL_Point> PointToFoodBody(int x, int y);

    std::vector<SDL_Point> m_food_body{4};

private:
    // private methods
    void BonusThread();
private:
    bool m_eaten{true};
    unsigned int m_remaining_time{0};  // time in milliseconds
    std::chrono::time_point<std::chrono::system_clock> m_deadline_last_checkpoint;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::future<void> m_future;

    // maximum time limit for bonus food to display in seconds
    static unsigned int MAX_TIME_LIMIT;
};


#endif //SDL2TEST_BONUSFOOD_H
