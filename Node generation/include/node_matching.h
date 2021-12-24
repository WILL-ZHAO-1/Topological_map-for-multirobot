#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <vector>
#include "globa.h"
#include "data_struct.h"

using namespace std;
class node_matching
{
public:
	node_matching();
	void Matches();
	void read();
	bool matches(graph_node &n1, graph_node &n2);
	void write(multimap<int, int> &m);

	deque<graph_node> point_list;
	vector<graph_node> ver_table;

};
