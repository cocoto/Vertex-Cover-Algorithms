#include "main.h"

void latex(
	std::ofstream *&f, std::string title, Graph &g
	, int kernel, int arb, int ap2, int heur
) {
	*f	<< title
		<< '&' << g.nb_edges()
		<< '&' << g.avg()
		<< '&' << g.max()
		<< '&' << kernel
		<< '&' << arb
		<< '&' << ap2
		<< '&' << heur
		<< "\\\\";
}

int main(int argc, char **argv)
{
	int c = 0, size = 0, res_2_approx,res_monheuristique,min,max;
	float p[5];
	bool res_kernel, res_arb;
	std::ofstream *f;
	char name[50];
	p[3]=0.1;
	p[4]=0.2;
	int indice_p;
	std::string titres[5]={"3/n","4/n","5/n","0.1","0.2"};
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
	  std::cout<<"Taille :"<<size<<"\n";
	  sprintf(name,"bin/result%d.tex",size);
	  f=new std::ofstream(name);
	  *f<<"$$\\begin{array}{||c||ccc||cccc||}\n \\hline \\hline \\\\ \n n="<<size<<"&m&\\Delta (G)&d_M(G)& Kernel-VC & ARB-VC & 2APPROX-VC & MonHeur-VC\\\\ \\hline \\hline\n";
	  p[0]=3.0/size;
	  p[1]=4.0/size;
	  p[2]=5.0/size;
	  for(indice_p=0;indice_p<5;indice_p++)
	  {
	    std::cout<<"\t Probabilité : "<<titres[indice_p]<<"\n";
	    Graph graph = Graph(size, p[indice_p]);
	    
	    
	    res_2_approx=function2approx(graph);
	    res_monheuristique=heuristic(graph);
	    //Fonction de recherche dichotomie
	    min=res_2_approx/2+(res_2_approx%2>0)?1:0;
	    max=res_2_approx;
	    while(max-min>1)
	    {
	     
	     /*
	     * Exécution de Kernel-VC et ARB-VC
	     */
	      res_kernel=functionKernelVC(graph, (max+min)/2);
	      res_arb=arb_vc(graph,(max+min)/2);
	      
	      if(/*res_arb &&*/ res_kernel)
	      {
		max=(max+min)/2;
	      }
	      else
	      {
// 		if(res_arb!=res_kernel)
// 		{
// 		  std::cout<<"NON MAIL LOL !\n";
// 		}
		min=(max+min)/2;
	      }
	    }
	    
	    
	     latex(f,titres[indice_p],graph,max,max,res_2_approx,res_monheuristique);
	     
	  }
	  
	  /*
	   * Cloture fichier
	   */
	  *f<<"\\end{array}\n";
	  f->close();
	  
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
