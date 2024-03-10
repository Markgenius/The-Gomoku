#include "black_chess.h"
#include <iostream>

black_chess::black_chess(int x, int y) {
    image.load("./image/black_.png");

    rect = image.rect();
    rect.translate(x, y);
}

QRect black_chess::getRect() {
    return rect;
}

void black_chess::setRect(QRect rct) {
    rect = rct;
}

QImage & black_chess::getImage() {
    return image;
}

bool black_chess::isAppeared() {
    return state;
}

void black_chess::setState(bool state_) {
    state = state_;
}
