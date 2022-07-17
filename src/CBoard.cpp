//
// Created by Chirkov on 06.05.2022.
//

#include "CBoard.h"


CBoard::CBoard()
{
    for (int i = 0; i < boardSize; i++)
        m_Board[i] = std::make_shared<COffboard>(COffboard(*this, i));

    for (int i = 0; i < colors; i++)
        for (int j = 0; j < castles; j++)
            castle_rights[i][j] = false;
    for (int i = 0; i < 13; i++)
        cntOfPieces[i] = 0;

    historyMoves = {};
    movesCnt = 0;
}

bool CBoard::fillBoard(const std::string & fen)
{
    for (int i = 0; i < boardSize; i++)
        m_Board[i] = std::make_shared<COffboard>(COffboard(*this, i));

    for (int i = 0; i < colors; i++)
        for (int j = 0; j < castles; j++)
            castle_rights[i][j] = false;

    for (int i = 0; i < 13; i++)
        cntOfPieces[i] = 0;
    historyMoves = {};
    movesCnt = 0;
    whitePower = 0;
    blackPower = 0;

    std::istringstream input(fen);
    std::string board;
    char fenTurn;
    std::string fenCastling;
    std::string fenEnPassant;
    int fenPly;
    int fenTurns;
    input >> board >> fenTurn >> fenCastling >> fenEnPassant >> fenPly >> fenTurns;
    const size_t size = board.size();
    size_t it = 0;
    int index = A8;
    for (; (it < size) && (fen[it] != ' '); it++)
    {
        if (fen[it] == ' ')
            break;
        if (fen[it] == '/')
        {
            index -= 18;
            continue;
        }
        if (std::isdigit(fen[it]))
            for (int j = 0; j < fen[it] - '0'; j++) {
                m_Board[index] = std::make_shared<CSpace>(CSpace(*this, index));
                index++;
            }
        else
        {
            switch(fen[it])
            {
                case 'p':
                    m_Board[index] = std::make_shared<CPawn>(CPawn(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[p]++;
                    if (cntOfPieces[p] > 10)
                        return false;
                    index++;
                    break;
                case 'P':
                    m_Board[index] = std::make_shared<CPawn>(CPawn(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[P]++;
                    if (cntOfPieces[P] > 10)
                        return false;
                    index++;
                    break;
                case 'r':
                    m_Board[index] = std::make_shared<CRook>(CRook(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[r]++;
                    if (cntOfPieces[r] > 10)
                        return false;
                    index++;
                    break;
                case 'R':
                    m_Board[index] = std::make_shared<CRook>(CRook(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[R]++;
                    if (cntOfPieces[R] > 10)
                        return false;
                    index++;
                    break;
                case 'b':
                    m_Board[index] = std::make_shared<CBishop>(CBishop(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[b]++;
                    if (cntOfPieces[b] > 10)
                        return false;
                    index++;
                    break;
                case 'B':
                    m_Board[index] = std::make_shared<CBishop>(CBishop(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[B]++;
                    if (cntOfPieces[B] > 10)
                        return false;
                    index++;
                    break;
                case 'n':
                    m_Board[index] = std::make_shared<CKnight>(CKnight(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[n]++;
                    if (cntOfPieces[n] > 10)
                        return false;
                    index++;
                    break;
                case 'N':
                    m_Board[index] = std::make_shared<CKnight>(CKnight(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[N]++;
                    if (cntOfPieces[N] > 10)
                        return false;
                    index++;
                    break;
                case 'q':
                    m_Board[index] = std::make_shared<CQueen>(CQueen(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[q]++;
                    if (cntOfPieces[q] > 10)
                        return false;
                    index++;
                    break;
                case 'Q':
                    m_Board[index] = std::make_shared<CQueen>(CQueen(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[Q]++;
                    if (cntOfPieces[Q] > 10)
                        return false;
                    index++;
                    break;
                case 'k':
                    m_Board[index] = std::make_shared<CKing>(CKing(*this, index, black));
                    blackPieces.push_back(m_Board[index]);
                    cntOfPieces[k]++;
                    if (cntOfPieces[k] > 1)
                        return false;
                    posBKing = index;
                    index++;
                    break;
                case 'K':
                    m_Board[index] = std::make_shared<CKing>(CKing(*this, index, white));
                    whitePieces.push_back(m_Board[index]);
                    cntOfPieces[K]++;
                    if (cntOfPieces[K] > 1)
                        return false;
                    posWKing = index;
                    index++;
                    break;
                default:
                    return false;
            }
        }
    }
    if (fenTurn == 'w')
        turn = Color::white;
    else if (fenTurn == 'b')
        turn = Color::black;
    else
        return false;

    for (char i : fenCastling)
    {
        if (i == '-')
            break;
        if (i == 'k')
            castle_rights[Color::black][Castle::king_side] = true;

        else if (i == 'K')
            castle_rights[Color::white][Castle::king_side] = true;

        else if (i == 'q')
            castle_rights[Color::black][Castle::queen_side] = true;

        else if (i == 'Q')
            castle_rights[Color::white][Castle::queen_side] = true;
        else
            return false;
    }
    if (fenEnPassant == "-")
    {
        enPassant = Pieces::SPACE;
    }
    else if ((enPassant = convertStrToInt(fenEnPassant)) == Pieces::OFFBOARD )
        return false;

    if (fenPly >= 0)
    {
        fiftyTurns = fenPly/2;
        ply = fenPly;
    } else
        return false;
    if (fenTurns > 0)
        turns = fenTurns;
    else
        return false;
    if (cntOfPieces[K] != 1 || cntOfPieces[k] != 1)
        return false;
    calculateStartPower();
    return true;
}

const std::shared_ptr<CPiece> & CBoard::operator[](int square) const {
    return m_Board[square];
}

std::shared_ptr<CPiece> & CBoard::operator[](int square) {
    return m_Board[square];
}

int CBoard::calculateCode(const std::string symbol)
{
    if (symbol == "p")
        return 0;
    else if (symbol == "P")
        return 1;
    else if (symbol == "r")
        return 2;
    else if (symbol == "R")
        return 3;
    else if (symbol == "b")
        return 4;
    else if (symbol == "B")
        return 5;
    else if (symbol == "n")
        return 6;
    else if (symbol == "N")
        return 7;
    else if (symbol == "q")
        return 8;
    else if (symbol == "Q")
        return 9;
    else if (symbol == "k")
        return 10;
    else if (symbol == "K")
        return 11;
    return -1;
}


void CBoard::calculateStartPower() {
    whitePower = 0, blackPower = 0;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            if (m_Board[j + i * 10].get()->getColor() == Color::white)
                whitePower += piecePower[calculateCode(m_Board[j + i * 10].get()->getChar())];
            if (m_Board[j + i * 10].get()->getColor() == Color::black)
                blackPower += piecePower[calculateCode(m_Board[j + i * 10].get()->getChar())];
        }
    }
}

void CBoard::printStats()
{
    std::cout << "Fifty moves: " << fiftyTurns  << std::endl;
    std::cout << "En Passant: " << convertIntToStr(enPassant) << std::endl;
    std::cout << "Castling: " << (castle_rights[white][king_side] ? "K" : "")
              << (castle_rights[white][queen_side] ? "Q" : "")
              << (castle_rights[black][king_side] ? "k" : "")
              << (castle_rights[black][queen_side] ? "q" : "") << std::endl;
    std::cout << "Actual turn: " << (turn == white ? "WHITE" : "BLACK") << std::endl;

}

void CBoard::pieceCnt()  {
    std::cout << "p, P, r, R, b, B, n, N, q, Q, k, K, ' '" << std::endl;
    for (const auto & i : cntOfPieces)
        std::cout << " " << i << "|";
    std::cout << std::endl;
}

void CBoard::print()
{
    std::cout << "   A B C D E F G H \n  ------------------" << std::endl;
    for (int i = 7; i >= 0; i--) {
        std::cout << i + 1 << "| ";
        for (int j = A1; j <= H1; j++) {
            std::cout << m_Board[j + i * 10]->getChar() << ' ';
        }
        std::cout << "|" << i + 1 << std::endl;
    }
    std::cout << "  ------------------\n   A B C D E F G H " << std::endl;
}


void CBoard::printTurn()
{
    std::cout << "Actual turn: " << (turn == white ? "WHITE" : "BLACK") << std::endl;
}

std::string CBoard::generateFen() const
{
    std::string Fen;
    std::string symb;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            symb = m_Board[i * 10 + j].get()->getChar();
            if (symb != ".")
                Fen+=symb;
            else {
                int cnt = 0;
                for (; j <= H1 && m_Board[i * 10 + j].get()->getChar() == "."; j++)
                    cnt++;
                j--;
                Fen+=cnt + '0';
                cnt = 0;
            }
        }
        Fen+='/';
    }
    Fen.pop_back();
    Fen+=" ";
    Fen+= turn == white ? "w " : "b ";
    if (castle_rights[white][Castle::king_side])
        Fen.push_back('K');
    else
        Fen+="";
    if (castle_rights[white][Castle::queen_side])
        Fen+="Q";
    else
        Fen+="";
    if (castle_rights[black][Castle::king_side])
        Fen+="k";
    else
        Fen+="";
    if (castle_rights[black][Castle::queen_side])
        Fen+="q";
    else
        Fen+="";
    if (!castle_rights[white][Castle::king_side] &&
        !castle_rights[white][Castle::queen_side] &&
        !castle_rights[black][Castle::king_side] &&
        !castle_rights[black][Castle::queen_side])
    {
        Fen+="-";
    }
    Fen+=" ";
    if (enPassant == Pieces::SPACE)
        Fen+="-";
    else
        Fen+= convertIntToStr(enPassant);
    Fen+=" ";

    Fen+=std::to_string(ply);
    Fen+=" ";
    Fen+=std::to_string(turns);
    return Fen;
}

std::string CBoard::FenForDraw() const
{
    std::string Fen;
    std::string symb;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            symb = m_Board[i * 10 + j].get()->getChar();
            if (symb != ".")
                Fen+=symb;
            else {
                int cnt = 0;
                for (; j <= H1 && m_Board[i * 10 + j].get()->getChar() == "."; j++)
                    cnt++;
                j--;
                Fen+=cnt + '0';
                cnt = 0;
            }
        }
        Fen+='/';
    }
    Fen.pop_back();
    Fen+=" ";
    Fen+= turn == white ? "w " : "b ";
    if (castle_rights[white][Castle::king_side])
        Fen.push_back('K');
    else
        Fen+="";
    if (castle_rights[white][Castle::queen_side])
        Fen+="Q";
    else
        Fen+="";
    if (castle_rights[black][Castle::king_side])
        Fen+="k";
    else
        Fen+="";
    if (castle_rights[black][Castle::queen_side])
        Fen+="q";
    else
        Fen+="";
    if (!castle_rights[white][Castle::king_side] &&
        !castle_rights[white][Castle::queen_side] &&
        !castle_rights[black][Castle::king_side] &&
        !castle_rights[black][Castle::queen_side])
    {
        Fen+="-";
    }
    Fen+=" ";
    if (enPassant == Pieces::SPACE)
        Fen+="-";
    else
        Fen+= convertIntToStr(enPassant);
    return Fen;
}


Color CBoard::actualTurn()
{
    return turn;
}

void CBoard::changeTurn()
{
    turn = (turn == white) ? black : white;
}


bool CBoard::sqAttacked(const int sq, Color color) const
{
    int tmp;
    Pieces piece;
    Color colorOfPiece;
    // checking attacking moves PAWN
    if (color == white)
    {
        if (m_Board[sq - 9]->getChar() == "P" || m_Board[sq - 11]->getChar() == "P")
        {
            return true;
        }
    } else
    {
        if (m_Board[sq + 9]->getChar() == "p" || m_Board[sq + 11]->getChar() == "p")
        {
            return true;
        }
    }

    //checking attacking moves KNIGHT
    for (auto i : AttackMovesKnight) {
        if (m_Board[sq +  i].get()->typeOfPiece() == KNIGHT && m_Board[sq + i].get()->getColor() == color)
        {
            return true;
        }
    }
    // checking attacking moves Bishop + Queen
    for (auto i : AttackMovesBishop)
    {
        tmp = sq + i;
        while (!IsOffBoard(tmp))
        {
            piece = m_Board[tmp].get()->typeOfPiece();
            colorOfPiece = m_Board[tmp].get()->getColor();
            if (piece != Pieces::SPACE)
            {
                if ((piece == Pieces::BISHOP || piece == Pieces::QUEEN) && colorOfPiece == color)
                {

                    return true;
                }
                break;
            }
            tmp += i;
        }
    }

    // checking attacking moves Rook + Queen
    for (auto i : AttackMovesRook) {
        tmp = sq + i;
        while (!IsOffBoard(tmp)) {
            piece = m_Board[tmp].get()->typeOfPiece();
            colorOfPiece = m_Board[tmp].get()->getColor();
            if (piece != Pieces::SPACE) {
                if ((piece == Pieces::ROOK || piece == Pieces::QUEEN) && colorOfPiece == color)
                {

                    return true;
                }
                break;
            }
            tmp += i;
        }
    }


    // checking attacking moves KING
    for (auto i : AttackMovesKing) {
        if (m_Board[sq +  i].get()->typeOfPiece() == KING && m_Board[sq + i].get()->getColor() == color)
        {

            return true;
        }
    }
    return false;
}

void CBoard::showSqatBySide(Color color)
{
    std::cout << "\nAttacked by " << (color == white ? "white" : "black") << std::endl;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            if (sqAttacked(m_Board[j + i * 10]->getPosition(),color))
                std::cout << "X";
            else
                std::cout << "-";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool CBoard::setPiece(int square, Color color, Pieces piece)
{
    // variable for figure to set
    std::shared_ptr<CPiece> tmp;
    if (m_Board[square].get()->typeOfPiece() != Pieces::SPACE)
        throw std::runtime_error("The cell is occupied by another figure");

    if (piece == Pieces::QUEEN)
    {
        tmp = std::make_shared<CQueen>(CQueen(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? Q : q]++;
        if (cntOfPieces[color == white ? Q : q] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else if (piece == Pieces::KING)
    {
        tmp = std::make_shared<CKing>(CKing(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? K : k]++;
        if (cntOfPieces[color == white ? K : k] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else if (piece == Pieces::KNIGHT)
    {
        tmp = std::make_shared<CKnight>(CKnight(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? N : n]++;
        if (cntOfPieces[color == white ? N : n] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else if (piece == Pieces::ROOK)
    {
        tmp = std::make_shared<CRook>(CRook(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? R : r]++;
        if (cntOfPieces[color == white ? R : r] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else if (piece == Pieces::BISHOP)
    {
        tmp = std::make_shared<CBishop>(CBishop(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? B : b]++;
        if (cntOfPieces[color == white ? B : b] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else if (piece == Pieces::PAWN)
    {
        tmp = std::make_shared<CPawn>(CPawn(*this, square, color));
        m_Board[square] = tmp;
        cntOfPieces[color == white ? P : p]++;
        if (cntOfPieces[color == white ? P : p] > 10)
            throw std::logic_error("Cannot add more pieces");
    }
    else
    {
        throw std::logic_error("Trying set SPACE or OFF BOARD piece");
    }
    if (color == Color::white) {
        whitePieces.push_back(tmp);
        whitePower += piecePower[calculateCode(tmp.get()->getChar())];
    }
    else {
        blackPieces.push_back(tmp);
        blackPower += piecePower[calculateCode(tmp.get()->getChar())];
    }
    return true;
}

bool CBoard::delPiece(int square) {

    int pieceCode = calculateCode(m_Board[square].get()->getChar());
    Color pieceColor = m_Board[square].get()->getColor();

    if (--(cntOfPieces[pieceCode]) < 0)
    {
        throw std::logic_error("Cannot delete more pieces");
    }

    if (m_Board[square]->typeOfPiece() == OFFBOARD || m_Board[square]->typeOfPiece() == OFFBOARD)
        throw std::logic_error("Cannot remove piece off board or empty piece");

    if (pieceColor == Color::white) {
        whitePieces.remove(m_Board[square]);
        whitePower -= piecePower[pieceCode];
    }
    else {
        blackPieces.remove(m_Board[square]);
        blackPower -= piecePower[pieceCode];
    }
    m_Board[square] = std::make_shared<CSpace>(CSpace(*this, square));
    return true;
}

bool CBoard::movePiece(int from, int to) {
    if (m_Board[from].get()->typeOfPiece() == OFFBOARD || m_Board[to].get()->typeOfPiece() == OFFBOARD || m_Board[to].get()->typeOfPiece() != SPACE)
    {
        throw std::logic_error("Cannot move piece from/to off board or empty piece");
    }

    m_Board[from].get()->setPosition(to);
    m_Board[to] = m_Board[from];
    m_Board[from] = std::make_shared<CSpace>(CSpace(*this, from));

    return true;
}


bool CBoard::makeTurn(const CMove & move)
{
    int from = move.getFrom();
    int to = move.getTo();
    CMoves tmp;
    historyMoves.push_back(tmp);
    // Check king
    if (m_Board[from].get()->typeOfPiece() == Pieces::KING)
    {
        if (move.getColor() == white)
            posWKing = to;
        else
            posBKing = to;
    }



    // enPassant move
    if (move.getEnPassant())
    {
        if (move.getColor() == white)
        {
            delPiece(to - 10);
        }
        else
        {
            delPiece(to + 10);
        }
    }

    // Castling move
    if (move.getCastle() && !actualCheck(turn))
    {
        if (to == C1)
            movePiece(A1, D1);
        else if (to == C8)
            movePiece(A8, D8);
        else if (to == G1)
            movePiece(H1, F1);
        else if (to == G8)
            movePiece(H8, F8);
        else
            throw std::logic_error("Error white make Castle!");
    }

    historyMoves[movesCnt].move = move;
    historyMoves[movesCnt].m_FiftyTurns = fiftyTurns;
    historyMoves[movesCnt].m_EnPassant = enPassant;
    historyMoves[movesCnt].m_castleRights[white][king_side] = castle_rights[white][king_side];
    historyMoves[movesCnt].m_castleRights[white][queen_side] = castle_rights[white][queen_side];
    historyMoves[movesCnt].m_castleRights[black][king_side] = castle_rights[black][king_side];
    historyMoves[movesCnt].m_castleRights[black][queen_side] = castle_rights[black][queen_side];
    movesCnt++;

    if (from == A1 || to == A1)
        castle_rights[white][queen_side] = false;
    if (from == H1 || to == H1)
        castle_rights[white][king_side] = false;
    if (from == A8 || to == A8)
        castle_rights[black][queen_side] = false;
    if (from == H8 || to == H8)
        castle_rights[black][king_side] = false;
    if (from == E1 || to == E1)
    {
        castle_rights[white][queen_side] = false;
        castle_rights[white][king_side] = false;
    }
    if (from == E8 || to == E8)
    {
        castle_rights[black][queen_side] = false;
        castle_rights[black][king_side] = false;
    }


    enPassant = Pieces::SPACE;

    if (turn == Color::black) {
        turns++;
        fiftyTurns++;
    }


    ply++;

    // capturing move
    if (!move.getEnPassant() && move.getCapture() != Pieces::SPACE)
    {
        delPiece(to);
        fiftyTurns = 0;
    }

    // check pawn && create enPassant
    if (m_Board[from].get()->typeOfPiece() == Pieces::PAWN) {
        fiftyTurns = 0;
        if (move.getPawnDoubleMove()) {
            if (move.getColor() == white)
                enPassant = from + 10;
            else
                enPassant = from - 10;
        }
    }

    movePiece(from, to);

    // check promotion
    if (move.getPromotion() != Pieces::SPACE) {
        delPiece(to);
        setPiece(to, move.getColor(), move.getPromotion());
    }

    std::string fen = FenForDraw();
    if (FENs.find(fen) != FENs.end())
    {
        FENs[fen]++;
        if (FENs[fen] == 3)
            repetitions = true;
    } else
        FENs.emplace(fen, 1);

    int tempKing = turn == white ? posWKing : posBKing;
    changeTurn();
    if (sqAttacked(tempKing, turn)) {
        undoTurn();
        return false;
    }

    if (isCheck() &&
        createPossibleMoves().empty())
    {
        isCheckMate = true;
    }
    return true;
}


std::list<CMove> CBoard::createPossibleMoves()
{
    std::list<CMove> moves;
    if (turn == Color::white)
    {
        for (auto & i: whitePieces)
        {
            moves.splice(moves.end(), i->possibleMoves());
        }
    } else
    {
        for (auto & i: blackPieces)
        {
            moves.splice(moves.end(), i->possibleMoves());
        }
    }
    return moves;
}


bool CBoard::getCastleWK() const
{
    return castle_rights[white][Castle::king_side];
}

bool CBoard::getCastleBK() const
{
    return castle_rights[black][Castle::king_side];
}

bool CBoard::getCastleWQ() const
{
    return castle_rights[white][Castle::queen_side];
}

bool CBoard::getCastleBQ() const
{
    return castle_rights[black][Castle::queen_side];
}

bool CBoard::getCastle() const
{
    if (!castle_rights[white][Castle::king_side] &&
        !castle_rights[black][Castle::king_side] &&
        !castle_rights[white][Castle::queen_side] &&
        !castle_rights[black][Castle::queen_side])
        return false;
    return true;
}

int CBoard::getEnPassant() const
{
    return enPassant;
}


bool CBoard::undoTurn() {

    std::string tmp = FenForDraw();
    if (FENs[tmp] == 3) {
        repetitions = false;
    }

    FENs[tmp]--;

    if (turn == Color::white) {
        turns--;
        fiftyTurns--;
    }

    ply--;
    movesCnt--;

    CMoves undo = historyMoves[movesCnt];
    // Move to be undone
    CMove undoMove = undo.move;
    int from = undoMove.getFrom();
    int to = undoMove.getTo();


    fiftyTurns = undo.m_FiftyTurns;
    enPassant = undo.m_EnPassant;
    castle_rights[white][king_side] = undo.m_castleRights[white][king_side];
    castle_rights[white][queen_side] = undo.m_castleRights[white][queen_side];
    castle_rights[black][king_side] = undo.m_castleRights[black][king_side];
    castle_rights[black][queen_side] = undo.m_castleRights[black][queen_side];
    changeTurn();
    // If the undo move is an en passant capture add the pawn back
    if (undoMove.getEnPassant()) {
        if (undoMove.getColor() == Color::white)
            setPiece(to - 10, Color::black, Pieces::PAWN);
        else
            setPiece(to + 10, Color::white, Pieces::PAWN);
    }

    // If the move is an castling move, move back the rook
    if (undoMove.getCastle())
    {
        if (to == C1)
            movePiece(D1, A1);
        else if (to == C8)
            movePiece(D8, A8);
        else if (to == G1)
            movePiece(F1, H1);
        else if (to == G8)
            movePiece(F8, H8);
        else
            throw std::logic_error("Error while undo previus move[castling]!");
    }

    movePiece(to, from);
    // If king was moved change king position
    if (m_Board[from]->typeOfPiece() == Pieces::KING) {
        if (undoMove.getColor() == white) {
            posWKing = from;
        }
        else {
            posBKing = from;
        }
    }

    // If the move was a capture, add the captured piece back
    if (undoMove.getCapture() != Pieces::SPACE && !undoMove.getEnPassant()) {
        setPiece(to, turn == white ? black : white, undoMove.getCapture());
    }

    // If the move was a promotion, remove promoted piece and add a pawn
    if (undoMove.getPromotion() != Pieces::SPACE) {
        delPiece(from);
        setPiece(from, turn, Pieces::PAWN);
    }

    return true;
}


bool CBoard::getCheckMate() const
{
    return isCheckMate;
}

bool CBoard::isCheck()
{
    return sqAttacked(turn == Color::white ? posWKing : posBKing,
                      turn == Color::white ? Color::black : Color::white);
}

bool CBoard::noPossibleMoves()
{
    std::list<CMove> tmp = createPossibleMoves();
    for (auto i : tmp)
    {
        if (makeTurn(i))
        {
            undoTurn();
            return false;
        }
    }
    return true;
}


std::string CBoard::getTurn()
{
    return turn == white ? "white" : "black";
}

void CBoard::printMoves(std::list<CMove> tmp)
{
    int cnt = 0;
    for (auto i : tmp)
    {
        cnt++;
        std::cout <<"Move[" << cnt << "]: (" << convertIntToStr(i.getFrom()) << ") (" << (convertIntToStr(i.getTo())) << ")\n";
    }
}

bool CBoard::isDraw()
{
    // Stalemate
    int kingStalemate = (turn == Color::white ? posWKing : posBKing);
    bool mate = true;
    for (auto & i : createPossibleMoves())
    {
        if (makeTurn(i))
        {
            undoTurn();
            mate = false;
        }
    }
    if (!sqAttacked(kingStalemate,
                   turn == Color::white ? black : white) &&
                   mate)
        return true;

    // king versus king rule
    if (whitePieces.size() == 1 && blackPieces.size() == 1)
        return true;

    // preparing for rules: king && bishop versus king || king && knight vs king
    int wB = 0;
    int wN = 0;
    int bB = 0;
    int bN = 0;
    for (auto i : whitePieces)
    {
        if (i->typeOfPiece() == Pieces::KNIGHT)
            wN++;
        if (i->typeOfPiece() == Pieces::BISHOP)
            wB++;
    }
    for (auto i : blackPieces)
    {
        if (i->typeOfPiece() == Pieces::KNIGHT)
            bN++;
        if (i->typeOfPiece() == Pieces::BISHOP)
            bB++;
    }
    // Bishop && King versus King
    if ((wB == 1 && whitePieces.size() == 2 && blackPieces.size() == 1) ||
        (bB == 1 && blackPieces.size() == 2 && whitePieces.size() == 1))
    {
        return true;
    }
    // Knight && King versus King
    if ((wN == 1 && whitePieces.size() == 2 && blackPieces.size() == 1) ||
        (bN == 1 && blackPieces.size() == 2 && whitePieces.size() == 1))
    {
        return true;
    }
    if (repetitions && playerVsPlayer)
    {
        return true;
    }

    // no pawn has moved and no capture has been made 50+ moves
    if (fiftyTurns > 49)
    {
        return true;
    }

    return false;
}

int CBoard::getWhitePower()
{
    return whitePower;
}

int CBoard::getBlackPower()
{
    return blackPower;
}

bool CBoard::isPossibleMove(CMove  move) {
    std::list<CMove> moveList = createPossibleMoves();
    for (const auto & i : moveList) {
        if (!makeTurn(i))
            continue;
        undoTurn();
        if (move.isIdenticalMove(i))
            return true;
    }
    return false;
}

void CBoard::setCheck(Color color)
{
    if (color == Color::white)
    {
        whiteCheck = true;
        castle_rights[white][king_side] = false;
        castle_rights[white][queen_side] = false;
    }
    else
    {
        blackCheck = true;
        castle_rights[black][king_side] = false;
        castle_rights[black][queen_side] = false;
    }

}


bool CBoard::actualCheck(Color color)
{
    return (color == Color::white ? whiteCheck : blackCheck);
}

void CBoard::setGameMode()
{
    playerVsPlayer = true;
}