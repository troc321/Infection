/**
 * MaskedHuman class implementation file.
 *
 * @author Esther Brandle and Trent Repass
 * @date April 2021
 */

#include "Board.h"
#include "Human.h"
#include "conio.h"
#include <iostream>

#ifndef MASKEDHUMAN_CPP
#define MASKEDHUMAN_CPP

using namespace std;

/**
 * @class MaskedHuman
 * @brief The MaskedHuman class declaration.
 */
MaskedHuman::MaskedHuman(bool initMasked,int initRow, int initCol, bool initInfected, Board* thisBoard)
    // Call the base class constructor here
    // The only way of calling a base class constructor in C++ (that I know of) if
    // using the :BaseClassName(...) syntax right here. There is no super() like Java. 
    :Human(initMasked, initRow, initCol, initInfected, thisBoard)
{
    // Put any MaskedHuman-specific constructor code here
}

MaskedHuman::~MaskedHuman() {
    // Put any destructor code that is specific to the MaskedHuman destructor here.
    // Unlike with a constructor in a derived class, you do not call the base class destructor.
}

void MaskedHuman::draw() {
    // Put any draw() method code here.
    // The base class draw will not be called (after all, you are redefining the base class draw() here).
    // If you do wish to call a base class method that is redefined in a derived class, you
    // can explicitly do so with BaseClass:method( ), ex: MaskedHuman::draw()
    // Writing draw() in the derived class draw() method just results in recursion, not calling the base
    // class' draw() method.
    // NOTE: I'm not saying you should call the base class draw() method here, just explaining
    // how to explicitly call a base class method that has been redefined.
    /** MaskedHuman draw function makes */
    cout << conio::gotoRowCol(row+1,col+1); 
    cout << conio::bgColor(conio::BLUE);

    cout << '=' << conio::resetAll() << flush;
}
/**
  * @breif the MaskedHuman move method
  * Masked Humans check to see if they can move 6 units up and over
  * from other areas. Otherwise, they move like normal humans.
  **/
void MaskedHuman::move() {
    // Generate a +/- 2 row and column delta.
    int rowDelta=rand()%5-2, colDelta=rand()%5-2;

    // Checks if Masked Human can move 6 units away (proper social distancing)
    if(board->tryMove(row+6, col+6)){
	    row += 6;
	    col += 6;
    }
    //If it can't move 6 units away, masked human moves normally.
    //Else, it moves regularly
    else if(board->tryMove(row+rowDelta, col+colDelta)) {
        row+=rowDelta;
        col+=colDelta;
    }
}
#endif // MASKEDHUMAN_CPP
