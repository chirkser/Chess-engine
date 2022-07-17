//
// Created by Chirkov on 06.05.2022.
//

#include "../CBoard.h"
#include "CPawn.h"

CPawn::CPawn(CBoard & board, int i ,Color color) : CPiece(board, i, color, Pieces::PAWN) {}

std::list<CMove> CPawn::possibleCaptures() const
{
    std::list<CMove> tmp;
    int sqLeft = color == Color::white ? 9 : -9;
    int sqRight = color == Color::white ? 11 : -11;
    Color clr = m_Board.actualTurn() == white ? black : white;
    int RankOfPromotion = color == Color::white ? RANK_7 : RANK_2;
    // push capture moves
    if (m_Board[index + sqLeft].get()->typeOfPiece() != Pieces::OFFBOARD && m_Board[index + sqLeft].get()->getColor() == clr)
    {
        if (calculateRank(index) == RankOfPromotion)
        {
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::QUEEN));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::KNIGHT));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::BISHOP));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::ROOK));
        }
        else
            tmp.push_back(addCaptureMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), false));
    }
    if (m_Board[index + sqRight].get()->typeOfPiece() != Pieces::OFFBOARD && m_Board[index + sqRight].get()->getColor() == clr)
    {
        if (calculateRank(index) == RankOfPromotion)
        {
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::QUEEN));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::KNIGHT));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::BISHOP));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::ROOK));
        }
        else
            tmp.push_back(addCaptureMove(type, index, index + sqRight, color, m_Board[index + sqLeft].get()->typeOfPiece(), false));
    }
    // push En Passant capture
//    if (index + sqLeft == m_Board.getEnPassant())
//        tmp.push_back(addCaptureMove(type, index, index + sqLeft, color,  Pieces::PAWN, true));
//    if (index + sqLeft == m_Board.getEnPassant())
//        tmp.push_back(addCaptureMove(type, index, index + sqRight, color,  Pieces::PAWN, true));
    return tmp;
}

std::list<CMove> CPawn::possibleMoves() const
{
    std::list<CMove> tmp;
    int sqLeft = color == Color::white ? 9 : -9;
    int sqRight = color == Color::white ? 11 : -11;
    int sqForward = color == Color::white ? 10 : -10;
    Color clr = m_Board.actualTurn() == white ? black : white;
    int RankOfStart = color == Color::white ? RANK_2 : RANK_7;
    int RankOfPromotion = color == Color::white ? RANK_7 : RANK_2;
    // push forward move
    if (m_Board[index + sqForward].get()->typeOfPiece() == Pieces::SPACE)
    {
        if (calculateRank(index) == RankOfPromotion)
        {
            tmp.push_back(addPromotionMove(type, index, index + sqForward, color, Pieces::SPACE, Pieces::QUEEN));
            tmp.push_back(addPromotionMove(type, index, index + sqForward, color, Pieces::SPACE, Pieces::KNIGHT));
            tmp.push_back(addPromotionMove(type, index, index + sqForward, color, Pieces::SPACE, Pieces::BISHOP));
            tmp.push_back(addPromotionMove(type, index, index + sqForward, color, Pieces::SPACE, Pieces::ROOK));
        } else
        {
            tmp.push_back(addMove(index, index + sqForward, color));
            if (m_Board[2*sqForward + index]->typeOfPiece() == Pieces::SPACE && calculateRank(index) == RankOfStart)
            {
                tmp.push_back(addDoubleMovePawn(index, 2*sqForward + index, color));
            }
        }
    }

    // push capture moves
    if (m_Board[index + sqLeft].get()->typeOfPiece() != Pieces::OFFBOARD && m_Board[index + sqLeft].get()->getColor() == clr)
    {
        if (calculateRank(index) == RankOfPromotion)
        {
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::QUEEN));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::KNIGHT));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::BISHOP));
            tmp.push_back(addPromotionMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), Pieces::ROOK));
        }
        else
            tmp.push_back(addCaptureMove(type, index, index + sqLeft, color, m_Board[index + sqLeft].get()->typeOfPiece(), false));
    }
    if (m_Board[index + sqRight].get()->typeOfPiece() != Pieces::OFFBOARD && m_Board[index + sqRight].get()->getColor() == clr)
    {
        if (calculateRank(index) == RankOfPromotion)
        {
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::QUEEN));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::KNIGHT));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::BISHOP));
            tmp.push_back(addPromotionMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), Pieces::ROOK));
        }
        else
            tmp.push_back(addCaptureMove(type, index, index + sqRight, color, m_Board[index + sqRight].get()->typeOfPiece(), false));
    }
    // push En Passant capture move
    if (index + sqLeft == m_Board.getEnPassant())
        tmp.push_back(addCaptureMove(type, index, index + sqLeft, color,  Pieces::PAWN, true));
    if (index + sqRight == m_Board.getEnPassant())
        tmp.push_back(addCaptureMove(type, index, index + sqRight, color,  Pieces::PAWN, true));
    return tmp;
}


std::string CPawn::getChar() const
{
    return color == black ? "p" : "P";
}