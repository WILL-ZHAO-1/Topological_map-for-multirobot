#pragma once
//Original image path
#define IMAGE "map/ee.png"
#define IMAGE3 "Creat/first_node.png"
#define IMAGE4 "Creat/final.png"
#define IMAGE5 "Creat/orignmap.png"
#define IMAGE6 "Creat/2map.png"
#define IMAGE7 "Creat/pmap.png"
#define IMAGE8 "Creat/edg.png"

//#define TEXXT "first_node.txt" //Node generated for the first time
#define TEXT1 "Creat/sim_node.txt" //Simplified node list
#define TEXT2 "Creat/ang_node.txt" //List of recognized corners
#define TEXT3 "Creat/tran_node.txt" 
//The origin of the map is the lower left corner, 
//the origin of image processing is the upper left corner,
//the coordinates after coordinate conversion

#define TEXT4 "Creat/match_node.txt"

//Node generation parameters
//Template size
#define ker_size 13
//Node simplification distance (a robot width 8 units (0.05m/pixel))
#define sim_dis 13
//Jump spawning node distance
#define Leap_dis 13

//Node matching parameters
#define rows_dis 15 
#define cols_dis 15 

//Topological map
//#define infinite 999




