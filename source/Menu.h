#ifndef MENU_H
#define MENU_H

class Menu {
public:
    Menu();

    void setTouchCoords(int touchX, int touchY); 

private:
    mutable int mode;
    void changeMenu();
};

#endif
