//
// Created by Chirkov on 12.05.2022.
//

#include "CLogic.h"



bool CLogic::isEnd() const
{
    return end;
}


bool CLogic::newGame()
{
    std::cout << "\n| (2p)  Player vs Player |\n| (pc[1][2][3]  Player vs Computer[difficulty] |\n";
    std::cout << "Enter game mode: ";

    if (!(std::cin >> input))
    {
        return false;
    }

    if (input == "pc1")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 1));
    } else if (input == "2p")
    {
        m_Board.setGameMode();
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerReal>(CPlayerReal(Color::black, m_Board));
    }else if (input == "pc2")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 2));
    }
    else if (input == "pc3")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 3));
    }
    else
    {
        std::cout << "Unknown game mode!\n";
        setGameStatus(false);
        return false;
    }

    m_Board.fillBoard(basicBoard);
    m_Board.print();
    m_Board.printTurn();
    // m_Board.printStats();
    setGameStatus(true);
    return true;
}

bool CLogic::saveGame()
{
    std::string res = m_Board.generateFen();
    std::ofstream file;
    std::cout << "Enter file name for save.\n";
    std::string inp;
    if (!(std::cin >> inp))
    {
        std::cout << "Error while reading filename!\n";
        return false;
    }

    if (!validFilename(inp))
    {
        std::cout << "Invalid file name!" << std::endl;
        return false;
    }
    file.open(path + inp + format, std::ios::out);
    if (!file.is_open())
        std::cout << "Error while opening file!\n";
    else
        file << m_Board.generateFen();
    file.close();
    return true;
}

bool CLogic::loadGame()
{
    std::cout << "\n| (2p)  Player vs Player |\n| (pc[1][2][3]  Player vs Computer[difficulty] |\n";
    std::cout << "Enter game mode: ";

    if (!(std::cin >> input))
    {
        return false;
    }

    if (input == "pc1")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 1));
    } else if (input == "2p")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerReal>(CPlayerReal(Color::black, m_Board));
    }else if (input == "pc2")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 2));
    }
    else if (input == "pc3")
    {
        m_White = std::make_shared<CPlayerReal>(CPlayerReal(Color::white, m_Board));
        m_Black = std::make_shared<CPlayerComputer>(CPlayerComputer(Color::black, m_Board, 3));
    }
    else
    {
        std::cout << "Unknown game mode!\n";
        setGameStatus(false);
        return false;
    }
    std::ifstream file;
    std::cout << "Enter file name for load.\n";
    std::string inp;
    std::string fen;
    if (!(std::cin >> inp))
    {
        std::cout << "Error while reading filename!\n";
        return false;
    }
    if (!validFilename(inp))
    {
        std::cout << "Invalid file name!" << std::endl;
        return false;
    }
    file.open(path + inp + format, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Error while opening file!" << std::endl;
        return false;
    }
    else
    {
        getline(file,fen);
        if (!m_Board.fillBoard(fen))
        {
            std::cout << "Error while loading board!" << std::endl;
            return false;
        }
        m_Board.print();
        m_Board.printTurn();
        setGameStatus(true);
        return true;
    }
    return true;
}

bool CLogic::Quit()
{
    std::cout << "Quit\n";
    setEnd();
    setGameStatus(false);
    return true;
}

void CLogic::setEnd()
{
    end = true;
}

bool CLogic::getGameStatus() const
{
    return isReady;
}

void CLogic::setGameStatus(bool status)
{
    isReady = status;
}

bool CLogic::takeTurn()
{
    if (!(m_Board.actualTurn() == white ? m_White->makeTurn() : m_Black->makeTurn()))
    {
        setEnd();
        return false;
    } else
    if (!(m_Board.actualTurn() == white ? m_White->isReal() : m_Black->isReal()))
    {
        if (!(m_Board.actualTurn() == white ? m_White->makeTurn() : m_Black->makeTurn()))
        {
            setEnd();
            return false;
        }
    }
    m_Board.print();
    m_Board.printTurn();
    //m_Board.printStats();

    return true;
}

bool CLogic::validFilename(std::string inp)
{
    if (inp == "" || inp == " ")
    {
        return false;
    }

    for (auto & i : inp)
    {
        if (i == '/')
            return false;
    }
    return true;
}


void CLogic::helpPlay()
{
    std::cout << "\n\nTo make a move, enter M or m and move in the desired format:\n";
    std::cout << "\nExample: m a2a3\n";
    std::cout << "\nTo save a game, enter S or s and write file name.\n";
    std::cout << "\nTo exit the game, type Q or q\n\n";
}

void CLogic::helpMain()
{
    std::cout << "\n\nAll commands in the game must be entered through the space bar\n";
    std::cout << "\nTo create a new game, enter N or n and choose game mode.\n";
    std::cout << "\nPossible game modes:\n1. (2p) Player vs Player\n2. (pc[1][2][3]) Player vs Computer[difficulty]\n";
    std::cout << "\nTo load a game, enter L or l and write file name.\n";
    std::cout << "\nTo exit the game, type Q or q\n\n";
}