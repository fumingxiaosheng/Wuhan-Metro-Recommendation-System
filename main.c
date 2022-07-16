#include<stdio.h>
#include<stdlib.h>
#include"dfstruct.h"
#include"global.h"
int locate_station(int m,int n);
int set_time_of_station(int total_sta);
int main(void){ 
	/*------------------------�����������人����ͼ---------------------------*/
	int i,j;	
	ROUTE[1][1]=0; //��������Ҫ 
	if(read()==1 &&optimization()==1) printf("��ӭ�����人������\n");
	/*----------------------------��¼����-----------------------------------*/ 
	int option=1;
	while(option){
		printf("1.��½�˺� 2.ע���˺� 3.�һ����� 0.�˳�ϵͳ\n");
		scanf("%d",&option);
		switch(option){
			case 1:if(Input_login()==1) goto chaxun;
					break;
			case 2:registers();
					break;
			case 3:reback();
					break;
			case 0:return 0;
		}
	}
	chaxun:printf("��½�ɹ�����ӭʹ�ã�\n");
	/*-----------------------------ϵͳ����-----------------------------------*/ 
	printf("1.��·��Ϣ��ѯ 2.վ����Ϣ��ѯ 3.������ʼվ����յ�վ 4.���˲�ѯ 5.�ֹ�����ӵ���� 0.�˳�ϵͳ\n");
	int dimension;//�洢�����ά��
	float min;//������ʾ���µ���С 
	int min_num; //��������ļ����ʱ�洢�ĵ�ǰӦ����������к� 
	int k;//����վ������Ŀ��� ��������·���Ŀ��� 
	scanf("%d",&option);
	while(option){
		switch(option){
			/*---����1����·��Ϣ��ѯ---*/ 
		case 1:{
				printf("����������Ҫ��ѯ�ĵ�����·��:");
				int Line_number;
				scanf("%d",&Line_number);
				if(Line_number!=4 &&Line_number!=8){
					i=locate_station(Line_number,1);
					j=locate_station(Line_number+1,1);
				}
				else if(Line_number==4){
					i=locate_station(4,1);
					j=locate_station(6,1);
				}
				else{
					i=locate_station(8,1);
					j=226;
				}
				for(;i<j;i++){
					printf("%d %s\n",Sta[i].num_of_sta,Sta[i].name);
				}
				break;
		}//end of case 1 
			
			/*---����2:վ����Ϣ��ѯ---*/ 
		case 2:{
				printf("1:վ����Ϣ��ѯ   0:�˳��ù���\n");
				scanf("%d",&k);
				while(k){
					int s_order;
					printf("������վ�����·�ź�վ�����:");
					scanf("%d %d",&i,&j);
					s_order=locate_station(i,j);
					printf("����Ϊ:%s\n�ɵִ�:\n",Sta[s_order].name);
					struct roadx* p=Sta[s_order].road_f;
					while(p!=NULL){
						int a,b,c;
						a=p->num_of_line;
						b=p->num_of_sta;
						c=locate_station(a,b);
						printf("%d %d %s\n",a,b,Sta[c].name);
						p=p->road_n;
					}
					printf("1:վ����Ϣ��ѯ   0:�˳��ù���\n");
					scanf("%d",&k);
				} 
			break;
		}//end of case 2
		
		/*---����3:������ʼվ����յ�վ---*/ 
	case 3:{
	int total_sta;
	tolerance=100;//��������Ӧ�����̶� 
	printf("�����뵱��ʱ��:");
	scanf("%d %f",&start_hour,&start_minute);
	hour=start_hour;
	minute=start_minute; 
	printf("������������·�ź����:"); 
	scanf("%d %d",&b1,&b2);
	//�ҵ���վ�����ڵ�λ�� 
	total_sta=locate_station(b1,b2);
	set_time_of_station(total_sta);
	if(Sta[total_sta].exc==1) printf("����Ϊ��%s(ת��վ��)\n",Sta[total_sta].name);
	else printf("����Ϊ��%s(��ת��վ��)\n",Sta[total_sta].name);
	//�����¼ӵ�ƥ���г�ʱ�̱��� 
	printf("����Ϊ��ǰʱ��ǰ15��������15���ӵ��г�ʱ�̱�\n");
	//���ڿ���ʻ�ķ�Χ
	int bhour,dhour;
	float bminute,dminute;
	bhour=start_hour;
	dhour=start_hour;
	bminute=start_minute;
	dminute=start_minute;
	if(bminute<15){
		bminute=bminute-15+60;
		bhour--;
	}
	else bminute=bminute-15;
	if(dminute>=45){
		dminute=dminute+15-60;
		dhour++;
	}
	else dminute=dminute+15;
	int ta_hour;
	float ta_minute;
	int u,o=1;//o�������� 
	//�����ʱ�̱� 
	printf("����\n");
	ta_hour=Sta[total_sta].a_arrive_hour;
	ta_minute=Sta[total_sta].a_arrive_minute;
	if(ta_minute<15){
		ta_minute=ta_minute-15+60;
		ta_hour--;
	}
	else ta_minute=ta_minute-15;
	for(u=1;u<=15;u++){
		if((ta_hour>bhour ||(ta_hour==bhour && ta_minute>bminute)) && (ta_hour<dhour ||(ta_hour==dhour && ta_minute<dminute)) && (ta_hour<Sta[total_sta].a_finish_hour || (ta_hour==Sta[total_sta].a_finish_hour && ta_minute<=Sta[total_sta].a_finish_minute)) && (ta_hour>Sta[total_sta].a_start_hour || (ta_hour==Sta[total_sta].a_start_hour && ta_minute>=Sta[total_sta].a_start_minute))){
		o=0;
		printf("��վʱ��: %d:%g  ��վʱ��: %d:%g\n",ta_hour,ta_minute,ta_hour,ta_minute+1);}
		if(ta_minute>=57){
			ta_minute=ta_minute+3-60;
			ta_hour++;
		}
		else ta_minute=ta_minute+3;
	}
	if(o) printf("��ǰ�޷���Ҫ����г���\n"); 
	//�����ʱ�̱�
	o=1;
	printf("����:\n");
	ta_hour=Sta[total_sta].b_arrive_hour;
	ta_minute=Sta[total_sta].b_arrive_minute;
	if(ta_minute<15){
		ta_minute=ta_minute-15+60;
		ta_hour--;
	}
	else ta_minute=ta_minute-15;
	for(u=1;u<=15;u++){
		if((ta_hour>bhour ||(ta_hour==bhour && ta_minute>bminute)) && (ta_hour<dhour ||(ta_hour==dhour && ta_minute<dminute)) &&  (ta_hour<Sta[total_sta].b_finish_hour || (ta_hour==Sta[total_sta].b_finish_hour && ta_minute<=Sta[total_sta].b_finish_minute)) && (ta_hour>Sta[total_sta].b_start_hour || (ta_hour==Sta[total_sta].b_start_hour && ta_minute>=Sta[total_sta].b_start_minute))){
		o=0;
		printf("��վʱ��: %d:%g  ��վʱ��: %d:%g\n",ta_hour,ta_minute,ta_hour,ta_minute+1);}
		if(ta_minute>=57){
			ta_minute=ta_minute+3-60;
			ta_hour++;
		}
		else ta_minute=ta_minute+3;
	}
	if(o) printf("��ǰ�޷���Ҫ����г���\n"); 
	//�������濪ʼ�Ĳ��� 
	printf("�������յ����·�ź����:");
	scanf("%d %d",&d1,&d2);
	total_sta=locate_station(d1,d2);
	if(Sta[total_sta].exc==1) printf("����Ϊ��%s(ת��վ��)\n\n\n\n",Sta[total_sta].name);
	else printf("����Ϊ��%s(��ת��վ��)\n\n\n\n",Sta[total_sta].name); 
	re:break;
	}//end of case 3���������յ� 
	
	/*---����4:���˲�ѯ---*/ 
	case 4:{
	/*�ж��Ƿ���Ҫ����*/
	if(b1==d1){
	int m=b1;
	int start,finish;//��־���ķ�Χ 
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
	if(key[start][1]>=b2&& key[start][1]>=d2) goto hello;
	if(key[finish][1]<=b2&& key[finish][1]<=d2) goto hello;
	for(i=start;i<=finish-1;i++){
		if(key[i][1]<=b2&& key[i][1]<=d2 && key[i+1][1]>=b2 && key[i+1][1]>=d2) goto hello;
	}	
	}
	/*��Ҫ�����Ż�ͼ�����*/ 
	optimization();
	order_of_start=add_points(b1,b2);
	order_of_finish=add_points(d1,d2);
	dimension=56;
	if(order_of_start==57 || order_of_start==56) dimension++;
	if(order_of_finish==57 || order_of_finish==56) dimension++;
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,1); 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_distance,1);
	/*���洦������ROUTE��ʵ�ֶ�·�����������*/
	if(ROUTE[0][0]==0 &&ROUTE[1][0]==0 &&ROUTE[2][0]==0 &&ROUTE[3][0]==0) printf("���ڵ������رգ����黻��������ͨ����!\n\n\n");
	else{
	//�����ظ���·��
	for(i=0;i<3;i++){
		if(ROUTE[i][0]==1){
			for(j=i+1;j<4;j++){
				if(ROUTE[j][0]==1 && ROUTE[i][7]==ROUTE[j][7]) ROUTE[j][0]=0;
			}
		}
	}
	printf("\n");
	//�������ʱ��Ĵ洢 
	max_time=0; 
	for(i=0;i<4;i++){
		if(ROUTE[i][0]==1 &&ROUTE[i][1]>max_time) max_time=ROUTE[i][1];
	}
	//����ʱ��˳�����
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("����·���Ƽ�����ʱ����С��������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<4;i++){
			if(ROUTE[i][1]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][1];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else fp=fopen("tdata7.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	//����Ʊ�۽������ 
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("�����Ƽ�·����Ʊ���ɵ͵�������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<4;i++){
			if(ROUTE[i][3]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][3];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else fp=fopen("tdata7.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	//��������ʱ��������
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("����·���Ƽ�������ʱ����С��������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<4;i++){
			if(ROUTE[i][2]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][2];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else fp=fopen("tdata7.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	} 
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	printf("������Ҫ�ܿ�ӵ���̶Ƚϸߵ�·��,�밴6�������ܹ����̵����ӵ���ȣ����ǽ�Ϊ�����½���·���Ƽ���\n");
	}//end of else
	goto transfer;
	
		/*����Ҫ�����Ż�ͼ�����*/ 
	hello:
	i=locate_station(b1,b2);
	j=locate_station(d1,d2);
	if(no_transfer(i,j)==0) printf("���ڵ������رգ����黻��������ͨ���ߣ�\n\n\n");
	transfer:
	break;
	}//end of case 4���˲�ѯ 
	
	/*---����5:�ֶ�����������---*/ 
	case 5:{
	printf("���ֶ����������� ,��*��ʼ,��#����(��ʽΪ:������·��,��ʼʱ��,����ʱ��,ӵ���̶�)\n");
	for(i=0;i<7;i++) mannul_crowding[i][0]=0;//������0 
	char a;
	getchar(); 
	while(getchar()!='#'){
		int num;
		scanf("%d",&num);
		scanf("%d %d %d %d %d",&mannul_crowding[num][1],&mannul_crowding[num][2],&mannul_crowding[num][3],&mannul_crowding[num][4],&mannul_crowding[num][5]);
		mannul_crowding[num][0]=1;
	}
	break;
	}//end of case 5 
	
	/*---����6���ܿ�ӵ��---*/ 
	case 6:{
	printf("������������̵�ӵ����:"); 
	scanf("%d",&tolerance);
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,1); 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_distance,1);
	set_crowding();
	update_djs_time();
	//������ʱ�������ٴν�����·������ 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,2); 
	//�����ظ�·��
	for(i=0;i<5;i++){
	if(ROUTE[i][0]==1){
		for(j=i+1;j<6;j++){
			if(ROUTE[j][0]==1 && ROUTE[i][7]==ROUTE[j][7]) ROUTE[j][0]=0;
			}
		}
	}
	if(ROUTE[0][0]==0 &&ROUTE[1][0]==0 &&ROUTE[2][0]==0 &&ROUTE[3][0]==0 && ROUTE[4][0]==0 &&ROUTE[5][0]==0) printf("�Բ���û��������Ҫ���·���Ƽ���\n\n");
	else{
	//��ʱ�������� 
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("����·���Ƽ���ʱ����С��������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<6;i++){
			if(ROUTE[i][1]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][1];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else if(min_num==3) fp=fopen("tdata7.txt", "r+");
			else if(min_num==4) fp=fopen("tdata8.txt", "r+");
			else fp=fopen("tdata9.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	//��Ʊ�����
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("����·���Ƽ���Ʊ���ɵ͵�������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<6;i++){
			if(ROUTE[i][3]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][3];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else if(min_num==3) fp=fopen("tdata7.txt", "r+");
			else if(min_num==4) fp=fopen("tdata8.txt", "r+");
			else fp=fopen("tdata9.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	//������ʱ��������� 
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("����·���Ƽ�������ʱ����С��������!\n");
	while(k){
		k=0;
		min=1000;
		for(i=0;i<6;i++){
			if(ROUTE[i][2]<min && ROUTE[i][0]==1 &&ROUTE[i][8]==1){
				min=ROUTE[i][2];
				min_num=i;
				k=1;
			}
		}
		if(k){
			FILE *fp;
			if(min_num==0) fp=fopen("tdata4.txt", "r+");
			else if(min_num==1) fp=fopen("tdata5.txt", "r+");
			else if(min_num==2) fp=fopen("tdata6.txt", "r+");
			else if(min_num==3) fp=fopen("tdata7.txt", "r+");
			else if(min_num==4) fp=fopen("tdata8.txt", "r+");
			else fp=fopen("tdata9.txt", "r+");
			char c;
			printf("********************************************************************\n");
			printf("��ʱ��Ϊ %g Ԥ�Ƶ���ʱ��%g:%g\n�ܾ���Ϊ %g Ʊ��Ϊ:%g\n�ۺ�ӵ����Ϊ %g ����ʱ��Ϊ %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//��ע�������Ѿ������� 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	}//end of else
	break;
}//end of case 5

}//end of switch
	printf("1.��·��Ϣ��ѯ 2.վ����Ϣ��ѯ 3.������ʼվ����յ�վ 4.���˲�ѯ 5.�ֹ�����ӵ���� 0.�˳�ϵͳ\n");
	scanf("%d",&option);
}//end of while


	/*����free����̬����Ŀռ�*/
	for(i=0;i<Total_sta;i++){
		struct roadx* fp1=Sta[i].road_f;
		struct roadx* fp2;
		while(fp1!=NULL){
			fp2=fp1->road_n;
			free(fp1);
			fp1=fp2;
		}
	}
	return 0;
}

/*ȷ��վ����Sta�����е�λ�ú���������Ϊվ�����·�ź���ţ����Ϊ��վ����վ������Sta�е�λ��*/ 
int locate_station(int m,int n){
	int order;
	int start_order;
	if(m<5) {
		order=Line[m-1].start-1+n;
	}
	else {
		order=Line[m-2].start-1+n;
	}
	return order;
}

/*ƥ���г�ʱ�̱��������ݵ�ǰʱ��hour��minute���ø�վ������һ������ͷ��򳵵ĵ�վʱ�����վʱ�䡣����Ϊվ����Sta�����е�λ�ã����Ϊ�ı�վ��ṹ���е�������ĵ�վ����վʱ��*/ 
int set_time_of_station(int total_sta){
	//����վʱ������� 
	if(hour<Sta[total_sta].a_start_hour || (hour==Sta[total_sta].a_start_hour && minute<=Sta[total_sta].a_start_minute)){
		Sta[total_sta].a_arrive_hour=Sta[total_sta].a_start_hour;
		Sta[total_sta].a_arrive_minute=Sta[total_sta].a_start_minute;
	}
	else{
		Sta[total_sta].a_arrive_hour=hour;
		if((minute-((int)(minute/3))*3)==0) Sta[total_sta].a_arrive_minute=minute;
		else Sta[total_sta].a_arrive_minute=((((int)(minute/3))+1)*3)%60;
		if(Sta[total_sta].a_arrive_minute==0 && minute!=0) Sta[total_sta].a_arrive_hour=hour+1;
	} 
	
	//������վʱ�������
	Sta[total_sta].a_leave_hour=Sta[total_sta].a_arrive_hour;
	Sta[total_sta].a_leave_minute=Sta[total_sta].a_arrive_minute+1;
	
	//����վʱ�������
	if(hour<Sta[total_sta].b_start_hour || (hour==Sta[total_sta].b_start_hour && minute<=Sta[total_sta].b_start_minute)){
		Sta[total_sta].b_arrive_hour=Sta[total_sta].b_start_hour;
		Sta[total_sta].b_arrive_minute=Sta[total_sta].b_start_minute;
	}
	else{
		Sta[total_sta].b_arrive_hour=hour;
		if(minute-((int)(minute/3))*3==0) Sta[total_sta].b_arrive_minute=minute;
		else Sta[total_sta].b_arrive_minute=((((int)(minute/3))+1)*3)%60;
		if(Sta[total_sta].b_arrive_minute==0 && minute!=0) Sta[total_sta].b_arrive_hour=hour+1;
	} 
	
	//������վʱ�������
	Sta[total_sta].b_leave_hour=Sta[total_sta].b_arrive_hour;
	Sta[total_sta].b_leave_minute=Sta[total_sta].b_arrive_minute+1;
	return 1;
}


