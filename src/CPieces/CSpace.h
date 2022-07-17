//
// Created by Chirkov on 12.05.2022.
//

#pragma once

#include "../CPiece.h"

/**
 * Class CSpace representing an empty cell on the board
 */

class CSpace : public CPiece
{
public:
    CSpace(CBoard & board, int i);

    /**
     * Generation of all possible moves of a chess piece
     * @return std::list<CMove>
     */
    std::list<CMove> possibleMoves() const override;

    /**
    * Generation of all possible captures of a chess piece
    * @return std::list<CMove>
    */
    std::list<CMove> possibleCaptures() const override;

    /**
     * Get string representation of piece
     * @return string
     */
    std::string getChar() const override;
};
