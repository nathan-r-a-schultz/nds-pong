#include "Paddle.h"

Paddle::Paddle(int length, int width, int x, int y, float speed) 
    : length(length), width(width), x(x), y(y), speed(speed) {}

void Paddle::moveLeft() {
    x -= speed;
}

void Paddle::moveRight() {
    x += speed;
}

int Paddle::getX() const {
    return x;
}

int Paddle::getY() const {
    return y;
}

int Paddle::getLength() const {
    return length;
}

int Paddle::getWidth() const {
    return width;
}
