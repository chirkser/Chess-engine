//
// Created by Chirkov on 06.05.2022.
//

#pragma once

#include "iostream"
#include "memory"
#include <map>
#include <list>
#include "vector"
#include <map>
#include "string"
#include <sstream>
#include "CPieces/CPawn.h"
#include "CPieces/CRook.h"
#include "CPieces/CKnight.h"
#include "CPieces/CSpace.h"
#include "CPieces/CBishop.h"
#include "CPieces/CQueen.h"
#include "CPieces/CKing.h"
#include "CPieces/COffboard.h"
#include "CMoves.h"



class CBoard {
public:
    CBoard();
    /**
     * reading FEN and filling board
     * @param FEN board representation by FEN
     * @return true FEN is good
     * @return false FEN is wrong
     */
    bool fillBoard(const std::string & FEN);
    /**
     * Generate actual FEN in the game
     * @return FEN in string format
     */
    std::string generateFen() const;
    /**
     * Generate actual FEN in the game for draw
     * @return FEN in string format
     */
    std::string FenForDraw() const;
    /**
     * Get piece in square
     * @param square
     * @return std::shared_ptr<CPiece>
     */
    const std::shared_ptr<CPiece> & operator[](int square) const;
    /**
     * Get piece in square
     * @param square
     * @return std::shared_ptr<CPiece>
     */
    std::shared_ptr<CPiece> & operator[](int square);
    /**
     * Getter of actual turn
     * @return white if actual turn - white
     * @return black if actual turn - black
     */
    Color actualTurn();
    /**
     * change actual turn from white to black or from black to white
     */
    void changeTurn();
    /**
     * Printing board
     */
    void print();
    /**
     * Setting piece to position on the board
     * @param square square
     * @param color color of piece
     * @param piece piece type
     * @return true
     */
    bool setPiece(int square, Color color, Pieces piece);
    /**
     * Deleting piece from square
     * @param square
     * @return true
     */
    bool delPiece(int square);
    /**
     * Move piece from square to square
     * @param from square from
     * @param to square to
     * @return true
     */
    bool movePiece(int from, int to);
    /**
     * Make a move
     * @param move
     * @return true
     */
    bool makeTurn(const CMove & move);
    /**
     * Cancel last move
     * @return true
     */
    bool undoTurn();
    /**
     * Conver Piece`s char to int
     * @param symbol
     * @return piece in int
     */
    int calculateCode(const std::string symbol);
    /**
     * calculating start power
     */
    void calculateStartPower();
    /**
     * print counts of every piece on the board
     */
    void pieceCnt();
    /**
     * print stats of the game
     */
    void printStats();
    /**
     * Check if the king is attacked
     * @param sq pos of king
     * @param color color of king
     * return true
     */
    bool sqAttacked(const int sq, Color color) const;
    /**
     * Creating all moves for white/black side
     * @return std::list<CMove>
     */
    std::list<CMove> createPossibleMoves();
    /**
     * print for sqAttacked
     * @param color actual side
     */
    void showSqatBySide(Color color);
    /**
     * get castle status for white king
     * @return true
     */
    bool getCastleWK() const;
    /**
     * get castle status for white queen
     * @return true
     */
    bool getCastleWQ() const;
    /**
     * get castle status for black king
     * @return true
     */
    bool getCastleBK() const;
    /**
     * get castle status for white queen
     * @return true
     */
    bool getCastleBQ() const;
    /**
     * get castle status
     * @return true
     */
    bool getCastle() const;
    /**
     * get enPassant square
     * @return square
     */
    int getEnPassant() const;
    /**
     * get checkmate status
     * @return true
     */
    bool getCheckMate() const;
    /**
     * get check status
     * @return true
     */
    bool isCheck();
    /**
     * get draw status
     * @return true
     */
    bool isDraw();
    /**
     * checking Checking whether there are accessible moves
     * @return true
     */
    bool noPossibleMoves();
    /**
     * getting actual turn
     * @return "white"
     * @return "black"
     */
    std::string getTurn();
    /**
     * print all possible moves for white/black side
     * @param tmp possible moves
     */
    void printMoves(std::list<CMove> tmp);
    /**
     * white power/score on the board
     * @return whitePower
     */
    int getWhitePower();
    /**
     * white power/score on the board
     * @return whitePower
     */
    int getBlackPower();
    /**
     * get actual color
     * @return Color::white
     * @return Color::black
     */
    Color getColor()
    {
        return turn;
    }
    /**
     * get all the white pieces on the board
     * @return list<std::shared_ptr<CPiece>>
     */
    const std::list<std::shared_ptr<CPiece>> & getWhitePieces() const {
        return whitePieces;
    }
    /**
  * get all the black pieces on the board
  * @return list<std::shared_ptr<CPiece>>
  */
    const std::list<std::shared_ptr<CPiece>> & getBlackPieces() const {
        return blackPieces;
    }
    /**
     * check if this move possible
     * @param move
     * @return true
     */
    bool isPossibleMove(CMove move);
    /**
     * If was check, set check for castling
     * @param color actual turn
     */
    void setCheck(Color color);
    /**
     * was check or no
     * @param color
     * @return true
     */
    bool actualCheck(Color color);
    /**
     * if game mode 2p set true
     */
    void setGameMode();
    /**
     * print actual turn [white/black]
     */
    void printTurn();
private:

    // Board is prepared and ready for game
    bool isReady = false;
    // Checkmate ?
    bool isCheckMate = false;
    bool whiteCheck = false;
    bool blackCheck = false;
    bool playerVsPlayer = false;
    // start helpful variables //

    // actual turn [white/black]
    Color turn;

    // count half moves
    int ply = 0;
    // count moves
    int fiftyTurns = 0;
    int turns = 0;
    // possible EnPassant
    int enPassant;

    int posWKing = E1;
    int posBKing = E8;

    // actual power on the board by side [white/black]
    int whitePower = 0;
    int blackPower = 0;

    // end helpful variables  //

    // board, ref: https://www.chessprogramming.org/10x12_Board
    std::shared_ptr<CPiece> m_Board[boardSize];

    // list of Pieces on board [white/black]
    std::list<std::shared_ptr<CPiece>> whitePieces;
    std::list<std::shared_ptr<CPiece>> blackPieces;

    // cnt of every piece on the board
    int cntOfPieces[13] = {};

    // castling
    bool castle_rights[colors][castles];

    // history of moves
    std::vector<CMoves> historyMoves;
    std::map<std::string, int> FENs;
    int movesCnt;
    bool repetitions = false;
};


