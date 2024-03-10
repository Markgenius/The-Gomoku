#include "wasted.h"
#include <iostream>

wasted::wasted() {
    image.load("./image/wasted.png");
    rect = image.rect();
}

QRect wasted::getRect() {
    return rect;
}

QImage & wasted::getImage() {
    return image;
}

void wasted::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
