#include "arb-vc.h"

bool arb_vc(Graph g, int k)
{
	pthread_testcancel();
	// Graph is covered without overflow in edge removal
	if (g.covered() && k >= 0) {
		return true;
	}
	
	// No more operation available
	if (k <= 0) {
		return false;
	}
	
	// Polynomial solving of lower degree graphs
// 	if (g.max() < 3) {
// 		return degree2_vc(g, k);
// 	}
	
	// Maximum degree node
	int id = g.id();
	
	Graph g1 = g, g2 = g;
	
	g1.erase_node(id);
	
	std::list<int>::const_iterator it = g[id]->begin();
	int k2 = k - g[id]->size();
	
	while (it != g[id]->end()) {		
		g2.erase_node(*it);
		++it;
	}
	
	return arb_vc(g1, k - 1) || arb_vc(g2, k2);
}

bool degree2_vc(Graph &g, int k)
{
	int i = 0;
	unsigned int size = 0;
	std::list<int>::iterator lt;
	std::map<int, std::list<int> > list = *g.edges();
	std::map<int, std::list<int> >::iterator it = list.begin();
	
	while (it != list.end()) {
		i    = 0;
		size = it->second.size();
		
		if (size == 0) {
			list.erase(it->first);
		} else {
			lt = it->second.begin();
			
			while (lt != it->second.end()) {
				list.erase(*lt);
				
				++lt;
				++i;
			}
			
			list.erase(it->first);
			++i;
			
			// size == 1 means we have a chain
			if (size == 1) {
				k -= floor(i / 2);
			} else { // size == 2 means we have a cycle
				k -= ceil(i / 2);
			}
		}
		
		++it;
	}
	
	return list.empty() && k >= 0;
}
