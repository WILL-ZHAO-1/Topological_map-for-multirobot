#include "data_struct.h"
#include "node_generate.h"
#include "node_simplify.h"
#include "node_matching.h"
#include "topology_map.h"

using namespace std;

int main()
{
	//Generate node
	node_generate t1(IMAGE);
	//Node simplification
	node_simplify t2(t1.generate_node());
	t1.result();

	//Node matching
	node_matching m;
	m.Matches();

	//Create a topology map
	Graph map, map2;
	//Calculate the global path
	map.short_path(0,23);
	map2.Heuristically_path(43,9);
	system("pause");
	return 0;
}
