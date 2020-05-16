#ifndef SDL2TEST_UTILS_H
#define SDL2TEST_UTILS_H

#include <random>

template <typename T>
class RandomNumberGenerator {
public:
    RandomNumberGenerator(int start, int end): engine(dev()), distribution(start, end) {
    }

    T Get() {
        return static_cast<T>(distribution(engine));
    }

public:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution;
};

#endif //SDL2TEST_UTILS_H
