#pragma once
//节点数据结构体
struct NODE {
	//节点的像素坐标
	int y, x;//(行，列)
};

//拓扑地图中的节点
struct graph_node
{
	//节点坐标
	int g_x, g_y;
	//节点序号
	int g_name;
	//节点访问权限
	bool g_visit;

};
//自定义数据的排序规则
struct Cmp
{
	bool operator () (graph_node const &a, graph_node const &b)const
	{
		if (a.g_y != b.g_y)
			return a.g_y<b.g_y;
		else if (a.g_x != a.g_x)
			return a.g_x<b.g_x;
		else return a.g_name < b.g_name;
	}
};