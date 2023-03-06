//
// Created by Hayden Collins on 2/3/23.
//

#include "Piece.h"

using namespace std;

Piece::Piece(int color) {
    hasMoved = false;
    side = color;
    pieceType = 'e';
}

vector<int> Piece::getAttackedSquares(int index, vector<unique_ptr<Piece>> &board) {
    return vector<int>{};
}
