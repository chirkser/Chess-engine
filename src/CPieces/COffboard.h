//
// Created by Chirkov on 15.05.2022.
//

#pragma once

#include "../CPiece.h"


/**
 * Class COffboard representing an an empty cell outside the board
 */

class COffboard : public CPiece
{
public:
    COffboard(CBoard &board, int i);

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

