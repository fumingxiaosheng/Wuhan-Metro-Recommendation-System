/*---------------------------------------------------文件区------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"



/*------------------------------------------------函数声明区------------------------------------------------------*/ 
int setroad(struct roadx* p,float road_length,int linen,int stan); 
int settransfer(int *transfer_point); 



/*-------------------------函数区，主要包含三个函数，read,setroad,settransfer------------------------------------*/ 
/*构建完整武汉地铁图函数，函数结果为创建了一个描述武汉地铁的邻接表*/ 
int read(void)
{ 
	int total_sta=0;
	FILE *fp;
	if ((fp = fopen("lineName.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0; 
    }
	/*线路信息和站点信息的共同存储,默认时间为2，拥挤度为50*/ 
	int i,j;//计数器
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
    		/*站点的正向初始到达时刻的设置*/
			if(Sta[total_sta].num_of_sta>=21) Sta[total_sta].a_start_hour=7;
			else Sta[total_sta].a_start_hour=6;
			if(Sta[total_sta].num_of_sta!=20 ) Sta[total_sta].a_start_minute=((Sta[total_sta].num_of_sta%20)-1)*3;
			else  Sta[total_sta].a_start_minute=57;
			/*站点反向初始到达时刻的设置*/ 
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)>=21) Sta[total_sta].b_start_hour=7;
			else Sta[total_sta].b_start_hour=6;
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)!=20) Sta[total_sta].b_start_minute=(((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)%20)-1)*3;
			else  Sta[total_sta].b_start_minute=57;
			//以下是新的添加的部分
			
    		/*站点的正向最后到达时刻的设置*/
			if(Sta[total_sta].num_of_sta>=21) Sta[total_sta].a_finish_hour=24;
			else Sta[total_sta].a_finish_hour=23;
			if(Sta[total_sta].num_of_sta!=20) Sta[total_sta].a_finish_minute=((Sta[total_sta].num_of_sta%20)-1)*3;
			else Sta[total_sta].a_finish_minute=57;
			/*站点反向最后到达时刻的设置*/ 
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)>=21) Sta[total_sta].b_finish_hour=24;
			else Sta[total_sta].b_finish_hour=23;
			if((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)!=20) Sta[total_sta].b_finish_minute=(((Line[i].nums_of_sta-Sta[total_sta].num_of_sta+1)%20)-1)*3;			
			else Sta[total_sta].b_finish_minute=57;
			//以上是新的添加的部分 
    		/*直连弧的设置*/ 
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
	/*换线弧的设置*/ 
	if ((fp = fopen("tdata2.txt", "r") )== NULL){
        printf("Cannot open file\n");
        return 0; 
    }
    int transfer_point[6]={0};//用来记录重复的站点的序列号
    i=0;
    //i用来标识转乘数组的位置，j用来临时存储缓冲区中的数据
	while(fscanf(fp,"%d",&j)!=EOF)
	{
		if(j!=0){
			transfer_point[i]=j;
			i++;
		}
		else{
			settransfer(transfer_point);//调用函数进行创建
			i=0;//进行下一个站点的存储 
		}
	}
	fclose(fp);
	return 1;
 }
 
 
 /*路段赋值函数,输入为站点A结构体中的指针，路径长度，站点A连接的站点的线路号和序列号*/
 int setroad(struct roadx* p,float road_length,int linen,int stan)
 {
 	p->distance=road_length;
 	p->num_of_line=linen;
 	p->num_of_sta=stan;
 	p->tra_time=2;
 	//p->cro_de=50;
	p->road_n=NULL; 
 }
 
 
 /*换乘设置函数，输入为存储一个站点不同标号的数组transfer_point,函数操作结果为将不同线路上的同一站点连接起来*/ 
int settransfer(int *transfer_point){
	int i,j;
	for(i=0;i<3;i++){
		if(transfer_point[2*i+1]==0) break;
		int m,n,tot_num;//m,n存储当前读取的序列号,tot_num存储该站点在站点数组中的位置 
		struct roadx* roadm_n;
		struct roadx* p;
		m=transfer_point[2*i];
		n=transfer_point[2*i+1];
		if(m<5) tot_num=Line[m-1].start+n-1;
		else tot_num=Line[m-2].start+n-1;
		Sta[tot_num].exc=1;
		roadm_n=Sta[tot_num].road_l;
		/*-----下面对(m,n)站点进行转乘线路的设置------*/ 
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
	for(i=0;i<6;i++) transfer_point[i]=0;//清空
	return 0; 
}
