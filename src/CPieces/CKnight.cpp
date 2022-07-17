//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CKnight.h"


CKnight::CKnight(CBoard & board, int i , Color color) : CPiece(board, i, color, Pieces::KNIGHT) {}

std::list<CMove> CKnight::possibleMoves() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    for (const auto & i : AttackMovesKnight) {
        if (m_Board[index + i].get()->typeOfPiece() == OFFBOARD)
            continue;
        // Push move
        if (m_Board[index + i].get()->typeOfPiece() == SPACE)
            tmp.push_back(addMove(index, index + i, color));
        // Capture move
        if (m_Board[index + i].get()->getColor() == clr)
            tmp.push_back(addCaptureMove(type, index, index + i, color, m_Board[index+i].get()->typeOfPiece(), false));
    }
    return tmp;
}

std::list<CMove> CKnight::possibleCaptures() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    for (const auto & i : AttackMovesKnight) {
        if (m_Board[index + i].get()->typeOfPiece() == OFFBOARD)
            continue;
        // Capture move
        if (m_Board[index + i].get()->getColor() == clr)
            tmp.push_back(addCaptureMove(type, index, index + i, color, m_Board[index+i].get()->typeOfPiece(), false));
    }
    return tmp;
}

std::string CKnight::getChar() const
{
    return color == black ? "n" : "N";
}