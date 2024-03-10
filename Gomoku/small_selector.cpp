#include "small_selector.h"
#include <iostream>

small_selector::small_selector() {
    image.load("./image/small_select.png");
    rect = image.rect();
}

QRect small_selector::getRect() {
    return rect;
}

QImage & small_selector::getImage() {
    return image;
}

void small_selector::moveTo(int x, int y) {
    rect.moveTo(x, y);
}
