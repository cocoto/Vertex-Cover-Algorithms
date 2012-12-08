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
	
	// Create the priority list
	rebuild();
	
	_nb_nodes = n;
	_nb_edges = m;
	
	_avg = (double) m / n;
}

/****************************************
**************** Getters ****************
****************************************/

int Graph::id() const
{
	return _id;
}

int Graph::max() const
{
	return _max;
}

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

const std::list<int>* Graph::operator [] (const int i) const
{
	return &(_edges.find(i)->second);
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
		
		++it;
	}
}

void Graph::rebuild()
{
	_id  = 0;
	_max = 0;
	
	std::map<int, std::list<int> >::iterator it = _edges.begin();
	int i = 0;
	
	while (it != _edges.end()) {
		++i;
		
		if (it->second.size() > _max) {
			_max = it->second.size();
			_id  = i;
		}
		
		++it;
	}
}

bool Graph::covered()
{
	return _nb_edges == 0;
}

bool Graph::hollow()
{
	return _nd_edges < 0;
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
				os << ", " << *lit;
				++lit;
			}
		}
		
		os << "}\n";
		++mit;
	}
	
	os  <<   "Nb. of nodes : " << g.nb_nodes()
		<< "\tNb. of edges : " << g.nb_edges()
		<< "\nMax. degree  : " << g.max()
		<< "\tAvg. degree  : " << g.avg()
		<< '\n';
		
	
	return os;
}
