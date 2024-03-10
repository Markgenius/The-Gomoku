#include <QImage>
#include <QRect>

class small_selector {
    public:
        small_selector();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();

    private:
        QImage image;
        QRect rect;
};
