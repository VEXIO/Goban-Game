#if _MSC_VER >= 1600    // VC2010
#pragma execution_character_set("utf-8")
#endif

#include "realboard.h"
#include "chessboard.h"

RealBoard::RealBoard(QWidget *parent) : QWidget(parent), ChessBoard() {
    width = 40;
    chessWidth = width * 0.8;
    topX = 80.f;
    topY = 100.f;
    QRect temp;

    float tx, ty;

    for (int i = 0; i < ChessBoardWidth - 1; i++) {
        for (int j = 0; j < ChessBoardWidth - 1; j++) {
            tx = topX + width * i;
            ty = topY + width * j;
            temp.setCoords(tx, ty, tx + width, ty + width);
            grids.push_back(temp);
        }
    }
}

void RealBoard::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // draw chess board table

    p.drawRects(grids);

    topX = 80.f - width / 2 + (width - chessWidth) / 2;
    topY = 100.f - width / 2 + (width - chessWidth) / 2;
    // draw chess
    for (int i = 0; i < ChessBoardWidth; i++) {
        for (int j = 0; j < ChessBoardWidth; j++) {
            if (this->currentChessBoard[i][j] == EMPTY) {
                continue;
            } else if (this->currentChessBoard[i][j] == WHITE) {
                p.setBrush(Qt::white);
            } else {
                p.setBrush(Qt::black);
            }
            p.drawEllipse(topX + width * i, topY + width * j, chessWidth, chessWidth);
        }
    }

    // text draw

    if (this->gameStatus) {
        // game is playing
        dispText = "游戏进行中...";
    } else {
        // game ends
        if (this->winner == -1) {
            dispText = "游戏未开始，请点击上方按钮开始游戏。";
        } else {
            if (this->winner == 1) {
                // 1P wins
                if (this->isAI) {
                    // AI losses
                    dispText = "你赢了！";
                } else {
                    // human 1P wins
                    dispText = "玩家1胜利！";
                }
            } else {
                // 2P wins
                if (this->isAI) {
                    // AI wins
                    dispText = "你输了！";
                } else {
                    // human 2P wins
                    dispText = "玩家2胜利！";
                }
            }
        }
    }
    p.drawText(55, 45, QString(dispText.c_str()));
}


void RealBoard::win(int winner) {
    this->gameStatus = false;
    this->winner = winner;
}

void RealBoard::play(bool isAIPlayer) {
    this->isAI = isAIPlayer;
    this->winner = -1;
    this->gameStatus = true;
}
