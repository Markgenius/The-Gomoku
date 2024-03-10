#include <ctime> // for time()
#include <unistd.h> // for sleep()
#include <QImage>
#include <QRect>

class Timer {
    public:
        Timer();
        void moveTo(int , int);
        QRect getRect();
        QImage & getImage();
        void setStart(time_t ts) {
            start_ts=ts;
        }
        time_t getStart() {
            return start_ts;
        }
        int getElapsedTime() {
            return time(NULL) - getStart();
        }

    private:
        QImage image;
        QRect rect;
        time_t start_ts;
};
