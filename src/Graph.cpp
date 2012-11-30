#include "Graph.h"

Couple Graph::graph(
	int n, double p
	, std::map<int, std::list<int>> *&graph, std::set<Couple> *&nodes
) {
	int i = 0, j = 0, r = 0, m = 0;
	double q = p * RAND_MAX, delta = 0.0;
	Couple a, b;
	std::vector<Couple> list;
	
	// Initiate the Couple list
	for (i = 1; i <= n; i++) {
		list.push_back(new Couple(i, 0));
	}
	
	// Build the edges
	for (i = 1; i <= n; i++) {
		a = list.at(i - 1);
		for(j = i + 1; j <= n; j++) {
			a = list.at(j - 1);
			r = rand();
			
			if (r <= q) {
				a.add();
				b.add();
				
				++m;
			}
		}
	}
	
	// Build the set of nodes
	for (i = 1; i <= n; i++) {
		a = list.at(i - 1);
		nodes.insert();
		delta += a.deg();
	}
	
	delta /= n;
	
	return Couple(delta, m);
}
