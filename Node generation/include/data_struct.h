#pragma once
struct NODE {
	int y, x;//
};
struct graph_node
{
	int g_x, g_y;
	int g_name;
	bool g_visit;

};
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
