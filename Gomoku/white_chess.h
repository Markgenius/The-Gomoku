#include <QImage>
#include <QRect>

class white_chess {
public:
    white_chess(int, int);

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
