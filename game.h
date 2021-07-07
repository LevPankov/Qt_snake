#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>

class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int MAP_WIDTH = 20;
    static const int MAP_HEIGHT = 20;
    static const int DELAY= 200;

    void initGame();
    void doDrawing();
    void localApple();
    void move();

    bool inGame;
    int timerId;

    QVector<QPoint> snake;

    QPoint apple;

    enum Directions {
        left, right, up, down
    };
    Directions dir;




};

#endif // GAME_H
