/*
    Aurelio Martinez
    12/18/2017
    I hereby certify that this code is my work and my work alone and understand the syllabus regarding plagiarized code.
*/
/*
    Extra credit:
    - Sound when you lose.
    - You lose counter when you exit.
    - Replay message.
    - RPG style and Menu.
    - There is difficulty ((******Normal difficult set all the movements as indicate it in the project instructions*****)).
*/
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <cstdlib>

// Structures
// Structure for the main character.
struct mainCoordinates {
    int yCoordinate = 18;
    int xCoordinate = 5;
};
// Structure for the Stupid MD.
struct stupidCoordinates {
    int yOpCoordinate = 2;
    int xOpCoordinate = 9;
};
// Structure for the Smart MD.
struct smartCoordinates {
    int yOpCoordinate = 2;
    int xOpCoordinate = 5;
};
// Structure for count.
struct counter {
    int round = 0;
    int mainCharMoveActions = 6;
};

// Constant global variables.
const char MAINCHAR = '@';
const char STUPIDMD = 's';
const char SMARTERMD = 'S';
const int STUPIDMINMOV = 1;
const int STUPIDMAXMOV = 3;
const int SMARTMINMOV = 3;
const int SMARTMAXMOV = 4;
const int ROW = 20;
const int COL = 15;

// Functions prototype.
int gameIntro();
void showManual();
int showDifficulty();
int returnRandomNumber();
void setGrid(char [][COL]);
void displayGrid(char [][COL]);
void displayBattleInfo(counter&);
void createMainCharacter(char [][COL], mainCoordinates&);
void moveMainCharacter(char [][COL], mainCoordinates&, stupidCoordinates&, smartCoordinates&);
void turnSignals(char [][COL], mainCoordinates&, stupidCoordinates&, smartCoordinates&);
void highBeams(char [][COL], mainCoordinates&, stupidCoordinates&, smartCoordinates&);
void createStupidMD(char [][COL], stupidCoordinates&, counter&);
void moveStupidMD(char [][COL], stupidCoordinates&, mainCoordinates&, bool&, int&);
void headDeath(char [][COL], bool&);
void sonicHorns(char [][COL], mainCoordinates&, stupidCoordinates&);
void createSmartMD(char [][COL], smartCoordinates&, counter&);
void moveSmartMD(char [][COL], smartCoordinates&, mainCoordinates&, bool&, int&);
void smartSonicHorns(char [][COL], mainCoordinates&, smartCoordinates&);

int main() {
    // Initializing variables.
    bool endGame = false;  // Validate if the game end or not.
    bool validator = false;  // Validate the Game Over and You Win.
    char choice = ' ';
    int loseCounter = 0;
    int introValue = 0;
    int difficulty = 0;

    // Game loop.
    do {
    // Structure tags.
    mainCoordinates mainPosition;
    counter cont;
    stupidCoordinates stupidCoordinates;
    smartCoordinates smartCoordinates;

    // Initializations in the loop to end it when need it.
    bool finishGame = false;

    // Showing the Game intro
    // Getting a value from the intro for difficulty.
    introValue = gameIntro();
    if(introValue == 1) {
        return 0;
    }
    if(introValue == -1){
        difficulty = -1;
    }
    if(introValue == -2){
        difficulty = -2;
    }

    // Setting the grid.
    char grid[ROW][COL] = {{' '}};
    setGrid(grid);

    // Displaying the grid.
    displayGrid(grid);

    // Create the main character in the grid .
    createMainCharacter(grid, mainPosition);

    // Round Loop.
    do {
       // Increasing Round Number every round.
       cont.round = cont.round + 1;

       // Main character turn.
       for (int i = 0; i < 5; i++) {
            displayBattleInfo(cont);
            moveMainCharacter(grid, mainPosition, stupidCoordinates, smartCoordinates);

           // If you get to the top you win!!.
          if (mainPosition.yCoordinate == 1) {
              cont.mainCharMoveActions = 0;
              finishGame = true;
              std::cout << "!!!!!YOU WIN!!!!" << std::endl;
              std::cout << "Press \"Enter\" to exit..";
              std::cin.ignore();
              std::cin.ignore();
              break;
          }
       }

       // Resetting move actions to "5".
       cont.mainCharMoveActions = 6;

      // Creating the Stupid and Smart MDs at second round.
      if (cont.round == 2) {
          createStupidMD(grid, stupidCoordinates, cont);
          createSmartMD(grid, smartCoordinates, cont);
      }

      // Opponent turn.
      if (finishGame == false) {
      moveStupidMD(grid, stupidCoordinates, mainPosition, finishGame, difficulty);
      }
      if (finishGame == false) {
      moveSmartMD(grid, smartCoordinates, mainPosition, finishGame, difficulty);
      }


      } while (finishGame == false);  // End of the round.

      // Loop to validate option when you finish the game.
      while (!validator) {
      loseCounter = loseCounter + 1;
      std::cout << "Do you want to play again? [y]Yes or [n]No:";
      std::cin >> choice;

      if (choice == 'y') {
        break;
      }

      if (choice == 'n') {
        std::cout << "You lose " << loseCounter << " times" << std::endl;
        return 0;
      }

      std::cout << "!!!!Select a valid option!!!!" << std::endl;
      }

    } while (endGame == false);  // End of the game.
}

// Functions
int gameIntro() {
    // Initializing variables.
    int valueHolder = 0;
    char option = ' ';
    bool validator = false;  // While loop validator.

    // Game intro.
    std::cout << std::setw(70) << "826 Gauntlet of Doom" << std::endl;
    std::cout << std::setw(71) << "Press \"Enter\" to start";
    std::cin.ignore();
    Sleep(1);
    system("CLS");

    while (!validator) {
        //  1st Menu.
        std::cout << std::setw(62) << "[a] New Game" << std::endl;
        std::cout << std::setw(65) << "[b] Show Manual" << std::endl;
        std::cout << std::setw(58) << "[c] Exit" << std::endl;
        std::cout << std::setw(96) << ">> Select \"a\" or \"b\" or \"c\" and press \"Enter\":";
        std::cin >> option;
        if (option == 'a') {  // Show the difficulty menu.
            Sleep(1);
            system("CLS");
            valueHolder = showDifficulty();
            return valueHolder;
            validator = true;

        }
        if (option == 'b') {  // Show the game manual.
            showManual();
            std::cout << "Press \"Enter\" to go to the main menu";
            std::cin.ignore();
            std::cin.ignore();
            // Clear the screen.
            system("CLS");
            continue;

        }
        if (option == 'c') {  // Exit of the program.
            std::cout << std::setw(72) << "Press \"Enter\" to exit.";
            std::cin.ignore();
            std::cin.ignore();
            return 1;
        }
        std::cout << std::setw(79) << "!!!!Select a valid option!!!!" << std::endl;
    }
     return 0;
}
void showManual() {
// Showing manual.
std:: cout << "*****************************Game Instructions**************************************" << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "826 Gauntlet of Doom															  " << std::endl;
std:: cout << "The Miami Drivers (MD) have been infected with the ignore the traffic rules virus " << std::endl;
std:: cout << "and are now driving the wrong way on 826. They simply don't see you and will flat " << std::endl;
std:: cout << "out run head-on into you!! Your job is to navigate all the way to the exit at the " << std::endl;
std:: cout << "top of the screen!!.															  " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "The game mechanics work like this:												  " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "+++++++The highway+++++++														  " << std::endl;
std:: cout << "The highway is a 20 row x 15 column playable grid.								  " << std::endl;
std:: cout << "The highway generates all the oncoming MD from the top several rows of the grid   " << std::endl;
std:: cout << "You are spawned in the bottom several rows of the grid							  " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "+++++++The stupid MD+++++                                                         " << std::endl;
std:: cout << "The \"Stupid\" MDs ---> (s)														  " << std::endl;
std:: cout << "These MD's generally drive straight down the road with occasional turns 		  " << std::endl;
std:: cout << "These MD's only have three move actions.										  " << std::endl;
std:: cout << "These MD's see you and actively attack											  " << std::endl;
std:: cout << "They will attack as soon as they get in range	   								  " << std::endl;
std:: cout << "+++++++The smart MD++++++														  " << std::endl;
std:: cout << "The \"Smart\" MDs ---> (S)														  " << std::endl;
std:: cout << "These MD see you and actively attack. They seriously want you to be killed!!      " << std::endl;
std:: cout << "They will attack as soon as they get in range (you define the range)    	      " << std::endl;
std:: cout << "They are smart however, so they sometimes act like \"Stupid\" MD's to fool you	  " << std::endl;
std:: cout << "These MD's have four move actions, but may decide to not use them all. 	 	      " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "+++++++The MD's Attacks++														  " << std::endl;
std:: cout << "--Head On Death (HOD)--														      " << std::endl;
std:: cout << "This attack only works if the MD is directly next to you and attempts to ram your " << std::endl;
std:: cout << "car. It has a 65% chance of succeeding. When the attack succeeds you lose.        " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "--Sonic Horns of Doom (SHD)--													  " << std::endl;
std:: cout << "This attack is valid from two squares away and has a 75% chance of hitting you.   " << std::endl;
std:: cout << "If you are hit by the SHD you will spin out and be pushed away from the car up to " << std::endl;
std:: cout << "three squares and end up pointing in a random direction. If you are hit twice in  " << std::endl;
std:: cout << "a row, your car will stall and not be able to move for a turn.					  " << std::endl;
std:: cout << "																		          " << std::endl;
std:: cout << "++++++++HUMAN++++++++++++														  " << std::endl;
std:: cout << "The Human ---> (@) 															      " << std::endl;
std:: cout << "You, being a Superior Human, have a fast car that has five move actions.		  " << std::endl;
std:: cout << "[Controls]															              " << std::endl;
std:: cout << "w ---> Move up																	  " << std::endl;
std:: cout << "s ---> Move Down																  " << std::endl;
std:: cout << "a ---> Move Left																  " << std::endl;
std:: cout << "d ---> Move Right																  " << std::endl;
std:: cout << "q ---> Move up+left															      " << std::endl;
std:: cout << "e ---> Move up+right															  " << std::endl;
std:: cout << "z ---> Move down+left															  " << std::endl;
std:: cout << "c ---> Move down+right															  " << std::endl;
std:: cout << "1 ---> 1st Power (Turn Signals of Accuracy)									      " << std::endl;
std:: cout << "2 ---> 2nd Power (High Beams of Blinding)										  " << std::endl;
std:: cout << "Enter ---> Do the actions														  " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "--Turn Signals of Accuracy (TSA)--											      " << std::endl;
std:: cout << "The TSA will cause an oncoming MD to shift one square in a random direction and   " << std::endl;
std:: cout << "has a 63% chance of hitting.                                                      " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "--High Beams of Blinding (HBB)--												  " << std::endl;
std:: cout << "The HBB has a 45% chance of hitting. This causes a MD to spin out in one 		  " << std::endl;
std:: cout << "direction for 2 squares. If it hits another MD, the MD is destroyed.			  " << std::endl;
std:: cout << "																				  " << std::endl;
std:: cout << "+++++++Movement and turns++													      " << std::endl;
std:: cout << "You and the MDs can move in any of the surrounding directions and squares up, 	  " << std::endl;
std:: cout << "down, left, right, and diagonally. Movement consumes one action per square.	      " << std::endl;
std:: cout << "Any attack by you or the MD takes one action									  " << std::endl;
std:: cout << "************************************************************************************" << std::endl;
}
int showDifficulty() {
    // Initializing variables.
    char option = ' ';
    bool validator = false;  // While loop validator.

    while (!validator) {
        // Difficulty Menu.
        std::cout << std::setw(62) << "Choose a difficulty" << std::endl;
        std::cout << std::setw(54) << "[a] Normal" << std::endl;
        std::cout << std::setw(52) << "[b] Hard" << std::endl;
        std::cout << std::setw(58) << "[c] Impossible" << std::endl;
        std::cout << std::setw(90) << ">> Select \"a\" or \"b\" or \"c\" and press \"Enter\":";
        std::cin >> option;
        if (option == 'a') {
            validator = true;
        }
        if (option == 'b') {
            return -1;
        }
        if (option == 'c') {
            return -2;
        }
        std::cout << std::setw(79) << "!!!!Select a valid option!!!!" << std::endl;
    }
}
int returnRandomNumber() {
    int aNumber = 0;
    const int MINNUMBER = 0;
    const int MAXNUMBER = 100;
    aNumber = (rand() % (MAXNUMBER - MINNUMBER + 1)) + MINNUMBER;
    return aNumber;
}
void setGrid(char grid[][COL]) {
    // Making the Grid Rows
    for (int i = 0; i < COL; i++) {
        grid[0][i] = static_cast<char>(205);
        grid[ROW - 1][i] = static_cast<char>(205);
    }

    // Making the Grid Columns
    for (int i = 0; i < ROW; i++) {
        grid[i][0] = static_cast<char>(186);
        grid[i][COL - 1] = static_cast<char>(186);
    }

    // Fix Borders for the Grid
    grid[0][0] = static_cast<char>(201);
    grid[ROW - 1][0] = static_cast<char>(200);
    grid[0][COL - 1] = static_cast<char>(187);
    grid[ROW - 1][COL - 1] = static_cast<char>(188);

    // Finish line.
    for (int i = 1; i < 14; i++) {
        grid[1][i] = static_cast<char>(176);
    }

    // Obstacles

}
void displayGrid(char grid[][COL]) {
    // Displaying the Grid
    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            std::cout  << grid[r][c];
        }
            std::cout << std::endl;
    }
}
void displayBattleInfo(counter &cont) {
    // Displaying round number.
    std::cout << "[Round #" << cont.round << "]" << std::endl;
    std::cout << std::endl;
    std::cout << "It's your turn!!!" << std::endl;
    // Decreasing action numbers.
    cont.mainCharMoveActions = cont.mainCharMoveActions - 1;
    // Displaying number of action left.
    std::cout << "You have " << cont.mainCharMoveActions << " actions" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // Displaying fight menu.
    std::cout << "***********************************Action Menu************************************************" << std::endl;
    std::cout << "*-> Make a move                                                                              *" << std::endl;
    std::cout << "* [a]Left  " << "[w]Up  " << "[d]Right  " << "[s]Down  " << "[q]TopLeft  " << "[e]TopRight  " << "[z]BottomLeft  " << "[c]BottomRight  *" << std::endl;
    std::cout << "*                                                                                            *" << std::endl;
    std::cout << "*-> Attack or Defense                                                                        *" << std::endl;
    std::cout << "* [1]TurnSignalAccuracy  [2]HighBeamsBlinding                                                *" << std::endl;
    std::cout << "*                                                                                            *" << std::endl;
    std::cout << "* Press \"Enter\"                                                                              *" << std::endl;
    std::cout << "**********************************************************************************************" << std::endl;
    std::cout << std::endl;
}
void createMainCharacter(char grid[][COL], mainCoordinates &mainPosition) {
    // Setting a point to start the game
    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = MAINCHAR;

    // Printing the character.
    system("CLS");
    displayGrid(grid);
}
void moveMainCharacter(char grid[][COL], mainCoordinates &mainPosition, stupidCoordinates &stupidCoordinates , smartCoordinates &smartCoordinates) {
    // Initializing variables.
    char direction = ' ';
    bool validator = false;

    // Loop to enter an action for the main character.
    do {
        std::cout << "Enter an action for the main character: ";
        std::cin >> direction;

        // switch statement to get the movements.
        switch (direction) {
            // Moving up with validation.
            case 'w':
                if (mainPosition.yCoordinate - 1 != 0 && grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] != 's'
                    && grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] != 'S') {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving left with validation.
            case 'a':
                if (mainPosition.xCoordinate - 1 != 0 && grid[mainPosition.yCoordinate][mainPosition.xCoordinate - 1] != 's'
                    && grid[mainPosition.yCoordinate][mainPosition.xCoordinate - 1] != 'S') {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving right with validation.
            case 'd':
                if (mainPosition.xCoordinate + 1 != 14 && grid[mainPosition.yCoordinate][mainPosition.xCoordinate + 1] != 's'
                    && grid[mainPosition.yCoordinate][mainPosition.xCoordinate + 1] != 'S') {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving down with validation.
            case 's':
                if (mainPosition.yCoordinate + 1 != 19 && grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate] != 's'
                    && grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate] != 'S') {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving diagonal [up+left] with validation.
            case 'q':
                if (grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate - 1] != 'S' && grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate - 1] != 's'
                    && mainPosition.xCoordinate - 1 != 0 && mainPosition.yCoordinate - 1 != 0) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving diagonal [up+right] with validation.
            case 'e':
                if (grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate + 1] != 'S' && grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate + 1] != 's'
                    && mainPosition.xCoordinate + 1 != 14 && mainPosition.yCoordinate - 1 != 0) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving diagonal [down+left] with validation.
            case 'z':
                if (grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate - 1] != 'S' && grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate - 1] != 's'
                    && mainPosition.xCoordinate - 1 != 0 && mainPosition.yCoordinate + 1 != 19) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                validator = true;
            break;

            // Moving diagonal [down+right] with validation.
            case 'c':
                if (grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate + 1] != 'S' && grid[mainPosition.yCoordinate + 1][mainPosition.xCoordinate + 1] != 's'
                    && mainPosition.xCoordinate + 1 != 14 && mainPosition.yCoordinate + 1 != 19) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                validator = true;
            break;

            // 1st power Turn Signals of Accuracy (TSA)
            case '1':
                turnSignals(grid, mainPosition, stupidCoordinates, smartCoordinates);
                validator = true;
            break;

            // 2nd power High Beams of Blinding (HBB)
            case '2':
                highBeams(grid, mainPosition, stupidCoordinates, smartCoordinates);
                validator = true;
            break;

            default:
            std::cout << "Enter a valid action key!!!!" << std::endl;
            Sleep(100);
        }
    } while (!validator);
        Sleep(1);
        system("CLS");
        displayGrid(grid);
    }
void turnSignals(char grid[][COL], mainCoordinates &mainPosition, stupidCoordinates &stupidCoordinates, smartCoordinates &smartCoordinates) {
    // Testing if there is an stupid in range [5 or less squares ahead].
    if (grid[mainPosition.yCoordinate - 5][mainPosition.xCoordinate] == 's' || grid[mainPosition.yCoordinate - 4][mainPosition.xCoordinate] == 's' ||
        grid[mainPosition.yCoordinate - 3][mainPosition.xCoordinate] == 's' || grid[mainPosition.yCoordinate - 2][mainPosition.xCoordinate] == 's' ||
        grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] == 's' ) {
        std::cout << "You are in range" << std::endl;
        Sleep(1200);
        std::cout << "Turn Signals of Accuracy!!!!!!!!!!" << std::endl;
        Sleep(1200);
        // Generate two random numbers.
        int randomNumber = returnRandomNumber();
        int anotherRandom = returnRandomNumber();

        // Validating the 63% of hit.
        if (randomNumber >= 0 && randomNumber <= 63) {

           // If the second random number is between [1-15]
           if(anotherRandom >= 1 && anotherRandom <= 15) {
              // If it hits and if it can move. Move it to the left.
              if (stupidCoordinates.xOpCoordinate - 1 != 0 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate - 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }

           // If the second random number is between [16-30]
           if(anotherRandom >= 16 && anotherRandom <= 30) {
              // If it hits. If it can move. Move it up.
              if (stupidCoordinates.yOpCoordinate - 1 != 0 && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate] = STUPIDMD;
              }
           }

           // If the second random number is between [31-45]
           if(anotherRandom >= 31 && anotherRandom <= 45) {
              // If it hits and if it can move. Move it to the right.
              if (stupidCoordinates.xOpCoordinate + 1 != 0 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [46-60]
           if(anotherRandom >= 46 && anotherRandom <= 60) {
              // If it hits. If it can move. Move it down.
              if (stupidCoordinates.yOpCoordinate + 1 != 19 && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate] = STUPIDMD;
              }
           }

           // If the second random number is between [61-70]
           if(anotherRandom >= 61 && anotherRandom <= 70) {
              // If it hits. If it can move. Move it up+left.
              if ((stupidCoordinates.yOpCoordinate - 1 != 0 && stupidCoordinates.xOpCoordinate - 1 != 0)
                   && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate - 1] != '@') {
                   grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                   grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }

           // If the second random number is between [71-80]
           if(anotherRandom >= 71 && anotherRandom <= 80) {
              // If it hits. If it can move. Move it down+right.
              if ((stupidCoordinates.yOpCoordinate + 1 != 19 && stupidCoordinates.xOpCoordinate + 1 != 14)
                   && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate + 1] != '@') {
                   grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                   grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [81-90]
           if(anotherRandom >= 81 && anotherRandom <= 90) {
              // If it hits. If it can move. Move it up+right.
              if ((stupidCoordinates.yOpCoordinate - 1 != 0 && stupidCoordinates.xOpCoordinate + 1 != 14)
                   && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate + 1] != '@') {
                   grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                   grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [91-100]
           if(anotherRandom >= 91 && anotherRandom <= 100) {
              // If it hits. If it can move. Move it down+left.
              if ((stupidCoordinates.yOpCoordinate + 1 != 19 && stupidCoordinates.xOpCoordinate - 1 != 0)
                   && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate - 1] != '@') {
                   grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                   grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }


        } else {
           // If it did not hit show that  it fails.
           std::cout << "Fail :(" << std::endl;
           Sleep(1200);
        }

     }

     // Testing if there is an smarter in range [5 or less squares ahead].
    if (grid[mainPosition.yCoordinate - 5][mainPosition.xCoordinate] == 'S' || grid[mainPosition.yCoordinate - 4][mainPosition.xCoordinate] == 'S' ||
        grid[mainPosition.yCoordinate - 3][mainPosition.xCoordinate] == 'S' || grid[mainPosition.yCoordinate - 2][mainPosition.xCoordinate] == 'S' ||
        grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] == 'S' ) {
        std::cout << "You are in range" << std::endl;
        Sleep(1200);
        std::cout << "Turn Signals of Accuracy!!!!!!!!!!" << std::endl;
        Sleep(1200);
        // Generate two random numbers.
        int randomNumber = returnRandomNumber();
        int anotherRandom = returnRandomNumber();

        // Validating the 63% of hit.
        if (randomNumber >= 0 && randomNumber <= 63) {

           // If the second random number is between [1-15]
           if(anotherRandom >= 1 && anotherRandom <= 15) {
              // If it hits and if it can move. Move it to the left.
              if (smartCoordinates.xOpCoordinate - 1 != 0 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate - 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }

           // If the second random number is between [16-30]
           if(anotherRandom >= 16 && anotherRandom <= 30) {
              // If it hits. If it can move. Move it up.
              if (smartCoordinates.yOpCoordinate - 1 != 0 && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate] = STUPIDMD;
              }
           }

           // If the second random number is between [31-45]
           if(anotherRandom >= 31 && anotherRandom <= 45) {
              // If it hits and if it can move. Move it to the right.
              if (smartCoordinates.xOpCoordinate + 1 != 0 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [46-60]
           if(anotherRandom >= 46 && anotherRandom <= 60) {
              // If it hits. If it can move. Move it down.
              if (smartCoordinates.yOpCoordinate + 1 != 19 && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate] = STUPIDMD;
              }
           }

           // If the second random number is between [61-70]
           if(anotherRandom >= 61 && anotherRandom <= 70) {
              // If it hits. If it can move. Move it up+left.
              if ((smartCoordinates.yOpCoordinate - 1 != 0 && smartCoordinates.xOpCoordinate - 1 != 0)
                   && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate - 1] != '@') {
                   grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                   grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }

           // If the second random number is between [71-80]
           if(anotherRandom >= 71 && anotherRandom <= 80) {
              // If it hits. If it can move. Move it down+right.
              if ((smartCoordinates.yOpCoordinate + 1 != 19 && smartCoordinates.xOpCoordinate + 1 != 14)
                   && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate + 1] != '@') {
                   grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                   grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [81-90]
           if(anotherRandom >= 81 && anotherRandom <= 90) {
              // If it hits. If it can move. Move it up+right.
              if ((smartCoordinates.yOpCoordinate - 1 != 0 && smartCoordinates.xOpCoordinate + 1 != 14)
                   && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate + 1] != '@') {
                   grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                   grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = STUPIDMD;
              }
           }

           // If the second random number is between [91-100]
           if(anotherRandom >= 91 && anotherRandom <= 100) {
              // If it hits. If it can move. Move it down+left.
              if ((smartCoordinates.yOpCoordinate + 1 != 19 && smartCoordinates.xOpCoordinate - 1 != 0)
                   && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate - 1] != '@') {
                   grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                   grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = STUPIDMD;
              }
           }


        } else {
           // If it did not hit show that  it fails.
           std::cout << "Fail :(" << std::endl;
           Sleep(1200);
        }

     } else {
       // If there is not enemy in range shows that there is not enemies.
       std::cout << "You are not in range [5 or less squares ahead]" << std::endl;
       Sleep(1200);
       std::cout << "Turn Signals of Accuracy [Fail]" << std::endl;
       Sleep(1200);
    }
}
void highBeams(char grid[][COL], mainCoordinates &mainPosition, stupidCoordinates &stupidCoordinates, smartCoordinates &smartCoordinates) {
     // Testing if there is an stupid in range [5 or less squares ahead].
    if (grid[mainPosition.yCoordinate - 5][mainPosition.xCoordinate] == 's' || grid[mainPosition.yCoordinate - 4][mainPosition.xCoordinate] == 's' ||
        grid[mainPosition.yCoordinate - 3][mainPosition.xCoordinate] == 's' || grid[mainPosition.yCoordinate - 2][mainPosition.xCoordinate] == 's' ||
        grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] == 's') {
        std::cout << "You are in range" << std::endl;
        Sleep(1200);
        std::cout << "High Beams of Blinding!!!!!!!!!!" << std::endl;
        Sleep(1200);

        // Generate one random number.
        int randomNumber = returnRandomNumber();

        // Validating the 45% of hit.
        if (randomNumber >= 0 && randomNumber <= 45) {

            // If it hits and if it can move. Move it to the right 2 squares.
            if ((stupidCoordinates.xOpCoordinate + 1 != 0 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 1] != '@') ||
                (stupidCoordinates.xOpCoordinate + 2 != 0 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 2] != '@')) {
                 grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                 grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 2] = STUPIDMD;
            }

        } else {
          // If it did not hit show that it fails.
          std::cout << "Fail :(" << std::endl;
          Sleep(1200);
          }

     }
     // Testing if there is an smarter in range [5 or less squares ahead].
    else if (grid[mainPosition.yCoordinate - 5][mainPosition.xCoordinate] == 'S' || grid[mainPosition.yCoordinate - 4][mainPosition.xCoordinate] == 'S' ||
             grid[mainPosition.yCoordinate - 3][mainPosition.xCoordinate] == 'S' || grid[mainPosition.yCoordinate - 2][mainPosition.xCoordinate] == 'S' ||
             grid[mainPosition.yCoordinate - 1][mainPosition.xCoordinate] == 'S') {
             std::cout << "You are in range" << std::endl;
             Sleep(1200);
             std::cout << "High Beams of Blinding!!!!!!!!!!" << std::endl;
             Sleep(1200);

             // Generate one random number.
             int randomNumber = returnRandomNumber();

             // Validating the 45% of hit.
             if (randomNumber >= 0 && randomNumber <= 45) {

                // If it hits and if it can move. Move it to the right 2 squares.
                if ((smartCoordinates.xOpCoordinate + 1 != 0 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 1] != '@') ||
                    (smartCoordinates.xOpCoordinate + 2 != 0 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 2] != '@')) {
                     grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                     grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 2] = SMARTERMD;
                }
             } else {
          // If it did not hit show that it fails.
          std::cout << "Fail :(" << std::endl;
          Sleep(1200);
          }
   } else {
       // If there is not enemy in range shows that there is not enemies.
       std::cout << "You are not in range [5 or less squares ahead]" << std::endl;
       Sleep(1200);
       std::cout << "High Beams of Blinding [Fail]" << std::endl;
       Sleep(1200);
     }
}
void createStupidMD(char grid[][COL], stupidCoordinates &stupidCoordinates, counter &cont) {
    // Creating the "Stupid" MD in the grid.
    grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = STUPIDMD;

    // Printing the character.
    system("CLS");
    displayGrid(grid);
}
void moveStupidMD(char grid[][COL], stupidCoordinates &stupidCoordinates, mainCoordinates &mainPosition, bool &finishGame, int &difficulty) {
    int aNumber = 0;  // Variable to hold number of movements.
    int anotherNumber = returnRandomNumber();  // Assigning a random number to set direction.

    // Generating a random number to see how many moves (1-3).
    aNumber = (rand() % (STUPIDMAXMOV - STUPIDMINMOV + 1)) + STUPIDMINMOV;

    // Difficulty ******If the difficult is normal all the movements will be set as indicate it in the project*****
    if (difficulty == -1) {
        aNumber = 5;
    }
    if (difficulty == -2) {
        aNumber = 6;
    }

    // For loop to move the MD (1-3) movements.
    for (int i = 0; i < aNumber; i++) {
        // 1st Power Head On Death (HOD)
        // Testing if there is the main character in range [1 square around].
        if (grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate] == '@' ||
            grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate - 1] == '@' ||
            grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 1] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate + 1] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate - 1] == '@' ||
            grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate + 1] == '@' ||
            grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate - 1] == '@') {
            // Using a function.
            headDeath(grid, finishGame);
            if (finishGame == true) {
                break;
            }
        }

        // Sonic Horns of Doom (SHD)
        // Testing if there is the main character in range [2 squares around].
        if (grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate] == '@' ||
            grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate - 2] == '@' ||
            grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 2] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate - 2] == '@' ||
            grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate + 2] == '@' ||
            grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate - 2] == '@' ||
            grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate + 2] == '@') {
            // Using a function.
            sonicHorns(grid, mainPosition, stupidCoordinates);
        }

        // 50% to move down.
        if (anotherNumber >= 0 && anotherNumber <= 50) {
           // If there is not a border and the main character, then move down.
           if (stupidCoordinates.yOpCoordinate + 1 != 19 && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate] = STUPIDMD;
           }
        }
        // 10% to move up.
        if (anotherNumber >= 51 && anotherNumber <= 60) {
           // If there is not a border and the main character, then move up.
           if (stupidCoordinates.yOpCoordinate - 1 != 1 && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate] = STUPIDMD;
           }
        }
        // 10% to move left.
        if (anotherNumber >= 61 && anotherNumber <= 70) {
           // If there is not a border and the main character, then move left.
           if (stupidCoordinates.xOpCoordinate - 1 != 0 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate - 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
           }
        }
        // 10% to move right.
        if (anotherNumber >= 71 && anotherNumber <= 80) {
           // If there is not a border and the main character, then move right.
           if (stupidCoordinates.xOpCoordinate + 1 != 14 && grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
           }
        }
        // 5% to move diagonal [up+right].
        if (anotherNumber >= 81 && anotherNumber <= 85) {
           // If there is not a border and the main character, then move [up+right].
           if ((stupidCoordinates.yOpCoordinate - 1 != 1 && stupidCoordinates.xOpCoordinate + 1 != 14)
                && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate + 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
           }
        }
        // 5% to move diagonal [up+left].
        if (anotherNumber >= 86 && anotherNumber <= 90) {
           // If there is not a border and the main character, then move [up+left].
           if ((stupidCoordinates.yOpCoordinate - 1 != 1 && stupidCoordinates.xOpCoordinate - 1 != 0)
                && grid[stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate - 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate - 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
           }
        }
        // 5% to move diagonal [down+right].
        if (anotherNumber >= 91 && anotherNumber <= 95) {
           // If there is not a border and the main character, then move [down+right].
           if ((stupidCoordinates.yOpCoordinate + 1 != 19 && stupidCoordinates.xOpCoordinate + 1 != 14)
                && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate + 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate + 1] = STUPIDMD;
           }
        }
        // 5% to move diagonal [down+left].
        if (anotherNumber >= 96 && anotherNumber <= 100) {
           // If there is not a border and the main character, then move [down+left].
           if ((stupidCoordinates.yOpCoordinate + 1 != 19 && stupidCoordinates.xOpCoordinate - 1 != 0)
                && grid[stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate - 1] != '@') {
                  grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate] = ' ';
                  grid[stupidCoordinates.yOpCoordinate = stupidCoordinates.yOpCoordinate + 1][stupidCoordinates.xOpCoordinate = stupidCoordinates.xOpCoordinate - 1] = STUPIDMD;
           }
        }
        Sleep(600);
        // Clear the screen.
        system("CLS");
        // Displaying the movement.
        displayGrid(grid);
    }
}
void headDeath(char grid[][COL], bool &finshGame) {
         // Displaying the message.
         std::cout << "Head On Death!!!!!!!!!!" << std::endl;
         Sleep(1200);

         // Generate one random number.
        int randomNumber = returnRandomNumber();

        // Validating the 65% of hit.
        if (randomNumber >= 0 && randomNumber <= 65) {
            std::cout << "Main character \"@\" got hit by the enemy" << std::endl << std::endl;
            Sleep(1200);
            std::cout << "\a!!!!!YOU DIE!!!!!" << std::endl;
            Sleep(2000);
            finshGame = true;
            std::cout << "Press ''Enter'' to exit..";
            std::cin.ignore();
            std::cin.ignore();
            // exit(EXIT_SUCCESS);

        } else {
          // If it did not hit show that it fails.
          std::cout << "Fail :)" << std::endl;
          Sleep(1200);
          }
}
void sonicHorns(char grid[][COL], mainCoordinates &mainPosition, stupidCoordinates &stupidCoordinates) {
     // Displaying the message.
     std::cout << "Sonic Horns of Doom!!!!!!!!!!" << std::endl;
     Sleep(1200);

     // Generate one random number.
     int randomNumber = returnRandomNumber();

     // Validating the 75% of hit.
     if (randomNumber >= 0 && randomNumber <= 75) {
         std::cout << "Main character \"@\" got hit by the enemy" << std::endl << std::endl;
         Sleep(1200);

         // If it was found two squares up.
         if (grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                if (mainPosition.yCoordinate - 3 == 1) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 1) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 1) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate] = MAINCHAR;
                }
         }

         // If it was found two squares down.
         if (grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                if (mainPosition.yCoordinate + 3 == 19) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate] = MAINCHAR;
                }
         }

         // If it was found two squares left.
         if (grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate - 2] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         // If it was found two squares right.
         if (grid[stupidCoordinates.yOpCoordinate][stupidCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [up+left].
         if (grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate - 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate - 3 == 0 || mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 0 || mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 0 || mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [down+right].
         if (grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate + 3 == 19 || mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19 || mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19 || mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [up+right].
         if (grid[stupidCoordinates.yOpCoordinate - 2][stupidCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate - 3 == 0 || mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 0 || mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 0 || mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [down+left].
         if (grid[stupidCoordinates.yOpCoordinate + 2][stupidCoordinates.xOpCoordinate - 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate + 3 == 19 || mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19 || mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19 || mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         Sleep(600);
        // Clear the screen.
        system("CLS");
        // Displaying the movement.
        displayGrid(grid);
     } else {
         // If it did not hit show that it fails.
         std::cout << "Fail :)" << std::endl;
         Sleep(1200);
       }
}
void createSmartMD(char grid[][COL], smartCoordinates &smartCoordinates, counter &cont) {
    // Creating the "Smart" MD in the grid.
    grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = SMARTERMD;

    // Printing the character.
    system("CLS");
    displayGrid(grid);
}
void moveSmartMD(char grid[][COL], smartCoordinates &smartCoordinates, mainCoordinates &mainPosition, bool &finishGame, int &difficulty) {

    int aNumber = 0;  // Variable to hold number of movements.    .

    // Generating a random number to see how many moves (3-4).
    aNumber = (rand() % (SMARTMAXMOV - SMARTMINMOV + 1)) + SMARTMINMOV;

    // Difficulty ******If the difficult is normal all the movements will be set as indicate it in the project*****
    if (difficulty == -1) {
        aNumber = 6;
    }
    if (difficulty == -2) {
        aNumber = 9;
    }

    // For loop to move the MD (3-4) movements.
    for (int i = 0; i < aNumber; i++) {
        // 1st Power Head On Death (HOD)
        // Testing if there is the main character in range [1 square around].
        if (grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate] == '@' ||
            grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate - 1] == '@' ||
            grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 1] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate + 1] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate - 1] == '@' ||
            grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate + 1] == '@' ||
            grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate - 1] == '@') {

            // Using a function.
            headDeath(grid, finishGame);
            if (finishGame == true) {
                break;
            }

        }

        // Sonic Horns of Doom (SHD)
        // Testing if there is the main character in range [2 squares around].
        if (grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate] == '@' ||
            grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate - 2] == '@' ||
            grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 2] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate - 2] == '@' ||
            grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate + 2] == '@' ||
            grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate - 2] == '@' ||
            grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate + 2] == '@') {
            // Using a function.
            smartSonicHorns(grid, mainPosition, smartCoordinates);
        }

        // Checking chase.
        int xSmart = smartCoordinates.xOpCoordinate;
        int ySmart = smartCoordinates.yOpCoordinate;
        int xMain = mainPosition.xCoordinate;
        int yMain = mainPosition.yCoordinate;

        // Move down.
        if (xSmart == xMain && ySmart < yMain) {
           // If there is not a border and the main character, then move down.
           if (smartCoordinates.yOpCoordinate + 1 != 19 && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate] = SMARTERMD;
           }
        }

        // Move up.
        if (xSmart == xMain && ySmart > yMain) {
           // If there is not a border and the main character, then move up.
           if (smartCoordinates.yOpCoordinate - 1 != 1 && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate] = SMARTERMD;
           }
        }
        // Move left.
        if (ySmart == yMain && xSmart > xMain) {
           // If there is not a border and the main character, then move left.
           if (smartCoordinates.xOpCoordinate - 1 != 0 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate - 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = SMARTERMD;
           }
        }
        // Move right.
        if (ySmart == yMain && xSmart < xMain) {
           // If there is not a border and the main character, then move right.
           if (smartCoordinates.xOpCoordinate + 1 != 14 && grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = SMARTERMD;
           }
        }
        // Move diagonal [up+right].
        if (xSmart < xMain && ySmart > yMain) {
           // If there is not a border and the main character, then move [up+right].
           if ((smartCoordinates.yOpCoordinate - 1 != 1 && smartCoordinates.xOpCoordinate + 1 != 14)
                && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate + 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = SMARTERMD;
           }
        }

        // Move diagonal [up+left].
        if (xSmart > xMain && ySmart > yMain) {
           // If there is not a border and the main character, then move [up+left].
           if ((smartCoordinates.yOpCoordinate - 1 != 1 && smartCoordinates.xOpCoordinate - 1 != 0)
                && grid[smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate - 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate - 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = SMARTERMD;
           }
        }
        // Move diagonal [down+right].
        if (xSmart < xMain && ySmart < yMain) {
           // If there is not a border and the main character, then move [down+right].
           if ((smartCoordinates.yOpCoordinate + 1 != 19 && smartCoordinates.xOpCoordinate + 1 != 14)
                && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate + 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate + 1] = SMARTERMD;
           }
        }
        // Move diagonal [down+left].
        if (xSmart > xMain && ySmart < yMain) {
           // If there is not a border and the main character, then move [down+left].
           if ((smartCoordinates.yOpCoordinate + 1 != 19 && smartCoordinates.xOpCoordinate - 1 != 0)
                && grid[smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate - 1] != '@') {
                  grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate] = ' ';
                  grid[smartCoordinates.yOpCoordinate = smartCoordinates.yOpCoordinate + 1][smartCoordinates.xOpCoordinate = smartCoordinates.xOpCoordinate - 1] = SMARTERMD;
           }
        }

        Sleep(600);
        // Clear the screen.
        system("CLS");
        // Displaying the movement.
        displayGrid(grid);
    }
}
void smartSonicHorns(char grid[][COL], mainCoordinates &mainPosition, smartCoordinates &smartCoordinates) {
     // Displaying the message.
     std::cout << "Sonic Horns of Doom!!!!!!!!!!" << std::endl;
     Sleep(1200);

     // Generate one random number.
     int randomNumber = returnRandomNumber();

     // Validating the 75% of hit.
     if (randomNumber >= 0 && randomNumber <= 75) {
         std::cout << "Main character \"@\" got hit by the enemy" << std::endl << std::endl;
         Sleep(1200);

         // If it was found two squares up.
         if (grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                if (mainPosition.yCoordinate - 3 == 1) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 1) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 1) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate] = MAINCHAR;
                }
         }

         // If it was found two squares down.
         if (grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
                if (mainPosition.yCoordinate + 3 == 19) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate] = MAINCHAR;
                }
         }

         // If it was found two squares left.
         if (grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate - 2] == '@') {
                grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         // If it was found two squares right.
         if (grid[smartCoordinates.yOpCoordinate][smartCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [up+left].
         if (grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate - 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate - 3 == 0 || mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 0 || mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 0 || mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [down+right].
         if (grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate + 3 == 19 || mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19 || mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19 || mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [up+right].
         if (grid[smartCoordinates.yOpCoordinate - 2][smartCoordinates.xOpCoordinate + 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate - 3 == 0 || mainPosition.xCoordinate + 3 == 14) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 2][mainPosition.xCoordinate = mainPosition.xCoordinate + 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 2 == 0 || mainPosition.xCoordinate + 2 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 1][mainPosition.xCoordinate = mainPosition.xCoordinate + 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate - 1 == 0 || mainPosition.xCoordinate + 1 == 14) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 0][mainPosition.xCoordinate = mainPosition.xCoordinate + 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate - 3][mainPosition.xCoordinate = mainPosition.xCoordinate + 3] = MAINCHAR;
                }
         }

         // If it was found two squares diagonal [down+left].
         if (grid[smartCoordinates.yOpCoordinate + 2][smartCoordinates.xOpCoordinate - 2] == '@') {
             grid[mainPosition.yCoordinate][mainPosition.xCoordinate] = ' ';
             if (mainPosition.yCoordinate + 3 == 19 || mainPosition.xCoordinate - 3 == 0) {
                    grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 2][mainPosition.xCoordinate = mainPosition.xCoordinate - 2] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 2 == 19 || mainPosition.xCoordinate - 2 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 1][mainPosition.xCoordinate = mainPosition.xCoordinate - 1] = MAINCHAR;
                }
                else if (mainPosition.yCoordinate + 1 == 19 || mainPosition.xCoordinate - 1 == 0) {
                         grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 0][mainPosition.xCoordinate = mainPosition.xCoordinate - 0] = MAINCHAR;
                }
                else {
                      grid[mainPosition.yCoordinate = mainPosition.yCoordinate + 3][mainPosition.xCoordinate = mainPosition.xCoordinate - 3] = MAINCHAR;
                }
         }

         Sleep(600);
        // Clear the screen.
        system("CLS");
        // Displaying the movement.
        displayGrid(grid);
     } else {
         // If it did not hit show that it fails.
         std::cout << "Fail :)" << std::endl;
         Sleep(1200);
       }
}

