#include <QImage>
#include <QRect>

class wasted {
    public:
        wasted();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();

    private:
        QImage image;
        QRect rect;
};
