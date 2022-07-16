/*--------------------------------------------�ļ���-----------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"


/*------------------------------------------����������---------------------------------------------------*/ 
int locate_transfer(int m,int n); 



/*----------------------------����������Ҫ����optimization��locate_transfer����--------------------------*/ 

/*�����人�����Ż�ͼ����*/ 
int optimization(){
	int i,j;//������ 
/*�����ɻ���վ�������*/
FILE *fp;
if ((fp = fopen("tdata3.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0;
    }
for(i=0;i<56;i++){
	fscanf(fp,"%d %d",&(key[i][0]),&(key[i][1]));
}
/*ʱ�����;������ĳ�ʼ��*/ 
for(i=0;i<58;i++){
	for(j=0;j<58;j++){
	djs_time[i][j]=1000;
	djs_distance[i][j]=1000;
	}
}
/*ʱ�����;������Ľ�һ������*/
for(i=0;i<56;i++){ 
	 /*�ȴ������ڵĽ��*/
	 //i����������jΪ��վ֮���·����
	 if(i==0){//��λ�ڵ�һ�� 
	 	j=key[1][1]-key[0][1];
	 	djs_time[0][1]=3*j;
	 	djs_distance[0][1]=j*Line[0].ava_len;
	 }
	 else if(i==55){//��λ�����һ�� 
	 	j=key[55][1]-key[54][1];
	 	djs_time[55][54]=3*j;
	 	djs_distance[55][54]=j*Line[6].ava_len;
	 }
	 else{//��λ���м� 
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
	 /*�ٴ����˵������*/ 
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
	 	tran_next=tran_next->road_n;//��һ���ƶ�ָ�� 
	 }
}
	return 1;
}

/*ȷ�����˵��ڼ��������е�λ�ú���������Ϊ��Ѱ�ҵ�վ�����·�ź���ţ����Ϊ���ڼ��������е����*/ 
int locate_transfer(int m,int n){
	int start;
	if(m<5) start=Line[m-1].start_of_trans;
	else start=Line[m-2].start_of_trans;
	while(key[start][1]!=n) start++;
	return start;
}




	
