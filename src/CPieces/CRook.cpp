//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CRook.h"

CRook::CRook(CBoard & board, int i ,Color color) : CPiece(board, i, color, Pieces::ROOK) {}

std::list<CMove> CRook::possibleMoves() const
{
    std::list<CMove> tmp;
    int square;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextClr;
    // push moves
    for (int i : AttackMovesRook)
    {
        square = index + i;
        while (m_Board[square].get()->typeOfPiece() != Pieces::OFFBOARD)
        {
            nextPiece = m_Board[square].get()->typeOfPiece();
            nextClr = m_Board[square].get()->getColor();
            if (nextPiece == Pieces::SPACE)
                tmp.push_back(addMove(index, square, color));
            if (nextPiece != Pieces::SPACE)
            {
                if (nextClr == clr)
                    tmp.push_back(addCaptureMove(type, index, square, color, m_Board[square].get()->typeOfPiece(), false));
                break;
            }
            square += i;
        }
    }
    return tmp;
}

std::list<CMove> CRook::possibleCaptures() const
{
    std::list<CMove> tmp;
    int square;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextClr;
    // push capture moves
    for (int i : AttackMovesRook)
    {
        square = index + i;
        while (m_Board[square].get()->typeOfPiece() != Pieces::OFFBOARD)
        {
            nextPiece = m_Board[square].get()->typeOfPiece();
            nextClr = m_Board[square].get()->getColor();
            if (nextPiece != Pieces::SPACE)
            {
                if (nextClr == clr)
                    tmp.push_back(addCaptureMove(type, index, square, color, m_Board[square].get()->typeOfPiece(), false));
                break;
            }
            square += i;
        }
    }
    return tmp;
}

std::string CRook::getChar() const
{
    return color == black ? "r" : "R";
}