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

//模板变量
const int ks = ker_size;
const int kr = (ker_size - 1) / 2;
const int leap_dis = Leap_dis;
//图像处理
class node_generate
{
public:
	//初始化读取图像
	node_generate(string path);

	//图像处理
	void image_processing();

	//图片边缘修整
	void Edge_trimming(Mat &m);
	void trimming(int r, int val, Mat &m);

	//遍历领域节点
	int traverse_node(int a, int b);

	//节点生成
	deque<NODE> generate_node();

	//修补节点
	//void fill_node();
	//int fill_match(int a,int b);

	//角点检测
	void ang_point();
	//角点匹配
	int match_ang_point(int a, int b);

	//显示节点状态
	void result();

	//第一次生成节点写入文本
	//void write(deque<NODE> &n);


	//原始图像保存
	Mat ori_map;
	//处理后的图像
	Mat node_map;
	Mat node_map2;
	//图像尺寸
	int m_row, m_cols;//(行，列）
	//修补边后的初始行
	int first;
	//节点生成模板
	int kernel[ks][ks] = { 0 };
	//角点检测模板
	int k_point[3][3] = { 0 };
	//角点坐标列表
	deque<NODE> point_list;
};