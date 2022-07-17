//
// Created by Chirkov on 06.05.2022.
//

#pragma once

#include "string"
#include "../CPlayer.h"

class CBoard;

/**
 * Class CPlayerReal representing a real player
 */

class CPlayerReal : public CPlayer {
public:
    CPlayerReal(Color clr, CBoard & board);

    /**
     * Gets information from the user and makes a move
     * @return true
     */
    bool makeTurn() override;

    /**
     * Checking if player is real
     * @return true
     */
    bool isReal();
};


