#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "realboard.h"
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

private:
    void startHuman();
    void startAI();
    QToolBar *toolBar;
    ChessController *cc;
    QAction *humanPlayAction, *AIPlayAction;
};

#endif // MAINWINDOW_H
