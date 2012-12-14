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
	
	return 1;
}
