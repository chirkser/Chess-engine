//
// Created by Chirkov on 06.05.2022.
//

#include "CPlayerReal.h"
#include "../CBoard.h"


CPlayerReal::CPlayerReal(Color clr, CBoard & board) : CPlayer(clr, board, 0) {}

bool CPlayerReal::isReal()
{
    return true;
}

bool CPlayerReal::makeTurn()
{
    std::string input;
    std::cout << "Enter turn: ";
    std::cin >> input;
    std::cout << "\n--------------------------------------------\n";
    CMove move;
    if (!move.isValidMove(input))
    {
        std::cout << "Unknown move!\nTry again or use (H)elp.\n";
        return true;
    }
    if (input.size() == 4)
        input += ' ';
    move.setMove(input);
    std::list<CMove> possibleMoves = board.createPossibleMoves();
    for (auto & i: possibleMoves)
    {
        if (move == i)
        {
            if (!board.makeTurn(i))
            {
                std::cout << "***   CHECK!   ***\nYour king is attacked! Make another move!\n";
                return true;
            }
            if (board.isCheck())
            {
                board.setCheck(board.getColor());
                if (board.noPossibleMoves())
                {
                    board.print();
                    std::cout << "***CHECKMATE!***\nCongratulations " << (color == Color::white ? "White" : "Black") << " Player!\n";
                    return false;
                }
                if (board.isDraw())
                {
                    board.print();
                    std::cout << "Draw! Game is over!\n";
                    return false;
                }
                std::cout << "***   CHECK!   ***\n";
                return true;
            }
            if (board.isDraw())
            {
                board.print();
                std::cout << "Draw! Game is over!\n";
                return false;
            }
            return true;
        }
    }
    std::cout << "Non-possible move!\n";
    return true;
}