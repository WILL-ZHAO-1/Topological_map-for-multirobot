#include "node_simplify.h"

using namespace std;

node_simplify::node_simplify(deque<NODE> &n)
{
	//this->ang_point_read();
	this->ori_node_deq = n;
	//this->read();
	cout << "Number of nodes： ";
	cout << this->ori_node_deq.size() << endl;
	this->Simplify();
}

void node_simplify::Simplify()
{
	//Simplify nodes by row
	NODE T1;
	int pre_y = 0;
	int pre_x = 0;
	this->m_top = this->ori_node_deq.front();
	while (!this->ori_node_deq.empty()) {
		T1 = this->ori_node_deq.front();
		if (pre_y != T1.y) {
			this->deque_full();
		}
		if (this->temp_deq.empty()) {
			this->temp_deq.push_back(T1);
			pre_y = T1.y;
			pre_x = T1.x;

		}
		else if (pre_y == T1.y && (pre_x + dis) <= T1.x) {
			this->temp_deq.push_back(T1);
			pre_x = T1.x;
		}
		this->ori_node_deq.pop_front();
	}
	this->deque_full();


	/*cout << "Number of original nodes： ";
	cout << this->ori_node_deq.size() << endl;
	cout << "Number of temporary nodes： ";
	cout << this->temp_deq.size() << endl;
	cout << "Simplify the number of nodes： ";
	cout << this->fin_node_deq.size() << endl;*/
	/*cout << "Feature node number： ";
	cout << this->type_node.size() << endl;
	for (auto k : this->type_node) {
	cout << k.y << "," << k.x << endl;
	}*/

	int num = 0;
	ofstream ofs;
	ofs.open(TEXT1, ios::out);
	for (auto w : fin_node_deq) {
	ofs << num << " " << w.y << " " << w.x << endl;
	num++;
	}
	ofs.close();
}

void node_simplify::deque_full()
{
	//Save the nodes of each row to the last queue
	//NODE temp2;
	if (this->fin_node_deq.empty()) {
		this->fin_node_deq = this->temp_deq;
		this->temp_deq.clear();
	}
	else {
		temp2 = this->temp_deq.front();
		if (abs(temp2.x - m_top.x) > dis || abs(temp2.y - m_top.y) > dis) {
			this->m_top = temp2;
			if (!this->ang_point.empty()) {
				if (abs(this->ang_point.front().x - temp2.x) <= 16 ) {
					this->choose();
				}
			}
			while (!this->temp_deq.empty()) {
				this->fin_node_deq.push_back(this->temp_deq.front());
				this->temp_deq.pop_front();
			}
		}
		if (!this->ang_point.empty()) {
			cout << ang_point.size() << endl;*/
			if (abs(this->ang_point.front().x - temp2.x) <= 16 ) {
				this->choose();
			}
		}
// 		while (!this->temp_deq.empty()) {
// 			this->fin_node_deq.push_back(this->temp_deq.front());
// 			this->temp_deq.pop_front();
// 		}
		this->temp_deq.clear();
	}
}

node_simplify::~node_simplify()
{
	this->ori_node_deq.clear();
	this->fin_node_deq.clear();
	this->temp_deq.clear();
}

void node_simplify::ang_point_read()
{
	ifstream ifs;
	ifs.open(TEXT2, ios::in);
	deque<NODE> point_list;
	NODE P;

	while (!ifs.eof())
	{
		ifs >> P.y >> P.x;
		point_list.push_back(P);
	}
	ifs.close();
	cout << point_list.size() << endl;

	NODE p1, p2, p3;
	while (!point_list.empty()) {
		p1 = point_list.front();
		point_list.pop_front();
		p2 = point_list.front();
		point_list.pop_front();
		if (abs(p1.x - p2.x) <= 5 || abs(p1.y - p2.y) <= 5) {
			p3.y = (p1.y + p2.y) / 2;
			p3.x = (p1.x + p2.x) / 2;
			this->ang_point.push_back(p3);
		}
	}
	/*for (auto k: this->ang_point) {
	cout << k.x << " " << k.y << endl;
	}*/
}

void node_simplify::choose()
{
	this->m_ang_dis = 100;
	int dis;
	NODE temp = this->ang_point.front();
	for (auto t : this->temp_deq) {
		dis = abs(temp.x - t.x) + abs(temp.y - t.y);
		if (dis <= m_ang_dis) {
			m_ang_dis = dis;
			if (this->type_node.empty()) {
				this->type_node.push_back(t);
			}
			else {
				this->type_node.pop_back();
				this->type_node.push_back(t);
			}

		}

		if ((temp.x - this->temp_deq.front().x) < 0) {
			this->ang_point.pop_front();
			NODE zero;
			zero.x = 0;
			zero.y = 0;
			this->type_node.push_back(zero);
		}

	}
}

//void node_simplify::read()
//{
//	ifstream ifs;  
//	ifs.open(IMAGE3, ios::in); 
//	NODE P;
//
//	while (!ifs.eof())
//	{
//		ifs >>P.x>>P.y;
//		this->ori_node_deq.push_back(P);
//	}
//	ifs.close();
//}
