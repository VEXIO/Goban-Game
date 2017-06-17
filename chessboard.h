#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ChessBoardWidth = 15;

struct ChessItem {
    ChessItem() {}
    ChessItem(ChessItem &it) : cx(it.cx), cy(it.cy), player(it.player) {}
    ChessItem(int cx, int cy, int player) : cx(cx), cy(cy), player(player) {}
    void set(int cx, int cy, int player) {
        this->cx = cx;
        this->cy = cy;
        this->player = player;
    }
    int cx, cy, player;
};

class ChessBoard : public QWidget {
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);
    void clear();
    void play(bool isAIPlayer);
    void win(int winner);

    const std::vector<std::vector<int>> & getChessBoard() {
        return currentChessBoard;
    }

    void paintEvent(QPaintEvent *e);

    ChessBoard &operator+=(const ChessItem &next);

private:
    std::vector<std::vector<int>> currentChessBoard;
    bool gameStatus = false, isAI;
    int winner = -1;

    string dispText;

    void updateChess(int x, int y, int val) {
        currentChessBoard[x][y] = val;
    }
};

#endif // CHESSBOARD_H
