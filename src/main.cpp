#include "main.h"

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
	
	double delta = 0.0;
	
	// p = 3/n
	Graph graph = Graph(size, (double) 3 / size);
	
	std::cout << graph;
	
	return 1;
}
