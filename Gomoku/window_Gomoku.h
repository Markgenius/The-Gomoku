#include <iostream>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QApplication>
#include <QKeyEvent>
#include <cmath>

#include <select_white.h>
#include <select_black.h>
#include <big_selector.h>
#include <small_selector.h>
#include <white_chess.h>
#include <black_chess.h>
#include <wasted.h>
#include <pass.h>

#define cheatMode  0     ///////////////////////////////////////////////////////   Cheat mode is HERE(The power of God)  < 0:off  1:chessing tips  2:computer strategy map  3:human chess expectation >

class loop : public QWidget {
    Q_OBJECT

public:
    loop(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void computer_turn(bool);
    int checkWin(int, int, bool);
    select_white tmr;

private:
    int timerId;
    QImage imageBG;
    QRect rectBG;
    select_white* select_white_;
    select_black* select_black_;
    big_selector* big_selector_;
    small_selector* small_selector_;
    white_chess* white_chess_[15][15];
    black_chess* black_chess_[15][15];
    wasted* wasted_;
    pass* pass_;

    int WIDTH_Winow = 800;
    int HEIGHT_Winow = 600;

    int page_state = 0;
    bool page0_selector = 0;  //0:white  1:black
    int small_selectX = 7, small_selectY = 7;
    int computer_selectX = -1, computer_selectY = -1;
    bool white_chess_state[15][15];
    bool black_chess_state[15][15];
    int gameState = 0;   //0:in game  1:white win  2:black win  3:tie
    bool ableToChess = true;   //false:computer_turn  true:human_turn
    long timeTrigger = 0;
    int timekiller = 15;      //15 sec for human turn

    int test[15][15];

};
