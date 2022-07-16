#ifndef _EXSTA_H_
#define _EXSTA_H_
/*-------------------全局变量外部声明区-------------------------*/ 
	extern struct linex Line[7];//线路 
	extern struct stationx Sta[230];//站点 
	extern int Total_sta;//总站点数 
	extern int key[56][2];//记录可换乘站点序列号的检索表 
	extern float djs_time[58][58];//简化图的时间矩阵
	extern float djs_distance[58][58];//简化图的距离矩阵 
	extern int hour;//当下的小时数 
	extern float minute; //当下的分钟数 
	extern int start_hour;
	extern float start_minute;//刚开始的时刻 
	extern float ROUTE[6][9];////分别对应求解的四条路径,分别为0：可用与否 1：总时间 2：加权时间 3: 票价 4: 到达的时刻之时 5：到达的时刻之秒 6：总距离 
	extern int mannul_crowding[8][6];//用于手动设置的人流量的存储，分别为是否存储，线路号，起始时，起始分，结束时，结束分，拥挤度 
	extern int b1,b2,d1,d2;//起始点终点的序列号
	extern int order_of_start,order_of_finish;//起始点和终点的在矩阵中的序列号
	extern int tolerance;//乘客的乘车容忍度 
	extern float max_time;//存储设置容忍度前所求取路径的大最大时间 
#endif
