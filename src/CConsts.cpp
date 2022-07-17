//
// Created by Chirkov on 12.05.2022.
//

#include "CConsts.h"


int calculateRank(int square)
{
    return square/10 - 2;
}

int convertStrToInt(std::string & str)
{
    if (str.size()!= 2)
        return Pieces::OFFBOARD;

    if ('1' > str[1] ||
        str[1] > '8' ||
        'a' > str[0] ||
        str[0] > 'h')
        return Pieces::OFFBOARD;

    int FILE = str[0] - 'a';
    int RANK = str[1] - '1';
    int square = FILE + RANK * 10 + A1;
    return square;
}


std::string convertIntToStr(int square)
{
    int FILE = square % 10;
    int RANK = square / 10;

    if (1 > FILE ||
        FILE > 8 ||
        2 > RANK ||
        RANK > 9)
        return "";


    std::string str;
    str.push_back(FILE - 1 + 'a');
    str.push_back(RANK - 2 + '1');
    return str;
}

bool IsOffBoard(int square) {

    if (0 <= square && square <= 19)
        return true;
    if (100 <= square && square <= 119)
        return true;
    if (square % 10 == 0 || square % 10 == 9)
        return true;
    return false;
}