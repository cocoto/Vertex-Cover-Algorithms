#include "main.h"
#define TEMPSMAX 5
void latex(
	std::ofstream *&f, std::string title, Graph &g
	, int kernel, int arb, int ap2, int heur
) {
	*f	<< title
	<< '&' << g.nb_edges()
	<< '&' << g.avg()
	<< '&' << g.max();
	if(kernel<0)
	{
		*f<<"& nrp";
	}
	else
	{
		*f<< '&' << kernel;
	}
	if(arb<0)
	{
		*f<<"& nrp";
	}
	else
	{
		*f<< '&' << arb;
	}
	if(ap2<0)
	{
		*f<<"& nrp";
	}
	else
	{
		*f<< '&' << ap2;
	}
	if(heur<0)
	{
		*f<< '&' << heur;
	}
	
	*f<< "\\\\\n";
}

void print_date(const time_t &now)
{
	struct tm *timelocal=localtime(&now);
	char result[10];
	strftime(result,10,"%X",timelocal);
	std::cout<<result;
}

int main(int argc, char **argv)
{
	int c = 0, size = 0, res_2_approx,res_monheuristique,min,max;
	float p[5];
	bool res_kernel=false, res_arb=false, timeout_kernel=false,timeout_arb=false;
	int val_kernel,val_arb;
	std::ofstream *f;
	char name[50];
	p[3]=0.1;
	p[4]=0.2;
	int indice_p;
	std::string titres[5]={"3/n","4/n","5/n","0.1","0.2"};
	time_t debut,fin;
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
		*f<<"\\begin{tabular}{||c||ccc||cccc||}\n \\hline \\hline \n n="<<size<<"&$m$&$\\Delta (G)$&$d_M(G)$& Kernel-VC & ARB-VC & 2APPROX-VC & MonHeur-VC\\\\ \\hline \\hline\n";
		p[0]=3.0/size;
		p[1]=4.0/size;
		p[2]=5.0/size;
		for(indice_p=0;indice_p<5;indice_p++)
		{
			std::cout<<"\t Probabilité : "<<titres[indice_p]<<"\t";
			debut=time(NULL);
			print_date(debut);
			std::cout<<"\n";
			Graph graph = Graph(size, p[indice_p]);
			
			/*
			 * Execution de mon heuristique (si >TEMPSMAX, alors NRP)
			 */
			debut=time(NULL);
			res_monheuristique=heuristic(graph);
			fin=time(NULL);
			if(fin-debut>TEMPSMAX)
			{
				res_monheuristique=-1;
			}
			
			/*
			 * Execution de 2-approx (si >TEMPSMAX, alors NRP)
			 */
			debut=time(NULL);
			res_2_approx=function2approx(graph);
			fin=time(NULL);
			if(fin-debut<=TEMPSMAX)
			{
				//Fonction de recherche dichotomie
				min=res_2_approx/2+(res_2_approx%2>0)?1:0;
				//max=std::min(res_2_approx,res_monheuristique);  VERSION OPTIMISEE
				max=res_2_approx;
				timeout_arb=false;
				timeout_kernel=false;
				while(max-min>1 && (!timeout_arb || !timeout_kernel))
				{
					/*
					 * Exécution de Kernel-VC et ARB-VC
					 */
					if(!timeout_kernel)
					{
						debut=time(NULL);
						res_kernel=functionKernelVC(graph, (max+min)/2);
						fin=time(NULL);
						if(fin-debut>TEMPSMAX)
						{
							timeout_kernel=true;
						}
					}
					
					if(!timeout_arb)
					{
						debut=time(NULL);
						res_arb=arb_vc(graph,(max+min)/2);
						fin=time(NULL);
						if(fin-debut>TEMPSMAX)
						{
							timeout_arb=true;
						}
					}
					
					
					if(res_arb!=res_kernel)
					{
						std::cout<<"NON MAIS LOL ! degre="<<(max+min)/2<<" kernel dit "<<res_kernel<<" alors que arb dit "<<res_arb<<" c'est quoi ce bordel !\n";
					}
					if((!timeout_arb && res_arb) || (!timeout_kernel && res_kernel))
					{
						max=(max+min)/2;
					}
					else
					{
						min=(max+min)/2;
					}
				}
				val_arb=timeout_arb?-1:max;
				val_kernel=timeout_kernel?-1:max;
			}
			else
			{
				res_2_approx=-1;
				val_arb=-1;
				val_kernel=-1;
			}
			latex(f,titres[indice_p],graph,val_kernel,val_arb,res_2_approx,res_monheuristique);
		}
		
		/*
		 * Cloture fichier
		 */
		*f<<"\\hline \\end{tabular}\n";
		f->close();
		delete f;
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
	
	return 1;
}
