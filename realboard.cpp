#if _MSC_VER >= 1600    // VC2010
#pragma execution_character_set("utf-8")
#endif

#include "realboard.h"
#include "chessboard.h"

RealBoard::RealBoard(QWidget *parent) : QWidget(parent), ChessBoard() {

}

void RealBoard::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    float width = 32.2;
    float chessWidth = width * 0.8;
    float topX = 17.f - width / 2 + (width - chessWidth) / 2;
    float topY = 107.f - width / 2 + (width - chessWidth) / 2;

    // draw chessboard
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
    p.drawText(5, 15, QString(dispText.c_str()));
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
