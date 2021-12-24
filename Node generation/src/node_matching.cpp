#include "node_matching.h"

using namespace std;

node_matching::node_matching()
{
	this->point_list.clear();
	this->read();
}

void node_matching::read()
{
	ifstream ifs;
	ifs.open(TEXT1, ios::in);
	graph_node P;
	int i = 0;
	while (!ifs.eof())
	{
		ifs >>P.g_name>> P.g_y >> P.g_x;
		this->point_list.push_back(P);
		this->ver_table.push_back(P);
	}
	ifs.close();
	cout << point_list.size() << endl;
	//cout << point_list.back().name << endl;
}

void node_matching::Matches()
{
	//Current node (traverse all nodes to match it) 
    graph_node temp1;
	temp1 = this->point_list.front();
	point_list.pop_front();

	deque<int> temp_list;
	temp_list.clear();
	multimap<int, int> arc_set;

	while (!point_list.empty()) {
		//Traverse the nodes to find the node that matches the current node
		for (auto temp2 : this->point_list) {
			if (abs(temp1.g_y - temp2.g_y) > rows_dis) {
				break;
			}
			if (this->matches(temp1, temp2)) {
				temp_list.push_back(temp2.g_name);
			}
		}
		for (auto t : temp_list) {
			arc_set.insert(make_pair(temp1.g_name, t));
		}
		temp_list.clear();
		temp1 = point_list.front();
		point_list.pop_front();
		//cout << point_list.size() << endl;
	}
	cout << "Number of edge sets：";
	cout << arc_set.size() << endl;
	this->write(arc_set);
}

bool node_matching::matches(graph_node &n1, graph_node &n2)
{
	int x1, x2;
	x1 = n1.g_x;
	x2 = n2.g_x;
	if (abs(x1 - x2) < cols_dis) {
		return true;
	}
	return false;
}

void node_matching::write(multimap<int, int> &m)
{
	int p1, p2;
	ofstream ofs;
	ofs.open(TEXT4, ios::out);
	for (auto w : m) {
		p1 = w.first;
		p2 = w.second;
		ofs << this->ver_table[p1].g_name << " " << this->ver_table[p1].g_y << " " << this->ver_table[p1].g_x << " "
			<< this->ver_table[p2].g_name << " " << this->ver_table[p2].g_y << " " << this->ver_table[p2].g_x << endl;
	}
	ofs.close();
}
