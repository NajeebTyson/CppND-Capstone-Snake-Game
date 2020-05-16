#ifndef SDL2TEST_UTILS_H
#define SDL2TEST_UTILS_H

#include <random>
#include <fstream>
#include <iostream>

#define SCORE_FILENAME "score.txt"

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

void write_score(unsigned int score) {
    std::ofstream file(SCORE_FILENAME);
    if (!file.is_open()) {
        std::cout << "Error! Failure score update." << std::endl;
        return;
    }
    file << score << std::endl;
    file.close();
}

unsigned int read_score() {
    std::ifstream file(SCORE_FILENAME);
    if (!file.is_open()) {
        std::cout << "Error! Failure score reading." << std::endl;
        return 0;
    }
    unsigned int score;
    file >> score;
    file.close();
    return score;
}

#endif //SDL2TEST_UTILS_H
