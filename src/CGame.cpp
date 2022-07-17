//
// Created by Chirkov on 06.05.2022.
//

#include "CGame.h"


bool CGame::runGame()
{
    while(true)
    {
        if (isEnd())
        {
            return true;
        }
        if (!getCommand())
            std::cout << unknownCmd << std::endl;
        if (!executeCommand())
            continue;
    }
}


bool CGame::isEnd()
{
    return logic.isEnd();
}


bool CGame::getCommand()
{
    if (!logic.getGameStatus())
    {
        m_Interface.printLogo();
        m_Interface.mainMenu();
    }
    else
    {
        m_Interface.printMenu();
    }

    std::cin >> command;

    return isValidCommand();
}

bool CGame::isValidCommand()
{
    if (!logic.getGameStatus())
    {
        if (command != "N" && command != "n" &&
            command != "L" && command != "l" &&
            command != "H" && command != "h" &&
            command != "Q" && command != "q" )
            return false;
        else
            return true;
    } else
    {
        if (command != "M" && command != "m" &&
            command != "S" && command != "s" &&
            command != "H" && command != "h" &&
            command != "Q" && command != "q" )
            return false;
        else
            return true;
    }

}

bool CGame::executeCommand()
{
    if (!logic.getGameStatus())
    {
        if (command == "N" || command == "n")
        {
            logic.newGame();
            return true;
        }
        else if (command == "L" || command == "l") {
            if (!logic.loadGame())
                return false;
            std::cout << "Game was successfully loaded!" << std::endl;
            return true;
        }
        else if (command == "H" || command == "h") {
            logic.helpMain();
            return true;
        }
        else if (command == "Q" || command == "q") {
            logic.setGameStatus(false);
            logic.setEnd();
            return true;
        }
        else
        {
            return false;
        }

    } else
    {

        if (command == "M" || command == "m")
        {
            if (!logic.getGameStatus())
            {
                std::cout << "Game not started" << std::endl;
                return false;
            }
            logic.takeTurn();
            return true;
        }
        else if (command == "S" || command == "s")
        {
            if (!logic.getGameStatus())
            {
                std::cout << "Nothing to save, try later." << std::endl;
                return false;
            }
            if (!logic.saveGame())
                return false;
            std::cout << "Game was saved!\n";
            return true;
        }
        else if (command == "H" || command == "h") {
            logic.helpPlay();
            return true;
        }
        else if (command == "Q" || command == "q") {
            logic.setGameStatus(false);
            logic.setEnd();
            return true;
        }
        else
            return false;
    }
}
