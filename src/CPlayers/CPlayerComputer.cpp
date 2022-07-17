//
// Created by Chirkov on 06.05.2022.
//

#include "CPlayerComputer.h"
#include "../CBoard.h"

CPlayerComputer::CPlayerComputer(Color clr, CBoard & board, int difficulty) : CPlayer(clr, board, difficulty) {}

bool CPlayerComputer::isReal()
{
    return false;
}

bool CPlayerComputer::makeTurn()
{
    CMove move;
    bool ok = false;
    if (compLevel == 1)
    {
        firstLevel();
    }
    else if (compLevel == 2)
    {
        while (!ok)
        {
            move = secondLevel();
            if (board.makeTurn(move))
            {
                ok = true;
            }
        }
        std::cout << "Computer make turn: " << convertIntToStr(move.getFrom()) << convertIntToStr(move.getTo()) << std::endl;
    }
    else if (compLevel == 3)
    {
        while (!ok)
        {
            move = thirdLevel();
            if (board.makeTurn(move))
            {
                ok = true;
            }
        }
        std::cout << "Computer make turn: " << convertIntToStr(move.getFrom()) << convertIntToStr(move.getTo()) << std::endl;
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
        std::cout << "CHECK!\n";
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

void CPlayerComputer::firstLevel()
{
    std::list<CMove> moves = board.createPossibleMoves();
    std::list<CMove>::iterator randIt = moves.begin();
    std::advance(randIt, std::rand() % moves.size());
    while(!board.makeTurn(*randIt)) {
        moves.remove(*randIt);
        randIt = moves.begin();
        std::advance(randIt, std::rand() % moves.size());
    }
}

CMove CPlayerComputer::secondLevel()
{
    CMove move;
    int best = 99999;
    int power = 0;
    std::list<CMove> tmp = board.createPossibleMoves();
    for (auto i : tmp)
    {
        if (!board.makeTurn(i))
            continue;
        power = evaluateBoardEasy();
        board.undoTurn();
        if (power < best)
        {
            best = power;
            move = i;
        }
    }
    return move;
}


int CPlayerComputer::evaluateBoardEasy()
{
    int score = board.getWhitePower() - board.getBlackPower();
    return (board.getColor() == white) ? score : -score;
}

int CPlayerComputer::evaluateBoard() {
    // Evaluate the board
    int power = board.getWhitePower() - board.getBlackPower();
    // whitePieces
    for (const auto & i : board.getWhitePieces()) {
        if (i->typeOfPiece() == Pieces::PAWN)
            power += powerPawn[i->getPosition()];
        else if (i->typeOfPiece() == Pieces::KNIGHT)
            power += powerKnight[i->getPosition()];
        else if (i->typeOfPiece() == Pieces::BISHOP)
            power += powerBishop[i->getPosition()];
        else if (i->typeOfPiece() == Pieces::ROOK)
            power += powerRook[i->getPosition()];
    }
    // blackPieces
    for (const auto & i : board.getBlackPieces()) {
        if (i->typeOfPiece() == Pieces::PAWN)
            power -= powerPawn[convertToBlack[i->getPosition()]];
        else if (i->typeOfPiece() == Pieces::KNIGHT)
            power -= powerKnight[convertToBlack[i->getPosition()]];
        else if (i->typeOfPiece() == Pieces::BISHOP)
            power -= powerBishop[convertToBlack[i->getPosition()]];
        else if (i->typeOfPiece() == Pieces::ROOK)
            power -= powerRook[convertToBlack[i->getPosition()]];
    }


    return board.getColor() == Color::white ? power : -power;
}


CMove CPlayerComputer::thirdLevel()
{
    CMove move;
    int best = 99999;
    int power = 0;
    std::list<CMove> tmp = board.createPossibleMoves();
    for (auto i : tmp)
    {
        if (!board.makeTurn(i))
            continue;
        power = evaluateBoard();
        board.undoTurn();
        if (power < best)
        {
            best = power;
            move = i;
        }
    }
    return move;
}

std::pair<int, CMove> CPlayerComputer::minMax(int depth, bool maximize)
{
    if (depth == 0)
    {
        std::pair<int, CMove> tmp;
        tmp.first = 0;
        tmp.second = thirdLevel();
        return tmp;
    }
    std::pair<int, CMove> result;
    if (board.isDraw())
    {
        result.first = 0;
        return result;
    }
    std::list<CMove> newMoves = board.createPossibleMoves();
    if (maximize)
    {
        std::pair<int, CMove> best;
        best.first = -9999;
        for (auto i : newMoves)
        {
            if (board.makeTurn(i))
            {
                best = (best.first < minMax((depth-1), !maximize).first) ? minMax((depth-1), maximize) : best;
                board.undoTurn();
            }
        }
        return best;
    } else
    {
        std::pair<int, CMove> best;
        best.first = 9999;
        for (auto i : newMoves)
        {
            if (board.makeTurn(i))
            {
                best = (best.first > minMax((depth-1), !maximize).first) ? minMax((depth-1), maximize) : best;
                board.undoTurn();
            }
        }
        return best;
    }
}