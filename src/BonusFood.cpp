#include "BonusFood.h"
#include <iostream>

unsigned int BonusFood::MAX_TIME_LIMIT = 5;

void BonusFood::Update() {
    if (m_remaining_time) {
        auto current_checkpoint = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(current_checkpoint - m_deadline_last_checkpoint);
        auto remaining_time = m_remaining_time - milliseconds.count();
        m_deadline_last_checkpoint = current_checkpoint;
        if (remaining_time > 0) {
            m_remaining_time = remaining_time;
        } else {
            m_remaining_time = 0;
        }
    }
}

void BonusFood::UpdatePosition(int x_, int y_) {
    m_x = static_cast<float>(x_);
    m_y = static_cast<float>(y_);
    m_food_body = std::move(PointToFoodBody(x_, y_));
}

bool BonusFood::isEaten() const {
    return m_eaten;
}

void BonusFood::Eaten(bool eaten_) {
    std::unique_lock<std::mutex> uLock(m_mutex);

    m_eaten = eaten_;
    if (!eaten_) {
        m_future = std::async(&BonusFood::BonusThread, this);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        m_remaining_time = MAX_TIME_LIMIT * 1000;
        m_deadline_last_checkpoint = std::chrono::system_clock::now();
    }
    if (eaten_) {
        m_remaining_time = 0;
        m_cond.notify_one();
        m_future.wait_for(std::chrono::milliseconds(100));
    }
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

void BonusFood::BonusThread() {
    std::unique_lock<std::mutex> uLock(m_mutex);
    m_cond.wait_for(uLock, std::chrono::seconds(MAX_TIME_LIMIT), [this]() {return isEaten();});
    m_eaten = true;
}

float BonusFood::GetRemainingTime() const {
    // return the percentage of remaining time
    return m_remaining_time / static_cast<float>(MAX_TIME_LIMIT * 1000);
}
