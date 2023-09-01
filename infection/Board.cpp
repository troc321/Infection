/**
 * @file Board.cpp
 * @brief Board class implementation (also called 'definition') file.
 * @author Esther Brandle and Trent Repass
 * @date April 2021
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "Human.h"
#include "MaskedHuman.h"

// When writing a class implementation file, you must "#include" the class
// declaration file.
#include "Board.h"

// We also use the conio namespace contents, so must "#include" the conio declarations.
#include "conio.h"

/**
 * @brief The Board class constructor, responsible for intializing a Board object.
 * The Board constructor is responsible for initializing all the Board object variables.
 *
 * @param rows The number of rows to make the board.
 * @param cols The number of columns to make the board.
 * @param numberOfHumans The number of humans to place on the board.
 */
Board::Board(int rows, int cols, int numberOfHumans) {
    numHumans = numberOfHumans;
    numMasked = 0; //Count number of masked humans out of total humans.
    numRows = rows;
    numCols = cols;
    currentTime = 0;
    uSleepTime = 100000;
    numInfected=0;
}

/**
 * @brief The Board class destructor.
 * The Board destructor is responsible for any last-minute cleaning 
 * up that a Board object needs to do before being destroyed. In this case,
 * it needs to return all the memory borrowed for creating the Human objects.
 */
Board::~Board() {
    for(int pos=0; pos<numHumans; ++pos) {
        delete humans[pos];
    }
}

/**
 * @brief function that runs the simulation
 * Creates human objects, infects one human, then runs simulation until all are infected.
 */
void Board::run() {
    int row, col, whichTypePerson;

    // Creates 'Human' objects and sets the array pointers to point at them.
    for(int pos=0; pos<numHumans; ++pos) {
        whichTypePerson = rand()%2;
        row = pos%numRows;       // row will be in range(0, numRows-1)
        col = random()%numCols;  // col will be in range(0, numCols-1)
        // Create and initialize another Human
        // Parameters are  row on board, col on board, initialy infected, 
        // and a pointer to this board object ('this').
        // if whichTypePerson == 0, make new Human
        if(whichTypePerson== 0){
            humans[pos] = new Human(false, row, col, false, this);
        }
        else{ // else make MaskedHuman
            humans[pos] = new MaskedHuman(true, row, col, false, this);
            ++numMasked;
        }
    }

    // Infect a random human in the range 0 to numHumans-1, checks to make sure first infected isn't masked.
    while(1){
        Human* currentHuman = humans[random()%numHumans];
        if(currentHuman->isMasked() == false){
            currentHuman->setInfected();
            break;
        }
    }

    for(currentTime=0; allInfected() == false; ++currentTime) {
        // Clear screen before every new time unit
        cout << conio::clrscr() << flush;

        // Tell each human to try moving
        for(int pos=0; pos<numHumans; ++pos) {
            humans[pos]->move();
        }

        // Deal with infection propagation.
        processInfection();

        // Tell each human to draw itself on board with updated infection status
        for(int pos=0; pos<numHumans; ++pos) {
            humans[pos]->draw();
        }

        // Print statistics.
        cout << conio::gotoRowCol(numRows+3, 1) 
             << "Time=" << currentTime 
             << " Total humans=" << numHumans
             << " Total masked=" << numMasked
             << " Total infected=" << numInfected << flush;

        // Sleep specified microseconds
        usleep(uSleepTime);
    }

    // Position the cursor so prompt shows up on its own line
    cout << endl;
}

/**
 * @brief Determines whether or not all humans are infected.
 * @return If even one human is uninfected, returns false. Otherwise, returns true.
 */
bool Board::allInfected() {
    for(int i=0; i<numHumans; ++i) {
        if(humans[i]->isInfected() == false) return false;
    }

    return true;
}

/**
 * @brief The function that handles one infection cycle to determine what new infections
 *        are present.
 * For each pair of adjacent humans in the simulation, processInfection() makes sure that if 
 * one is infected, the other becomes infected as well.
 */
void Board::processInfection() {
    for( int i=0; i<numHumans; ++i ) {
        for( int j=i+1; j<numHumans; ++j ) {
            if( isNextTo(humans[i], humans[j])){
                //If regular human touches masked human, regular becomes masked
                if(humans[i]->isMasked() && (humans[j]->isMasked()==false &&
                            humans[j]->isInfected()==false)){
                    int row, col = 0;
                    humans[j]->getLocation(row, col);
                    delete humans[j];
                    humans[j] = new MaskedHuman(true, row, col, false, this);
                    ++numMasked;
                } else if(humans[j]->isMasked() && (humans[i]->isMasked()==false &&
                             humans[i]->isInfected()==false)){
                    int row, col = 0;
                    humans[i]->getLocation(row, col);
                    delete humans[i];
                    humans[i] = new MaskedHuman(true, row, col, false, this);
                    ++numMasked;
                }

                //If regular human touches infected human, regular become infected
                else if( humans[i]->isInfected() && (humans[j]->isInfected()==false && 
                            humans[j]->isMasked()==false)) {
                   humans[j]->setInfected();
                } else if ( humans[j]->isInfected() && (humans[i]->isInfected()==false &&
                            humans[i]->isMasked()==false)) {
                   humans[i]->setInfected();
                    }
                //If infected human touches masked human, masked becomes regular
                else if(humans[i]->isInfected() && humans[j]->isMasked()){
                    int row, col = 0;
                    humans[j]->getLocation(row, col);
                    delete humans[j];
                    humans[j] = new Human(false, row, col, false, this);
                    --numMasked;
                } else if(humans[j]->isInfected() && humans[i]->isMasked()){
                    int row, col = 0;
                    humans[i]->getLocation(row, col);
                    delete humans[i];
                    humans[i] = new Human(false, row, col, false, this);
                    --numMasked;
                }
            }
        }
    }

    // Reset the board 'numInfected' count and recount how many are infected.
    numInfected = 0;

    for( int i=0; i<numHumans; ++i ) {
        if( humans[i]->isInfected() ) numInfected++;
    }
}

/**
 * @brief The function that determines whether a particular move can happen.
 *        If the move would go off the board, or land on the same position as another
 *        human, the function returns false (do not move). Otherwise, it returns true (ok to proceed).
 * @param[in] row the row the human wishes to move to.
 * @param[in] col the col the human wishes to move to.
 * @return Whether the human calling this function may move to the specified row and column.
 */
bool Board::tryMove(int row, int col) {
    int tryRow=-1, tryCol=-1;

    // If off board, the move is not permitted
    if( row<0 || row>=numRows || col<0 || col>=numCols ) return false;

    // Else if another human is on the same location, the move is not permitted
    for(int i=0; i<numHumans; ++i) {
        humans[i]->getLocation(tryRow, tryCol);
        if( row==tryRow && col==tryCol ) return false;
    }

    // No problems, so the move is permitted
    return true;
}

/**
 * @brief The function that determines whether two humans are on adjacent squares.
 * @param h1 pointer to first human object.
 * @param h2 pointer to second human object.
 * @return Whether or not h1 and h2 are on adjacent squares.
 */
bool Board::isNextTo(Human *h1, Human* h2) {
    // Get human location information
    int h1Row, h1Col;
    h1->getLocation(h1Row, h1Col);
    int h2Row, h2Col;
    h2->getLocation(h2Row, h2Col);

    // Return whether h1 and h2 are on adjacent squares in any direction 
    // (horizontally, vertically, diagonally).
    return abs(h1Row-h2Row)<=1 && abs(h1Col-h2Col)<=1;
}

