#include "big_selector.h"
#include <iostream>

big_selector::big_selector() {
    image.load("./image/big_select.png");
    rect = image.rect();
}

QRect big_selector::getRect() {
    return rect;
}

QImage & big_selector::getImage() {
    return image;
}

void big_selector::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
