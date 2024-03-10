#include "pass.h"
#include <iostream>

pass::pass() {
    image.load("./image/pass.png");
    rect = image.rect();
}

QRect pass::getRect() {
    return rect;
}

QImage & pass::getImage() {
    return image;
}

void pass::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
