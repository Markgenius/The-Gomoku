#include "white_chess.h"
#include <iostream>

white_chess::white_chess(int x, int y) {
    image.load("./image/white_.png");

    rect = image.rect();
    rect.translate(x, y);
}

QRect white_chess::getRect() {
    return rect;
}

void white_chess::setRect(QRect rct) {
    rect = rct;
}

QImage & white_chess::getImage() {
    return image;
}

bool white_chess::isAppeared() {
    return state;
}

void white_chess::setState(bool state_) {
    state = state_;
}
