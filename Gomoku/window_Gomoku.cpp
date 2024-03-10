#include "window_Gomoku.h"


loop::loop(QWidget* parent) : QWidget(parent) {
    imageBG.load("./image/board.png");
    timerId = startTimer(10);
    if (imageBG.isNull()) {
        std::cout << "Failed to back ground picture!\n";
    }
    rectBG = imageBG.rect();

    select_white_ = new select_white();
    select_black_ = new select_black();
    big_selector_ = new big_selector();
    small_selector_ = new small_selector();
    wasted_ = new wasted();
    pass_ = new pass();

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){
            white_chess_[x][y] = new white_chess(17.5-15/2+17.18*x, 17.5-15/2+17.18*y);
            black_chess_[x][y] = new black_chess(17.5-15/2+17.18*x, 17.5-15/2+17.18*y);
            white_chess_[x][y] ->setState(false);
            black_chess_[x][y] ->setState(false);
            test[x][y] = 0;
        }
    }
}


void loop::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);

    QPen pen;
    QFont font;

    if(page_state == 0){
        //rectBG.moveTo(0, 0);
        //painter.drawImage(rectBG, imageBG);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setFont(QFont("times", 20));
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(90, 60, QString("Gomoku"));

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setFont(QFont("times", 10));
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(70, 78, QString("GoMoKuKuMoGoMoKu !"));

        select_white_->moveTo(80, 100);
        painter.drawImage(select_white_->getRect(), select_white_->getImage());
        if(page0_selector == 0){
            big_selector_->moveTo(80, 100);
            painter.drawImage(big_selector_->getRect(), big_selector_->getImage());
        }

        select_black_->moveTo(150, 100);
        painter.drawImage(select_black_->getRect(), select_black_->getImage());
        if(page0_selector == 1){
            big_selector_->moveTo(150, 100);
            painter.drawImage(big_selector_->getRect(), big_selector_->getImage());
        }

        painter.setRenderHint(QPainter::Antialiasing, true);
        font.setPointSize(10);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(42, 175, QString("Use four 'arrow keys' to select"));
        painter.drawText(42, 190, QString("   and 'space key' to ensure"));
        painter.setRenderHint(QPainter::Antialiasing, true);
        font.setPointSize(8);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(20, 215, QString(">>Don't be sad if you lose to the Demon AI"));
        painter.drawText(20, 230, QString(">>Because you're just a little human"));
        painter.drawText(20, 245, QString(">>Or you can turn on cheatMode->1"));
        painter.drawText(20, 260, QString(">>Good luck, and try to save the world :)"));

    }
    else if(page_state == 1){
        rectBG.moveTo(0, 0);
        painter.drawImage(rectBG, imageBG);

        painter.setRenderHint(QPainter::Antialiasing, true);
        font.setPointSize(10);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        if(page0_selector == 1) painter.drawText(10, 270, QString("Your colour: Black"));
        else painter.drawText(10, 270, QString("Your colour: White"));

        if(page0_selector == 1) painter.drawText(150, 270, QString("PC's colour: White"));
        else painter.drawText(150, 270, QString("PC's colour: Black"));

        small_selector_->moveTo(17.5-17/2+17.15*small_selectX, 17.5-17/2+17.15*small_selectY);
        painter.drawImage(small_selector_->getRect(), small_selector_->getImage());

        for(int x = 0; x < 15; x++)  //draw white chess
            for(int y = 0; y < 15; y++)
                if(white_chess_[x][y]->isAppeared()) painter.drawImage(white_chess_[x][y]->getRect(), white_chess_[x][y]->getImage());



        for(int x = 0; x < 15; x++){  //draw white chess
            for(int y = 0; y < 15; y++)
                if(black_chess_[x][y]->isAppeared()) painter.drawImage(black_chess_[x][y]->getRect(), black_chess_[x][y]->getImage());
        }

        pen.setColor(Qt::red);
        painter.setPen(pen);
        for(int x = 0; x < 15; x++){
            for(int y = 0; y < 15; y++)
            if(test[x][y] != 0) painter.drawText(17.5-(4)+17.15*x, 17.5-(-6)+17.15*y, QString("%1").arg(test[x][y]));
        }

        if(tmr.getElapsedTime() - timeTrigger > 0 && gameState == 0){
            timeTrigger = tmr.getElapsedTime();
            timekiller --;
        }
        if(timekiller <= 0) ableToChess = false;  //let computer chess, if human think over 15 sec

        if(!ableToChess){
            if(gameState == 0) {
                gameState = checkWin(small_selectX, small_selectY, page0_selector);   //check human
                if(gameState == 0){
                    computer_turn(!page0_selector);
                    if(computer_selectX >=0 && computer_selectY >=0){
                        gameState = checkWin(computer_selectX, computer_selectY, !page0_selector);  //check computer
                    }
                }
            }
            if(gameState == 0) ableToChess = true;
        }

        if(gameState != 0){
            if(page0_selector == 0){
                if(gameState == 1){
                    pass_->moveTo(0, 0);
                    painter.drawImage(pass_->getRect(), pass_->getImage());
                }
                else{
                    wasted_->moveTo(0, 0);
                    painter.drawImage(wasted_->getRect(), wasted_->getImage());
                }
            }
            else{
                if(gameState == 2){
                    pass_->moveTo(0, 0);
                    painter.drawImage(pass_->getRect(), pass_->getImage());
                }
                else{
                    wasted_->moveTo(0, 0);
                    painter.drawImage(wasted_->getRect(), wasted_->getImage());
                }
            }
        }


        painter.setRenderHint(QPainter::Antialiasing, true);
        font.setPointSize(10);
        painter.setFont(font);
        if(timekiller > 5) pen.setColor(Qt::black);     //alarm the human.Change colour to red if <=5 sec
        else pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawText(10, 13, QString("TimeLeft <=%1").arg(timekiller));  //tmr.getElapsedTime()   //gameState
    }
    //update();
}


void loop::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
        {
            if(page_state == 0) page0_selector = page0_selector==0? 1:0;
            else if(page_state == 1 && ableToChess) small_selectX = small_selectX>0 ? small_selectX-1:0;
            break;
        }
        case Qt::Key_Right:
        {
            if(page_state == 0) page0_selector = page0_selector==0? 1:0;
            else if(page_state == 1 && ableToChess) small_selectX = small_selectX<14 ? small_selectX+1:14;
            break;
        }
        case Qt::Key_Down:
        {
            if(page_state == 1 && ableToChess) small_selectY = small_selectY<14 ? small_selectY+1:14;
            break;
        }
        case Qt::Key_Up:
        {
            if(page_state == 1 && ableToChess) small_selectY = small_selectY>0 ? small_selectY-1:0;
            break;
        }
        case Qt::Key_Space:
        {
            if(page_state == 0){
                if(page0_selector == 0){  //computer first step
                    black_chess_[7][7] ->setState(true);  //take the centre first
                }
                tmr.setStart(time(NULL));
                page_state = 1;  //playing page
            }
            else if(page_state == 1){
                if(ableToChess){  //human turn
                    if(page0_selector == 0) {  //if human select white
                        if(!black_chess_[small_selectX][small_selectY]->isAppeared() && !white_chess_[small_selectX][small_selectY]->isAppeared()){
                            white_chess_[small_selectX][small_selectY] ->setState(true);
                            ableToChess = false;  //computer turn
                        }
                    }
                    else if(!black_chess_[small_selectX][small_selectY]->isAppeared() && !white_chess_[small_selectX][small_selectY]->isAppeared()){
                        black_chess_[small_selectX][small_selectY] ->setState(true);
                        ableToChess = false;  //computer turn
                    }

                }
            }
            break;
        }

        case Qt::Key_Escape:
            qApp->exit();
            break;
    }
}

//checking the state of game (type:0 is white  1 is black)
//0:in game  1:white win  2:black win  3:tie
int loop::checkWin(int x, int y, bool type){
    bool checkAllFill = true;
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
            if(!white_chess_[i][j]->isAppeared() && !black_chess_[i][j]->isAppeared()) checkAllFill = false;
    if(checkAllFill) return 3;  //The game is tie

    int chessCount[8];
    int dirCount = 0;
    for(int i = 0; i < 8; i++) chessCount[i] = 0;

    for(int xDir = -1; xDir <= 1; xDir++){
        for(int yDir = -1; yDir <= 1; yDir++){
            if(xDir == 0 && yDir == 0) continue; //skip 0,0 direction
            for(int step = 1; step <= 5; step++){  //if having other 4 connect win, if more than or less continue game
                int xCounting = x+xDir*step, yCounting = y+yDir*step;
                if(xCounting > 14 || xCounting < 0) continue;
                if(yCounting > 14 || yCounting < 0) continue;
                if(type == 0){  //type:0 is white  1 is black
                    if(white_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                    else step = 5;  //stop counting if empty in medium
                }
                else{
                    if(black_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                    else step = 5;
                }
            }
            dirCount ++;
        }
    }
    int gameState_ = 0;  //0:in game  1:white win  2:black win  3:tie
    for(int i = 0; i <= 3; i++) chessCount[i] += chessCount[i+((3-i)*2+1)];  //combining opposite direction (total 4 pairs)
    for(int i = 0; i <= 3; i++) {
        if(chessCount[i] == 4 && type == 0) gameState_ = 1;
        else if(chessCount[i] == 4 && type == 1) gameState_ = 2;
    }
    return gameState_;
}

void loop::computer_turn(bool type){
    timekiller = 15; //reset human turn countdown timer
    int computerMap[15][15], humanMap[15][15];
    bool computerState[15][15], humanState[15][15];
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){
            computerMap[x][y] = 0;
            humanMap[x][y] = 0;
            computerState[x][y] = false;
            humanState[x][y] = false;
        }
    }
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){
            bool comState = false;
            if(type == 0 && white_chess_[x][y]->isAppeared()) comState = true;
            else if(type == 1 && black_chess_[x][y]->isAppeared()) comState = true;
            computerState[x][y] = comState;

            bool humState = false;
            if(type == 0 && black_chess_[x][y]->isAppeared()) humState = true;
            else if(type == 1 && white_chess_[x][y]->isAppeared()) humState = true;
            humanState[x][y] = humState;
        }
    }

    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){

            if(computerState[x][y]){
                int chessCount[8];
                int dirCount = 0;
                for(int i = 0; i < 8; i++) chessCount[i] = 1;
                for(int xDir = -1; xDir <= 1; xDir++){
                    for(int yDir = -1; yDir <= 1; yDir++){
                        if(xDir == 0 && yDir == 0) continue; //skip 0,0 direction
                        for(int step = 1; step <= 5; step++){  //if having other 4 connect win, if more than or less continue game
                            int xCounting = x+xDir*step, yCounting = y+yDir*step;
                            if(xCounting > 14 || xCounting < 0) continue;
                            if(yCounting > 14 || yCounting < 0) continue;
                            if(type == 0){  //type:0 is white  1 is black
                                if(white_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                                else step = 5;  //stop counting if empty in medium
                            }
                            else{
                                if(black_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                                else step = 5;
                            }
                        }
                        dirCount ++;
                    }
                }
                if(!computerState[x-1][y-1] && !humanState[x-1][y-1]) {
                    if(computerState[x-2][y-2]) {
                        if((x-2)>=0 && (x-2)<=14 && (y-2)>=0 && (y-2)<=14) {
                            computerMap[x-1][y-1] += chessCount[7];  //write at positon 0
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x-1][y-1] < chessCount[7]) computerMap[x-1][y-1] = chessCount[7];  //write at positon 0
                }

                if(!computerState[x-1][y-0] && !humanState[x-1][y-0]) {
                    if(computerState[x-2][y-0]) {
                        if((x-2)>=0 && (x-2)<=14 && (y-0)>=0 && (y-0)<=14) {
                            computerMap[x-1][y-0] += chessCount[6];  //write at positon 1
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y-0)>=0 && (y-0)<=14) if(computerMap[x-1][y-0] < chessCount[6]) computerMap[x-1][y-0] = chessCount[6];  //write at positon 1
                }

                if(!computerState[x-1][y+1] && !humanState[x-1][y+1]) {
                    if(computerState[x-2][y+2]) {
                        if((x-2)>=0 && (x-2)<=14 && (y+2)>=0 && (y+2)<=14) {
                            computerMap[x-1][y+1] += chessCount[5];  //write at positon 2
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x-1][y+1] < chessCount[5]) computerMap[x-1][y+1] = chessCount[5];  //write at positon 2
                }

                if(!computerState[x-0][y-1] && !humanState[x-0][y-1]) {
                    if(computerState[x-0][y-2]) {
                        if((x-0)>=0 && (x-0)<=14 && (y-2)>=0 && (y-2)<=14) {
                            computerMap[x-0][y-1] += chessCount[4];  //write at positon 3
                        }
                    }
                    else if((x-0)>=0 && (x-0)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x-0][y-1] < chessCount[4]) computerMap[x-0][y-1] = chessCount[4];  //write at positon 3
                }

                if(!computerState[x-0][y+1] && !humanState[x-0][y+1]) {
                    if(computerState[x-0][y+2]) {
                        if((x-0)>=0 && (x-0)<=14 && (y+2)>=0 && (y+2)<=14) {
                            computerMap[x-0][y+1] += chessCount[3];  //write at positon 4
                        }
                    }
                    else if((x-0)>=0 && (x-0)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x-0][y+1] < chessCount[3]) computerMap[x-0][y+1] = chessCount[3];  //write at positon 4
                }

                if(!computerState[x+1][y-1] && !humanState[x+1][y-1]) {
                    if(computerState[x+2][y-2]) {
                        if((x+2)>=0 && (x+2)<=14 && (y-2)>=0 && (y-2)<=14) {
                            computerMap[x+1][y-1] += chessCount[2];  //write at positon 5
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x+1][y-1] < chessCount[2]) computerMap[x+1][y-1] = chessCount[2];  //write at positon 5
                }

                if(!computerState[x+1][y-0] && !humanState[x+1][y-0]) {
                    if(computerState[x+2][y-0]) {
                        if((x+2)>=0 && (x+2)<=14 && (y-0)>=0 && (y-0)<=14) {
                            computerMap[x+1][y-0] += chessCount[1];  //write at positon 6
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y-0)>=0 && (y-0)<=14) if(computerMap[x+1][y-0] < chessCount[1]) computerMap[x+1][y-0] = chessCount[1];  //write at positon 6
                }

                if(!computerState[x+1][y+1] && !humanState[x+1][y+1]) {
                    if(computerState[x+2][y+2]) {
                        if((x+2)>=0 && (x+2)<=14 && (y+2)>=0 && (y+2)<=14) {
                            computerMap[x+1][y+1] += chessCount[0];  //write at positon 7
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x+1][y+1] < chessCount[0]) computerMap[x+1][y+1] = chessCount[0];  //write at positon 7
                }


                for(int i = 0; i < 15; i++) for(int j = 0; j < 15; j++) if(computerMap[i][j] > 4) computerMap[i][j] = 0;

            }




            if(humanState[x][y]){
                int chessCount[8];
                int dirCount = 0;
                for(int i = 0; i < 8; i++) chessCount[i] = 1;
                for(int xDir = -1; xDir <= 1; xDir++){
                    for(int yDir = -1; yDir <= 1; yDir++){
                        if(xDir == 0 && yDir == 0) continue; //skip 0,0 direction
                        for(int step = 1; step <= 5; step++){  //if having other 4 connect win, if more than or less continue game
                            int xCounting = x+xDir*step, yCounting = y+yDir*step;
                            if(xCounting > 14 || xCounting < 0) continue;
                            if(yCounting > 14 || yCounting < 0) continue;
                            if(type == 1){  //type:0 is white  1 is black
                                if(white_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                                else step = 5;  //stop counting if empty in medium
                            }
                            else{
                                if(black_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                                else step = 5;
                            }
                        }
                        dirCount ++;

                    }
                }


                    if(!computerState[x-1][y-1] && !humanState[x-1][y-1]) {
                        if(humanState[x-2][y-2]) {
                            if((x-2)>=0 && (x-2)<=14 && (y-2)>=0 && (y-2)<=14) {
                                humanMap[x-1][y-1] += chessCount[7];  //write at positon 0
                            }
                        }
                        else if((x-1)>=0 && (x-1)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x-1][y-1] < chessCount[7]) humanMap[x-1][y-1] = chessCount[7];  //write at positon 0
                    }

                    if(!computerState[x-1][y-0] && !humanState[x-1][y-0]) {
                        if(humanState[x-2][y-0]) {
                            if((x-2)>=0 && (x-2)<=14 && (y-0)>=0 && (y-0)<=14) {
                                humanMap[x-1][y-0] += chessCount[6];  //write at positon 1
                            }
                        }
                        else if((x-1)>=0 && (x-1)<=14 && (y-0)>=0 && (y-0)<=14) if(humanMap[x-1][y-0] < chessCount[6]) humanMap[x-1][y-0] = chessCount[6];  //write at positon 1
                    }

                    if(!computerState[x-1][y+1] && !humanState[x-1][y+1]) {
                        if(humanState[x-2][y+2]) {
                            if((x-2)>=0 && (x-2)<=14 && (y+2)>=0 && (y+2)<=14) {
                                humanMap[x-1][y+1] += chessCount[5];  //write at positon 2
                            }
                        }
                        else if((x-1)>=0 && (x-1)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x-1][y+1] < chessCount[5]) humanMap[x-1][y+1] = chessCount[5];  //write at positon 2
                    }

                    if(!computerState[x-0][y-1] && !humanState[x-0][y-1]) {
                        if(humanState[x-0][y-2]) {
                            if((x-0)>=0 && (x-0)<=14 && (y-2)>=0 && (y-2)<=14) {
                                humanMap[x-0][y-1] += chessCount[4];  //write at positon 3
                            }
                        }
                        else if((x-0)>=0 && (x-0)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x-0][y-1] < chessCount[4]) humanMap[x-0][y-1] = chessCount[4];  //write at positon 3
                    }

                    if(!computerState[x-0][y+1] && !humanState[x-0][y+1]) {
                        if(humanState[x-0][y+2]) {
                            if((x-0)>=0 && (x-0)<=14 && (y+2)>=0 && (y+2)<=14) {
                                humanMap[x-0][y+1] += chessCount[3];  //write at positon 4
                            }
                        }
                        else if((x-0)>=0 && (x-0)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x-0][y+1] < chessCount[3]) humanMap[x-0][y+1] = chessCount[3];  //write at positon 4
                    }

                    if(!computerState[x+1][y-1] && !humanState[x+1][y-1]) {
                        if(humanState[x+2][y-2]) {
                            if((x+2)>=0 && (x+2)<=14 && (y-2)>=0 && (y-2)<=14) {
                                humanMap[x+1][y-1] += chessCount[2];  //write at positon 5
                            }
                        }
                        else if((x+1)>=0 && (x+1)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x+1][y-1] < chessCount[2]) humanMap[x+1][y-1] = chessCount[2];  //write at positon 5
                    }

                    if(!computerState[x+1][y-0] && !humanState[x+1][y-0]) {
                        if(humanState[x+2][y-0]) {
                            if((x+2)>=0 && (x+2)<=14 && (y-0)>=0 && (y-0)<=14) {
                                humanMap[x+1][y-0] += chessCount[1];  //write at positon 6
                            }
                        }
                        else if((x+1)>=0 && (x+1)<=14 && (y-0)>=0 && (y-0)<=14) if(humanMap[x+1][y-0] < chessCount[1]) humanMap[x+1][y-0] = chessCount[1];  //write at positon 6
                    }

                    if(!computerState[x+1][y+1] && !humanState[x+1][y+1]) {
                        if(humanState[x+2][y+2]) {
                            if((x+2)>=0 && (x+2)<=14 && (y+2)>=0 && (y+2)<=14) {
                                humanMap[x+1][y+1] += chessCount[0];  //write at positon 7
                            }
                        }
                        else if((x+1)>=0 && (x+1)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x+1][y+1] < chessCount[0]) humanMap[x+1][y+1] = chessCount[0];  //write at positon 7
                    }

                    for(int i = 0; i < 15; i++) for(int j = 0; j < 15; j++) if(humanMap[i][j] > 4) humanMap[i][j] = 0;

            }

        }
    }///////


    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(humanState[i][j]) computerMap[i][j] = 0;
            if(computerState[i][j]) humanMap[i][j] = 0;
            else if(!computerState[i][j]) computerMap[i][j] ++;  //make computer map priorer than humanMap
        }
    }

    int comHolder = 0;
    int comHolderX = 0, comHolderY = 0;
    int humHolder = 0;
    int humHolderX = 0, humHolderY = 0;
    for(int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){

            if(comHolder < computerMap[x][y]) {
                comHolder = computerMap[x][y];
                comHolderX = x;
                comHolderY = y;
            }
            if(humHolder < humanMap[x][y]) {
                humHolder = humanMap[x][y];
                humHolderX = x;
                humHolderY = y;
            }

        }
    }
    if(comHolder > humHolder){
        computer_selectX = comHolderX;
        computer_selectY = comHolderY;
    }
    else{
        computer_selectX = humHolderX;
        computer_selectY = humHolderY;
    }
    if(type == 0){
        white_chess_[computer_selectX][computer_selectY] ->setState(true);   //computer chessing
    }
    else black_chess_[computer_selectX][computer_selectY] ->setState(true);    //computer chessing

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            test[i][j] = 0;
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// cheating operation Start
if(cheatMode == 1){   //give some tips for stupit human bruh~~
for(int x = 0; x < 15; x++){
    for(int y = 0; y < 15; y++){
        computerMap[x][y] = 0;
        humanMap[x][y] = 0;
        computerState[x][y] = false;
        humanState[x][y] = false;
    }
}
for(int x = 0; x < 15; x++){
    for(int y = 0; y < 15; y++){
        bool comState = false;
        if(type == 0 && white_chess_[x][y]->isAppeared()) comState = true;
        else if(type == 1 && black_chess_[x][y]->isAppeared()) comState = true;
        computerState[x][y] = comState;

        bool humState = false;
        if(type == 0 && black_chess_[x][y]->isAppeared()) humState = true;
        else if(type == 1 && white_chess_[x][y]->isAppeared()) humState = true;
        humanState[x][y] = humState;
    }
}

for(int x = 0; x < 15; x++){
    for(int y = 0; y < 15; y++){

        if(computerState[x][y]){
            int chessCount[8];
            int dirCount = 0;
            for(int i = 0; i < 8; i++) chessCount[i] = 1;
            for(int xDir = -1; xDir <= 1; xDir++){
                for(int yDir = -1; yDir <= 1; yDir++){
                    if(xDir == 0 && yDir == 0) continue; //skip 0,0 direction
                    for(int step = 1; step <= 5; step++){  //if having other 4 connect win, if more than or less continue game
                        int xCounting = x+xDir*step, yCounting = y+yDir*step;
                        if(xCounting > 14 || xCounting < 0) continue;
                        if(yCounting > 14 || yCounting < 0) continue;
                        if(type == 0){  //type:0 is white  1 is black
                            if(white_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                            else step = 5;  //stop counting if empty in medium
                        }
                        else{
                            if(black_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                            else step = 5;
                        }
                    }
                    dirCount ++;
                }
            }
            if(!computerState[x-1][y-1] && !humanState[x-1][y-1]) {
                if(computerState[x-2][y-2]) {
                    if((x-2)>=0 && (x-2)<=14 && (y-2)>=0 && (y-2)<=14) {
                        computerMap[x-1][y-1] += chessCount[7];  //write at positon 0
                    }
                }
                else if((x-1)>=0 && (x-1)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x-1][y-1] < chessCount[7]) computerMap[x-1][y-1] = chessCount[7];  //write at positon 0
            }

            if(!computerState[x-1][y-0] && !humanState[x-1][y-0]) {
                if(computerState[x-2][y-0]) {
                    if((x-2)>=0 && (x-2)<=14 && (y-0)>=0 && (y-0)<=14) {
                        computerMap[x-1][y-0] += chessCount[6];  //write at positon 1
                    }
                }
                else if((x-1)>=0 && (x-1)<=14 && (y-0)>=0 && (y-0)<=14) if(computerMap[x-1][y-0] < chessCount[6]) computerMap[x-1][y-0] = chessCount[6];  //write at positon 1
            }

            if(!computerState[x-1][y+1] && !humanState[x-1][y+1]) {
                if(computerState[x-2][y+2]) {
                    if((x-2)>=0 && (x-2)<=14 && (y+2)>=0 && (y+2)<=14) {
                        computerMap[x-1][y+1] += chessCount[5];  //write at positon 2
                    }
                }
                else if((x-1)>=0 && (x-1)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x-1][y+1] < chessCount[5]) computerMap[x-1][y+1] = chessCount[5];  //write at positon 2
            }

            if(!computerState[x-0][y-1] && !humanState[x-0][y-1]) {
                if(computerState[x-0][y-2]) {
                    if((x-0)>=0 && (x-0)<=14 && (y-2)>=0 && (y-2)<=14) {
                        computerMap[x-0][y-1] += chessCount[4];  //write at positon 3
                    }
                }
                else if((x-0)>=0 && (x-0)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x-0][y-1] < chessCount[4]) computerMap[x-0][y-1] = chessCount[4];  //write at positon 3
            }

            if(!computerState[x-0][y+1] && !humanState[x-0][y+1]) {
                if(computerState[x-0][y+2]) {
                    if((x-0)>=0 && (x-0)<=14 && (y+2)>=0 && (y+2)<=14) {
                        computerMap[x-0][y+1] += chessCount[3];  //write at positon 4
                    }
                }
                else if((x-0)>=0 && (x-0)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x-0][y+1] < chessCount[3]) computerMap[x-0][y+1] = chessCount[3];  //write at positon 4
            }

            if(!computerState[x+1][y-1] && !humanState[x+1][y-1]) {
                if(computerState[x+2][y-2]) {
                    if((x+2)>=0 && (x+2)<=14 && (y-2)>=0 && (y-2)<=14) {
                        computerMap[x+1][y-1] += chessCount[2];  //write at positon 5
                    }
                }
                else if((x+1)>=0 && (x+1)<=14 && (y-1)>=0 && (y-1)<=14) if(computerMap[x+1][y-1] < chessCount[2]) computerMap[x+1][y-1] = chessCount[2];  //write at positon 5
            }

            if(!computerState[x+1][y-0] && !humanState[x+1][y-0]) {
                if(computerState[x+2][y-0]) {
                    if((x+2)>=0 && (x+2)<=14 && (y-0)>=0 && (y-0)<=14) {
                        computerMap[x+1][y-0] += chessCount[1];  //write at positon 6
                    }
                }
                else if((x+1)>=0 && (x+1)<=14 && (y-0)>=0 && (y-0)<=14) if(computerMap[x+1][y-0] < chessCount[1]) computerMap[x+1][y-0] = chessCount[1];  //write at positon 6
            }

            if(!computerState[x+1][y+1] && !humanState[x+1][y+1]) {
                if(computerState[x+2][y+2]) {
                    if((x+2)>=0 && (x+2)<=14 && (y+2)>=0 && (y+2)<=14) {
                        computerMap[x+1][y+1] += chessCount[0];  //write at positon 7
                    }
                }
                else if((x+1)>=0 && (x+1)<=14 && (y+1)>=0 && (y+1)<=14) if(computerMap[x+1][y+1] < chessCount[0]) computerMap[x+1][y+1] = chessCount[0];  //write at positon 7
            }


            for(int i = 0; i < 15; i++) for(int j = 0; j < 15; j++) if(computerMap[i][j] > 4) computerMap[i][j] = 0;

        }




        if(humanState[x][y]){
            int chessCount[8];
            int dirCount = 0;
            for(int i = 0; i < 8; i++) chessCount[i] = 1;
            for(int xDir = -1; xDir <= 1; xDir++){
                for(int yDir = -1; yDir <= 1; yDir++){
                    if(xDir == 0 && yDir == 0) continue; //skip 0,0 direction
                    for(int step = 1; step <= 5; step++){  //if having other 4 connect win, if more than or less continue game
                        int xCounting = x+xDir*step, yCounting = y+yDir*step;
                        if(xCounting > 14 || xCounting < 0) continue;
                        if(yCounting > 14 || yCounting < 0) continue;
                        if(type == 1){  //type:0 is white  1 is black
                            if(white_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                            else step = 5;  //stop counting if empty in medium
                        }
                        else{
                            if(black_chess_[xCounting][yCounting]->isAppeared()) chessCount[dirCount] ++;
                            else step = 5;
                        }
                    }
                    dirCount ++;

                }
            }


                if(!computerState[x-1][y-1] && !humanState[x-1][y-1]) {
                    if(humanState[x-2][y-2]) {
                        if((x-2)>=0 && (x-2)<=14 && (y-2)>=0 && (y-2)<=14) {
                            humanMap[x-1][y-1] += chessCount[7];  //write at positon 0
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x-1][y-1] < chessCount[7]) humanMap[x-1][y-1] = chessCount[7];  //write at positon 0
                }

                if(!computerState[x-1][y-0] && !humanState[x-1][y-0]) {
                    if(humanState[x-2][y-0]) {
                        if((x-2)>=0 && (x-2)<=14 && (y-0)>=0 && (y-0)<=14) {
                            humanMap[x-1][y-0] += chessCount[6];  //write at positon 1
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y-0)>=0 && (y-0)<=14) if(humanMap[x-1][y-0] < chessCount[6]) humanMap[x-1][y-0] = chessCount[6];  //write at positon 1
                }

                if(!computerState[x-1][y+1] && !humanState[x-1][y+1]) {
                    if(humanState[x-2][y+2]) {
                        if((x-2)>=0 && (x-2)<=14 && (y+2)>=0 && (y+2)<=14) {
                            humanMap[x-1][y+1] += chessCount[5];  //write at positon 2
                        }
                    }
                    else if((x-1)>=0 && (x-1)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x-1][y+1] < chessCount[5]) humanMap[x-1][y+1] = chessCount[5];  //write at positon 2
                }

                if(!computerState[x-0][y-1] && !humanState[x-0][y-1]) {
                    if(humanState[x-0][y-2]) {
                        if((x-0)>=0 && (x-0)<=14 && (y-2)>=0 && (y-2)<=14) {
                            humanMap[x-0][y-1] += chessCount[4];  //write at positon 3
                        }
                    }
                    else if((x-0)>=0 && (x-0)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x-0][y-1] < chessCount[4]) humanMap[x-0][y-1] = chessCount[4];  //write at positon 3
                }

                if(!computerState[x-0][y+1] && !humanState[x-0][y+1]) {
                    if(humanState[x-0][y+2]) {
                        if((x-0)>=0 && (x-0)<=14 && (y+2)>=0 && (y+2)<=14) {
                            humanMap[x-0][y+1] += chessCount[3];  //write at positon 4
                        }
                    }
                    else if((x-0)>=0 && (x-0)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x-0][y+1] < chessCount[3]) humanMap[x-0][y+1] = chessCount[3];  //write at positon 4
                }

                if(!computerState[x+1][y-1] && !humanState[x+1][y-1]) {
                    if(humanState[x+2][y-2]) {
                        if((x+2)>=0 && (x+2)<=14 && (y-2)>=0 && (y-2)<=14) {
                            humanMap[x+1][y-1] += chessCount[2];  //write at positon 5
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y-1)>=0 && (y-1)<=14) if(humanMap[x+1][y-1] < chessCount[2]) humanMap[x+1][y-1] = chessCount[2];  //write at positon 5
                }

                if(!computerState[x+1][y-0] && !humanState[x+1][y-0]) {
                    if(humanState[x+2][y-0]) {
                        if((x+2)>=0 && (x+2)<=14 && (y-0)>=0 && (y-0)<=14) {
                            humanMap[x+1][y-0] += chessCount[1];  //write at positon 6
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y-0)>=0 && (y-0)<=14) if(humanMap[x+1][y-0] < chessCount[1]) humanMap[x+1][y-0] = chessCount[1];  //write at positon 6
                }

                if(!computerState[x+1][y+1] && !humanState[x+1][y+1]) {
                    if(humanState[x+2][y+2]) {
                        if((x+2)>=0 && (x+2)<=14 && (y+2)>=0 && (y+2)<=14) {
                            humanMap[x+1][y+1] += chessCount[0];  //write at positon 7
                        }
                    }
                    else if((x+1)>=0 && (x+1)<=14 && (y+1)>=0 && (y+1)<=14) if(humanMap[x+1][y+1] < chessCount[0]) humanMap[x+1][y+1] = chessCount[0];  //write at positon 7
                }

                for(int i = 0; i < 15; i++) for(int j = 0; j < 15; j++) if(humanMap[i][j] > 4) humanMap[i][j] = 0;

        }

    }
}

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(humanState[i][j]) computerMap[i][j] = 0;
            if(computerState[i][j]) humanMap[i][j] = 0;
            else if(!computerState[i][j]) computerMap[i][j] ++;  //make computer map priorer than humanMap
        }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// cheating operation End
        comHolder = 0;
        comHolderX = 0;
        comHolderY = 0;
        humHolder = 0;
        humHolderX = 0;
        humHolderY = 0;
        for(int x = 0; x < 15; x++){
            for(int y = 0; y < 15; y++){

                if(comHolder < computerMap[x][y]) {
                    comHolder = computerMap[x][y];
                    comHolderX = x;
                    comHolderY = y;
                }
                if(humHolder < humanMap[x][y]) {
                    humHolder = humanMap[x][y];
                    humHolderX = x;
                    humHolderY = y;
                }

            }
        }




        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){

                int diff = 0;
                if(humHolder > comHolder-2){    //human attack computer
                    diff = humHolder - (comHolder-2);
                    if(humanMap[i][j] == humHolder) test[i][j] = diff==0? 1: diff;
                }
                else{   //protect human from computer
                    diff = (comHolder-2) - humHolder;
                    if(computerMap[i][j] == comHolder) test[i][j] = diff==0? -1: diff;
                }

            }
        }
    }
    else if(cheatMode == 2){   //for debug only
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                test[i][j] = computerMap[i][j];
            }
        }
    }
    else if(cheatMode == 3){   //for debug only
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                test[i][j] = humanMap[i][j];
            }
        }
    }

}

void loop::timerEvent(QTimerEvent* event) {
    repaint();
}
