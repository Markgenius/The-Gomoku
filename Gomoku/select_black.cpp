#include "select_black.h"
#include <iostream>

select_black::select_black() {
    image.load("./image/black_select.png");
    rect = image.rect();
}

QRect select_black::getRect() {
    return rect;
}

QImage & select_black::getImage() {
    return image;
}

void select_black::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
