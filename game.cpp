#include "game.h"

#include <QDebug>
#include <QPainter>

Game::Game() {
    resize (DOT_WIDTH * MAP_WIDTH, DOT_HEIGHT * MAP_HEIGHT);

    initGame();

}

void Game::timerEvent(QTimerEvent *) {
    if (inGame) {
        //check_apple();
        move();
    }

    repaint();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key) {
    case Qt::Key_Left:
        qDebug() << "Left";
        break;
    case Qt::Key_Right:
        qDebug() << "Right";
        break;
    }
}

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
        //gameOver();
    }
}

void Game::paintEvent(QPaintEvent *)
{
    doDrawing();
}

void Game::localApple()
{
    srand(time(NULL));
    apple.setX(rand() % MAP_WIDTH);
    apple.setY(rand() % MAP_HEIGHT);
}

void Game::move()
{
    for (int i=snake.size()-1; i>0; i--){
        snake[i] = snake[i-1];
    }

    switch (dir) {
        case left: {snake[0].rx() -= 1; break;}
        case right: {snake[0].rx() += 1; break;}
        case up: {snake[0].ry() -= 1; break;}
        case down: {snake[0].ry() += 1; break;}
    }
}

void Game::initGame(){
    inGame = true;
    dir = right;

    snake.resize(3);

    for (int i=0; i<snake.size(); i++){
        snake[i].setX(snake.size() - i - 1);
        snake[i].setY(0);
    }

    localApple();

    timerId = startTimer(DELAY);
}

