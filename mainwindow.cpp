#if _MSC_VER >= 1600    // VC2010
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QMouseEvent>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setFixedSize(485, 600);
    // chessboard 490 557
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

    QToolBar *toolBar = addToolBar(tr("&开始"));
    toolBar->addAction(humanPlayAction);
    toolBar->addAction(AIPlayAction);

    setStyleSheet("QMainWindow {"
                          "background-image: url(:/images/chessBoard);"
                          "background-repeat:no-repeat;"
                          "background-position: bottom left"
                          "}");
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
    float width = 32.2;
    float chessWidth = 0.95 * width;
    float topX = 17.f - width / 2 + (width - chessWidth) / 2;
    float topY = 107.f - width / 2 + (width - chessWidth) / 2;
    float cx = e->x() - topX, cy = e->y() - topY - width;
    int ccx = cx / width, ccy = cy / width;
    if (cx > ccx * width + chessWidth || cy > ccy * width + chessWidth) { return; }
    cc->nextStep(ccx, ccy);
    update();
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
