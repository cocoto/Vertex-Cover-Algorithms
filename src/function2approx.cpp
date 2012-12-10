#include <iostream>
#include <list>
#include <map>
#include "Graph.h"

std::list<int> fonction2approx(Graph graphe)
{
  std::list<int> resultat;
  int sommet1,sommet2;
  std::list<int>::iterator it;
  std::map<int,std::list< int> >::iterator it_graphe;
  while(!graphe.covered())
  {
    //graphe.rebuild();
    sommet1=graphe.id(); //selection du sommet de degré le plus grand (u)
    sommet2=graphe[sommet1]->front(); //selection d'un sommet lié (v)
    resultat.push_back(sommet1);
    resultat.push_back(sommet2);
    //Suppression de u (et de ses arrêtes)
    graphe.erase_node(sommet1);
    //Suppression de v (et de ses arrêtes)
    graphe.erase_node(sommet2);
  }
return resultat;
}
