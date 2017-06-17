#include "mainwindow.h"
#include "chessboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ChessBoard cb;
    ChessController cc(cb);
    w.setCentralWidget(&cb); // link chessboard display widget
    w.chessInstance(&cc); // link chess controller
    w.show();

    return a.exec();
}
