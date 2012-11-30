#include <iostream>
#include <list>
#include <set>
#include <map>
#include "Couple.h"

std::list<int> fonction2approx(std::map<int,std::list< int> > graphe)
{
  std::list<int> resultat;
  int sommet1,sommet2;
  std::list<int>::iterator it;
  std::map<int,std::list< int> >::iterator it_graphe;
  while(!graphe.empty())
  {
    sommet1=graphe.begin()->first; //selection du sommet de degré le plus grand (u)
    sommet2=graphe[sommet1].front(); //selection d'un sommet lié (v)
    resultat.push_back(sommet1);
    resultat.push_back(sommet2);
    //Suppression des arrêtes de u
    it=graphe[sommet1].begin();
    while(it!=graphe[sommet1].end())
    {
      graphe[*it].remove(sommet1);
      if(graphe[*it].empty())
      {
	graphe.erase(*it);
      }
      it++;
    }
    //On efface v du graphe
    graphe.erase(sommet1);
    //Test d'existence de v (si pas effacé ci-dessus)
    if(graphe.find(sommet2)!=graphe.end())
    {
      
      //Suppression des arrêtes de u
      it=graphe[sommet2].begin();
      while(it!=graphe[sommet2].end())
      {
	graphe[*it].remove(sommet2);
	if(graphe[*it].empty())
	{
	  graphe.erase(*it);
	}
	it++;
      }
      graphe.erase(sommet2);
    }
  }
return resultat;
}
