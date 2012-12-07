#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>

#include <cstdlib>
#include <time.h>

#include "Couple.h"

/*
 * TODO : Ajouter la définition des classes
 * 
 * std::map<int, std::list<int> > *edges = new std::map<int, std::list<int> >;
 * std::set<Couple> *nodes = new std::set<Couple>;
 * 
 * Dans la classe (private)
 *
 * TODO : Définir les accesseurs
 * TODO : Définir l'opérateur [] = edges.[]
 * TODO : Définir la fonction erase_edge(const int &node1, const int &node2) = efface les deux arrètes (2--1, 1--2)
 * TODO : Définir la fonction erase_node(const int &) = supression de nodes, supression des arretes adjacentes
 * TODO : Définir la fonction bool empty_edge() = toutes les arrêtes sont couvertes
 */
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
