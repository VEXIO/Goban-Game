
#ifndef REALBOARD_H
#define REALBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <string>
#include <vector>
#include "chessitem.h"
#include "chessboard.h"
#include "constants.h"

using namespace std;

class ChessBoard;

class RealBoard : public QWidget, public ChessBoard {
Q_OBJECT
public:
    RealBoard(QWidget *parent = nullptr);

    void play(bool isAIPlayer);

    void win(int winner);

    void paintEvent(QPaintEvent *e);

private:
    bool gameStatus = false, isAI;
    int winner = -1;

    QVector<QRect> grids;

    float width, chessWidth, topX, topY;

    string dispText;
};

#endif // REALBOARD_H
