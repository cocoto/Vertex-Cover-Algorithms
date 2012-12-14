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
#include <unistd.h>

// Classes
#include "Couple.h"
#include "Graph.h"

// Resolution
#include "arb-vc.h"
#include "function2approx.h"
#include "functionKernelVC.h"
#include "heuristic.h"

int  main(int, char**);
void latex(std::ofstream*&, std::string, Graph&, int, int, int, int);

#endif
