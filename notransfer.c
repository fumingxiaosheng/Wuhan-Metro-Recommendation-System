/*------------------------------------------ͷ�ļ���------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------------����������---------------------------------------------------*/ 
extern int ca_price(float);
/*����Ϊ����Ҫ���˵�·���ṩ*/

/*---------------------------------����������Ҫ����no_transfer����---------------------------------------*/ 

/*�ú���ʵ�ֶԲ���Ҫ����·�ߵ��Ƽ�������Ϊ������ź��յ����ţ��ڶ�̬ģ��˳�������ʵ��ӵ���ȡ���Ȩӵ���ȡ�
����ʱ�䡢Ʊ�۵���⣬��������������·�ߴ洢����Ӧ���ļ���*/ 
int no_transfer(int total_station1,int total_station2){
	float total_crowding=0;//����ӵ���ܼ�Ȩ 
	float mental_time=0;//�ܵļ�Ȩʱ�� 
	int C=0;//����������˼���ӵ���ȵ� 
	int cro;//ʵʱ��¼ÿһ��·�ε�ӵ���� 
	FILE *fp; 
	fopen("tdata4.txt", "w");//�Ƚ����ļ������
	fp=fopen("tdata4.txt", "r+");//�ļ��Ķ�д 
	hour=start_hour;
	minute=start_minute;
	/*����������ʻ�����*/ 
	if(total_station1<total_station2){
		int total_station;
		if((hour==Sta[total_station1].a_finish_hour && minute>Sta[total_station1].a_finish_minute) || hour>Sta[total_station1].a_finish_hour) return 0;
		if(hour==Sta[total_station1].a_leave_hour) mental_time+=(Sta[total_station1].a_leave_minute-minute);
		else mental_time+=(Sta[total_station1].a_leave_minute+60-minute);
		hour=Sta[total_station1].a_leave_hour;
		minute=Sta[total_station1].a_leave_minute;
		fprintf(fp,"%s",Sta[total_station1].name);
		cro=ca_crowding(b1);
		fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
		C++;
		total_crowding+=(float)cro;
		if(minute==58){
				hour++;
				minute=0;
			}
		else minute+=2;//����Ϊ��һվ�ĵ�վʱ�� 
		if(cro>=75) mental_time+=2*1.5;
		else if(cro>=20) mental_time+=2;
		else mental_time+=2*0.6;
		for(total_station=total_station1+1;total_station<total_station2;total_station++){
			if((hour==Sta[total_station].a_finish_hour && minute>Sta[total_station].a_finish_minute) || hour>Sta[total_station].a_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_station].name);
			minute+=1;//����Ϊ��վ����վʱ�� 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;	
			cro=ca_crowding(b1);
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
		
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//����Ϊ��һվ�ĵ�վʱ�� 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}
			//�����·����� 
			printf("������վ֮�䲻�����ɻ���վ�㣬����ֱ�\n");
			float route_time=(hour-start_hour-1)*60+minute+60-start_minute;
			float route_distance;
			if(b1<5) route_distance=(total_station2-total_station1)*Line[b1-1].ava_len;
			else route_distance=(total_station2-total_station1)*Line[b1-2].ava_len;
			int route_price=ca_price(route_distance);
			total_crowding=total_crowding/C;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ%g Ԥ�Ƶ���ʱ�̣�%d:%g \n�ܾ���Ϊ��%g Ʊ��Ϊ:%d \n �ۺ�ӵ����Ϊ %g  ����ʱ��Ϊ %g\n",route_time,hour,minute,route_distance,route_price,total_crowding,mental_time);
			//���ļ��д洢��������ݽ������ 
			fclose(fp);
			fp=fopen("tdata4.txt", "r+");
			char c;
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n");
	}
	/*����������ʻ�����*/ 
	else{
		int total_station;
		if((hour==Sta[total_station1].b_finish_hour && minute>Sta[total_station1].b_finish_minute) || hour>Sta[total_station1].b_finish_hour) return 0;
		if(hour==Sta[total_station1].b_leave_hour) mental_time+=(Sta[total_station1].b_leave_minute-minute);
		else mental_time+=(Sta[total_station1].b_leave_minute+60-minute);
		hour=Sta[total_station1].b_leave_hour;
		minute=Sta[total_station1].b_leave_minute;
		fprintf(fp,"%s",Sta[total_station1].name);
		cro=ca_crowding(b1);
		fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
		C++;
		total_crowding+=(float)cro;
		if(minute==58){
				hour++;
				minute=0;
			}
		else minute+=2;//����Ϊ��һվ�ĵ�վʱ�� 
		if(cro>=75) mental_time+=2*1.5;
		else if(cro>=20) mental_time+=2;
		else mental_time+=2*0.6;	
		for(total_station=total_station1-1;total_station>total_station2;total_station--){
			if((hour==Sta[total_station].b_finish_hour && minute>Sta[total_station].b_finish_minute) || hour>Sta[total_station].b_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_station].name);
			minute+=1;//����Ϊ��վ����վʱ�� 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(b1);
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
			if(minute==58){
				hour++;
				minute=0;
			}
			else minute+=2;//����Ϊ��һվ�ĵ�վʱ�� 
			if(cro>=75) mental_time+=2*1.5;
			else if(cro>=20) mental_time+=2;
			else mental_time+=2*0.6;
		}

			printf("������վ֮�䲻�����ɻ���վ�㣬����ֱ�\n");
			float route_time=(hour-start_hour-1)*60+minute+60-start_minute;
			float route_distance;
			if(b1<5) route_distance=(total_station1-total_station2)*Line[b1-1].ava_len;
			else route_distance=(total_station1-total_station2)*Line[b1-2].ava_len;
			int route_price=ca_price(route_distance);
			total_crowding=total_crowding/C;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ%g Ԥ�Ƶ���ʱ�̣�%d:%g \n�ܾ���Ϊ��%g Ʊ��Ϊ:%d \n�ۺ�ӵ����Ϊ %g  ����ʱ��Ϊ %g\n",route_time,hour,minute,route_distance,route_price,total_crowding,mental_time);
			//���ļ��д洢��������ݽ������ 
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
