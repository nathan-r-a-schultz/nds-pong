#ifndef PADDLE_H
#define PADDLE_H

class Paddle {
public:
    Paddle(int length, int width, int x, int y, float speed);

    void moveLeft();
    void moveRight();

    int getX() const;
    int getY() const;
    int getLength() const;
    int getWidth() const;
    void render() const;

private:
    int length, width;
    int x, y;
    float speed;
};

#endif
