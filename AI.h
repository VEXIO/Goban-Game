//
// Created by RenYi on 2017/6/17.
//

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
    ChessItem getBestItem(const VirtualBoard &board);

    int negaMax(const VirtualBoard &thisBoard, int deep, int alpha, int beta, ItemType itemType, vector<ChessItem> &thisBestItems,vector<ChessItem>& steps);

    int searchCount=0;
// debug
int ABcut=0;
private:
    list<ChessItem> genCandidate(const VirtualBoard &thisBoard,ItemType itemType);



};


#endif //GOBANGAME_AI_H
