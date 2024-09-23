#ifndef BALL_H
#define BALL_H

class Ball {
public:
    Ball(int width, int height, float xSpeed, float ySpeed);

    void updatePosition();
    void reverseX();
    void reverseY();
    void increaseSpeed();
    void resetSpeed();
    void reset();

    bool checkCollision(int paddleX, int paddleY, int paddleLength, int paddleWidth) const;
    bool isOutOfBounds() const;

    int getX() const;
    int getY() const;
    void setX(int newX) const;
    void setY(int newX) const;
    float getSpeedX() const;
    float getSpeedY() const;
    int getWidth() const;
    int getHeight() const;

private:
    mutable int x, y;
    mutable float xSpeed, ySpeed;
    int width, height;
};

#endif
