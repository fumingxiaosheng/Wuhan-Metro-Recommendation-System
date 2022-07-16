/*----------------------------------------------头文件区-------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"


/*----------------------------------------函数区，主要包括add_points函数-------------------------------------------*/ 
/*加点函数，简化图中加入某点(m,n)，若该点不在图中，则加入至order处，并返回1，否则返回0。输入为待加入点的线路号和序号，处理结果为改变了优化矩阵*/
int add_points(int m,int n){ 
		int start,finish,i,j,order;//start表示起点，finish表示终点,i用来计数器,j用作记录相邻间的站点数,order表示添加的位置； 
		/*确定需要处理的矩阵范围*/ 
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
		for(i=start;(i<=finish)&&(key[i][1]<n);i++);//确定该点在地铁线上的相对位置 
		/*1.不需要添加结点，直接返回*/
		if(key[i][1]==n) return i; 
		/*2.需要添加结点，先确定要添加的位置和平均路段长度distance*/
		order=56;
		float distance; 
		for(j=0;j<58;j++){
			if(djs_time[56][j]!=1000){//若序号56以被添加，则设序号为57 
				order=57;
				break;
			}
		}
		if(m<5) distance=Line[m-1].ava_len;
		else distance=Line[m-2].ava_len;
		/*(1)若在地铁线头*/ 
		if(i==start){
			j=key[i][1]-n;
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		/*(2)若在地铁线尾*/
		else if(i==finish+1){
			i=finish;
			j=n-key[i][1];
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		/*(3)在地铁线中,处在i-1和i之间*/
		else{ 
			/*打断i-1和i之间的联系*/ 
			djs_time[i][i-1]=1000;
			djs_time[i-1][i]=1000;
			djs_distance[i][i-1]=1000;
			djs_distance[i-1][i]=1000;
			/*构建i-1和order之间的联系*/
			j=n-key[i-1][1];
			djs_time[i-1][order]=2*j;
			djs_time[order][i-1]=2*j;
			djs_distance[i-1][order]=j*distance;
			djs_distance[order][i-1]=j*distance; 
			/*构建i和order之间的联系*/
			j=key[i][1]-n;
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		return order;
}

