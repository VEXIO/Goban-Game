#include "chesscontroller.h"

void ChessController::startGame(bool isAIPlayer) {
    this->isAIPlayer = isAIPlayer;
    this->isPlaying = true;
    this->currentPlayer = 1;
    stepCnt = 0;
    cb.clear();
    cb.play(isAIPlayer);
}

int ChessController::judgeSingleDirect(int dx, int dy) const {
    int cnt = 1;
    int cx = nextStepItem.cx, cy = nextStepItem.cy, p = nextStepItem.player;
    while (cx + dx * cnt >=0 && cx + dx * cnt < ChessBoardWidth &&
           cy + dy * cnt >=0 && cy + dy * cnt < ChessBoardWidth &&
           curChessBoard[cx + dx * cnt][cy + dy * cnt] == nextStepItem.player) {
        cnt++;
    }
    return cnt - 1;
}

bool ChessController::judge() {
    if ( judgeSingleDirect(-1, -1) + judgeSingleDirect(1,  1) >= 4 ||
         judgeSingleDirect(-1,  1) + judgeSingleDirect(1, -1) >= 4 ||
         judgeSingleDirect(-1,  0) + judgeSingleDirect(1,  0) >= 4 ||
         judgeSingleDirect( 0, -1) + judgeSingleDirect(0,  1) >= 4 ) {
        this->isPlaying = false;
        cb.win(currentPlayer);
        return true;
    }
    return false;
}

ChessItem ChessController::AIgo() {
    int cx, cy;
    for (int i=0; i<ChessBoardWidth; i++) {
        for (int j=0; j<ChessBoardWidth; j++) {
            if (curChessBoard[i][j] == -1) {
                ChessItem nstep;
                nstep.set(i, j, currentPlayer);
                return nstep;
            }
        }
    }
}

void ChessController::nextStep(int cx, int cy) {
    if (!isPlaying) { return; }
    if (cx < 0 || cy < 0 || cx >= ChessBoardWidth || cy >= ChessBoardWidth) { return; }
    if (curChessBoard[cx][cy] != -1) { return; }
    nextStepItem.set(cx, cy, currentPlayer);
    cb += nextStepItem;
    if (judge()) { return; }
    currentPlayer = !currentPlayer;
    if (!currentPlayer && isAIPlayer) {
        nextStepItem = AIgo();
        cb += nextStepItem;
        if (judge()) { return; }
        currentPlayer = !currentPlayer;
    }
}
