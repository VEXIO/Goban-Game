//
// Created by RenYi on 2017/6/17.
//

#ifndef GOBANGAME_CONSTANTS_H
#define GOBANGAME_CONSTANTS_H

enum ItemType {
    EMPTY = -1,
    WHITE = 0,
    BLACK = 1
};


enum TypeScore {
    ONE = 10,
    TWO = 1000,
    THREE = 20000,
    FOUR = 1000000,
    FIVE = 50000000,
    BLOCKED_ONE = 1,
    BLOCKED_TWO = 30,
    BLOCKED_THREE = 1000,
    BLOCKED_FOUR = 400000
};

const int MAX = 1000000000;
const int MIN = -1000000000;
#endif //GOBANGAME_CONSTANTS_H
