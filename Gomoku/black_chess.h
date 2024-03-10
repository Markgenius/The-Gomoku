#include <QImage>
#include <QRect>

class black_chess {
public:
    black_chess(int, int);

    void resetState();
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    bool isAppeared();
    void setState(bool);

private:
    QImage image;
    QRect rect;
    bool state = 0;
};
