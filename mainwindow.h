#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessboard.h"
#include "chesscontroller.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void chessInstance(ChessController *cc) { this->cc = cc; }
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void startHuman();
    void startAI();
    ChessController *cc;
    QAction *humanPlayAction, *AIPlayAction;
};

#endif // MAINWINDOW_H
