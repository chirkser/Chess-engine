//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CBishop.h"

CBishop::CBishop(CBoard & board, int i ,Color color) : CPiece(board, i, color, Pieces::BISHOP) {}

std::list<CMove> CBishop::possibleMoves() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextClr;
    int nextSquare = 0;
    for (const auto &i: AttackMovesBishop)
    {
        nextSquare = index + i;
        while (m_Board[nextSquare].get()->typeOfPiece() != OFFBOARD)
        {
            nextClr = m_Board[nextSquare].get()->getColor();
            nextPiece = m_Board[nextSquare].get()->typeOfPiece();
            if (nextPiece == Pieces::SPACE)
                tmp.push_back(addMove(index, nextSquare, color));
            if (!(nextPiece == Pieces::SPACE))
            {
                if (nextClr == clr) {
                    tmp.push_back(
                            addCaptureMove(type, index, nextSquare, color, m_Board[nextSquare].get()->typeOfPiece(),
                                           false));
                }
                break;
            }
                nextSquare += i;
            }
        }
    return tmp;
}

std::list<CMove> CBishop::possibleCaptures() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextClr;
    int nextSquare = 0;
    for (const auto &i: AttackMovesBishop)
    {
        nextSquare += index + i;
        while (m_Board[nextSquare].get()->typeOfPiece() != OFFBOARD)
        {
            nextClr = m_Board[nextSquare].get()->getColor();
            nextPiece = m_Board[nextSquare].get()->typeOfPiece();
            if (!(nextPiece == Pieces::SPACE))
            {
                if (nextClr == clr) {
                    tmp.push_back(
                            addCaptureMove(type, index, nextSquare, color, m_Board[nextSquare].get()->typeOfPiece(),
                                           false));
                }
                break;
            }
                nextSquare += i;
        }
    }
    return tmp;
}

std::string CBishop::getChar() const
{
    return color == black ? "b" : "B";
}