//
// Created by RenYi on 2017/6/17.
//

#ifndef WIDGET_CHESSBOARD_H
#define WIDGET_CHESSBOARD_H


#include <vector>
#include <string>
#include <iostream>
#include "constants.h"
#include "chessitem.h"

using namespace std;
const int ChessBoardWidth = 15;

class ChessBoard {
public:
    ChessBoard();

    ChessBoard(const ChessBoard &board);

    ChessBoard &operator+=(const ChessItem &next);

    ChessBoard &operator-=(const ChessItem &next);

    const vector<vector<ItemType> > &getChessBoard() const {
        return currentChessBoard;
    }

    bool isBlock(const ChessItem point) const;

    bool isEmpty(const ChessItem point) const;

    bool isItem(const ChessItem point) const;

    static ItemType reverseItemType(ItemType itemType) {
        return itemType == BLACK ? WHITE : BLACK;
    }

    virtual void clear();

protected:
    vector<vector<ItemType> > currentChessBoard;

    void updateChess(int x, int y, ItemType val);

    virtual void set(const ChessItem &next);

    void remove(const ChessItem &next);

};

#endif //WIDGET_CHESSBOARD_H
