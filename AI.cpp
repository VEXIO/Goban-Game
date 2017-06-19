//
// Created by RenYi on 2017/6/17.
//

#include <ctime>
#include "AI.h"
#include "helpers.h"

ChessItem AI::getBestItem(const VirtualBoard &board) {
    vector<ChessItem> bestItems;
    vector<ChessItem> steps;
    steps.resize(DEEP);

    int score = negaMax(board, DEEP, MIN, MAX, board.getComPointType(), bestItems, steps);
    if (score < -3000000) {
        return genCandidate(board, board.getComPointType()).front();
    }
    for (auto item = bestItems.begin(); item != bestItems.end(); item++) {
        cout << item->cx << " " << item->cy << endl;
    }

    return bestItems[(int)(rand()%bestItems.size())];
}

int AI::negaMax(const VirtualBoard &thisBoard, int deep, int alpha, int beta, ItemType itemType,
                vector<ChessItem> &thisBestItems, vector<ChessItem> &steps) {
    searchCount++;

    //todo
//    if(alpha==10215 && deep==1){
//        cout<<1;
//    }

    int pureScore = thisBoard.evalGlobalScore(itemType);

    if (deep <= 0 || greaterOrEqualThan(pureScore, FOUR)) {
        if (deep == DEEP) {
            thisBestItems = vector<ChessItem>{genCandidate(thisBoard, itemType).front()};
        }
        return pureScore;
    }

    int best = MIN;
    vector<ChessItem> nextBestItems;

    list<ChessItem> candidates = genCandidate(thisBoard, itemType);
    for (auto candidate = candidates.begin(); candidate != candidates.end(); candidate++) {
        candidate->setPlayer(itemType);
        VirtualBoard copyBoard(thisBoard);
        copyBoard += *candidate;
        //todo
//        if(candidate->cx==9 && candidate->cy==4){
//            cout<<1;
//        }
//        cout<<deep<<" x:"<<candidate->cx<<" y:"<<candidate->cy<<endl;
        int score = -negaMax(copyBoard, deep - 1, -beta, -max(alpha, best),
                             VirtualBoard::reverseItemType(itemType), nextBestItems, steps);
//        cout<<deep<<" x:"<<candidate->cx<<" y:"<<candidate->cy<<" "<<score<<endl;
        candidate->score = score;
        if (greaterThan(score, best)) {
            best = score;
            steps[DEEP - deep] = *candidate;
            if (deep == DEEP) {
                thisBestItems.clear();
                thisBestItems.push_back(*candidate);
            }

            //todo
//            if (deep == DEEP) {
//                cout<<1;
//            }
        } else if (equal(score, best) && deep == DEEP) {
            steps[DEEP - deep] = *candidate;
            thisBestItems.push_back(*candidate);
        }
        if (greaterOrEqualThan(best, beta)) {
            ABcut++;
            break;
        }
    }

    return best;
}

list<ChessItem> AI::genCandidate(const VirtualBoard &thisBoard, ItemType itemType) {
    list<ChessItem> result, oppFives, fours, blockedFours, doubleThrees, threes, twos, neighbors;
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
                    oppFives.push_back(ChessItem(i, j));
                } else if (self >= FOUR) {
                    fours.push_front(ChessItem(i, j));
                } else if (opponent >= BLOCKED_FOUR) {
                    fours.push_back(ChessItem(i, j));
                } else if (self >= BLOCKED_FOUR) {
                    blockedFours.push_front(ChessItem(i, j));
                } else if (opponent >= 2 * THREE) {
                    blockedFours.push_back(ChessItem(i, j));
                } else if (self >= 2 * THREE) {
                    doubleThrees.push_front(ChessItem(i, j));
                } else if (opponent >= THREE) {
                    doubleThrees.push_back(ChessItem(i, j));
                } else if (self >= THREE) {
                    threes.push_back(ChessItem(i, j));
                } else if (opponent >= TWO) {
                    threes.push_back(ChessItem(i, j));
                } else if (self >= TWO) {
                    twos.push_back(ChessItem(i, j));
                } else if (self > 0) {
                    neighbors.push_back(ChessItem(i, j));
                }
            }
        }
    }
    if (oppFives.size() > 0) {
        return oppFives;
    }
    result.splice(result.end(), doubleThrees);
    result.splice(result.end(), threes);
    result.splice(result.end(), twos);
    result.splice(result.end(), neighbors);
//    cout<<fives.size()<<endl;
    return result;
}