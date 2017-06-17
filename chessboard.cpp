#include "chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent) {
    this->currentChessBoard.resize(ChessBoardWidth);
    for (int i=0; i<ChessBoardWidth; i++) {
        this->currentChessBoard[i].resize(ChessBoardWidth);
        for (int j=0; j<ChessBoardWidth; j++) {
            this->currentChessBoard[i][j] = -1;
        }
    }
}

void ChessBoard::clear() {
    for (int i=0; i<ChessBoardWidth; i++) {
        for (int j=0; j<ChessBoardWidth; j++) {
            currentChessBoard[i][j] = -1;
        }
    }
}

void ChessBoard::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    float width = 32.2;
    float chessWidth = width * 0.8;
    float topX = 17.f - width / 2 + (width - chessWidth) / 2;
    float topY = 107.f - width / 2 + (width - chessWidth) / 2;

    // draw chessboard
    for (int i=0; i<ChessBoardWidth; i++) {
        for (int j=0; j<ChessBoardWidth; j++) {
            if (this->currentChessBoard[i][j] == -1) {
                continue;
            } else if (this->currentChessBoard[i][j] == 1) {
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

ChessBoard &ChessBoard::operator+=(const ChessItem &next) {
    this->updateChess(next.cx, next.cy, next.player);
    return *this;
}

void ChessBoard::win(int winner) {
    this->gameStatus = false;
    this->winner = winner;
}

void ChessBoard::play(bool isAIPlayer) {
    this->isAI = isAIPlayer;
    this->winner = -1;
    this->gameStatus = true;
}
