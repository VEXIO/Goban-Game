#include "chessboard.h"

ChessBoard::ChessBoard() {
    this->currentChessBoard.resize(ChessBoardWidth);
    for (int i = 0; i < ChessBoardWidth; i++) {
        this->currentChessBoard[i].resize(ChessBoardWidth, EMPTY);
    }
}

void ChessBoard::updateChess(int x, int y, ItemType val) {
    currentChessBoard[x][y] = val;
}

ChessBoard &ChessBoard::operator+=(const ChessItem &next) {
    set(next);
    return *this;
}

ChessBoard &ChessBoard::operator-=(const ChessItem &next) {
    remove(next);
    return *this;
}

ChessBoard::ChessBoard(const ChessBoard &board) {
    this->currentChessBoard.resize(ChessBoardWidth);
    for (int i = 0; i < ChessBoardWidth; i++) {
        this->currentChessBoard[i].resize(ChessBoardWidth);
        for (int j = 0; j < ChessBoardWidth; j++) {
            currentChessBoard[i][j] = board.getChessBoard()[i][j];
        }
    }
}

void ChessBoard::remove(const ChessItem &next) {
    updateChess(next.cx, next.cy, EMPTY);
}

void ChessBoard::set(const ChessItem &next) {
    if (isEmpty(next)) {
        updateChess(next.cx, next.cy, next.player);
    }
}

bool ChessBoard::isBlock(const ChessItem chessItem) const {
    return chessItem.cx < 0 || chessItem.cy < 0 ||
           chessItem.cx >= ChessBoardWidth || chessItem.cy >= ChessBoardWidth ||
           (currentChessBoard[chessItem.cx][chessItem.cy] != chessItem.player &&
            currentChessBoard[chessItem.cx][chessItem.cy] != EMPTY);
}

bool ChessBoard::isEmpty(const ChessItem point) const {
    return point.cx >= 0 && point.cy >= 0 &&
           point.cx < ChessBoardWidth && point.cy < ChessBoardWidth &&
           currentChessBoard[point.cx][point.cy] == EMPTY;
}

bool ChessBoard::isItem(const ChessItem point) const {
    return point.cx >= 0 && point.cy >= 0 &&
           point.cx < ChessBoardWidth && point.cy < ChessBoardWidth &&
           currentChessBoard[point.cx][point.cy] != EMPTY;
}

void ChessBoard::clear() {
    for (int i = 0; i < ChessBoardWidth; i++) {
        for (int j = 0; j < ChessBoardWidth; j++) {
            currentChessBoard[i][j] = EMPTY;
        }
    }
}