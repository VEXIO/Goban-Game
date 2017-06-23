
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

class ChessController;

class RealBoard : public QWidget, public ChessBoard {
Q_OBJECT
public:
    RealBoard(QWidget *parent = nullptr);

    void play(bool isAIPlayer);

    void win(int winner);

    void paintEvent(QPaintEvent *e);

    void linkCC(ChessController *cc) { this->cc = cc; }

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool gameStatus = false, isAI;
    int winner = -1;

    QVector<QRect> grids;

    ChessController *cc;

    float width, chessWidth, topX, topY;

    string dispText;
};


#include "chesscontroller.h"


#endif // REALBOARD_H
