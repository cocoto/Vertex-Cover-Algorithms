#include "functionKernelVC.h"
bool functionKernelVC(Graph graphe, int k)
{
  std::map<int,std::list< int> >::const_iterator it_graphe=graphe.edges()->begin();
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
  if (graphe.nb_edges()>k*k) return false;
  else
  {
    std::set<int> set_edges;
    it_graphe=graphe.edges()->begin();
    while(it_graphe!=graphe.edges()->end())
    {
      set_edges.insert(it_graphe->first);
      it_graphe++;
    }
    //std::cout<<"Fin de Kernel VC, k="<<k<<" à tester avec "<<set_edges.size()<<" noeuds\n";
    //return functionBruteforce(k,set_edges,graphe);
    return arb_vc(graphe,k);
  }
}

bool functionBruteforce(int k, std::set<int> nodes, Graph graphe)
{
  std::set<int> nodes2=nodes;
  std::set<int>::iterator it;
  if(k==0)
  {
    return graphe.covered();
  }
  else
  {
    it=nodes.begin();
    while(it!=nodes.end())
    {
      //nodes2=nodes;
      nodes2.erase(*it);
      Graph graphe2=graphe;
      
      if(graphe2[*it]->size()>0)
      {
	graphe2.erase_node(*it);
	if(graphe2.covered())
	{
	  return true;
	}
	// std::cout<<"étage "<<k<<" retrait de "<<*it<<"\n";
	if(functionBruteforce(k-1,nodes2,graphe2))
	{
	  return true;
	} 
      }
      it++;
    }
    return false;
  }
}
