#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <vector>
#include "realboard.h"

class ChessController {
public:
    ChessController(RealBoard &cb) : cb(cb), curChessBoard(cb.getChessBoard()) {}
    void startGame(bool isAIPlayer);
    void nextStep(int cx, int cy);
private:
    RealBoard &cb;
    const std::vector<std::vector<int>>& curChessBoard;
    bool judge();
    int judgeSingleDirect(int dx, int dy) const;
    ChessItem AIgo();

    ChessItem nextStepItem;
    int currentPlayer = 1; // 1p=1 or 2p=0  default 1p;
    int stepCnt;
    bool isAIPlayer = false; // default no AI
    bool isPlaying = false;
};

#endif // CHESSCONTROLLER_H
