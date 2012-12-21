#ifndef MAIN_H
#define MAIN_H

// Std lib
#include <map>
#include <set>
#include <list>
#include <algorithm>

// C lib
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

// Classes
#include "Graph.h"

// Resolution
#include "arb-vc.h"
#include "function2approx.h"
#include "functionKernelVC.h"
#include "heuristic.h"

int  main(int, char**);
void latex(std::ofstream*&, std::string, Graph&, int, int, int, int);
void* exec_kernel(void* data);
void* exec_arb(void* data);
void* exec_2approx(void* data);
void* exec_monheur(void* data);
void* stop2(void* data);
void* stop(void* data);
void print_date(const time_t &now);

#endif
