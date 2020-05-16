#ifndef SDL2TEST_GAMEOBJECT_H
#define SDL2TEST_GAMEOBJECT_H


class GameObject {
public:
    GameObject() = default;

    GameObject(float x_, float y_): m_x(x_), m_y(y_) {}

    virtual void Update() = 0;

    float m_x{0}, m_y{0};  // position of object

};

#endif //SDL2TEST_GAMEOBJECT_H
