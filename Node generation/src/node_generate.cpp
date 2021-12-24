#include "globa.h"
#include "node_generate.h"

node_generate::node_generate(string path)
{
	//初始化结构体元素
	for (int i = 0; i < ks; ++i) {
		for (int j = 0; j < ks; ++j) {
			this->kernel[i][j] = 255;
		}
	}
	//读取图像
	this->ori_map = imread(path, 0);
	//获取图像长款
	this->m_row = this->ori_map.rows;
	this->m_cols = this->ori_map.cols;
	cout << this->m_row << " " << this->m_cols << endl;

	cv::imwrite(IMAGE5, this->ori_map);
	//cv::namedWindow("map", CV_WINDOW_NORMAL);
	//imshow("map", this->ori_map);
	//waitKey(0);
	this->image_processing();
}

void node_generate::image_processing()
{
	//储存二值化图片
	Mat bin_map;
	//储存膨胀后的图片
	Mat dil_map;
	//Mat dil_map2;
	//Mat dil_map3;

	//图片二值化处理
	cv::threshold(this->ori_map, bin_map, 200, 255, THRESH_BINARY);
	cv::imwrite(IMAGE6, bin_map);
	//膨胀和腐蚀的模板
	Mat element = cv::getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Mat element2 = cv::getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	//膨胀操作(是针对大的像素值的，对于地图就是白色区域是膨胀的)对于黑的部分来说像腐蚀
	dilate(bin_map, dil_map, element);
	//腐蚀操作，对于黑的来说像膨胀操作
	//erode(dil_map, dil_map2, element);
	//dilate(dil_map2, dil_map3, element);
	erode(dil_map, this->node_map, element);

	cv::imwrite(IMAGE7, this->node_map);
	//修补图像的四周
	//this->Edge_trimming(node_map);
	//cv::imwrite(IMAGE8, this->node_map);
	//拷贝一份地图
	this->node_map2 = this->node_map.clone();

	//显示图像
	//cv::namedWindow("map2", CV_WINDOW_NORMAL);
	//imshow("map2", bin_map);
	//cv::namedWindow("map3", CV_WINDOW_NORMAL);
	//imshow("map3", dil_map);
	//cv::namedWindow("map", CV_WINDOW_NORMAL);
	//imshow("map", node_map);
	//waitKey(0);

}

void node_generate::Edge_trimming(Mat &m)
{
	int count1;
	int count2;
	//上边修整，遇到自由区域结束
	int row = 0;
	while (true) {
		count1 = 0;
		count2 = 0;
		for (int j = 0; j < this->m_cols; ++j)
		{
			if (m.at<uchar>(row, j) == 255) {
				//白色个数
				count1++;
			}
			if (m.at<uchar>(row + 1, j) == 255) {
				//白色个数
				count2++;
			}
		}
		if (count1 >0 && count1 == count2) {
			//cout << row;
			this->first = row;
			break;
		}
		else if (count1>0) {
			this->trimming(row, 0, m);
		}
		row++;
	}

	//下边修整
	row = this->m_row - 1;
	while (true) {
		count1 = 0;
		count2 = 0;
		for (int i = 0; i < this->m_cols; ++i)
		{
			if (m.at<uchar>(row, i) == 255) {
				//白色个数
				count1++;
			}
			if (m.at<uchar>(row - 1, i) == 255) {
				//白色个数
				count2++;
			}
		}
		if (count1 >0 && count1 == count2) {
			//cout << row;
			break;
		}
		else if (count1>0) {
			this->trimming(row, 0, m);
		}
		row--;
	}
	//左边修整
	int cols = 0;
	while (true) {
		count1 = 0;
		count2 = 0;
		for (int k = 0; k < this->m_row; ++k)
		{
			if (m.at<uchar>(k, cols) == 255) {
				//白色个数
				count1++;
			}
			if (m.at<uchar>(k, cols+1) == 255) {
				//白色个数
				count2++;
			}
		}
		if (count1 >0 && count1 == count2) {
			//cout << row;
			break;
		}
		else if (count1>0) {
			this->trimming(-cols, 0, m);
		}
		cols++;
	}

	//右边修整
	cols = this->m_cols-1;
	while (true) {
		count1 = 0;
		count2 = 0;
		for (int g = 0; g < this->m_row; ++g)
		{
			if (m.at<uchar>(g, cols) == 255) {
				//白色个数
				count1++;
			}
			if (m.at<uchar>(g, cols - 1) == 255) {
				//白色个数
				count2++;
			}
		}
		if (count1 >0 && count1 == count2) {
			//cout << row;
			break;
		}
		else if (count1>0) {
			this->trimming(-cols, 0, m);
		}
		cols--;
	}

}

void node_generate::trimming(int r, int val, Mat &m)
{
	if (r >= 0) {
		for (int i = 0; i < this->m_cols; ++i) {
			m.at<uchar>(r, i) = val;
		}
	}
	else {
		r = 0 - r;
		for (int j = 0; j < this->m_row; ++j) {
			m.at<uchar>(j, r) = val;
		}
	}


}

int node_generate::traverse_node(int a, int b)
{
	//该点的匹配结果
	int R = 0;
	int y = a - kr;
	int x = b - kr;
	//遍历结构体元素，计算匹配度
	for (int i = 0; i < ks; ++i) {
		for (int j = 0; j < ks; ++j) {
			R = R + (this->kernel[i][j] - this->node_map.at<uchar>(y + i, x + j));
		}
	}
	return R;
}

deque<NODE> node_generate::generate_node()
{
	//创建节点保存队列、节点
	deque<NODE> temp;
	NODE p;
	//遍历所有像素(增加跳跃)
	for (int i = this->first + kr; i < leap_dis*(this->m_row / leap_dis); i += leap_dis) {
		for (int j = kr; j < this->m_cols - kr; ++j) {
			int r = this->traverse_node(i, j);
			if (r == 0) {
				this->node_map.at<uchar>(i, j) = r;
				p.y = i;
				p.x = j;
				temp.push_back(p);
			}
		}
	}

	//遍历所有像素，没有跳跃
	/*for (int k = kr; k < this->m_row-kr; ++k) {
	for (int g = kr; g < this->m_cols - kr; ++g) {
	int r = this->match(k, g);
	if (r == 0) {
	this->node_map.at<uchar>(k, g) = r;
	}
	}
	}*/

	////生成的节点队列个数
	//cout << "生成的节点个数: ";
	//cout << temp.size() << endl;

	//显示节点生成结果
	/*cv::namedWindow("map4", CV_WINDOW_NORMAL);
	imshow("map4", node_map);
	waitKey(0);*/

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //PNG格式图片的压缩级别  
	compression_params.push_back(9);  //这里设置保存的图像质量级别

	//保存图像
	cv::imwrite(IMAGE3, this->node_map, compression_params);
	////节点写入文本
	//this->write(temp);
	return temp;
}

void node_generate::result()
{
	ifstream ifs;
	ifs.open(TEXT1, ios::in);
	NODE P;
	deque<NODE> temp;
	int tem;
	while (!ifs.eof())
	{
		ifs >> tem >> P.x >> P.y;
		temp.push_back(P);
	}
	ifs.close();

	for (auto k : temp) {
		this->node_map2.at<uchar>(k.x, k.y) = 0;
	}

	////简化后写入节点
	int t = this->m_row;
	ofstream ofs;
	ofs.open(TEXT3, ios::out);
	int i = 0;
	for (auto w : temp) {
		ofs <<i<<" "<< t - w.x << " " << w.y << endl;
		i++;
	}
	ofs.close();
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //PNG格式图片的压缩级别  
	compression_params.push_back(9);  //这里设置保存的图像质量级别
	cv::imwrite(IMAGE4, this->node_map2, compression_params);

	cv::namedWindow("map4", CV_WINDOW_NORMAL);
	imshow("map4", node_map2);
	waitKey(0);
}

//角点检测
void node_generate::ang_point()
{
	//初始化模板元素
	this->k_point[0][0] = 1;
	this->k_point[0][2] = 1;
	this->k_point[1][1] = -5;
	this->k_point[2][0] = 1;
	this->k_point[2][2] = 1;

	int N;
	NODE temp;
	deque<NODE> point_list;
	//遍历图像元素
	for (int i = 1; i < this->m_row - 1; i++) {
		for (int j = 1; j < this->m_cols - 1; j++) {
			N = this->match_ang_point(i, j);
			if (N == 765) {
				temp.y = i;
				temp.x = j;
				point_list.push_back(temp);
			}
		}
	}

	//输出坐标点列表
	/*cout << this->point_list.size() << "对" << endl;
	for (auto g : this->point_list) {
	cout << g.x << "," << g.y << endl;
	}*/

	ofstream ofs;
	ofs.open(TEXT2, ios::out);
	for (auto w : point_list) {
		ofs << w.y << " " << w.x << endl;
	}
	ofs.close();

}

int node_generate::match_ang_point(int a, int b)
{
	int n = 0;
	int y = a - 1;
	int x = b - 1;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			n = n + k_point[i][j] * this->node_map.at<uchar>(y + i, x + j);
		}
	}
	return n;
}

//void Image::write(deque<NODE> &n)
//{
//	ofstream ofs;
//	ofs.open(TEXXT, ios::out);
//	for (auto w : n) {
//		ofs << w.x << " " << w.y << endl;
//	}
//	ofs.close();
//}



