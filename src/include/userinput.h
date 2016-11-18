#ifndef _USERINPUT_H_
#define _USERINPUT_H_

#include <string>

//functions for getting inputs from user in a manner that won't cause bugs galore
//unlike some other standard functions that crash if you sneeze at them
//I'm looking at you, std::stoi and std::stod

int stringToInt(string userInput);

char getCharInput();

int getIntInput();

double stringToDouble(string userInput);

#endif