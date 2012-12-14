#include "main.h"
#include "function2approx.cpp"
#include "functionKernelVC.cpp"

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
	int c = 0, size = 0;

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
	
	// p = 3/n
	Graph graph = Graph(size, (double) 3 / size);
	
	std::cout << graph;
	std::list<int> d_approx=fonction2approx(graph);
	std::cout<<d_approx.size()<<"\n";
	std::list<int>::iterator it=d_approx.begin();
	while(it!=d_approx.end())
	{
	  std::cout<<*it<<" ";
	  it++;
	}
	std::cout<<"\n";
	int i;
 	for(i=0;i<=(int)d_approx.size();i++)
	{
	  std::cout<<i<<" = "<<(fonctionKernelVC(graph, i)?"true":"false")<<"\n";
	}
	
	return 1;
}
