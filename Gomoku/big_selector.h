#include <QImage>
#include <QRect>

class big_selector {
    public:
        big_selector();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();

    private:
        QImage image;
        QRect rect;
};
