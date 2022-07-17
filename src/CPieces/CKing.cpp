//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CKing.h"

CKing::CKing(CBoard & board, int i ,Color color) : CPiece(board, i, color, Pieces::KING) {}

std::list<CMove> CKing::possibleMoves() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    // Push king moves
    for (auto & i : AttackMovesKing)
    {
        if (m_Board[index + i].get()->typeOfPiece() == Pieces::OFFBOARD)
            continue;
        // Simple move
        if (m_Board[index + i].get()->typeOfPiece() == Pieces::SPACE)
            tmp.push_back(addMove(index, index + i, color));
        // Capture move
        if (m_Board[index + i].get()->getColor() == clr)
            tmp.push_back(addCaptureMove(type, index, index + i, color,  m_Board[index + i].get()->typeOfPiece(), false));
    }

    if (m_Board.getCastle())
    {
        if (color == Color::white)
        {
            if (m_Board.getCastleWK())
            {
                if (m_Board[H1].get()->typeOfPiece() == Pieces::ROOK)
                {
                    if (m_Board[F1].get()->typeOfPiece() == Pieces::SPACE && m_Board[G1].get()->typeOfPiece() == Pieces::SPACE)
                    {
                        if (!m_Board.sqAttacked(E1, Color::black) && !m_Board.sqAttacked(F1, Color::black))
                        {
                            tmp.push_back(addCastlingMove('K'));
                        }
                    }
                }
            }
            if (m_Board.getCastleWQ())
            {
                if (m_Board[A1].get()->typeOfPiece() == Pieces::ROOK)
                {
                    if (m_Board[D1].get()->typeOfPiece() == Pieces::SPACE &&
                        m_Board[B1].get()->typeOfPiece() == Pieces::SPACE &&
                        m_Board[C1].get()->typeOfPiece() == Pieces::SPACE)
                    {
                        if (!m_Board.sqAttacked(B1, Color::black) && !m_Board.sqAttacked(D1, Color::black))
                        {
                            tmp.push_back(addCastlingMove('Q'));
                        }
                    }
                }
            }
        } else
        {
            if (m_Board.getCastleBK())
            {
                if (m_Board[H1].get()->typeOfPiece() == Pieces::ROOK)
                {
                    if (m_Board[F8].get()->typeOfPiece() == Pieces::SPACE && m_Board[G8].get()->typeOfPiece() == Pieces::SPACE)
                    {
                        if (!m_Board.sqAttacked(E8, Color::white) && !m_Board.sqAttacked(F8, Color::white))
                        {
                            tmp.push_back(addCastlingMove('k'));
                        }
                    }
                }
            }
            if (m_Board.getCastleBQ())
            {
                if (m_Board[A8].get()->typeOfPiece() == Pieces::ROOK)
                {
                    if (m_Board[D8].get()->typeOfPiece() == Pieces::SPACE &&
                        m_Board[B8].get()->typeOfPiece() == Pieces::SPACE &&
                        m_Board[C8].get()->typeOfPiece() == Pieces::SPACE)
                    {
                        if (!m_Board.sqAttacked(E8, Color::white) && !m_Board.sqAttacked(D8, Color::white))
                        {
                            tmp.push_back(addCastlingMove('q'));
                        }
                    }
                }
            }
        }
    }
    return tmp;
}

std::list<CMove> CKing::possibleCaptures() const
{
    std::list<CMove> tmp;
    Color clr = m_Board.actualTurn() == white ? black : white;
    // Push king moves
    for (auto & i : AttackMovesKing)
    {
        if (m_Board[index + i].get()->typeOfPiece() == Pieces::OFFBOARD)
            continue;
        // Capture move
        if (m_Board[index + i].get()->getColor() == clr)
            tmp.push_back(addCaptureMove(type, index, index + i, color,  m_Board[index + i].get()->typeOfPiece(), false));
    }
    return tmp;
}

std::string CKing::getChar() const
{
    return color == black ? "k" : "K";
}

bool CKing::twoKingsAround() const
{
    Color clr = m_Board.actualTurn() == white ? black : white;
    for (auto i : AttackMovesKing)
    {
        if (m_Board[index + i].get()->typeOfPiece() == Pieces::KING &&
            m_Board[index + i].get()->getColor() == clr)
            return true;
    }
    return false;
}