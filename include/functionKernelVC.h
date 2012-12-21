#ifndef FUNCTIONKERNELVC
#define FUNCTIONKERNELVC
#include <pthread.h>
#include <list>
#include <map>
#include <set>
#include "Graph.h"
#include "arb-vc.h"
bool functionKernelVC(Graph graphe, int k);
bool functionBruteforce(int k, std::set<int> nodes, Graph graphe);
#endif