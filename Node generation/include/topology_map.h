#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include "globa.h"
#include "data_struct.h"

using namespace std;
const int MAX = 56; //定点个数
//定义矩阵图数据结构
class Graph {
public:
	Graph();
	//初始化邻接矩阵
	void initial();
	//建立边关系
	void creat_arc();
	float calculate_weight(graph_node &g1, graph_node &g2);
	//删除边
	void delete_arc(int a, int b);
	//读取边集
	void read();
	void print();
	//最短路径算法
	void short_path(int s, int f);
	//启发式算法
	void Heuristically_path(int s, int f);
	//计算前进代价值
	float calculate_forwardcost(int s, int n);

	//定点表
	//vector<graph_node> 
	//邻接矩阵
	float m_matrix[MAX][MAX];
	//顶点表
	vector<graph_node> m_vertable;
	multimap<graph_node, graph_node, Cmp> arc_set;
};