#ifndef _DFSTRUCT_H_
#define _DFSTRUCT_H_
/*------------------------------结构体的定义----------------------------*/ 
typedef struct The_users   //typedef 可以定义结构体别名
{
    char id[11]; //账号 
    char pwd[20]; //密码 
    char name[15];//姓名为字符串 
    char sex; //性别为单个字符
	long phone; //电话号码为长整型 
}users; 
struct linex{
	int num_of_line;//标识线路序号 
	int ful_cap;//标识满员人数
	float total_line_len;//线路总长度 
	float ava_len;//每一路段的平均长度 
	int nums_of_sta;//站点数目 
	int start;//标记该条线路在站点数组开始的位置
	int start_of_trans;//标识该条线路第一个换乘点在检索表开始的位置 
	float cro_del;//表示该线路的拥挤程度，若该路段的拥挤程度超过容忍程度，则设置为1000,否则为1 
};
struct stationx{
	int num_of_line;int num_of_sta;
	char name[100];//站点的标识，线路号，名称； 
	int exc;//是否换乘站点，若是，则为1.否则为0
	int a_start_hour;float a_start_minute;//正向列车首次到达时间；
	int b_start_hour;float b_start_minute;//反向列车首次到达时间 
	int a_finish_hour;float a_finish_minute;//正向列车最后一次到达时间；
	int b_finish_hour;float b_finish_minute;//反向列车最后一次到达时间
	int a_arrive_hour;float a_arrive_minute;//正向即将到达的时间； 
	int a_leave_hour;float a_leave_minute;//正向列车的离站时间； 
	int b_arrive_hour;float b_arrive_minute;//反向即将到达的时间； 
	int b_leave_hour;float b_leave_minute;//反向列车的离站时间；
	struct roadx* road_f;//指向当前的第一条路段
	struct roadx* road_l;//指向当前的最后一条路段
};
 struct roadx{	
	int num_of_line;int num_of_sta;//弧头的序列号  
	float tra_time;//表示的是在该路段的乘车时间
	float distance;//表示该路段的长度，若是环线的话，则长度为0 	
	struct roadx* road_n;//指向下一路段 
};
#endif
