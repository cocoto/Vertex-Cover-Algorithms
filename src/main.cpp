#include "main.h"
#define TEMPSMAX 180
/*
 * Fonction remplissant une ligne du tableau LaTeX dans le flux f
 * Si une valeur est égale à -X, alors la case correspondante est notée "nrp"
 */

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
		*f<<"& nrp";
	}
	else
	{
		*f<< '&' << heur;
	}
	
	*f<< "\\\\\n";
}

/*
 * Variables statics du problèmes
 * Ces variables sont utilisées par les threads, et n'occasionnent pas de conflits
 */
static bool res_kernel, timeout_kernel, res_arb, timeout_arb; //Résultats des algorithmes et notification de timeout
static int k, res_2_approx,res_monheuristique;	//Résultats des heuristiques
static pthread_mutex_t mutex_chrono = PTHREAD_MUTEX_INITIALIZER; //Mutex empéchant la destruction du chrono lorsque celui-ci est dépassé

/*
 * Fonction Thread de l'algorithme de kernelisation
 */
void* exec_kernel(void* data)
{
	Graph graph=*(Graph*)data;
	bool resultat=functionKernelVC(graph,k);
	res_kernel=resultat;
	return NULL;
}

/*
 * Fonction Thread de l'algorithme d'arbre binaire  de recherche borné
 */
void* exec_arb(void* data)
{
	//sleep(10);
	Graph graph=*(Graph*)data;
	bool resultat=arb_vc(graph,k);
	res_arb=resultat;
	return NULL;
}

/*
 * Fonction Thread de l'algorithme de 2-Approximation
 */
void* exec_2approx(void* data)
{
	Graph graph=*(Graph*)data;
	int resultat=function2approx(graph);
	res_2_approx=resultat;
	return NULL;
}

/*
 * Fonction Thread de l'algorithme Mon-Heuristique
 */
void* exec_monheur(void* data)
{
	Graph graph=*(Graph*)data;
	int resultat=heuristic(graph);
	res_monheuristique=resultat;
	return NULL;
}

/*
 * Algorihtme de timout des fonctions 2-Approx et Mon-Heuristique
 * 
 */
void* stop2(void* data)
{
	int fin_2approx,fin_monheur; //Entiers informant la bonne fermeture des threads
	pthread_t* tab_thread=(pthread_t*)data;
	
	
	//On attend X secondes
	sleep(TEMPSMAX);
	
	
	pthread_mutex_lock (&mutex_chrono); //Mutex de sécurité
	
	std::cout<<"TEMPS MAX DEPASSE\n";
	//On termine les threads
	fin_2approx=pthread_cancel(tab_thread[0]);
	fin_monheur=pthread_cancel(tab_thread[1]);
	
	//On met à jour les données
	if(fin_2approx==0) //fin_X est égal à zéro uniquement si le chronomètre est à l'origine de la terminaison du thread
	{
		std::cout<<"DEPASSEMENT 2Approx\n";
		res_2_approx=-1;
	}
	if(fin_monheur==0)
	{
		std::cout<<"DEPASSEMENT Mon Heuristique\n";
		res_monheuristique=-1;
	}
	pthread_mutex_unlock (&mutex_chrono);
	return NULL;
}

/*
 * Algorithme de timeout des fonctions Arb-VC et Kernel-VC
 * CF description ci-dessus
 */
void* stop(void* data)
{
	int fin_arb,fin_kernel;
	pthread_t* tab_thread=(pthread_t*)data;
	
	
	//On attend X secondes
	sleep(TEMPSMAX);
	pthread_mutex_lock (&mutex_chrono);
	std::cout<<"TEMPS MAX DEPASSE\n";
	//On termine les threads
	fin_kernel=pthread_cancel(tab_thread[0]);
	fin_arb=pthread_cancel(tab_thread[1]);
	
	//On met à jour les données
	if(fin_kernel==0)
	{
		std::cout<<"DEPASSEMENT KERNEL\n";
		timeout_kernel=true;
	}
	if(fin_arb==0)
	{
		std::cout<<"DEPASSEMENT ARB\n";
		timeout_arb=true;
	}
	pthread_mutex_unlock (&mutex_chrono);
	return NULL;
}

/*
 * Fonction d'affichage de l'heure courante
 */
void print_date(const time_t &now)
{
	struct tm *timelocal=localtime(&now);
	char result[10];
	strftime(result,10,"%X",timelocal);
	std::cout<<result;
}



int main(int argc, char **argv)
{
	(void) argv;
	(void) argc;
	int size = 0,min,max;
	
	float p[5]; //Tableau des probabilités
	/*
	 * Activation des variables statiques
	 */
	res_arb=false;
	timeout_kernel=false;
	timeout_arb=false;
	res_kernel=false;
	
	
	int val_kernel,val_arb; //Valeurs finales (optimales) des kernel et arb
	std::ofstream *f; //Fichier de sortie LaTeX
	char name[50];	  //Nom des lignes du tableau (5/n...0.2)
	int indice_p;
	pthread_t exec[2]; //On créé un tableau de 2 threads (kernel,arb) ou (2-approx,monheuristique)
	pthread_t timer; //On créer un thread de timeout
	time_t debut; //Temps actuel (heure)
	
	p[3]=0.1;
	p[4]=0.2;
	std::string titres[5]={"3/n","4/n","5/n","0.1","0.2"};
	
	size=10; //On commence les tableaux à n=10
	while(size<=1000) //Jusqu'à au maximum n=1000
	{
		/*
		 * Mise en place du début du tableau LaTeX
		 */
		std::cout<<"Taille :"<<size<<"\n";
		sprintf(name,"bin/result%d.tex",size);
		f=new std::ofstream(name);
		*f<<"\\begin{tabular}{||c||ccc||cccc||}\n \\hline \\hline \n n="<<size<<"&$m$&$\\Delta (G)$&$d_M(G)$& Kernel-VC & ARB-VC & 2APPROX-VC & MonHeur-VC\\\\ \\hline \\hline\n";
		p[0]=3.0/size;
		p[1]=4.0/size;
		p[2]=5.0/size;
		
		
		/*
		 * Boucle sur les valeurs de p
		 */
		for(indice_p=0;indice_p<5;indice_p++)
		{
			std::cout<<"\t Probabilité : "<<titres[indice_p]<<"\t";
			debut=time(NULL);
			print_date(debut);
			std::cout<<"\n";
			
			/*
			 * génération du graphe de taille size et de proba p
			 */
			Graph graph = Graph(size, p[indice_p]);
			
			
			pthread_create(&exec[0], NULL, exec_2approx, (void*)&graph);
			pthread_create(&exec[1], NULL, exec_monheur, (void*)&graph);
			pthread_create(&timer,NULL,stop2,(void*) &exec);
			pthread_join(exec[0], NULL);
			pthread_join(exec[1], NULL);
			pthread_mutex_lock (&mutex_chrono);
			pthread_cancel(timer);
			pthread_mutex_unlock (&mutex_chrono);
			
			if(res_2_approx>=0)
			{
				
				/*
				 * Recherche dichotomique
				 */
				//Fonction de recherche dichotomie
				min=res_2_approx/2+((res_2_approx%2>0)?1:0);
				//max=std::min(res_2_approx,res_monheuristique);  VERSION OPTIMISEE
				max=res_2_approx;
				timeout_arb=false;
				timeout_kernel=false;

				while(max-min>1 && (!timeout_arb || !timeout_kernel))
				{
					std::cout<<"\t\t\t\tDichotomie : min="<<min<<" max="<<max<<"\n";
					pthread_t exec[2]; //On créé un tableau de 2 threads (kernel et arb)
					k=(max+min)/2; //On définit k (variable static)
					
					/*
					 * Lancement de Kernel-VC s'il n'a pas dépassé le timeout
					 * Au cours de la recherche dichotomique
					 */
					if(!timeout_kernel){
						//std::cout<<"Appel à Kernel\n";
						pthread_create(&exec[0], NULL, exec_kernel, (void*)&graph);
					}
					
					/*
					 * Lancement de Arb-VC s'il n'a pas dépassé le timeout
					 * Au cours de la recherche dichotomique
					 */
					if(!timeout_arb)
					{
						//std::cout<<"Appel à Arb\n";
						pthread_create(&exec[1],NULL,exec_arb, (void*)&graph);
					}
					
					/*
					 * Lancement du timeout
					 */
					pthread_create(&timer,NULL,stop,(void*) &exec);
					
					/*
					 * Mise en attente de la terminaison des threads créés (arb et kernel)
					 */
					if(!timeout_kernel)
					{
						//std::cout<<"Attente de fin de kernel \n";
						pthread_join(exec[0], NULL);
						//std::cout<<"Fin de Kernel\n";
					}
					if(!timeout_arb)
					{
						pthread_join(exec[1],NULL);
						//std::cout<<"Fin de Arb\n";
					}
					
					/*
					 * Destruction du thread de timeout (si les deux fonctions précédantes ont terminés dans les délais)
					 */
 					pthread_mutex_lock (&mutex_chrono);
 					pthread_cancel(timer);
 					pthread_mutex_unlock (&mutex_chrono);

					
					/*
					 * Mise à jour des bornes de la dichotomie
					 */
					if((!timeout_arb && res_arb) || (!timeout_kernel && res_kernel))
					{
						max=(max+min)/2;
					}
					else
					{
						min=(max+min)/2;
					}
				}//Fin de la dichotomie
				
				/*
				 * Si un algorithme à été abandonné pendant la dichotomie, alors il prend pour valeur NRP
				 */
				val_arb=timeout_arb?-1:max;
				val_kernel=timeout_kernel?-1:max;
			}
			else //Cas de fonction 2-approx trop longue
			{
				val_arb=-1;
				val_kernel=-1;
			}
			//Ajout de la ligne dans le tableau
			latex(f,titres[indice_p],graph,val_kernel,val_arb,res_2_approx,res_monheuristique);
		}//Fin de la boucle sur les valeurs de P
		
		/*
		 * Cloture fichier
		 */
		*f<<"\\hline \\end{tabular}\n";
		f->close();
		delete f;
		
		//Passage à la nouvelle valeur de n
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