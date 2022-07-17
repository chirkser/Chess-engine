//
// Created by Chirkov on 06.05.2022.
//

#include "CPiece.h"

CPiece::CPiece(CBoard & board, int i, Color color, Pieces p) : m_Board(board), index(i), color(color), type(p) {}

Pieces CPiece::typeOfPiece()
{
    return type;
}

Color CPiece::getColor()
{
    return color;
}

int CPiece::getPosition()
{
    return index;
}

void CPiece::setPosition(int square)
{
    index = square;
}