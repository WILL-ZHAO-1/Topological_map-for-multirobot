#pragma once
//原始图像路径
#define IMAGE "map/ee.png"
#define IMAGE3 "Creat/first_node.png"
#define IMAGE4 "Creat/final.png"
#define IMAGE5 "Creat/orignmap.png"
#define IMAGE6 "Creat/2map.png"
#define IMAGE7 "Creat/pmap.png"
#define IMAGE8 "Creat/edg.png"

//#define TEXXT "first_node.txt" //第一次生成的节点
#define TEXT1 "Creat/sim_node.txt" //简化后的节点列表
#define TEXT2 "Creat/ang_node.txt" //识别出来的角点列表
#define TEXT3 "Creat/tran_node.txt" //地图的原点是左下角，图像处理的原点是左上角，坐标转换后的坐标

#define TEXT4 "Creat/match_node.txt"

//节点生成参数
//模板大小
#define ker_size 13
//节点简化距离(一个机器人宽度8个单位（0.05m/像素）)
#define sim_dis 13
//跳跃生成节点距离
#define Leap_dis 13

//节点匹配参数
#define rows_dis 15 //行距
#define cols_dis 15 //列距

////拓扑地图
//#define infinite 999




