/*-------------------------------------------文件区-------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h" 

/*------------------------------------------函数声明区----------------------------------------------*/ 
float ca_distance(int (*)[3]);
int ca_crowding(int);
int ca_time(FILE *,int (*)[3]);
int ca_price(float);
extern int locate_station(int,int);
extern int set_time_of_station(int);

/*-------------------------------------本c文件的全局变量区------------------------------------------*/ 
int nums_of_route;//存储求得路径的站点数  
float total_crowding;//计算拥挤总加权 
float mental_time;//总的加权时间 


/*--------------函数区，主要包括Dijkstra、ca_distance、ca_crowding、ca_time和ca_price函数------------*/ 

/*求解短路函数，输入为待处理的数组的维数，起始点和终点在数组中的位置，待处理的数组，表示是否需要考虑容忍度的标记*/ 
int Dijkstra(int dimension,int order_of_start,int order_of_finish,float (*djs)[58],int fre){
	/*---对二维数组djs进行操作，求解序号为order_of_start到序号为order_of_finish的点的第一条最短路径---*/
	float distance[58]={0};//存储最短距离
	int pre[58]={0};//存储前一个顶点
	int mark[58]={0};//若找到最短路径，则为1，否则为0；
	int i,j;//计数器 
	/*初始化变量*/
	for(i=0;i<dimension;i++){
		distance[i]=djs[order_of_start][i];
		pre[i]=order_of_start;
		mark[i]=0;
	}
	mark[order_of_start]=1;
	/*进行求解*/ 
	int min_num,min_key=1;//标识当前找到最短路径的点,min_key用于开关 
	for(i=1;i<dimension;i++){
		/*找到当前最短路径的点序号为min_num*/ 
		min_key=1;
		for(j=0;j<dimension;j++){
			if(mark[j]==0&&min_key){
				min_num=j;//找到第一个未找到最短路的点
				min_key=0;
			}
			if(mark[j]==0&&(!min_key)&&(distance[j]<distance[min_num])) min_num=j;
		}
		/*标记min_num所代表的点，并更新distance数组*/
		mark[min_num]=1;
		for(j=0;j<dimension;j++){
			if(mark[j]==0&&(distance[j]>distance[min_num]+djs[min_num][j])){
				distance[j]=distance[min_num]+djs[min_num][j];
				pre[j]=min_num;
			}
		}
   }

	/*反向存储所求得的路径*/
	int route1[100][3];//存储求得的路径，第一个代表的是在时间、距离矩阵中的序列号，后面代表的是站点号
	j=0;
	route1[j][0]=order_of_finish;
	route1[j][1]=d1;
	route1[j][2]=d2;
	i=pre[order_of_finish];
	for(j=1;i!=order_of_start;j++){
		route1[j][0]=i;
		route1[j][1]=key[i][0];
		route1[j][2]=key[i][1];
		i=pre[i];	
	}
	route1[j][0]=order_of_start;
	route1[j][1]=b1;
	route1[j][2]=b2;
	nums_of_route=j;
	 
	/*使用一个文件存储路径,注意应先进行文件的清空，并判断使用哪一个文件。判断在数组中的位置*/
	int R;//标记所需要存储的路线信息在数组中的位置 
	if(fre==2) R=4;
	else if(djs==djs_time) R=0;
	else R=2;
	FILE *fp;
	if(fre==2){
		fopen("tdata8.txt", "w");
		fp=fopen("tdata8.txt", "r+"); 
	}
	else if(djs==djs_time){
		fopen("tdata4.txt", "w");
		fp=fopen("tdata4.txt", "r+"); 
	}
	else{
		fopen("tdata6.txt", "w");
		fp=fopen("tdata6.txt", "r+");
	}
	
	/*对相关路线的计算*/ 
	float route_distance;//路线的长度 
	int route_price;//票价
	float route_time;//路线的时间 
	route_distance=ca_distance(route1);
	if(route_distance>999){
		ROUTE[R][0]=0;
		return 0;	
		}
	route_price=ca_price(route_distance);
	hour=start_hour;
	minute=start_minute;
//刚刚逃走的位置 
	if(ca_time(fp,route1)==0) {//不符合拥挤度的要求和时间要求时 
		ROUTE[R][0]=0;
	}
	else{
	route_time=(hour-start_hour-1)*60+minute+60-start_minute;
	/*if(hour>=23&&minute>0 || hour>=24) {//超出了时间范围 
		ROUTE[R][0]=0;
		return 0;
	} */ 
	//else {//符合要求并对相应的路线赋予相应的值 
		ROUTE[R][0]=1;
		ROUTE[R][1]=route_time;
		ROUTE[R][2]=mental_time;
		ROUTE[R][3]=route_price;
		ROUTE[R][4]=hour;
		ROUTE[R][5]=minute;
		ROUTE[R][6]=total_crowding;
		ROUTE[R][7]=route_distance;
		fclose(fp);
//	}
}



	/*------下面处理第二条路径------*/
	/*判断需要哪一个文件和数组中的哪一个位置*/ 
	if(fre==2){
		fopen("tdata9.txt", "w");
		fp=fopen("tdata9.txt", "r+"); 
	}
	else if(djs==djs_time){
		fopen("tdata5.txt", "w");
		fp=fopen("tdata5.txt", "r+");
	}
	else{
		fopen("tdata7.txt", "w");
		fp=fopen("tdata7.txt", "r+"); 
	}
	if(fre==2) R=5;
	else if(djs==djs_time) R=1;
	else R=3;
	
	/*第二条线路的求解*/ 
	int pre2[200];
	float distance2[200]; 
	for(i=nums_of_route-1;i>=0;i--){
		int order=route1[i][0];//order代表的是该点在数组中的位置 
		pre2[i]=1;
		distance2[i]=10000;
		for(j=0;j<dimension;){
			if(distance2[i]>djs[j][order]+distance[j] && j!=pre[order]){
				//下面进行环路的判断
				//现在找到了一个结点j，判断j前面的所有前驱系欸但是否含有order，有的话，直接退出
				int sp=pre[j];
				while(sp!=order_of_start){
					if(sp==order){
						goto restart;
					}
					sp=pre[sp];
				} 
				distance2[i]=djs[j][order]+distance[j];
				pre2[i]=j;
			}
			restart:j++;
		}
		j=pre[order];
		if(i<nums_of_route-1 && distance2[i]>djs[j][order]+distance2[i+1]){
				distance2[i]=djs[j][order]+distance2[i+1];
				pre2[i]=i+1+58;
		}
	}
	if(distance2[0]>1000){
		ROUTE[R][0]=0;
		return 0;
	}
	
	/*反向存储第二条道路*/ 
	else{
	int route2[100][3];//存储求得的路径，第一个代表的是在时间、距离矩阵中的序列号，后面代表的是站点号;
	j=0;
	route2[j][0]=order_of_finish;
	route2[j][1]=d1;
	route2[j][2]=d2;
	i=pre2[0];
	for(j=1;i!=order_of_start;j++){
		if(i>57){
			route2[j][0]=route1[i-58][0];
			route2[j][1]=route1[i-58][1];
			route2[j][2]=route1[i-58][2];
			i=pre2[i-58];
		}
		else{
			route2[j][0]=i;
			route2[j][1]=key[i][0];
			route2[j][2]=key[i][1];
			i=pre[i];
		}	
	}
	route2[j][0]=order_of_start;
	route2[j][1]=b1;
	route2[j][2]=b2;
	nums_of_route=j;
	/*线路相关信息的计算*/
	route_distance=ca_distance(route2);
	route_price=ca_price(route_distance); 
	hour=start_hour;
	minute=start_minute;
	if(ca_time(fp,route2)==0){//不符合拥挤度的要求 
	ROUTE[R][0]=0;
	}
	else{
	route_time=(hour-start_hour-1)*60+minute+60-start_minute;
/*	if(hour>=23&&minute>0 || hour>=24) {
		ROUTE[R][0]=0;//不符合时间的要求 
		return 0;
	} */ 
//	else {//进行换线结果的存储 
		ROUTE[R][0]=1;
		ROUTE[R][1]=route_time;
		ROUTE[R][2]=mental_time;
		ROUTE[R][3]=route_price;
		ROUTE[R][4]=hour;
		ROUTE[R][5]=minute;
		ROUTE[R][6]=total_crowding;
		ROUTE[R][7]=route_distance;
		fclose(fp);
//	}
}
}
	return 1;
}

/*求解距离函数，根据存储反向路径的route数组求解路径的距离。输入为路径数组，输出为路径距离*/
float ca_distance(int (*route)[3]){
	int i,j;//用来指示路段在djs_diatance数组中的位置 
	int m;//m用来计数 
	float route_distance=0;
	for(m=nums_of_route;m>=1;m--){
		i=route[m][0];
		j=route[m-1][0];
		route_distance+=djs_distance[i][j];
	}
	return route_distance;
} 
 
/*求解票价函数，输入为距离，输出为票价*/
int ca_price(float distance){
	int price;
	if (distance <= 4)price = 2;
	else if (distance <= 8)price = 3;
	else if (distance <= 12)price = 4;
	else if (distance <= 18)price = 5;
	else if (distance <= 24)price = 6;
	else if (distance <= 32)price = 7;
	else if (distance <= 40)price = 8;
	else if (distance <= 50)price = 9;
	else {
		price = 9;
		float dis = distance - 50;
		while (dis > 0) {
			dis -= 20;
			price++;
		}
	}
	return price;
}

/*计算时间函数，动态更新时间，模拟乘车情况。输入为待写入的文件指针，路径数组；执行该函数的结果为将路径写入文件、路径中
每一个站点拥挤度的获得，加权时间的获得，加权拥挤度的获得。若该路径在动态模拟过程中出现超过最大容忍度的情况，则该函数
将废除该条路径*/ 
int ca_time(FILE *fp,int (*route)[3]){
	int i,j,total_sta,m1,n1,m2,n2,key=1;//key是用来控制转乘站点的输出的 
	total_crowding=0;
	mental_time=0;
	int C=0;//用来计算加了几个拥挤度的 
	int cro;//实时记录每一个路段的拥挤度 
	for(i=nums_of_route;i>=1;i--){
		m1=route[i][1];
		n1=route[i][2];
		total_sta=locate_station(m1,n1);//m1,n1标志着当前的站点号,total_sta表示其在数组中的位置 
		if(key) {
			fprintf(fp,"%s",Sta[total_sta].name);
		}
		m2=route[i-1][1];
		n2=route[i-1][2];
		
		/*-----------------------------------两个站点都在同一条线路且正向行驶---------------------------------------*/ 
		if(m1==m2 && n2>n1){
			set_time_of_station(total_sta);
			if((hour==Sta[total_sta].a_finish_hour && minute>Sta[total_sta].a_finish_minute) || hour>Sta[total_sta].a_finish_hour) {
				return 0;
			}
			//根据到站时间来更新离站时间 
			if(hour==Sta[total_sta].a_leave_hour) mental_time+=(Sta[total_sta].a_leave_minute-minute);
			else mental_time+=(Sta[total_sta].a_leave_minute+60-minute);
			hour=Sta[total_sta].a_leave_hour;
			minute=Sta[total_sta].a_leave_minute;
			cro=ca_crowding(m1); 
			fprintf(fp,"(拥挤度为%d %)\n",cro);
			if(cro>tolerance) return 0;//若超过最大容忍度，则作废该条路径 
			C++;
			total_crowding+=(float)cro;
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		for(j=n1+1;j<=n2-1;j++){
			total_sta=locate_station(m1,j);
			if((hour==Sta[total_sta].a_finish_hour && minute>Sta[total_sta].a_finish_minute) || hour>Sta[total_sta].a_finish_hour) {
				return 0;
			}
			fprintf(fp,"%s",Sta[total_sta].name);
			minute=minute+1;//更新为本站的离站时间 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(m1); 
			fprintf(fp,"(拥挤度为%d %)\n",cro);
			if(cro>tolerance) return 0;
			C++;
			total_crowding+=(float)cro;
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}
		key=1;
		} 
		/*------------------------------两个站点都在同一条线路且反向行驶--------------------------------------------*/ 
		else if(m1==m2 && n2<n1){
			set_time_of_station(total_sta);
			if((hour==Sta[total_sta].b_finish_hour && minute>Sta[total_sta].b_finish_minute )|| hour>Sta[total_sta].b_finish_hour) return 0;
			if(hour==Sta[total_sta].b_leave_hour) mental_time+=(Sta[total_sta].b_leave_minute-minute);
			else mental_time+=(Sta[total_sta].b_leave_minute+60-minute);
			//根据到站时间来更新离站时间 
			hour=Sta[total_sta].b_leave_hour;
			minute=Sta[total_sta].b_leave_minute;
			cro=ca_crowding(m1);  
			fprintf(fp,"(拥挤度为%d %)\n",cro);
			if(cro>tolerance) return 0;
			C++;
			total_crowding+=(float)cro;
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		for(j=n1-1;j>=n2+1;j--){
			total_sta=locate_station(m1,j);
			if((hour==Sta[total_sta].b_finish_hour && minute>Sta[total_sta].b_finish_minute) || hour>Sta[total_sta].b_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_sta].name);
			minute=minute+1;//更新为本站的离站时间 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(m1); 
			fprintf(fp,"(拥挤度为%d %)\n",cro);
			if(cro>tolerance) return 0;
			C++;
			total_crowding+=(float)cro;
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}
		key=1;
		}
		/*--------------------------------------------该站点为换乘的站点---------------------------------------------*/
		else{
			fprintf(fp,"(!!!!!!Transfer to Line %d)\n",m2);
			mental_time+=3.5;
			if(minute>=58){
				hour++;
				minute=minute+2-60;
			}
			else {
				if(i==1) minute=minute+3.5;
				else minute=minute+2;//更新为换乘站点的到站时间 
			}
			key=0;
		} 
	}
	total_crowding=total_crowding/C;//加权拥挤度的计算 
	return 1;
}

/*计算拥挤度函数，据线路和时间来判断相应路段的拥挤程度。输入为线路号，输出为拥挤度。*/ 
int ca_crowding(int num_of_line){
	if(mannul_crowding[num_of_line][0]==1){//判断是否有更新过的拥挤度 
		if((hour<mannul_crowding[num_of_line][3]&&hour>mannul_crowding[num_of_line][1]) || (hour==mannul_crowding[num_of_line][3]&&minute<=mannul_crowding[num_of_line][4]) || (hour==mannul_crowding[num_of_line][1]&&minute>=mannul_crowding[num_of_line][2])){
			return mannul_crowding[num_of_line][5];
		}
	} 
	if(num_of_line==1 || num_of_line==3){
		if((hour==7&&minute>=30) || hour==8 ||(hour==9&&minute==0)) return 80;
		else if((hour==16&&minute>=30) || hour==17 || (hour==18&&minute<=30) ) return 75;
		else return 40;
	}
	else if(num_of_line==8){
		if((hour<=14 && hour>=10) || (hour==9 && minute>=30) || (hour==15 && minute==0)) return 65;
		else return 20;
	}
	else if(num_of_line==6 ||num_of_line==7){
		if((hour==19 && minute==0) || (hour==22 &&minute==0) ||(hour<=21&&hour>=20)) return 65;
		else return 15;
	}
	else return 50;
}
