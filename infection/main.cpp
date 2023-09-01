/**
 * @file main.cpp
 * @brief Contains the main function that starts the infection simulation.
 *
 * @author Esther Brandle and Trent Repass
 * @date April 2021
 **/

#include <iostream>

#include <cstdlib>
#include <termio.h>
#include <exception>

// Board.h needs to be included here because we create a Board
// object below.
#include "Board.h"

using namespace std;

/**
 * @fn main()
 * @brief main function that starts the simulation running
 * The main function does the following:
 * (1) seeds the random number generator
 * (2) creates a board object that is 20 rows, 80 columns, 70 humans
 * (3) starts the simulation running by calling the board's run function.
 **/

/**
 * @brief displays opening splash screen text
 **/
void showSplashScreen(){

    // clear screen
    cout << "\033[2J\033[1;1H";
    cout << "ABOUT THE PROGRAM - WOW HOST" << endl;
    cout << "HOST hears a sound and turns around." << endl << endl;
    cout << "        WELCOME" << endl;
    cout << "(jovial) Why hello there! I'm William Oliver Warren" << endl <<
        "(WOW for short), and I'll be your written host for this" << endl << 
        "evening. A pleasure to make your acquaintance! Please" << endl <<
        "don't hesitate to contact my creators with any questions" << endl <<
        "you may have. Tea? Coffee? No? Well, let's get to it then!" << endl << endl;
    cout << "        ABOUT THE PROGRAM" << endl;
    cout << "(serious) I'm sure you're curious about this program." << endl <<
        "Let me tell you a bit about it." << endl << endl;
    cout << "(informational) As I'm sure you already know, this" << endl <<
        "is an infection simulator. (humorous) I assure you" << endl <<
        "there are absolutely no flaws in it and this is EXACTLY" << endl <<
        "how infections spread in real life." << endl << endl;
    cout << "There are three types of humans: regular [green]," << endl <<
        "infected [red], and the derived type - masked [blue]." << endl <<
        "I've heard that some people like triggering the" << endl <<
        "apocalypse in this assignment by creating zombies or" << endl <<
        "summonning aliens, but my creators preferred to do their" << endl <<
        "best to quell the tide of infection and, ultimately," << endl << 
        "death. Although futile, their efforts are admirable." << endl << endl;
    cout << "When a regular human meets a masked human, the regular" << endl <<
        "human sees the light and puts on a mask in an attempt at" << endl <<
        "self-preservation. Sadly, these are one-time-use masks," << endl <<
        "so when a masked human meets an infected human, they lose" << endl <<
        "their mask. Even those lucky enough to temporarily evade" << endl <<
        "the infected are not safe. My creators have noticed an" << endl <<
        "odd practice from the masked community: a tendancy to" << endl <<
        "huddle together in the corner." << endl << endl;
    cout << "        CONSPIRACY THEORY" << endl;
    cout << "Scientists are still trying to determine whether" << endl <<
        "this illogical behaviour is a direct consequence of" << endl <<
        "mask-wearing or if there is a deeper, more mysterious cause." << endl <<
        "(conspiratorial) Who knows? Maybe it IS aliens!" << endl << endl;
    cout << "Judge for yourself. Will this behaviour lead to" << endl <<
        "salvation, or will it bring their downfall?" << endl << endl;
    cout << "Press [ENTER] to start." << endl;
}
int main() {
    // Only seed the random number generator once!
    srandom( time(NULL) );
    showSplashScreen();
    // Stalls program until user hits enter
    while(1){
        if(cin.get() == '\n'){
            break;
        }
    }
    Board board(20, 80, 70);
    board.run();
    return 0;
}
