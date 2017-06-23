#if _MSC_VER >= 1600    // VC2010
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QMouseEvent>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setFixedSize(930, 730);
    setWindowTitle(tr("五子棋游戏"));

    humanPlayAction = new QAction("双人游戏", this);
    humanPlayAction->setShortcuts(QKeySequence::New); // Ctrl+N
    connect(humanPlayAction, &QAction::triggered, this, &MainWindow::startHuman);

    AIPlayAction = new QAction("人机对战", this);
    AIPlayAction->setShortcuts(QKeySequence::SelectAll); // Ctrl+A
    connect(AIPlayAction, &QAction::triggered, this, &MainWindow::startAI);

    QMenu *file = menuBar()->addMenu(tr("&开始"));
    file->addAction(humanPlayAction);
    file->addAction(AIPlayAction);

    toolBar = addToolBar(tr("&开始"));
    toolBar->addAction(humanPlayAction);
    toolBar->addAction(AIPlayAction);

    setStyleSheet("QMainWindow {"
                          "background-image: url(:/images/chessBoard);"
                          "background-repeat:no-repeat;"
                          "background-position: bottom left"
                          "}");
}

void MainWindow::startHuman() {
    QMessageBox::information(this, tr("Information"), tr("开始双人游戏"));
    cc->startGame(false);
}

void MainWindow::startAI() {
    QMessageBox::information(this, tr("Information"), tr("开始人机对战"));
    cc->startGame(true);
}

MainWindow::~MainWindow() {
}


