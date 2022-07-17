//
// Created by Chirkov on 06.05.2022.
//

#pragma once


#include "CBoard.h"
#include "CConsts.h"
#include "iostream"


/**
 * Parent class CPlayer representing players in the game
 */
class CPlayer {
public:

    /**
     * Constructor
     * @param clr color of player
     * @param board chess board
     * @param difficulty difficulty of AI
     */
    CPlayer(Color clr, CBoard & board, int difficulty);


    virtual ~CPlayer() = default;

    /**
     * Make a turn for actual player
     * @return true
     */
    virtual bool makeTurn() = 0;

    /**
     * Check if this is a real player or not
     * @return true
     */
    virtual bool isReal() = 0;


protected:

    // Player colo
    Color color;

    // Chess board
    CBoard & board;

    // AI level
    int compLevel = 0;
};

