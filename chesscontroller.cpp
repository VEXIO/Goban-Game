#include "chesscontroller.h"

void ChessController::startGame(bool isAIPlayer) {
    this->isAIPlayer = isAIPlayer;
    this->isPlaying = true;
    this->currentPlayer = BLACK;
    stepCnt = 0;
    virtualBoard.clear();
    cb.clear();
    cb.play(isAIPlayer);
}

int ChessController::judgeSingleDirect(int dx, int dy) const {
    int cnt = 1;
    int cx = nextStepItem.cx, cy = nextStepItem.cy, p = nextStepItem.player;
    while (cx + dx * cnt >= 0 && cx + dx * cnt < ChessBoardWidth &&
           cy + dy * cnt >= 0 && cy + dy * cnt < ChessBoardWidth &&
           curChessBoard[cx + dx * cnt][cy + dy * cnt] == nextStepItem.player) {
        cnt++;
    }
    return cnt - 1;
}

bool ChessController::judge() {
    if (judgeSingleDirect(-1, -1) + judgeSingleDirect(1, 1) >= 4 ||
        judgeSingleDirect(-1, 1) + judgeSingleDirect(1, -1) >= 4 ||
        judgeSingleDirect(-1, 0) + judgeSingleDirect(1, 0) >= 4 ||
        judgeSingleDirect(0, -1) + judgeSingleDirect(0, 1) >= 4) {
        this->isPlaying = false;
        cb.win(currentPlayer);
        return true;
    }
    return false;
}

ChessItem ChessController::AIgo() {
    ChessItem nextItem = AI::getBestItem(virtualBoard);
    return nextItem;
}

void ChessController::nextStep(int cx, int cy) {
    cout<<cx<<cy;
    if (!isPlaying) { return; }
    if (cx < 0 || cy < 0 || cx >= ChessBoardWidth || cy >= ChessBoardWidth) { return; }
    if (curChessBoard[cx][cy] != EMPTY) { return; }
    if (isAIPlayer && currentPlayer == WHITE) {
        return;
    }
    nextStepItem.set(cx, cy, currentPlayer);
    cb += nextStepItem;
    virtualBoard+=nextStepItem;

    if (judge()) { return; }
    currentPlayer = ChessBoard::reverseItemType(currentPlayer);
    if (currentPlayer == WHITE && isAIPlayer) {
        nextStepItem = AIgo();
        cb += nextStepItem;
        virtualBoard += nextStepItem;
        if (judge()) { return; }
        currentPlayer = ChessBoard::reverseItemType(currentPlayer);
    }
}
