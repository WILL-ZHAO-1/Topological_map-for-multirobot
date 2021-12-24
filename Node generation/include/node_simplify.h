#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include <deque>
#include <string>
#include "globa.h"
#include "data_struct.h"

using namespace std;
using namespace cv;

const int dis = sim_dis;

class node_simplify
{
public:
	node_simplify(deque<NODE> &n);
	//对每行节点稀疏化
	void Simplify ();
	//将每行稀疏后的节点放入最终队列(可增加每列节点的稀疏化)
	void deque_full();

	//读取第一次节点队列
	//void read();

	//角点读取
	void ang_point_read();
	//节点匹配
	void choose();

	~node_simplify();


	//判断头节点
	NODE m_top;
	//距离判断
	int m_dis;
	//原始节点队列
	deque<NODE> ori_node_deq;
	//简化后的节点队列
	deque<NODE> fin_node_deq;
	//临时队列
	deque<NODE> temp_deq;

	//与角点判断有关
	//距离判断
	int m_ang_dis;
	//角点列表
	deque<NODE> ang_point;
	//特征节点列表
	deque<NODE> type_node;
};