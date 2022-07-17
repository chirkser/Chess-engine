//
// Created by Chirkov on 12.05.2022.
//

#include "CSpace.h"

CSpace::CSpace(CBoard & board, int i) : CPiece(board, i, none, Pieces::SPACE) {}

std::string CSpace::getChar() const
{
    return ".";
}

std::list<CMove> CSpace::possibleMoves() const
{
    std::list<CMove> tmp;
    return tmp;
}

std::list<CMove> CSpace::possibleCaptures() const
{
    std::list<CMove> tmp;
    return tmp;
}
