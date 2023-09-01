/**
 * Masked Human Class
 * 
 * @author Esther Brandle and Trent Repass
 * @date April 2021
 */

// The class references both Board and Human, so must include the .h files.
#include "Board.h"
#include "Human.h"

#ifndef MASKEDHUMAN_H
#define MASKEDHUMAN_H

using namespace std;

/**
 * @class MaskedHuman
 * @brief The MaskedHuman class declaration.
 */

class MaskedHuman : public Human {
  public:
    MaskedHuman(bool initMasked, int initRow, int initCol, bool initInfected, Board* thisBoard);
    virtual ~MaskedHuman();
    virtual void draw();
    virtual void move();
};

#endif // MASKEDHUMAN_H
