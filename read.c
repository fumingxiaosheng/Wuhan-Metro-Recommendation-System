/*---------------------------------------------------�ļ���------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"



/*------------------------------------------------����������------------------------------------------------------*/ 
int setroad(struct roadx* p,float road_length,int linen,int stan); 
int settransfer(int *transfer_point); 



/*-------------------------����������Ҫ��������������read,setroad,settransfer------------------------------------*/ 
/*���������人����ͼ�������������Ϊ������һ�������人�������ڽӱ�*/ 
int read(void)
{ 
	int total_sta=0;
	FILE *fp;
	if ((fp = fopen("lineName.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0; 
    }
	/*��·��Ϣ��վ����Ϣ�Ĺ�ͬ�洢,Ĭ��ʱ��Ϊ2��ӵ����Ϊ50*/ 
	int i,j;//������
	struct roadx* p;
	struct roadx* q; 
	float roadx_length;
    for(i=0;i<7;i++)
    {
    	fscanf(fp,"%d %d %f %d %d %d",&(Line[i].num_of_line),&(Line[i].ful_cap),&(Line[i].total_line_len),&(Line[i].nums_of_sta),&(Line[i].start),&(Line[i].start_of_trans));
		fgetc(fp); 
		Total_sta+=Line[i].nums_of_sta;
		roadx_length=Line[i].total_line_len/(Line[i].nums_of_sta-1);
		Line[i].ava_len=roadx_length; 
		for(j=0;j<Line[i].nums_of_sta;j++){
			fscanf(fp,"%[^,]%*c",Sta[total_sta].name);
    		Sta[total_sta].exc=0;
    		Sta[total_sta].num_of_line=Line[i].num_of_line;
    		Sta[total_sta].num_of_sta=j+1;
    		/*վ��������ʼ����ʱ�̵�����*/
			if(Sta[total_sta].num_of_sta>=21) Sta[total_sta].a_start_hour=7;
			else Sta[total_sta].a_start_hour=6;
			if(Sta[total_sta].num_of_sta!=20 ) Sta[total_sta].a_start_minute=((Sta[total_sta].num_of_sta%20)-1)*3;
			else  Sta[total_sta].a_start_minute=57;
			/*վ�㷴���ʼ����ʱ�̵�����*/ 
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)>=21) Sta[total_sta].b_start_hour=7;
			else Sta[total_sta].b_start_hour=6;
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)!=20) Sta[total_sta].b_start_minute=(((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)%20)-1)*3;
			else  Sta[total_sta].b_start_minute=57;
			//�������µ���ӵĲ���
			
    		/*վ���������󵽴�ʱ�̵�����*/
			if(Sta[total_sta].num_of_sta>=21) Sta[total_sta].a_finish_hour=24;
			else Sta[total_sta].a_finish_hour=23;
			if(Sta[total_sta].num_of_sta!=20) Sta[total_sta].a_finish_minute=((Sta[total_sta].num_of_sta%20)-1)*3;
			else Sta[total_sta].a_finish_minute=57;
			/*վ�㷴����󵽴�ʱ�̵�����*/ 
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)>=21) Sta[total_sta].b_finish_hour=24;
			else Sta[total_sta].b_finish_hour=23;
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)!=20) Sta[total_sta].b_finish_minute=(((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)%20)-1)*3;			
			else Sta[total_sta].b_finish_minute=57;
			//�������µ���ӵĲ��� 
    		/*ֱ����������*/ 
    		p=(struct roadx*)malloc(sizeof(struct roadx));
    		if(j==0){
    			Sta[total_sta].road_f=p;
    			Sta[total_sta].road_l=p;
				setroad(p,roadx_length,Line[i].num_of_line,2);	
			}
			else if(j==Line[i].nums_of_sta-1){
				Sta[total_sta].road_f=p;
				Sta[total_sta].road_l=p;
				setroad(p,roadx_length,Line[i].num_of_line,Line[i].nums_of_sta-1);
			}
			else{
				Sta[total_sta].road_f=p;
				setroad(p,roadx_length,Line[i].num_of_line,Sta[total_sta].num_of_sta-1);
				q=(struct roadx*)malloc(sizeof(struct roadx));
				p->road_n=q;
				Sta[total_sta].road_l=q;
				setroad(q,roadx_length,Line[i].num_of_line,Sta[total_sta].num_of_sta+1);
			}
    		total_sta++;
		}
	}
	/*���߻�������*/ 
	if ((fp = fopen("tdata2.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0; 
    }
    int transfer_point[6]={0};//������¼�ظ���վ������к�
    i=0;
    //i������ʶת�������λ�ã�j������ʱ�洢�������е�����
	while(fscanf(fp,"%d",&j)!=EOF)
	{
		if(j!=0){
			transfer_point[i]=j;
			i++;
		}
		else{
			settransfer(transfer_point);//���ú������д���
			i=0;//������һ��վ��Ĵ洢 
		}
	}
	fclose(fp);
	return 1;
 }
 
 
 /*·�θ�ֵ����,����Ϊվ��A�ṹ���е�ָ�룬·�����ȣ�վ��A���ӵ�վ�����·�ź����к�*/
 int setroad(struct roadx* p,float road_length,int linen,int stan)
 {
 	p->distance=road_length;
 	p->num_of_line=linen;
 	p->num_of_sta=stan;
 	p->tra_time=2;
 	//p->cro_de=50;
	p->road_n=NULL; 
 }
 
 
 /*�������ú���������Ϊ�洢һ��վ�㲻ͬ��ŵ�����transfer_point,�����������Ϊ����ͬ��·�ϵ�ͬһվ����������*/ 
int settransfer(int *transfer_point){
	int i,j;
	for(i=0;i<3;i++){
		if(transfer_point[2*i+1]==0) break;
		int m,n,tot_num;//m,n�洢��ǰ��ȡ�����к�,tot_num�洢��վ����վ�������е�λ�� 
		struct roadx* roadm_n;
		struct roadx* p;
		m=transfer_point[2*i];
		n=transfer_point[2*i+1];
		if(m<5) tot_num=Line[m-1].start+n-1;
		else tot_num=Line[m-2].start+n-1;
		Sta[tot_num].exc=1;
		roadm_n=Sta[tot_num].road_l;
		/*-----�����(m,n)վ�����ת����·������------*/ 
		for(j=0;j<3;j++){
			if(transfer_point[2*j+1]==0) break;
			if(transfer_point[2*j]!=m){
			p=(struct roadx*)malloc(sizeof(struct roadx));
			p->distance=0;
 			p->num_of_line=transfer_point[2*j];
 			p->num_of_sta=transfer_point[2*j+1];
		 	p->tra_time=3.5;
		 	//p->cro_de=50;
			p->road_n=NULL;
			roadm_n->road_n=p;
			roadm_n=p;
			}
		}
		Sta[tot_num].road_l=roadm_n; 
	}
	for(i=0;i<6;i++) transfer_point[i]=0;//���
	return 0; 
}
