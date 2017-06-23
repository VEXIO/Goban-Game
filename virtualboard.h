#ifndef WIDGET_VIRTUALBOARD_H
#define WIDGET_VIRTUALBOARD_H

#include <vector>
#include <iostream>
#include "constants.h"
#include "chessboard.h"

using namespace std;

const pair<int, int> DIR[] = {{1,  0},
                              {0,  1},
                              {1,  1},
                              {-1, 1},

                              {-1, 0},
                              {0,  -1},
                              {-1, -1},
                              {1,  -1}};

class Score {
private:
    int dirScore[4] = {0}, total = 0, convertTotal = 0;
public:
    void setDirScore(const int &dir, const int &score);

    int getTotal() const {
        return convertTotal;
    }

    void setTotal(int total) {
        this->total = total;
        convertTotal = total;
    }
};

class VirtualBoard : public ChessBoard {
public:
    VirtualBoard(ItemType AIColor);

    VirtualBoard(const VirtualBoard &board);

//    VirtualBoard(const vector<std::vector<ItemType >> &board);

    const vector<vector<Score> > &getScores(ItemType itemType) const;

    void set(const ChessItem &next);

    void clear();

    int evalGlobalScore(ItemType itemType) const;

    ItemType getComPointType() const;

    ItemType getHumPointType() const;

    void print(bool showScores = false);

private:
    ItemType comPointType;
    ItemType humPointType;
    vector<vector<Score> > blackScores;
    vector<vector<Score> > whiteScores;

    int evalScoreInOneDir(ChessItem item, int updateDir);

    int calcTypeScore(int totalItems, int firstEmpty, int blockType,bool isEmpty);

};


#endif //WIDGET_VIRTUALBOARD_H
