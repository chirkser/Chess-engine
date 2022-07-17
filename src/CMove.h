//
// Created by Chirkov on 16.05.2022.
//

#pragma once

#include <iostream>
#include "CConsts.h"



/**
 * Class for representation Move of piece
 */
class CMove {
public:
    CMove() = default;
    /**
     * Constructor
     * @param from move FROM
     * @param to move TO
     * @param color color of Piece
     * @param capture is it capture? true/false
     * @param promotion is it promotion? true/false
     * @param pawn is it double pawn move? true/false
     * @param passant is it EnPassant? true/false
     * @param castle is it Castle? true/false
     * @param score score of the move
     */
    CMove(int from, int to, Color color, Pieces capture = Pieces::SPACE, Pieces promotion = Pieces::SPACE, bool pawn = false, bool passant = false, bool castle = false, int score = 0);
    /**
     * Setter for move
     * @param move move in string format
     * @return true
     */
    bool setMove(const std::string move);
    /**
     * Getter for variable from
     * @return square on the board
     */
    int getFrom() const;
    /**
     * Getter for variable color
     * @return color of Piece
     */
    Color getColor() const;
    /**
     * Getter for variable to
     * @return square on the board
     */
    int getTo() const;
    /**
     * Getter for variable EnPassant
     * @return true
     */
    bool getEnPassant() const;
    /**
     * Getter for variable castle
     * @return true
     */
    bool getCastle() const;
    /**
     * Getter for variable capture
     * @return type of piece
     */
    Pieces getCapture() const;
    /**
     * Getter for variable pawnDoubleMove
     * @return true
     */
    bool getPawnDoubleMove() const;
    /**
     * Getter for variable promotion
     * @return type of piece
     */
    Pieces getPromotion() const;
    /**
     * Checking Checking the validity of a move
     * @param input
     * @return true
     */
    bool isValidMove(std::string input);
    // operator ==
    bool operator == (const CMove & other);
    /**
     * Checking if two moves identical
     * @param move other move
     * @return true
     */
    bool isIdenticalMove(CMove move);
private:
    // variables from and where the move will be made
    int from = OFFBOARD;
    int to = OFFBOARD;


    // Color of piece
    Color pieceColor = white;
    // Piece type of capture
    Pieces capture = Pieces::SPACE;
    // Piece type of promotion
    Pieces promotion = Pieces::SPACE;

    // is it double move(pawn)
    bool pawnDoubleMove = false;
    // status of EnPassant
    bool EnPassant = false;
    // status of Castle
    bool castle = false;
    // Move score
    int score = 0;
};

// Useful functions for generating and defining allowed piece moves
CMove addMove(int from, int to, Color color);
CMove addPromotionMove(Pieces exchange, int from, int to,  Color color,  Pieces capture, Pieces promotion);
CMove addDoubleMovePawn(int from, int to, Color color);
CMove addCaptureMove(Pieces piece, int from, int to, Color color, Pieces capture, bool enPassant);
CMove addCastlingMove(char piece);

// Conversion piece type -> int
int convertPieceToInt(Pieces piece);
// Conversion move in string -> int
int convertSq(const std::string & square);
