#include "timer.h"
#include <iostream>

Timer::Timer() {
    image.load("./image/brainsmash_1.png");
    rect = image.rect();
}

QRect Timer::getRect() {
    return rect;
}

QImage & Timer::getImage() {
    return image;
}

void Timer::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
