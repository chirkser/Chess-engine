//
// Created by Chirkov on 06.05.2022.
//

#pragma once

#include <iostream>
#include "CMove.h"
#include "list"

class CBoard;


/**
 * Parent class CPiece  for every Piece in game
 */
class CPiece {
public:
    /**
     * Constructor
     * @param board chess board
     * @param i position
     * @param color color
     * @param p type of piece
     */
    explicit CPiece(CBoard & board, int i, Color color, Pieces p);

    virtual ~CPiece() = default;

    /**
     * Getter for piece type
     * @return piece
     */
    virtual Pieces typeOfPiece();

    /**
     * Getter for piece colo
     * @return color
     */
    virtual Color getColor();

    /**
     * Getter for piece position
     * @return square
     */
    virtual int getPosition();


    /**
     * Generation of all possible moves of a chess piece
     * @return std::list<CMove>
     */
    virtual std::list<CMove> possibleMoves() const = 0;
    /**
    * Generation of all possible captures of a chess piece
    * @return std::list<CMove>
    */
    virtual std::list<CMove> possibleCaptures() const = 0;

    /**
     * Get string representation of piece
     * @return string
     */
    virtual std::string  getChar () const { return "."; }
    /**
     * Setter for piece position
     * @param square
     */
    virtual void setPosition(int square);
protected:
    // Game board
    CBoard & m_Board;

    // Position
    int index;

    // Piece color
    Color color;

    // Piece type
    Pieces type;
};

