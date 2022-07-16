/*--------------------------------------------文件区-----------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"


/*------------------------------------------函数声明区---------------------------------------------------*/ 
int locate_transfer(int m,int n); 



/*----------------------------函数区，主要包括optimization和locate_transfer函数--------------------------*/ 

/*构建武汉地铁优化图函数*/ 
int optimization(){
	int i,j;//计数器 
/*构建可换乘站点检索表*/
FILE *fp;
if ((fp = fopen("tdata3.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0;
    }
for(i=0;i<56;i++){
	fscanf(fp,"%d %d",&(key[i][0]),&(key[i][1]));
}
/*时间矩阵和距离矩阵的初始化*/ 
for(i=0;i<58;i++){
	for(j=0;j<58;j++){
	djs_time[i][j]=1000;
	djs_distance[i][j]=1000;
	}
}
/*时间矩阵和距离矩阵的进一步设置*/
for(i=0;i<56;i++){ 
	 /*先处理相邻的结点*/
	 //i用来计数，j为两站之间的路段数
	 if(i==0){//点位于第一个 
	 	j=key[1][1]-key[0][1];
	 	djs_time[0][1]=3*j;
	 	djs_distance[0][1]=j*Line[0].ava_len;
	 }
	 else if(i==55){//点位于最后一个 
	 	j=key[55][1]-key[54][1];
	 	djs_time[55][54]=3*j;
	 	djs_distance[55][54]=j*Line[6].ava_len;
	 }
	 else{//点位于中间 
	 	if(key[i][0]==key[i-1][0]){
	 		j=key[i][1]-key[i-1][1];
	 		djs_time[i][i-1]=3*j;
	 		if(key[i][0]<5) djs_distance[i][i-1]=j*Line[(key[i][0]-1)].ava_len;
	 		else djs_distance[i][i-1]=j*Line[(key[i][0]-2)].ava_len;
		 }
		 if(key[i][0]==key[i+1][0]){
		 	j=key[i+1][1]-key[i][1];
	 		djs_time[i][i+1]=3*j;
	 		if(key[i][0]<5) djs_distance[i][i+1]=j*Line[(key[i][0]-1)].ava_len;
	 		else djs_distance[i][i+1]=j*Line[(key[i][0]-2)].ava_len;
		 } 
	 }
	 /*再处理换乘点的连接*/ 
	 int total_sta;
	 if(key[i][0]<5) total_sta=Line[(key[i][0]-1)].start+key[i][1]-1;
	 else total_sta=Line[(key[i][0]-2)].start+key[i][1]-1;
	 struct roadx* tran_next;
	 tran_next=Sta[total_sta].road_f;
	 while(tran_next->num_of_line==key[i][0]) tran_next=tran_next->road_n;
	 while(tran_next){
	 	int m,n,t;
	 	m=tran_next->num_of_line;
	 	n=tran_next->num_of_sta;
	 	t=locate_transfer(m,n);
	 	djs_time[i][t]=4;
	 	djs_distance[i][t]=0;
	 	tran_next=tran_next->road_n;//进一步移动指针 
	 }
}
	return 1;
}

/*确定换乘点在检索数组中的位置函数，输入为待寻找的站点的线路号和序号，输出为其在检索数组中的序号*/ 
int locate_transfer(int m,int n){
	int start;
	if(m<5) start=Line[m-1].start_of_trans;
	else start=Line[m-2].start_of_trans;
	while(key[start][1]!=n) start++;
	return start;
}




	
