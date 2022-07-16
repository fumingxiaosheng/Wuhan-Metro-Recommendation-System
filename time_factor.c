/*---------------------------------------------ͷ�ļ���-----------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------------����������------------------------------------------------------*/
extern int ca_crowding(int);


/*----------------------����������Ҫ����set_crowding,update_djs_time����------------------------------------*/ 
/*�ú���ʵ�������·�ıܿ��Ĺ��ܣ���Ҫ˼·���£�����ǰ�����ĵ�·�����һ�����ĳ˳�ʱ�䣬����ʼʱ�̿�ʼ����̬ģ��
��·ӵ���ȵı仯�����������̶ȣ�ͨ��������cro_delʵ�ֱܿ�����·��ִ�иú����Ľ��Ϊ����Line������ÿ����·��cro_del*/ 
int set_crowding(void){
	//�Ƚ��г�ʼ�� 
	hour=start_hour;
	minute=start_minute;
	int timing;//ÿʮ���ӽ���һ��ʱ��ĸ���
	int Line_crowding;
	int i,j;
	/*�Ƚ���cro_del�ĳ�ʼ��*/ 
	for(i=0;i<7;i++){
		Line[i].cro_del=1;
	} 
	for(timing=0;timing<=max_time;timing+=10){
		//�������ʱ��ĸ���
		if(minute>=50){
			hour++;
			minute=minute+10-60;
		}
		else minute+=10;
		//�������ÿһ����·Line.cro_del�����ã�����������ֱ������Ϊ1000�����������·
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


/*�ú������ݸ��º��Line�����е�cro_delʵ�ֶ�ʱ�����ĸ���*/ 
int update_djs_time(void){
	int i,j;//��������ʱ��������������
	int m,n;//�������к�Ϊi��Ӧ��վ��λ�� 
	
	/*------��56*56�ĳ�ʼ�����������------*/ 
	for(i=0;i<56;i++){
		m=key[i][0];
		n=key[i][1];
		int start,finish;
		float time_factor;//��վ��������·��ӵ���̶� 
		/*������Ҫ�޸ĵĴ��·�Χ*/ 
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
		/*���ó˳�����*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*��56*56�ľ�������޸�*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[i][j]!=4 && djs_time[i][j]!=1000) djs_time[i][j]=djs_time[i][j]*time_factor;//���ǲ��ǻ��˵���� 
		}
		} 
		
		
		/*------���������޸�------*/
		if(order_of_start==56 || order_of_start==57){
		m=b1;
		n=b2;
		int start,finish;
		float time_factor;//��վ��������·��ӵ���̶� 
		/*������Ҫ�޸ĵĴ��·�Χ*/ 
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
		/*���ó˳�����*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*��56*56�ľ�������޸�*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[order_of_start][j]!=4 && djs_time[order_of_start][j]!=1000) {
				//���ǲ��ǻ��˵������ע��ת�þ�������� 
				djs_time[order_of_start][j]=djs_time[order_of_start][j]*time_factor;
				djs_time[j][order_of_start]=djs_time[j][order_of_start]*time_factor;
			}
		}
	} 
	
	
	
	/*------���յ�����޸�------*/
	if(order_of_finish==56 || order_of_finish==57){
		m=b1;
		n=b2;
		int start,finish;
		float time_factor;//��վ��������·��ӵ���̶� 
		/*������Ҫ�޸ĵĴ��·�Χ*/ 
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
		/*���ó˳�����*/
		if(m<5) time_factor=Line[m-1].cro_del;
		else time_factor=Line[m-2].cro_del;
		/*��56*56�ľ�������޸�*/ 
		for(j=start;j<=finish;j++){
			if(djs_time[order_of_start][j]!=4 && djs_time[order_of_start][j]!=1000) {
				//���ǲ��ǻ��˵������ע��ת�þ�������� 
				djs_time[order_of_finish][j]=djs_time[order_of_finish][j]*time_factor;
				djs_time[j][order_of_finish]=djs_time[j][order_of_finish]*time_factor;
			}
		}
	}
	
	return 1;//���óɹ�����ֵΪ1 
}

 
