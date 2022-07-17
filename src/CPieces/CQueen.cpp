//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CQueen.h"

CQueen::CQueen(CBoard & board, int i ,Color color) : CPiece(board, i, color, Pieces::QUEEN) {}

std::list<CMove> CQueen::possibleMoves() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextColor;
    int square;
    // push queen moves
    for (int i : AttackMovesKing)
    {
        square = index + i;
        while (m_Board[square].get()->typeOfPiece() != Pieces::OFFBOARD)
        {
            nextPiece = m_Board[square].get()->typeOfPiece();
            nextColor = m_Board[square].get()->getColor();
            if (nextPiece == Pieces::SPACE)
                tmp.push_back(addMove(index, square, color));

            if (nextPiece != Pieces::SPACE) {
                if (nextColor == clr)
                {
                    tmp.push_back(addCaptureMove(type, index, square, color, m_Board[square].get()->typeOfPiece(),false));
                }
                break;
            }
            square += i;
        }
    }
    return tmp;
}

std::list<CMove> CQueen::possibleCaptures() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    Pieces nextPiece;
    Color nextColor;
    int square;
    // push queen moves
    for (int i : AttackMovesKing)
    {
        square = index + i;
        while (m_Board[square].get()->typeOfPiece() != Pieces::OFFBOARD)
        {
            nextPiece = m_Board[square].get()->typeOfPiece();
            nextColor = m_Board[square].get()->getColor();

            if (nextPiece != Pieces::SPACE) {
                if (nextColor == clr)
                {
                    tmp.push_back(addCaptureMove(type, index, square, color, m_Board[square].get()->typeOfPiece(),false));
                }
                // ?
                break;
            }
            square += i;
        }
    }
    return tmp;
}

std::string CQueen::getChar() const
{
    return color == black ? "q" : "Q";
}