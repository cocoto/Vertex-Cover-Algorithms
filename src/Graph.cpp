#include "Graph.h"

/**
 *	Build a graph representation based on an adjacency list, and ordered on the
 *	size of the latter.
 *
 *	@param int n   number of nodes
 *	@param double  rate of edge existence
 *	@param struct* map indexed on node id, with the list of its edges as second
 *	               member (adjacency list)
 *
 *	@return double average degree of the graph's nodes
 */
Graph::Graph(
	int n, double p
	, std::map<int, std::list<int> > *&graph, std::set<Couple> *&nodes
) {
	int i = 0, j = 0, r = 0, m = 0;
	double q = p * RAND_MAX;
	
	std::list<int> *la, *lb;
  	std::map<int, std::list<int> >::iterator a, b;

	srand(time(NULL));
	
	// Build the edges
	for (i = 1; i <= n; i++) {
		// Adjacency list of node a
		la = &(*graph)[i];
				
		for(j = i + 1; j <= n; j++) {
			// Adjacency list of node b
			lb = &(*graph)[j];
			
			r = rand();
			
			if (r <= q) {
				++m;
				
				la->push_back(j);
				lb->push_back(i);
			}
		}
	}
	
	for (i = 1; i <= n; i++) {
		Couple c = Couple(i, graph[i].size());
		nodes->insert(c);
	}
	
	_nodes = n;
	_edges = m;
	
	_avg = m / n;
}
