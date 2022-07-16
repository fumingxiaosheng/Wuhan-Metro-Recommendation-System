/*---------------------------------------------头文件区-----------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------------函数声明区------------------------------------------------------*/
extern int ca_crowding(int);


/*----------------------函数区，主要包括set_crowding,update_djs_time函数------------------------------------*/ 
/*该函数实现相关线路的避开的功能，主要思路如下：根据前面求解的道路，获得一个最大的乘车时间，从起始时刻开始，动态模拟
线路拥挤度的变化，若超过容忍度，通过设置其cro_del实现避开这条路。执行该函数的结果为调整Line数组中每条线路的cro_del*/ 
int set_crowding(void){
	//先进行初始化 
	hour=start_hour;
	minute=start_minute;
	int timing;//每十分钟进行一次时间的更新
	int Line_crowding;
	int i,j;
	/*先进行cro_del的初始化*/ 
	for(i=0;i<7;i++){
		Line[i].cro_del=1;
	} 
	for(timing=0;timing<=max_time;timing+=10){
		//下面进行时间的更新
		if(minute>=50){
			hour++;
			minute=minute+10-60;
		}
		else minute+=10;
		//下面进行每一条线路Line.cro_del的设置，若超过，则直接设置为1000，即打断这条路
		for(i=0;i<=3;i++){
			Line_crowding=ca_crowding(i+1);
			if(Line_crowding>tolerance) Line[i].cro_del=1000;
		}
		for(i=4;i<=6;i++){
			Line_crowding=ca_crowding(i+2);
			if(Line_crowding>tolerance) Line[i].cro_del=1000;
		} 
	}
	return 1; 
}


/*该函数根据更新后的Line数组中的cro_del实现对时间矩阵的更新*/ 
int update_djs_time(void){
	int i,j;//用作对于时间矩阵操作的坐标
	int m,n;//代表序列号为i对应的站点位置 
	
	/*------对56*56的初始矩阵进行设置------*/ 
	for(i=0;i<56;i++){
		m=key[i][0];
		n=key[i][1];
		int start,finish;
		float time_factor;//该站点所在线路的拥挤程度 
		/*设置需要修改的大致范围*/ 
		if(m<5&&m!=4) start=Line[m-1].start_of_trans;
		else start=Line[m-2].start_of_trans;
		if(m<4&&m!=4) finish=Line[m].start_of_trans-1;
		else finish=Line[m-1].start_of_trans-1;
		if(m==4){
			start=25;
			finish=30;
		}
		if(m==8){
			start=49;
			finish=55;
		} 
		/*设置乘车因子*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*对56*56的矩阵进行修改*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[i][j]!=4 && djs_time[i][j]!=1000) djs_time[i][j]=djs_time[i][j]*time_factor;//考虑不是换乘的情况 
		}
		} 
		
		
		/*------对起点进行修改------*/
		if(order_of_start==56 || order_of_start==57){
		m=b1;
		n=b2;
		int start,finish;
		float time_factor;//该站点所在线路的拥挤程度 
		/*设置需要修改的大致范围*/ 
		if(m<5&&m!=4) start=Line[m-1].start_of_trans;
		else start=Line[m-2].start_of_trans;
		if(m<4&&m!=4) finish=Line[m].start_of_trans-1;
		else finish=Line[m-1].start_of_trans-1;
		if(m==4){
			start=25;
			finish=30;
		}
		if(m==8){
			start=49;
			finish=55;
		} 
		/*设置乘车因子*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*对56*56的矩阵进行修改*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[order_of_start][j]!=4 && djs_time[order_of_start][j]!=1000) {
				//考虑不是换乘的情况，注意转置矩阵的设置 
				djs_time[order_of_start][j]=djs_time[order_of_start][j]*time_factor;
				djs_time[j][order_of_start]=djs_time[j][order_of_start]*time_factor;
			}
		}
	} 
	
	
	
	/*------对终点进行修改------*/
	if(order_of_finish==56 || order_of_finish==57){
		m=b1;
		n=b2;
		int start,finish;
		float time_factor;//该站点所在线路的拥挤程度 
		/*设置需要修改的大致范围*/ 
		if(m<5&&m!=4) start=Line[m-1].start_of_trans;
		else start=Line[m-2].start_of_trans;
		if(m<4&&m!=4) finish=Line[m].start_of_trans-1;
		else finish=Line[m-1].start_of_trans-1;
		if(m==4){
			start=25;
			finish=30;
		}
		if(m==8){
			start=49;
			finish=55;
		} 
		/*设置乘车因子*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*对56*56的矩阵进行修改*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[order_of_start][j]!=4 && djs_time[order_of_start][j]!=1000) {
				//考虑不是换乘的情况，注意转置矩阵的设置 
				djs_time[order_of_finish][j]=djs_time[order_of_finish][j]*time_factor;
				djs_time[j][order_of_finish]=djs_time[j][order_of_finish]*time_factor;
			}
		}
	}
	
	return 1;//设置成功返回值为1 
}

 
