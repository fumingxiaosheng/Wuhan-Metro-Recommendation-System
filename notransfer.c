/*------------------------------------------头文件区------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------------函数声明区---------------------------------------------------*/ 
extern int ca_price(float);
/*以下为不需要换乘的路线提供*/

/*---------------------------------函数区，主要包括no_transfer函数---------------------------------------*/ 

/*该函数实现对不需要换乘路线的推荐，输入为起点的序号和终点的序号，在动态模拟乘车过程中实现拥挤度、加权拥挤度、
心理时间、票价的求解，并将符合条件的路线存储如相应的文件中*/ 
int no_transfer(int total_station1,int total_station2){
	float total_crowding=0;//计算拥挤总加权 
	float mental_time=0;//总的加权时间 
	int C=0;//用来计算加了几个拥挤度的 
	int cro;//实时记录每一个路段的拥挤度 
	FILE *fp; 
	fopen("tdata4.txt", "w");//先进行文件的清空
	fp=fopen("tdata4.txt", "r+");//文件的读写 
	hour=start_hour;
	minute=start_minute;
	/*考虑正向行驶的情况*/ 
	if(total_station1<total_station2){
		int total_station;
		if((hour==Sta[total_station1].a_finish_hour && minute>Sta[total_station1].a_finish_minute) || hour>Sta[total_station1].a_finish_hour) return 0;
		if(hour==Sta[total_station1].a_leave_hour) mental_time+=(Sta[total_station1].a_leave_minute-minute);
		else mental_time+=(Sta[total_station1].a_leave_minute+60-minute);
		hour=Sta[total_station1].a_leave_hour;
		minute=Sta[total_station1].a_leave_minute;
		fprintf(fp,"%s",Sta[total_station1].name);
		cro=ca_crowding(b1);
		fprintf(fp,"(拥挤度为%d %)\n",cro);
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
		for(total_station=total_station1+1;total_station<total_station2;total_station++){
			if((hour==Sta[total_station].a_finish_hour && minute>Sta[total_station].a_finish_minute) || hour>Sta[total_station].a_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_station].name);
			minute+=1;//更新为本站的离站时间 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;	
			cro=ca_crowding(b1);
			fprintf(fp,"(拥挤度为%d %)\n",cro);
		
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}
			//相关线路的输出 
			printf("由于两站之间不包含可换乘站点，建议直达！\n");
			float route_time=(hour-start_hour-1)*60+minute+60-start_minute;
			float route_distance;
			if(b1<5) route_distance=(total_station2-total_station1)*Line[b1-1].ava_len;
			else route_distance=(total_station2-total_station1)*Line[b1-2].ava_len;
			int route_price=ca_price(route_distance);
			total_crowding=total_crowding/C;
			printf("********************************************************************\n");
			printf("总时间为%g 预计到达时刻：%d:%g \n总距离为：%g 票价为:%d \n 综合拥挤度为 %g  心理时间为 %g\n",route_time,hour,minute,route_distance,route_price,total_crowding,mental_time);
			//对文件中存储的相关内容进行输出 
			fclose(fp);
			fp=fopen("tdata4.txt", "r+");
			char c;
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n");
	}
	/*考虑逆向行驶的情况*/ 
	else{
		int total_station;
		if((hour==Sta[total_station1].b_finish_hour && minute>Sta[total_station1].b_finish_minute) || hour>Sta[total_station1].b_finish_hour) return 0;
		if(hour==Sta[total_station1].b_leave_hour) mental_time+=(Sta[total_station1].b_leave_minute-minute);
		else mental_time+=(Sta[total_station1].b_leave_minute+60-minute);
		hour=Sta[total_station1].b_leave_hour;
		minute=Sta[total_station1].b_leave_minute;
		fprintf(fp,"%s",Sta[total_station1].name);
		cro=ca_crowding(b1);
		fprintf(fp,"(拥挤度为%d %)\n",cro);
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
		for(total_station=total_station1-1;total_station>total_station2;total_station--){
			if((hour==Sta[total_station].b_finish_hour && minute>Sta[total_station].b_finish_minute) || hour>Sta[total_station].b_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_station].name);
			minute+=1;//更新为本站的离站时间 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(b1);
			fprintf(fp,"(拥挤度为%d %)\n",cro);
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//更新为下一站的到站时间 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}

			printf("由于两站之间不包含可换乘站点，建议直达！\n");
			float route_time=(hour-start_hour-1)*60+minute+60-start_minute;
			float route_distance;
			if(b1<5) route_distance=(total_station1-total_station2)*Line[b1-1].ava_len;
			else route_distance=(total_station1-total_station2)*Line[b1-2].ava_len;
			int route_price=ca_price(route_distance);
			total_crowding=total_crowding/C;
			printf("********************************************************************\n");
			printf("总时间为%g 预计到达时刻：%d:%g \n总距离为：%g 票价为:%d \n综合拥挤度为 %g  心理时间为 %g\n",route_time,hour,minute,route_distance,route_price,total_crowding,mental_time);
			//对文件中存储的相关内容进行输出 
			fclose(fp);
			fp=fopen("tdata4.txt", "r+");
			char c;
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n");
	}
	return 1; 
} 
