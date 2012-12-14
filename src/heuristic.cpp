#include "heuristic.h"

int heuristic(Graph g)
{
	int k = 0;
	
	while (!g.covered()) {
		g.erase_node(g.id());
		++k;
	}
	
	return k;
}
