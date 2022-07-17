//
// Created by Chirkov on 22.05.2022.
//

#pragma once

#include "CConsts.h"
#include "CMove.h"


/**
 * Class to store game history (for draw check)
 */
struct CMoves
{
    CMoves()
    {
        m_castleRights[white][queen_side] = false;
        m_castleRights[black][queen_side] = false;
        m_castleRights[white][king_side] = false;
        m_castleRights[black][king_side] = false;
    }
    // Castle rights
    bool m_castleRights[colors][castles]{};

    CMove move;

    int m_EnPassant = Pieces::OFFBOARD;
    //  if no capture has been made and no pawn has been moved in the last fifty moves
    int m_FiftyTurns = 0;
    // FEN of the board
    std::string FEN;
};


