#include <iostream>
#include <list>
#include <map>
#include "Graph.h"

bool fonctionKernelVC(Graph graphe, int k)
{
  std::map<int,std::list< int> >::const_iterator it_graphe;
  int degre;
   while(it_graphe!=graphe.edges()->end() && k!=0 && !graphe.covered())
   {
     degre=it_graphe->second.size();
     if(degre==1)
     {
       k--;
       graphe.erase_node(it_graphe->second.front());
       it_graphe=graphe.edges()->begin();
     }
     else if(degre>k)
     { 
       k--;
       graphe.erase_node(it_graphe->first);
       it_graphe=graphe.edges()->begin();
     }
     else
     {
      it_graphe++;
     }
   }
  return graphe.nb_edges()<=k*k;
}
