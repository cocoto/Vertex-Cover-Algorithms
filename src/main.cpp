#include "main.h"

int main(int argc, char **argv)
{
	int c = 0, size = 0;

	if (argc < 2) {
		std::cout << "Ce programme s'appelle ./mvc -n <taille>" << std::endl;
		return 0;
	} else {
		while ((c = getopt(argc, argv, "n:")) != -1) {
			if (c == 'n') {
				size = atoi(optarg);
			}
		}
	}
	
	std::map<int, std::list<int> > *edges = new std::map<int, std::list<int> >;
	std::set<Couple> *nodes = new std::set<Couple>;
	double delta = 0.0;
	
	// p = 3/n
	Graph graph = Graph(size, (double) 3 / size, edges, nodes);
	
	std::map<int, std::list<int> >::iterator mit = edges->begin();
	std::list<int>::iterator lit;
	
	while (mit != edges->end()) {
		lit = mit->second.begin();
		
		std::cout << '[' << mit->first << "]\t: {";
		
		while (lit != mit->second.end()) {
			std::cout << *lit << ',';
			++lit;
		}
		
		std::cout << '}' << std::endl;
		++mit;
	}
	
	return 1;
}
