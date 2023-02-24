//
// Created by Hayden Collins on 2/21/23.
//

#include "Empty.h"


Empty::Empty(int color) : Piece(color) {
    value = 0;
    unicode = ".";
    side = color;
}

vector<int> Empty::getAttackedSquares(int initial_pos) {
    return vector<int>{};
}
