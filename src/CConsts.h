//
// Created by Chirkov on 12.05.2022.
//

#pragma once

#include "iostream"
#include "string"

#define boardSize 120
#define colors 2
#define castles 2

const std::string basicBoard = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string unknownCmd = "Unknown command, try again or write (H)elp.";
const std::string invalidGameMode = "Invalid game mode.";

/**
 * Calculating Rank(1-8)
 * @param square
 * @return
 */
int calculateRank(int square);

/**
 * Each color has two types of castling rights, king and queen castle
 */
enum Castle
{ king_side, queen_side };

/**
 * Color of Piece
 */
enum Color
{ white, black, none };

/**
 * path for save/load
 */
const std::string path ="examples/";
const std::string format = ".txt";

/**
 * chess Pieces
 */
enum Pieces
{
    BISHOP,
    KING,
    KNIGHT,
    PAWN,
    QUEEN,
    ROOK,
    SPACE,
    OFFBOARD
};

/**
 * chess pieces
 */
enum
{
    p,
    P,
    r,
    R,
    b,
    B,
    n,
    N,
    q,
    Q,
    k,
    K,
    S
};


/**
 * Board representation MailBox 10x12
 * ref: https://www.chessprogramming.org/10x12_Board
 */
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, Offboard
};

/**
 * Possible attack moves for Pieces | ref: https://www.chessprogramming.org/10x12_Board
 */
const int AttackMovesKing[8] = {-11, -10, -9, -1, 1, 9, 10, 11};
const int AttackMovesQueen[8] = {-11, -10, -9, -1, 1, 9, 10, 11};
const int AttackMovesRook[4] = {-10, -1, 1, 10};
const int AttackMovesKnight[8] = {-21, -19, -12, -8, 8, 12, 19, 21};
const int AttackMovesBishop[4] = {-11, -9, 9, 11};

// using for level 3 AI
/**
 * power of each piece on the board
 */
const int piecePower[13] = {100,
                            100,
                            550,
                            550,
                            325,
                            325,
                            325,
                            325,
                            1000,
                            1000,
                            50000,
                            50000,
                            0};

/**
 * Power pawn in all squares on board
 */
const int powerPawn[120] = {
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   10  ,	10  ,	0	, -10	, -10	,	0	,	10	,	10	,   0,
        0   ,   5   ,	0   ,	0	,	5	,	5	,	0	,	0	,	5	,   0,
        0   ,   0   ,	0   ,	10	,	20	,	20	,	10	,	0	,	0	,   0,
        0   ,   5   ,	5   ,	5	,	10	,	10	,	5	,	5	,	5	,   0,
        0   ,   10  ,	10  ,	10	,	20	,	20	,	10	,	10	,	10	,   0,
        0   ,   20  ,	20  ,	20	,	30	,	30	,	20	,	20	,	20	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0   ,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0
};

/**
 * Power knight in all squares on board
 */
const int powerKnight[120] = {
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0	,  -10	,	0	,	0	,	0	,	0	,  -10	,	0	,   0,
        0   ,   0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,   0,
        0   ,   0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,   0,
        0   ,   0	,	0	,	10	,	20	,	20	,	10	,	5	,	0	,   0,
        0   ,   5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,   0,
        0   ,   5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	0	,	0	,	0	,	0	,	0	,	0   ,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0
};

/**
 * Power Bishop in all squares on board
 */
const int powerBishop[120] = {
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0	,	0	,  -10	,	0	,	0	,  -10	,	0	,	0	,   0,
        0   ,   0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,   0,
        0   ,   0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,   0,
        0   ,   0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,   0,
        0   ,   0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,   0,
        0   ,   0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,   0,
        0   ,   0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,   0,
        0   ,   0	,	0	,	0	,	0	,	0	,	0	,	0	,	0   ,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0
};

/**
 * Power Rook in all squares on board
 */
const int powerRook[120] = {
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,   0,
        0   ,   25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,   0,
        0   ,   0	,	0	,	5	,	10	,	10	,	5	,	0	,	0   ,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0
};

/**
 * Power of pieces for black side
 */
const int convertToBlack[120] = {
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   91	,	92	,	93	,	94	,	95	,	96	,	97	,	98	,   0,
        0   ,   81	,	82	,	83	,	84	,	85	,	86	,	87	,	88	,   0,
        0   ,   71	,	72	,	73	,	74	,	75	,	76	,	77	,	78	,   0,
        0   ,   61	,	62	,	63	,	64	,	65	,	66	,	67	,	68	,   0,
        0   ,   51	,	52	,	53	,	54	,	55	,	56	,	57	,	58	,   0,
        0   ,   41	,	42	,	43	,	44	,	45	,	46	,	47	,	48	,   0,
        0   ,   31	,	32	,	33	,	34	,	35	,	36	,	37	,	38	,   0,
        0   ,   21	,	22	,	23	,	24	,	25	,	26	,	27	,	28  ,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0,
        0   ,   0   ,	0   ,	0	,	0	,	0	,	0	,	0	,	0	,   0
};
/**
 * Enum for rows in Board
 */
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

/**
 * Enum for cols in Board
 */
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};

/**
 * array for power of every capture on the board
 */
const int powerCapture[13] = {100,
                               200,
                               300,
                               400,
                               500,
                               600};

/**
 * Conversion string square to int square ("A1" -> 21)
 * @param str
 * @return square
 */
int convertStrToInt(std::string & str);
/**
 * Conversion int square to string (21 -> "A1")
 * @param square
 * @return string
 */
std::string convertIntToStr(int square);
/**
 * if square beyond the board
 * @param position
 * @return true
 */
bool IsOffBoard(int position);