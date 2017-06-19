//
// Created by RenYi on 2017/6/17.
//

#include <QCoreApplication>
#include <ctime>
#include "AI.h"
#include "helpers.h"
#include "chessitem.h"

ChessItem AI::getBestItem(const VirtualBoard &board) {
    vector<ChessItem> bestItems;
    vector<ChessItem> steps;
    steps.resize(DEEP);
    int score = negaMax(board, DEEP, MIN, MAX, board.getComPointType(), bestItems, steps);
    if (score < -FIVE * 0.8) {
        auto candidates = genCandidate(board, board.getComPointType());
        auto item = candidates.front();
        item.setPlayer(board.getComPointType());
        return item;
    }
    for (auto item = bestItems.begin(); item != bestItems.end(); item++) {
        // cout << item->cx << " " << item->cy << endl;
    }
//
    ChessItem solution = bestItems[(int) (rand() % bestItems.size())];
    solution.setPlayer(board.getComPointType());
    return solution;
}

int AI::negaMax(const VirtualBoard &thisBoard, int deep, int alpha, int beta, ItemType itemType,
                vector<ChessItem> &thisBestItems, vector<ChessItem> &steps) {

    int pureScore = thisBoard.evalGlobalScore(itemType);
    if (deep <= 0 || greaterOrEqualThan(pureScore, FOUR*EVAL_BIAS)) {
        if (deep == DEEP) {
            thisBestItems = vector<ChessItem>{genCandidate(thisBoard, itemType).front()};
        }
        return pureScore;
    }

    int best = MIN;
    vector<ChessItem> nextBestItems;

    list<ChessItem> candidates = genCandidate(thisBoard, itemType);
    if(candidates.size()==1 && deep==DEEP){
        ChessItem chessItem=candidates.front();
        thisBestItems.push_back(chessItem);
        return 0;
    }

    for (auto candidate = candidates.begin(); candidate != candidates.end(); candidate++) {
        candidate->setPlayer(itemType);
        VirtualBoard copyBoard(thisBoard);
        copyBoard += *candidate;
        //todo
//        if (candidate->cx == 7 && candidate->cy == 13 && deep == DEEP) {
//            cout << 1;
//        }
//        cout<<deep<<" x:"<<candidate->cx<<" y:"<<candidate->cy<<endl;
        int score = -negaMax(copyBoard, deep - 1, -beta, -max(alpha, best),
                             VirtualBoard::reverseItemType(itemType), nextBestItems, steps);
//        cout<<deep<<" x:"<<candidate->cx<<" y:"<<candidate->cy<<" "<<score<<endl;
//        if (candidate->cx == 7 && candidate->cy == 13 && deep == DEEP) {
//            cout << 1;
//        }

        candidate->score = score;
        if (greaterThan(score, best)) {
            best = score;
            steps[DEEP - deep] = *candidate;
            if (deep == DEEP) {
                thisBestItems.clear();
                thisBestItems.push_back(*candidate);
            }

        } else if (equal(score, best) && deep == DEEP) {
            steps[DEEP - deep] = *candidate;
            thisBestItems.push_back(*candidate);
        }
        if (greaterOrEqualThan(best, beta)) {
            break;
        }
    }

    QCoreApplication::processEvents();

    if (deep == DEEP) {
        // cout << 1;
    }
    return best;
}

list<ChessItem> AI::genCandidate(const VirtualBoard &thisBoard, ItemType itemType) {
    list<ChessItem> result, oppFivesOrFour, fours, threes, neighbors;
    for (int i = 0; i < ChessBoardWidth; i++) {
        for (int j = 0; j < ChessBoardWidth; j++) {
            int self, opponent;
            if (thisBoard.isEmpty(ChessItem(i, j))) {
                if (itemType == BLACK) {
                    self = thisBoard.getScores(BLACK)[i][j].getTotal();
                    opponent = thisBoard.getScores(WHITE)[i][j].getTotal();
                } else {
                    self = thisBoard.getScores(WHITE)[i][j].getTotal();
                    opponent = thisBoard.getScores(BLACK)[i][j].getTotal();
                }
                if (self >= FIVE) {
                    return list<ChessItem>{ChessItem(i, j)};
                } else if (opponent >= FOUR) {
                    oppFivesOrFour.push_back(ChessItem(i, j));
                } else if (self >= FOUR) {
                    fours.push_back(ChessItem(i, j));
                } else if (self >= THREE) {
                    threes.push_back(ChessItem(i, j));
                } else if (self > 0) {
                    neighbors.push_back(ChessItem(i, j));
                }
            }
        }
    }
    if (oppFivesOrFour.size() > 0) {
        return oppFivesOrFour;
    }
    result.splice(result.end(), fours);
    result.splice(result.end(), threes);
    result.splice(result.end(), neighbors);
    return result;
}
