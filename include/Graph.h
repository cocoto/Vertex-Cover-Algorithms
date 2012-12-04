#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>

#include <cstdlib>
#include <time.h>

#include "Couple.h"

class Couple;

class Graph
{
	private :
		int _max, _edges, _nodes;
		double _avg;
	public :
		Graph(int, double, std::map<int, std::list<int> >*&
			, std::set<Couple> *&nodes);
			
		int max() const;
		int num() const;
		double avg() const;
		
		void get(int);
		void sub(int);
};

#endif
