#include "mainwindow.h"
#include "realboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    RealBoard cb;
    ChessController cc(cb);
    cb.linkCC(&cc);
    w.setCentralWidget(&cb); // link chessboard display widget
    w.chessInstance(&cc); // link chess controller
    w.show();

    return a.exec();
}
