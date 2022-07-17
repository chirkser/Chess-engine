//
// Created by Chirkov on 06.05.2022.
//

#pragma once
#include "iostream"
#include "../CPlayer.h"


class CBoard;

/**
 * Class CPlayerComputer representing a real player
 */

class CPlayerComputer : public CPlayer {
public:
    CPlayerComputer(Color clr, CBoard & board, int difficulty);

    /**
     * Makes best turn. Depends on the difficulty selected by the user
     * @return true
     */
    bool makeTurn() override;

    /**
    * Checking if player is real
    * @return true
    */
    bool isReal() override;

    /**
     * Determines the power on the board for level 3
     * @return score
     */
    int evaluateBoard();
    /**
    * Determines the power on the board easily for level 2
    * @return score
    */
    int evaluateBoardEasy();
    /**
     * Algorithm min a max -> Doesn't work well, left it unused
     * @param depth
     * @param maximize
     * @return std::pair<int, CMove>
     */
    std::pair<int, CMove> minMax(int depth, bool maximize);
    /**
     * Finding the best move for difficulty 1
     */
    void firstLevel();
    /**
     * Finding the best move for difficulty 2
     * @return CMove
     */
    CMove secondLevel();
    /**
     * Finding the best move for difficulty 3
     * @return CMove
     */
    CMove thirdLevel();
private:
};


