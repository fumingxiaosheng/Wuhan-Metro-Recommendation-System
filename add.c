/*----------------------------------------------ͷ�ļ���-------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"


/*----------------------------------------����������Ҫ����add_points����-------------------------------------------*/ 
/*�ӵ㺯������ͼ�м���ĳ��(m,n)�����õ㲻��ͼ�У��������order����������1�����򷵻�0������Ϊ����������·�ź���ţ�������Ϊ�ı����Ż�����*/
int add_points(int m,int n){ 
		int start,finish,i,j,order;//start��ʾ��㣬finish��ʾ�յ�,i����������,j������¼���ڼ��վ����,order��ʾ��ӵ�λ�ã� 
		/*ȷ����Ҫ����ľ���Χ*/ 
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
		for(i=start;(i<=finish)&&(key[i][1]<n);i++);//ȷ���õ��ڵ������ϵ����λ�� 
		/*1.����Ҫ��ӽ�㣬ֱ�ӷ���*/
		if(key[i][1]==n) return i; 
		/*2.��Ҫ��ӽ�㣬��ȷ��Ҫ��ӵ�λ�ú�ƽ��·�γ���distance*/
		order=56;
		float distance; 
		for(j=0;j<58;j++){
			if(djs_time[56][j]!=1000){//�����56�Ա���ӣ��������Ϊ57 
				order=57;
				break;
			}
		}
		if(m<5) distance=Line[m-1].ava_len;
		else distance=Line[m-2].ava_len;
		/*(1)���ڵ�����ͷ*/ 
		if(i==start){
			j=key[i][1]-n;
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		/*(2)���ڵ�����β*/
		else if(i==finish+1){
			i=finish;
			j=n-key[i][1];
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		/*(3)�ڵ�������,����i-1��i֮��*/
		else{ 
			/*���i-1��i֮�����ϵ*/ 
			djs_time[i][i-1]=1000;
			djs_time[i-1][i]=1000;
			djs_distance[i][i-1]=1000;
			djs_distance[i-1][i]=1000;
			/*����i-1��order֮�����ϵ*/
			j=n-key[i-1][1];
			djs_time[i-1][order]=2*j;
			djs_time[order][i-1]=2*j;
			djs_distance[i-1][order]=j*distance;
			djs_distance[order][i-1]=j*distance; 
			/*����i��order֮�����ϵ*/
			j=key[i][1]-n;
			djs_time[i][order]=2*j;
			djs_time[order][i]=2*j;
			djs_distance[i][order]=j*distance;
			djs_distance[order][i]=j*distance;
		} 
		return order;
}

