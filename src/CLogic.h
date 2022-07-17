//
// Created by Chirkov on 12.05.2022.
//

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include "CBoard.h"
#include "CPlayers/CPlayerReal.h"
#include "CPlayers/CPlayerComputer.h"


/**
 * Class representation game logic
 */
class CLogic
{
public:
    /**
     * Checking whether the game has started or not yet
     * @return true
     */
    bool getGameStatus() const;
    /**
     * Set game status
     * @param status
     */
    void setGameStatus(bool status);

    /**
     * The command responsible for starting a new game
     * @return true
     */
    bool newGame();
    /**
     * The command responsible for saving actual game
     * @return true
     */
    bool saveGame();
    /**
     * The command responsible for loading a game
     * @return true
     */
    bool loadGame();
    /**
     * The command responsible for making a move
     * @return true
     */
    bool takeTurn();
    /**
     * The command responsible for quitting the game
     * @return true
     */
    bool Quit();

    /**
     * End game check
     * @return true
     */
    bool isEnd() const;
    /**
     * Setter for end game status
     */
    void setEnd();
    /**
     * Checking the validity of user input
     * @param inp
     * @return true
     */
    bool validFilename(std::string inp);
    /**
     * helpful text
     */
    void helpMain();
    /**
     * helpful text
     */
    void helpPlay();
private:
    /**
     * game is started or no
     */
    bool isReady = false;
    /**
     * game is ended or no
     */
    bool end = false;
    /**
     * for user input
     */
    std::string input;
    /**
     * CBoard object
     */
    CBoard m_Board;

    bool flag = false;
    /**
     * CPlayer object for white player
     */
    std::shared_ptr<CPlayer> m_White;
    /**
     * CPlayer object for black player
     */
    std::shared_ptr<CPlayer> m_Black;
};
