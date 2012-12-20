#include "function2approx.h"
int function2approx(Graph graphe)
{
  int resultat=0;
  int sommet1,sommet2;
  std::list<int>::iterator it;
  std::map<int,std::list< int> >::iterator it_graphe;
  while(!graphe.covered())
  {
    //graphe.rebuild();
    sommet1=graphe.id(); //selection du sommet de degré le plus grand (u)
    sommet2=graphe[sommet1]->front(); //selection d'un sommet lié (v)
    resultat+=2;
    try{
    //Suppression de u (et de ses arrêtes)
    graphe.erase_node(sommet1);
    //Suppression de v (et de ses arrêtes)
    graphe.erase_node(sommet2);
    }
    catch(std::string s)
    {
    }
  }
return resultat;
}
