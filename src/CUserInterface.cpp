//
// Created by Chirkov on 06.05.2022.
//

#include "CUserInterface.h"


void CUserInterface::printLogo()
{
    std::cout << "    ======================================\n";
    std::cout << "       _____ _    _ ______  _____ _____\n";
    std::cout << "      / ____| |  | |  ____|/ ____/ ____|\n";
    std::cout << "     | |    | |__| | |__  | (___| (___ \n";
    std::cout << "     | |    |  __  |  __|  \\___ \\\\___ \\ \n";
    std::cout << "     | |____| |  | | |____ ____) |___) |\n";
    std::cout << "      \\_____|_|  |_|______|_____/_____/\n\n";
    std::cout << "    ======================================\n\n";
}

void CUserInterface::printMenu()
{
    std::cout << "Commands: (M)ove \t(S)ave \t(H)elp \t(Q)uit \n";
}

void CUserInterface::mainMenu()
{
    std::cout << "    (N)ew game\t(L)oad\t(H)elp\t(Q)uit \n";
}
