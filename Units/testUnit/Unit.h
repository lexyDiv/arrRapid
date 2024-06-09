#pragma once

// 1536 256

template <typename T>
class Unit
{
public:
    int x;
    int y;
    int conor;
    int alpha;
    int animX = 0;
    int animY = 0;
    int animStepX = 1536 / 6;
    int animStepY = 256;
    int gabX;
    int gabY;
    T texture;
    Unit();
    Unit(int x,
         int y,
         int conor,
         int alpha,
         int gabX,
         int gabY,
         T texture);
         void draw();
   // ~Unit();
};

template <typename T>
inline Unit<T>::Unit()
{
}

template <typename T>
inline Unit<T>::Unit(int x, int y, int conor, int alpha, int gabX, int gabY, T texture)
{
    this->x = x;
    this->y = y;
    this->conor = conor;
    this->alpha = alpha;
    this->gabX = gabX;
    this->gabY = gabY;
    this->texture = texture;
}

template <typename T>
inline void Unit<T>::draw()
{
    this->texture->render(
        this->x,
        this->y,
        this->conor,
        this->alpha,
        this->animX,
        this->animY,
        this->animStepX,
        this->animStepY,
        this->gabX,
        this->gabY
    );
}
