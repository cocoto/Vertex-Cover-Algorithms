#include "Graph.h"

Graph::Graph(int n, double p)
{
	int i = 0, j = 0, r = 0, m = 0;
	// Threshold for edge existency
	double q = p * RAND_MAX;

	srand(time(NULL));
	
	std::cout << "Existence rate : " << q / RAND_MAX * 100 << "%\n";
	
	// Build the edges
	for (i = 1; i <= n; i++) {
		for(j = i + 1; j <= n; j++) {
			r = rand();
			
			if (r <= q) {
				++m;
				
				_edges[i].push_back(j);
				_edges[j].push_back(i);
			}
		}
	}
	
	int size = 0;
	_max     = 0;
	
	// Create the priority list
	for (i = 1; i <= n; i++) {
		size = _edges[i].size();
		
		if (size > _max) {
			_max = size;
		}
		
		Couple c = Couple(i, size);
		_nodes.insert(c);
	}
	
	_nb_nodes = n;
	_nb_edges = m;
	
	_avg = (double) m / n;
}

/****************************************
**************** Getters ****************
****************************************/

double Graph::avg() const
{
	return _avg;
}

int Graph::nb_edges() const
{
	return _nb_edges;
}

int Graph::nb_nodes() const
{
	return _nb_nodes;
}
		
const std::map<int, std::list<int> >* Graph::edges() const
{
	return &_edges;
}

std::set<Couple> Graph::nodes() const
{
	return _nodes;
}

std::list<int> Graph::operator [] (const int i)
{
	return _edges[i];
}

/****************************************
**************** Methods ****************
****************************************/

void Graph::erase_edge(const int &i, const int &j)
{
	_edges[i].remove(j);
	_edges[j].remove(i);
	
	--_nb_edges;
}

void Graph::erase_node(const int &i)
{
	// We remove as much edges as incident to designated node.
	_nb_edges -= _edges[i].size();
	_edges.erase(i);
	
	std::map<int, std::list<int> >::iterator it = _edges.begin();
	
	while (it != _edges.end()) {
		it->second.remove(i);
	}
}

bool Graph::covered()
{
	return _nb_edges == 0;
}

std::ostream& operator << (std::ostream &os, const Graph &g)
{
	std::map<int, std::list<int> >::const_iterator mit = g.edges()->begin();
	std::list<int>::const_iterator lit;
	
	while (mit != g.edges()->end()) {
		os << '[' << mit->first << "]\t: {";
		
		lit = mit->second.begin();
		
		if (mit->second.size() > 0) {
			os << *lit;
		
			++lit;
	
			while (lit != mit->second.end()) {
				os << ',' << *lit;
				++lit;
			}
		}
		
		os << "}\n";
		++mit;
	}
	
	return os;
}
