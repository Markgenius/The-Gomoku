#include <QImage>
#include <QRect>

class select_black {
    public:
        select_black();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();

    private:
        QImage image;
        QRect rect;
        time_t start_ts;
};
