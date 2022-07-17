#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

/**
 * The class CUserInterface responsible for displaying the menu
 */

class CUserInterface {
public:
    CUserInterface() = default;

    /**
     * Printing Chess logo
     */
    void printLogo();

    /**
     * Printing menu
     */
    void printMenu();

    /**
     * Printing main menu
     */
    void mainMenu();

};



