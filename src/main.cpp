#include "main.h"
#include <unistd.h>
#include "function2approx.cpp"
#include "functionKernelVC.cpp"
int main(int argc, char **argv)
{
	int c = 0, size = 0, res_2_approx,min,max;
	float p[5];
	bool res_kernel, res_arb;
	p[3]=0.1;
	p[4]=0.2;
	int indice_p;
	if (argc < 2) {
		std::cout << "Ce programme s'appelle ./prog -n <taille>" << std::endl;
		return 0;
	} else {
		while ((c = getopt(argc, argv, "n:")) != -1) {
			if (c == 'n') {
				size = atoi(optarg);
			}
		}
	}
	
	size=10;
	while(size<=1000)
	{
	  p[0]=3.0/size;
	  p[1]=4.0/size;
	  p[2]=5.0/size;
	  for(indice_p=0;indice_p<5;indice_p++)
	  {
	    Graph graph = Graph(size, p[indice_p]);
	    
	    
	    res_2_approx=fonction2approx(graph);
	    
	    //Fonction de recherche dichotomie
	    min=res_2_approx/2;
	    max=res_2_approx;
	    while(min!=max)
	    {
	     
	     /*
	     * Exécution de Kernel-VC et ARB-VC
	     */
	      res_kernel=fonctionKernelVC(graph, (max+min)/2);
	      res_arb=arb_vc(graph,(max+min)/2);
	      
	      if(res_arb && res_kernel)
	      {
		min=(max+min)/2;
	      }
	      else
	      {
		max=(max+min)/2;
	      }
	    }
	    
	    /*
	     * latex(titre[indice_p],graphe,min,min,res_2_approx,res_monheuristique);
	     */
	  }
	  
	  
	  
	  if(size<100)
	  {
	    size+=10;
	  }
	  else if(size<500)
	  {
	    size+=20;
	  }
	  else if(size<1000)
	  {
	    size+=50;
	  }
	  else
	  {
	    size+=100;
	  }
	}
// 	// p = 3/n
// 	Graph graph = Graph(size, (double) 3 / size);
// 	
// 	std::cout << graph;
// 	std::list<int> d_approx=fonction2approx(graph);
// 	std::cout<<d_approx.size()<<"\n";
// 	std::list<int>::iterator it=d_approx.begin();
// 	while(it!=d_approx.end())
// 	{
// 	  std::cout<<*it<<" ";
// 	  it++;
// 	}
// 	std::cout<<"\n";
// 	int i;
//  	for(i=0;i<=(int)d_approx.size();i++)
// 	{
// 	  std::cout<<i<<" = "<<(fonctionKernelVC(graph, i)?"true":"false")<<"\n";
// 	}
	
	return 1;
}
