#ifndef GOBANGAME_CHESSITEM_H
#define GOBANGAME_CHESSITEM_H

#include "constants.h"
#include <iostream>
#include <QtCore/QMetaType>

using namespace std;
class ChessItem {
public:
    ChessItem() {}

    ChessItem(const ChessItem &it) : cx(it.cx), cy(it.cy), player(it.player) {}

    ChessItem(const int cx, const int cy, const ItemType player = EMPTY) : cx(cx), cy(cy), player(player) {}

    ChessItem(const int cx, const int cy, const int score, const ItemType player = EMPTY) : cx(cx), cy(cy),
                                                                                            player(player) {
        cout<<score;
    }

    void set(const int cx, const int cy, const ItemType player) {
        this->cx = cx;
        this->cy = cy;
        this->player = player;
    }

    void setPlayer(ItemType player) {
        ChessItem::player = player;
    }

    int cx;
    int cy;
    ItemType player;
};

#endif //GOBANGAME_CHESSITEM_H
