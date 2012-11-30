#include "main.h"

int main(int argc, int **argv)
{
	int c = 0, size = 0;

	if (argc < 3) {
		std::cout << "Ce programme s'appelle ./vc -n <taille>" << std::endl;
		return 0;
	} else {
		while ((c = getopt(argc, argv, "n::")) != -1) {
			if (c == 'n') {
				if (optarg != '') {
					size = atoi(optarg);
				} else {
					size = 20;
				}
			}
		}
	}
	
	std::map<int, std::list<int>> graph;
	std::set<Couple> nodes;
	
	
}
