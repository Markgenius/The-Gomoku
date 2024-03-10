#include "select_white.h"
#include <iostream>

select_white::select_white() {
    image.load("./image/white_select.png");
    rect = image.rect();
}

QRect select_white::getRect() {
    return rect;
}

QImage & select_white::getImage() {
    return image;
}

void select_white::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
