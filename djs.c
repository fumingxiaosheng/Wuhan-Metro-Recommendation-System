/*-------------------------------------------�ļ���-------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h" 

/*------------------------------------------����������----------------------------------------------*/ 
float ca_distance(int (*)[3]);
int ca_crowding(int);
int ca_time(FILE *,int (*)[3]);
int ca_price(float);
extern int locate_station(int,int);
extern int set_time_of_station(int);

/*-------------------------------------��c�ļ���ȫ�ֱ�����------------------------------------------*/ 
int nums_of_route;//�洢���·����վ����  
float total_crowding;//����ӵ���ܼ�Ȩ 
float mental_time;//�ܵļ�Ȩʱ�� 


/*--------------����������Ҫ����Dijkstra��ca_distance��ca_crowding��ca_time��ca_price����------------*/ 

/*����·����������Ϊ������������ά������ʼ����յ��������е�λ�ã�����������飬��ʾ�Ƿ���Ҫ�������̶ȵı��*/ 
int Dijkstra(int dimension,int order_of_start,int order_of_finish,float (*djs)[58],int fre){
	/*---�Զ�ά����djs���в�����������Ϊorder_of_start�����Ϊorder_of_finish�ĵ�ĵ�һ�����·��---*/
	float distance[58]={0};//�洢��̾���
	int pre[58]={0};//�洢ǰһ������
	int mark[58]={0};//���ҵ����·������Ϊ1������Ϊ0��
	int i,j;//������ 
	/*��ʼ������*/
	for(i=0;i<dimension;i++){
		distance[i]=djs[order_of_start][i];
		pre[i]=order_of_start;
		mark[i]=0;
	}
	mark[order_of_start]=1;
	/*�������*/ 
	int min_num,min_key=1;//��ʶ��ǰ�ҵ����·���ĵ�,min_key���ڿ��� 
	for(i=1;i<dimension;i++){
		/*�ҵ���ǰ���·���ĵ����Ϊmin_num*/ 
		min_key=1;
		for(j=0;j<dimension;j++){
			if(mark[j]==0&&min_key){
				min_num=j;//�ҵ���һ��δ�ҵ����·�ĵ�
				min_key=0;
			}
			if(mark[j]==0&&(!min_key)&&(distance[j]<distance[min_num])) min_num=j;
		}
		/*���min_num������ĵ㣬������distance����*/
		mark[min_num]=1;
		for(j=0;j<dimension;j++){
			if(mark[j]==0&&(distance[j]>distance[min_num]+djs[min_num][j])){
				distance[j]=distance[min_num]+djs[min_num][j];
				pre[j]=min_num;
			}
		}
   }

	/*����洢����õ�·��*/
	int route1[100][3];//�洢��õ�·������һ�����������ʱ�䡢��������е����кţ�����������վ���
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
	 
	/*ʹ��һ���ļ��洢·��,ע��Ӧ�Ƚ����ļ�����գ����ж�ʹ����һ���ļ����ж��������е�λ��*/
	int R;//�������Ҫ�洢��·����Ϣ�������е�λ�� 
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
	
	/*�����·�ߵļ���*/ 
	float route_distance;//·�ߵĳ��� 
	int route_price;//Ʊ��
	float route_time;//·�ߵ�ʱ�� 
	route_distance=ca_distance(route1);
	if(route_distance>999){
		ROUTE[R][0]=0;
		return 0;	
		}
	route_price=ca_price(route_distance);
	hour=start_hour;
	minute=start_minute;
//�ո����ߵ�λ�� 
	if(ca_time(fp,route1)==0) {//������ӵ���ȵ�Ҫ���ʱ��Ҫ��ʱ 
		ROUTE[R][0]=0;
	}
	else{
	route_time=(hour-start_hour-1)*60+minute+60-start_minute;
	/*if(hour>=23&&minute>0 || hour>=24) {//������ʱ�䷶Χ 
		ROUTE[R][0]=0;
		return 0;
	} */ 
	//else {//����Ҫ�󲢶���Ӧ��·�߸�����Ӧ��ֵ 
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



	/*------���洦��ڶ���·��------*/
	/*�ж���Ҫ��һ���ļ��������е���һ��λ��*/ 
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
	
	/*�ڶ�����·�����*/ 
	int pre2[200];
	float distance2[200]; 
	for(i=nums_of_route-1;i>=0;i--){
		int order=route1[i][0];//order������Ǹõ��������е�λ�� 
		pre2[i]=1;
		distance2[i]=10000;
		for(j=0;j<dimension;){
			if(distance2[i]>djs[j][order]+distance[j] && j!=pre[order]){
				//������л�·���ж�
				//�����ҵ���һ�����j���ж�jǰ�������ǰ��ϵ�G���Ƿ���order���еĻ���ֱ���˳�
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
	
	/*����洢�ڶ�����·*/ 
	else{
	int route2[100][3];//�洢��õ�·������һ�����������ʱ�䡢��������е����кţ�����������վ���;
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
	/*��·�����Ϣ�ļ���*/
	route_distance=ca_distance(route2);
	route_price=ca_price(route_distance); 
	hour=start_hour;
	minute=start_minute;
	if(ca_time(fp,route2)==0){//������ӵ���ȵ�Ҫ�� 
	ROUTE[R][0]=0;
	}
	else{
	route_time=(hour-start_hour-1)*60+minute+60-start_minute;
/*	if(hour>=23&&minute>0 || hour>=24) {
		ROUTE[R][0]=0;//������ʱ���Ҫ�� 
		return 0;
	} */ 
//	else {//���л��߽���Ĵ洢 
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

/*�����뺯�������ݴ洢����·����route�������·���ľ��롣����Ϊ·�����飬���Ϊ·������*/
float ca_distance(int (*route)[3]){
	int i,j;//����ָʾ·����djs_diatance�����е�λ�� 
	int m;//m�������� 
	float route_distance=0;
	for(m=nums_of_route;m>=1;m--){
		i=route[m][0];
		j=route[m-1][0];
		route_distance+=djs_distance[i][j];
	}
	return route_distance;
} 
 
/*���Ʊ�ۺ���������Ϊ���룬���ΪƱ��*/
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

/*����ʱ�亯������̬����ʱ�䣬ģ��˳����������Ϊ��д����ļ�ָ�룬·�����飻ִ�иú����Ľ��Ϊ��·��д���ļ���·����
ÿһ��վ��ӵ���ȵĻ�ã���Ȩʱ��Ļ�ã���Ȩӵ���ȵĻ�á�����·���ڶ�̬ģ������г��ֳ���������̶ȵ��������ú���
���ϳ�����·��*/ 
int ca_time(FILE *fp,int (*route)[3]){
	int i,j,total_sta,m1,n1,m2,n2,key=1;//key����������ת��վ�������� 
	total_crowding=0;
	mental_time=0;
	int C=0;//����������˼���ӵ���ȵ� 
	int cro;//ʵʱ��¼ÿһ��·�ε�ӵ���� 
	for(i=nums_of_route;i>=1;i--){
		m1=route[i][1];
		n1=route[i][2];
		total_sta=locate_station(m1,n1);//m1,n1��־�ŵ�ǰ��վ���,total_sta��ʾ���������е�λ�� 
		if(key) {
			fprintf(fp,"%s",Sta[total_sta].name);
		}
		m2=route[i-1][1];
		n2=route[i-1][2];
		
		/*-----------------------------------����վ�㶼��ͬһ����·��������ʻ---------------------------------------*/ 
		if(m1==m2 && n2>n1){
			set_time_of_station(total_sta);
			if((hour==Sta[total_sta].a_finish_hour && minute>Sta[total_sta].a_finish_minute) || hour>Sta[total_sta].a_finish_hour) {
				return 0;
			}
			//���ݵ�վʱ����������վʱ�� 
			if(hour==Sta[total_sta].a_leave_hour) mental_time+=(Sta[total_sta].a_leave_minute-minute);
			else mental_time+=(Sta[total_sta].a_leave_minute+60-minute);
			hour=Sta[total_sta].a_leave_hour;
			minute=Sta[total_sta].a_leave_minute;
			cro=ca_crowding(m1); 
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
			if(cro>tolerance) return 0;//������������̶ȣ������ϸ���·�� 
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
		for(j=n1+1;j<=n2-1;j++){
			total_sta=locate_station(m1,j);
			if((hour==Sta[total_sta].a_finish_hour && minute>Sta[total_sta].a_finish_minute) || hour>Sta[total_sta].a_finish_hour) {
				return 0;
			}
			fprintf(fp,"%s",Sta[total_sta].name);
			minute=minute+1;//����Ϊ��վ����վʱ�� 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(m1); 
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
			if(cro>tolerance) return 0;
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
		}
		key=1;
		} 
		/*------------------------------����վ�㶼��ͬһ����·�ҷ�����ʻ--------------------------------------------*/ 
		else if(m1==m2 && n2<n1){
			set_time_of_station(total_sta);
			if((hour==Sta[total_sta].b_finish_hour && minute>Sta[total_sta].b_finish_minute )|| hour>Sta[total_sta].b_finish_hour) return 0;
			if(hour==Sta[total_sta].b_leave_hour) mental_time+=(Sta[total_sta].b_leave_minute-minute);
			else mental_time+=(Sta[total_sta].b_leave_minute+60-minute);
			//���ݵ�վʱ����������վʱ�� 
			hour=Sta[total_sta].b_leave_hour;
			minute=Sta[total_sta].b_leave_minute;
			cro=ca_crowding(m1);  
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
			if(cro>tolerance) return 0;
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
		for(j=n1-1;j>=n2+1;j--){
			total_sta=locate_station(m1,j);
			if((hour==Sta[total_sta].b_finish_hour && minute>Sta[total_sta].b_finish_minute) || hour>Sta[total_sta].b_finish_hour) return 0;
			fprintf(fp,"%s",Sta[total_sta].name);
			minute=minute+1;//����Ϊ��վ����վʱ�� 
			if(cro>=75) mental_time+=1*1.5;
			else if(cro>=20) mental_time+=1;
			else mental_time+=1*0.6;
			cro=ca_crowding(m1); 
			fprintf(fp,"(ӵ����Ϊ%d %)\n",cro);
			if(cro>tolerance) return 0;
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
		}
		key=1;
		}
		/*--------------------------------------------��վ��Ϊ���˵�վ��---------------------------------------------*/
		else{
			fprintf(fp,"(!!!!!!Transfer to Line %d)\n",m2);
			mental_time+=3.5;
			if(minute>=58){
				hour++;
				minute=minute+2-60;
			}
			else {
				if(i==1) minute=minute+3.5;
				else minute=minute+2;//����Ϊ����վ��ĵ�վʱ�� 
			}
			key=0;
		} 
	}
	total_crowding=total_crowding/C;//��Ȩӵ���ȵļ��� 
	return 1;
}

/*����ӵ���Ⱥ���������·��ʱ�����ж���Ӧ·�ε�ӵ���̶ȡ�����Ϊ��·�ţ����Ϊӵ���ȡ�*/ 
int ca_crowding(int num_of_line){
	if(mannul_crowding[num_of_line][0]==1){//�ж��Ƿ��и��¹���ӵ���� 
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
