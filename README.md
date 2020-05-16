# CPPND: Capstone Snake Game Extended with Bonus Food

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Project Rubrics

#### Loop/Functions/IO
* The project reads data from a file and process the data, or the program writes data to a file.
    * File handling is used in program to save/read highest score
    * File: `src/utils.h`, Line# `26...46`
    * File: `src/game.cpp`, Line# `25, 58`
#### Object Oriented Programming
* The project uses Object Oriented Programming techniques.
    * OOP is used in game objects.
    * Files: `GameObject.h/cpp`, `BonusFood.h/cpp`
* Classes use appropriate access specifiers for class members.
    * Files: `GameObject.h`, `BonusFood.h`
* Derived class functions override virtual base class functions.
    * Bonus food is overriding the Update method of Game Object.
    * File: `BonusFood.h`, Line# `17`
    * File: `BonusFood.cpp`, Line# `6`
* Templates generalize functions in the project.
    * Random number generator `class RandomNumberGenerator` is generalized using templates
    * FIle: `utils.h`, Line# `10`
#### Memory Management
* The project makes use of references in function declarations.
    * `BonusFood` object is passed to renderer as a reference
    * File: `rendere.h`, Line# `15`
    * Method: `void Render(Snake const snake, SDL_Point const &food, const BonusFood &bonus_food);`
* The project uses move semantics to move data, instead of copying it, where possible.
    * File: `BonusFood.cpp`, Line# `23`
#### Concurrency
* The project uses multithreading.
    * File: `BonusFood.cpp`, Line# `35`
* A promise and future is used in the project.
    * File: `BonusFood.h`, Line# `42`
    * File: `BonusFood.cpp`, Line# `43`
* A mutex or lock is used in the project.
    * File: `BonusFood.h`, Line# `40`
    * File: `BonusFood.cpp`, Line# `31, 66`
* A condition variable is used in the project.
    * File: `BonusFood.h`, Line# `41`
    * File: `BonusFood.cpp`, Line# `42, 67`
