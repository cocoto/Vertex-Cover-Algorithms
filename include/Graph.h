#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>

#include <cstdlib>
#include <time.h>
#include <iostream>

#include "Couple.h"

/**
 *	Glass to represent a graph. Constructed with a number of nodes and an edge
 *	existence probability.
 *	Built around two internal lists :
 *		- _edges : adjacency list of the graph, a map indexed on nodes.
 *		- _nodes : set of nodes, ordered on the number of edges they each have.
 *
 ***	TODO	***
 *	- Add node degree decrement in erase_* methods.
 *	- Think about custom structure for nodes priority list, we want a container
 *	  indexed on nodes' ids and ordered on their degrees. Can't use map :
 *	  sorting on keys only ; set require resorting to sub-class Couple, hard to
 *	  maintain (find(i)->min() brings errors).
 */
class Graph
{
	private :
		// In order :
		// 	- maximum degree of the graphe
		//	- number of edges
		//	- number of nodes
		int _max, _nb_edges, _nb_nodes;
		// Average degree of the graph
		double _avg;
		
		// Adjacency list
		std::map<int, std::list<int> > _edges;
		// Ordered list of nodes
		std::set<Couple> _nodes;
		
	public :
		/**
		 *	Build a graph representation based on an adjacency list, and
		 *	maintain an ordered set of nodes on their degree.
		 *
		 *	@param int    number of nodes
		 *	@param double rate of edge existence
		 */
		Graph(int, double);
		
		// - Getters
		int nb_nodes() const;
		int nb_edges() const;
		double   avg() const;
		
		const std::map<int, std::list<int> >* edges() const;
		std::set<Couple> nodes() const;
		
		// - Accessor
		std::list<int> operator [] (const int);
		
		// - Methods
		/**
		 *	Delete edge (i,j) from the graph. Removing it from the lists of each
		 *	of its ends, and adjusting their respective degrees.
		 *
		 *	@param int head
		 *	@param int tail
		 */
		void erase_edge(const int&, const int&);
		/**
		 *	Deletes a node from the graph ; removing it from the list of nodes,
		 *	and each of its reference in any adjacency list.
		 *
		 *	@param int id of the node to delete
		 */
		void erase_node(const int&);
		/**
		 *	Tells if we have covered our graph, i.e. all edges have been removed.
		 *
		 *	@return bool
		 */
		bool covered();
};

std::ostream& operator << (std::ostream&, const Graph&);

#endif
