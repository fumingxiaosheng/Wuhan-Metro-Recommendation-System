#ifndef _GLOBAL_H_
#define _GLOBAL_H_
/*-------------------全局变量声明区-------------------------*/ 
	struct linex Line[7];//线路 
	struct stationx Sta[230];//站点 
	int Total_sta=0;//总站点数 
	int key[56][2];//记录可换乘站点序列号的检索表 
	float djs_time[58][58];//简化图的时间矩阵
	float djs_distance[58][58];//简化图的距离矩阵 
	int hour;//当下的小时数 
	float minute; //当下的分钟数 
	int start_hour;
	float start_minute;//刚开始的时刻 
	float ROUTE[6][9];//分别对应求解的四条路径,分别为0：可用与否 1：总时间 2：加权时间 3: 票价 4: 到达的时刻之时 5：到达的时刻之秒 6：总距离 
	int mannul_crowding[9][6];//用于手动设置的人流量的存储，分别为是否存储，线路号，起始时，起始分，结束时，结束分，拥挤度 
	int b1,b2,d1,d2;//起始点终点的具体位置 
	int order_of_start,order_of_finish;//起始点和终点的在矩阵中的序列号 
	int tolerance;//乘客的乘车容忍度 
	float max_time;//存储设置容忍度前所求取路径的大最大时间 
/*-------------------函数声明区域--------------------------*/
extern int read(void);
extern int optimization(void);
extern int add_points(int,int);
extern int Dijkstra(int,int,int,float (*)[58],int);
extern int set_crowding();
extern int update_djs_time();
extern int no_transfer(int,int);
extern void Create_File();
extern void registers();
extern int Input_login();
extern void reback();
#endif
