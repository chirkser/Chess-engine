//
// Created by Chirkov on 16.05.2022.
//

#include "CMove.h"

CMove::CMove(int from, int to, Color color, Pieces capture, Pieces promotion, bool pawn, bool passant, bool castle, int score) : from(from),
                                                                                                                                 to(to),
                                                                                                                                 pieceColor(color),
                                                                                                                                 capture(capture),
                                                                                                                                 promotion(promotion),
                                                                                                                                 pawnDoubleMove(pawn),
                                                                                                                                 EnPassant(passant),
                                                                                                                                 castle(castle),
                                                                                                                                 score(score)
{}

bool CMove::setMove(const std::string move)
{
    std::string sqFrom;
    sqFrom.push_back(move[0]);
    sqFrom.push_back(move[1]);

    std::string sqTo;
    sqTo.push_back(move[2]);
    sqTo.push_back(move[3]);

    if (convertSq(sqFrom) == -1 ||
        convertSq(sqTo) == -1)
        throw std::logic_error("Unknown square on the board");
    from = convertSq(sqFrom);
    to = convertSq(sqTo);
    if (move[4] == '\n' || move[4] == ' ')
        return true;
    if (move[4] != 'q' &&
        move[4] != 'r' &&
        move[4] != 'b' &&
        move[4] != 'n')
    {
        std::cout << "Unknown promotion\n";
        return false;
    }


    if (move[4] == 'q')
        promotion = Pieces::QUEEN;
    else if (move[4] == 'r')
        promotion = Pieces::ROOK;
    else if (move[4] == 'b')
        promotion = Pieces::BISHOP;
    else
        promotion = Pieces::KNIGHT;
    return true;
}

bool CMove::operator==(const CMove &other)
{
    if (from != other.from)
        return false;
    if (to != other.to)
        return false;
    if (promotion != other.promotion)
        return false;
    return true;
}

int CMove::getFrom() const {
    return from;
}

int CMove::getTo() const {
    return to;
}

Color CMove::getColor() const {
    return pieceColor;
}

bool CMove::getEnPassant() const {
    return EnPassant;
}

bool CMove::getCastle() const
{
    return castle;
}

Pieces CMove::getCapture() const
{
    return capture;
}

bool CMove::getPawnDoubleMove() const
{
    return pawnDoubleMove;
}

Pieces CMove::getPromotion() const
{
    return promotion;
}

CMove addMove(int from, int to, Color color) {
    return CMove(from, to, color, Pieces::SPACE, Pieces::SPACE, false, false, false, 0);
}

CMove addPromotionMove(Pieces exchange, int from, int to,  Color color,  Pieces capture, Pieces promotion) {
    if (capture != Pieces::SPACE)
        return CMove(from, to, color, capture, promotion, false, false, false, powerCapture[convertPieceToInt(capture)] + 6 - ( powerCapture[convertPieceToInt(exchange)] / 100) + 1000000);
    return CMove(from, to, color, capture, promotion, false, false, false, 0);
}

CMove addDoubleMovePawn(int from, int to,Color color) {
    return CMove(from, to, color, Pieces::SPACE, Pieces::SPACE, true, false,  false, 0);
}

CMove addCaptureMove(Pieces piece, int from, int to, Color color, Pieces capture, bool enPassant) {
    return CMove(from, to, color, capture,  Pieces::SPACE, false, enPassant, false, powerCapture[convertPieceToInt(capture)] + 6 - (powerCapture[convertPieceToInt(piece)] / 100) + 1000000);
}

CMove addCastlingMove(char piece) {
    if (piece == 'K')
        return CMove(E1, G1, Color::white, Pieces::SPACE, Pieces::SPACE, false, false, true, 0);
    else if (piece == 'Q')
        return CMove(E1, C1, Color::white, Pieces::SPACE, Pieces::SPACE, false, false, true, 0);
    else if (piece == 'k')
        return CMove(E8, G8, Color::black, Pieces::SPACE, Pieces::SPACE, false, false, true, 0);
    else if (piece == 'q')
        return CMove(E8, C8, Color::black, Pieces::SPACE, Pieces::SPACE, false, false, true, 0);
    else
        throw std::logic_error("Unknown castle move");
}


bool CMove::isValidMove(std::string input)
{
    std::string firstSq;
    std::string secondSq;
    firstSq.push_back(input[0]);
    firstSq.push_back(input[1]);
    secondSq.push_back(input[2]);
    secondSq.push_back(input[3]);
    if (convertStrToInt(firstSq) == Pieces::OFFBOARD ||
        convertStrToInt(secondSq) == Pieces::OFFBOARD)
        return false;
    return true;
}

int convertPieceToInt(Pieces piece)
{
    if (piece == Pieces::PAWN)
        return 0;
    else if (piece == Pieces::KNIGHT)
        return 1;
    else if (piece == Pieces::BISHOP)
        return 2;
    else if (piece == Pieces::ROOK)
        return 3;
    else if (piece == Pieces::QUEEN)
        return 4;
    else if (piece == Pieces::KING)
        return 5;
    else
        throw std::logic_error("Trying convert SPACE or OFF BOARD to int");
}

int convertSq(const std::string & square)
{
    if (square.length() != 2)
        return -1;

    int FILE = square[0] - 'a';
    int RANK = square[1] - '1';

    if ('1' > square[1]
        || square[1] > '8'
        ||'a' > square[0]
        || square[0] > 'h')
        return -1;

    return A1 + FILE + RANK * 10;
}

bool CMove::isIdenticalMove(CMove move) {
    if (pieceColor != move.pieceColor)
        return false;
    if (from != move.from)
        return false;
    if (from != move.to)
        return false;
    if (promotion != move.promotion)
        return false;
    if (capture != move.capture)
        return false;
    if (pawnDoubleMove != move.pawnDoubleMove)
        return false;
    if (EnPassant != move.EnPassant)
        return false;
    if (castle != move.castle)
        return false;
    return true;
}