#include "game.h"

#include <QDebug>

Game::Game() {
    resize (DOT_WIDTH * MAP_WIDTH, DOT_HEIGHT * MAP_HEIGHT);

    initGame();
}

//смена состояния происходит по таймеру
void Game::timerEvent(QTimerEvent *) {
    if (inGame) {
        dir_changed = false;
        eatingApple();
        move();
        checkCrash();
        repaint();
    }
}

//по нажатию клавиши управления
void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (!dir_changed){     //за кадр можно сменить направление только раз
        switch (key) {
        case Qt::Key_Left:
            if (dir == up || dir == down) dir = left;
            dir_changed = true;
            break;
        case Qt::Key_Right:
            if (dir == up || dir == down) dir = right;
            dir_changed = true;
            break;
        case Qt::Key_Up:
            if (dir == left || dir == right) dir = up;
            dir_changed = true;
            break;
        case Qt::Key_Down:
            if (dir == left || dir == right) dir = down;
            dir_changed = true;
            break;
        }
    }
}

//отрисовка игры
void Game::doDrawing()
{
    QPainter qp(this);

    if (inGame){
        //фон
        qp.setBrush(Qt::black);
        qp.drawRect(0, 0, MAP_WIDTH * DOT_WIDTH, MAP_HEIGHT * DOT_HEIGHT);

        //яблоко
        qp.setBrush(Qt::red);
        qp.drawRect(apple.x() * DOT_WIDTH, apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

        //змейка
        for(int i=0; i<snake.size(); i++){
            qp.setBrush(Qt::green);
            qp.drawRect(snake[i].x() * DOT_WIDTH, snake[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }
    }
    else  {
        gameOver();
    }
}

//ивент отрисовки
void Game::paintEvent(QPaintEvent *)
{
    doDrawing();
}

//создание яблока
void Game::localApple()
{
    srand(time(NULL));
    apple.setX(rand() % MAP_WIDTH);
    apple.setY(rand() % MAP_HEIGHT);

    badApple = false;
    for(int i=0; i<snake.size(); i++){
        if (snake[i] == apple) {
            badApple = true;
            break;
        }
    }
}

void Game::eatingApple()
{
    if (apple == snake[0]) {
        snake.push_back(QPoint(0,0));
        do localApple(); while(badApple);
    }
}

//управление движением
void Game::move()
{
    for (int i=snake.size()-1; i>0; i--){
        snake[i] = snake[i - 1];
    }

    switch (dir) {
        case left: {snake[0].rx() -= 1; break;}
        case right: {snake[0].rx() += 1; break;}
        case up: {snake[0].ry() -= 1; break;}
        case down: {snake[0].ry() += 1; break;}
    }
}

//проверка на столкновение
void Game::checkCrash() {
    // столкновение с хвостом
    if (snake.size() > 4){
        for (int i=1; i<snake.size(); i++){
            if (snake[i] == snake[0]) inGame = false;
        }
    }

    //столкновение со стеной
    if (snake[0].x() >= MAP_WIDTH || snake[0].x() < 0) inGame = false;
    if (snake[0].y() >= MAP_HEIGHT || snake[0].y() < 0) inGame = false;

    if (!inGame) killTimer(timerId);
}

//конец игры
void Game::gameOver()
{
    QMessageBox finWindow;
    finWindow.setText("GameOver");
    finWindow.exec();

    initGame();
}

//создание игры
void Game::initGame(){
    inGame = true;
    dir = right;
    dir_changed = false;
    badApple = false;

    snake.resize(3);

    for (int i=0; i<snake.size(); i++){
        snake[i].setX(snake.size() - i - 1);
        snake[i].setY(0);
    }

    do localApple(); while(badApple);

    timerId = startTimer(DELAY);
}

