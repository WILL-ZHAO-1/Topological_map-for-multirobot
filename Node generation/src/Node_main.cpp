#include "data_struct.h"
#include "node_generate.h"
#include "node_simplify.h"
#include "node_matching.h"
#include "topology_map.h"

using namespace std;

int main()
{
	node_generate t1(IMAGE);
	//角点检测
	//t1.ang_point();
	//节点简化
	node_simplify t2(t1.generate_node());
	t1.result();

	//节点匹配
	//node_matching m;
	//m.Matches();

	//创建拓扑地图
	//Graph map, map2;
	////map.short_path(0,23);
	//map2.Heuristically_path(43,9);
	system("pause");
	return 0;
}