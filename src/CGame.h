//
// Created by Chirkov on 06.05.2022.
//

#pragma once

#include <iostream>
#include <memory>
#include "CUserInterface.h"
#include "CLogic.h"

class CGame {
public:
    /**
     * Main game loop
     * @return true
     */
    bool runGame();

    /**
     * read from console user input
     * @return true
     */
    bool getCommand();

    /**
     * Check the validity of the command
     * @return true
     */
    bool isValidCommand();

    /**
     * Handle command
     * @return true
     */
    bool executeCommand();

    /**
     * Check if game was ended
     * @return true
     */
    bool isEnd();
private:

    // object CUserInterface
    CUserInterface m_Interface;
    // object CLogic
    CLogic logic;
    // for input
    std::string command;
};


