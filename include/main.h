#ifndef MAIN_H
#define MAIN_H

// Std lib
#include <map>
#include <set>
#include <list>

// C lib
#include <iostream>
#include <fstream>
#include <cstring>

// Classes
#include "Couple.h"
#include "Graph.h"

// Resolution
#include "arb-vc.h"

int  main(int, char**);
void latex(std::ofstream*&, std::string, Graph&, int, int, int, int);

#endif
