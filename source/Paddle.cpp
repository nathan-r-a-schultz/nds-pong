#include <nds.h>
#include <gl2d.h>
#include "Paddle.h"

Paddle::Paddle(int length, int width, int x, int y, float speed) 
    : length(length), width(width), x(x), y(y), speed(speed) {}

void Paddle::moveLeft() {
    x -= speed;
}

void Paddle::moveRight() {
    x += speed;
}

void Paddle::constrainPosition() {
    if (x < 0) {
        x = 0;
    }
    if (x > 255 - length) {
        x = 255 - length;
    }
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

void Paddle::render() const {
    glBoxFilled(x, y, x + length, y + width, RGB15(255, 255, 255));
    glBoxFilled(x + 1, y + 1, x + length - 1, y + width - 1, RGB15(212, 212, 212));
}

void Paddle::reset() const {
    x = 128 - 50 / 2;
    y = 157;
}