#include "Ball.h"

Ball::Ball(int width, int height, float xSpeed, float ySpeed)
    : x(0), y(0), xSpeed(xSpeed), ySpeed(ySpeed), width(width), height(height) {}

void Ball::updatePosition() {
    x += xSpeed;
    y += ySpeed;
}

void Ball::reverseX() {
    xSpeed = -xSpeed;
}

void Ball::reverseY() {
    ySpeed = -ySpeed;
}

void Ball::increaseSpeed() {
    xSpeed *= 1.1;
    ySpeed *= 1.1;
}

void Ball::resetSpeed() {
    xSpeed = 0;
    ySpeed = 0;
}

void Ball::reset() {
    x = 0;
    y = 0;
    xSpeed = 1;
    ySpeed = 1;
}

bool Ball::checkCollision(int paddleX, int paddleY, int paddleLength, int paddleWidth) const {
    return x < paddleX + paddleLength && x + width > paddleX && y + height >= paddleY && y <= paddleY + paddleWidth;
}

bool Ball::isOutOfBounds() const {
    return y + height > 191;
}

int Ball::getX() const {
    return x;
}

int Ball::getY() const {
    return y;
}

void Ball::setX(int newX) const {
    x = newX;
}

void Ball::setY(int newY) const {
    y = newY;
}

float Ball::getSpeedX() const {
    return xSpeed;
}

float Ball::getSpeedY() const {
    return ySpeed;
}

int Ball::getWidth() const {
    return width;
}

int Ball::getHeight() const {
    return height;
}
