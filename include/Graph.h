#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>

#include <cstdlib>
#include <time.h>
#include <iostream>

/**
 *	Glass to represent a graph. Constructed with a number of nodes and an edge
 *	existence probability.
 *	Built around an adjacency list, a map indexed on nodes.
 *	Also keeps track of the node with highest degree as we may need it in our
 *	heuristics selections. Rather than implement an automatic update on each
 *	deletion, we use the Graph::rebuild() method when needed, allowing for a
 *	ligther process when handling multiple nodes at once.
 *
 ***	TODO	***
 *
 *	- Look into Graph::operator[] to see why we cannot return &_edges[i];
 *
 *	== Feedback ==
 *	- Think about custom structure for nodes priority list, we want a container
 *	  indexed on nodes' ids and ordered on their degrees. Can't use map :
 *	  sorting on keys only ; set require resorting to sub-class Couple, hard to
 *	  maintain (find(i)->second->min() brings errors).
 *	  Status : using a save of the node of highest degree as it is the only one
 *	           that matters.
 */
class Graph
{
	private :
		static const std::string _NODE_NOT_FOUND;
		// In order :
		//	- id of the node with the maximum degree
		// 	- maximum degree of the graphe
		//	- number of edges
		//	- number of nodes
		//  - average degree of the graph
		int    _id, _max, _nb_edges, _nb_nodes;
		double _avg;
		bool   _changed;
		
		// Adjacency list
		std::map<int, std::list<int> > _edges;
		/**
		 *	Re-assigns the values for _id and _max, emulating the priority list.
		 */
		void _rebuild();
		
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
		int       id();
		int      max();
		
		int      cid() const;
		int     cmax() const;
		double   avg() const;
		int nb_nodes() const;
		int nb_edges() const;
		
		const std::map<int, std::list<int> >* edges() const;
		
		// - Accessor
		/**
		 *	Fetches the adjacency list of the node of given id in the inner list.
		 *
		 *	@param int id of the node
		 *
		 *	@return list<int>* the corresponding adjacency list
		 */
		const std::list<int>* operator [] (const int) const;
		
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
		bool covered() const;
		/**
		 *	Tells if we have removed too many edges at once.
		 *
		 *	@return bool
		 */
		bool hollow() const;
};

std::ostream& operator << (std::ostream&, const Graph&);

#endif
