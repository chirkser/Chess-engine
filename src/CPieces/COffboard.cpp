//
// Created by Chirkov on 15.05.2022.
//

#include "COffboard.h"


COffboard::COffboard(CBoard & board, int i) : CPiece(board, i, none, OFFBOARD) {}

std::string COffboard::getChar() const
{
    return "_";
}

std::list<CMove> COffboard::possibleMoves() const
{
    std::list<CMove> tmp;
    return tmp;
}

std::list<CMove> COffboard::possibleCaptures() const
{
    std::list<CMove> tmp;
    return tmp;
}