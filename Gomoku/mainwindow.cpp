#include "window_Gomoku.h"
#include <QDesktopWidget>
#include <QApplication>

int WIDTH_window = 275;
int HEIGHT_window = 275;
int x, y;
int MonWidth;
int MonHeight;

void centre(QWidget &widget) {
    QDesktopWidget* Mydesktop = QApplication::desktop();

    MonWidth = Mydesktop->width();
    MonHeight = Mydesktop->height();
    x = (MonWidth - WIDTH_window) / 2;
    y = (MonHeight = HEIGHT_window) / 2;

    widget.setGeometry(x, y, WIDTH_window, HEIGHT_window);
    widget.setFixedSize(WIDTH_window, HEIGHT_window);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    loop window_Gomoku;
    window_Gomoku.setWindowTitle("The Gomoku V1.0");
    window_Gomoku.show();

    centre(window_Gomoku);

    return app.exec();
}
