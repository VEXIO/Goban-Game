#ifndef GOBANGAME_AI_H
#define GOBANGAME_AI_H


#include <list>
#include <iostream>
#include <algorithm>
#include "chessitem.h"
#include "virtualboard.h"
#include "config.h"

class AI {
public:
    static ChessItem getBestItem(const VirtualBoard &board);

    static int negaMax(const VirtualBoard &thisBoard, int deep, int alpha, int beta, ItemType itemType, vector<ChessItem> &thisBestItems,vector<ChessItem>& steps);

private:
    static list<ChessItem> genCandidate(const VirtualBoard &thisBoard,ItemType itemType);

};


#endif //GOBANGAME_AI_H
