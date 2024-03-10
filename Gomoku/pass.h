#include <QImage>
#include <QRect>

class pass {
    public:
        pass();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();

    private:
        QImage image;
        QRect rect;
};
