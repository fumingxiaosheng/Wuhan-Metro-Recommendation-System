#include<stdio.h>
#include<stdlib.h>
#include"dfstruct.h"
#include"global.h"
int locate_station(int m,int n);
int set_time_of_station(int total_sta);
int main(void){ 
	/*------------------------构建完整的武汉地铁图---------------------------*/
	int i,j;	
	ROUTE[1][1]=0; //作处理需要 
	if(read()==1 &&optimization()==1) printf("欢迎乘坐武汉地铁！\n");
	/*----------------------------登录界面-----------------------------------*/ 
	int option=1;
	while(option){
		printf("1.登陆账号 2.注册账号 3.找回密码 0.退出系统\n");
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
	chaxun:printf("登陆成功，欢迎使用！\n");
	/*-----------------------------系统界面-----------------------------------*/ 
	printf("1.线路信息查询 2.站点信息查询 3.设置起始站点和终点站 4.换乘查询 5.手工设置拥挤度 0.退出系统\n");
	int dimension;//存储数组的维数
	float min;//用来表示当下的最小 
	int min_num; //用于最后文件输出时存储的当前应该输出的序列号 
	int k;//进行站点遍历的控制 和最后输出路径的控制 
	scanf("%d",&option);
	while(option){
		switch(option){
			/*---功能1：线路信息查询---*/ 
		case 1:{
				printf("请输入您需要查询的地铁线路号:");
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
			
			/*---功能2:站点信息查询---*/ 
		case 2:{
				printf("1:站点信息查询   0:退出该功能\n");
				scanf("%d",&k);
				while(k){
					int s_order;
					printf("请输入站点的线路号和站点序号:");
					scanf("%d %d",&i,&j);
					s_order=locate_station(i,j);
					printf("名称为:%s\n可抵达:\n",Sta[s_order].name);
					struct roadx* p=Sta[s_order].road_f;
					while(p!=NULL){
						int a,b,c;
						a=p->num_of_line;
						b=p->num_of_sta;
						c=locate_station(a,b);
						printf("%d %d %s\n",a,b,Sta[c].name);
						p=p->road_n;
					}
					printf("1:站点信息查询   0:退出该功能\n");
					scanf("%d",&k);
				} 
			break;
		}//end of case 2
		
		/*---功能3:设置起始站点和终点站---*/ 
	case 3:{
	int total_sta;
	tolerance=100;//不设置相应的容忍度 
	printf("请输入当下时刻:");
	scanf("%d %f",&start_hour,&start_minute);
	hour=start_hour;
	minute=start_minute; 
	printf("请输入起点的线路号和序号:"); 
	scanf("%d %d",&b1,&b2);
	//找到该站点所在的位置 
	total_sta=locate_station(b1,b2);
	set_time_of_station(total_sta);
	if(Sta[total_sta].exc==1) printf("名称为：%s(转乘站点)\n",Sta[total_sta].name);
	else printf("名称为：%s(非转乘站点)\n",Sta[total_sta].name);
	//这是新加的匹配列车时刻表功能 
	printf("以下为当前时刻前15分钟至后15分钟的列车时刻表：\n");
	//现在框定行驶的范围
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
	int u,o=1;//o用作开关 
	//正向的时刻表 
	printf("正向：\n");
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
		printf("到站时间: %d:%g  离站时间: %d:%g\n",ta_hour,ta_minute,ta_hour,ta_minute+1);}
		if(ta_minute>=57){
			ta_minute=ta_minute+3-60;
			ta_hour++;
		}
		else ta_minute=ta_minute+3;
	}
	if(o) printf("当前无符合要求的列车！\n"); 
	//反向的时刻表
	o=1;
	printf("反向:\n");
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
		printf("到站时间: %d:%g  离站时间: %d:%g\n",ta_hour,ta_minute,ta_hour,ta_minute+1);}
		if(ta_minute>=57){
			ta_minute=ta_minute+3-60;
			ta_hour++;
		}
		else ta_minute=ta_minute+3;
	}
	if(o) printf("当前无符合要求的列车！\n"); 
	//这是下面开始的部分 
	printf("请输入终点的线路号和序号:");
	scanf("%d %d",&d1,&d2);
	total_sta=locate_station(d1,d2);
	if(Sta[total_sta].exc==1) printf("名称为：%s(转乘站点)\n\n\n\n",Sta[total_sta].name);
	else printf("名称为：%s(非转乘站点)\n\n\n\n",Sta[total_sta].name); 
	re:break;
	}//end of case 3设置起点和终点 
	
	/*---功能4:换乘查询---*/ 
	case 4:{
	/*判断是否需要换线*/
	if(b1==d1){
	int m=b1;
	int start,finish;//标志求解的范围 
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
	/*需要调用优化图的情况*/ 
	optimization();
	order_of_start=add_points(b1,b2);
	order_of_finish=add_points(d1,d2);
	dimension=56;
	if(order_of_start==57 || order_of_start==56) dimension++;
	if(order_of_finish==57 || order_of_finish==56) dimension++;
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,1); 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_distance,1);
	/*下面处理数组ROUTE，实现对路径的排序输出*/
	if(ROUTE[0][0]==0 &&ROUTE[1][0]==0 &&ROUTE[2][0]==0 &&ROUTE[3][0]==0) printf("由于地铁将关闭，建议换乘其他交通工具!\n\n\n");
	else{
	//处理重复的路段
	for(i=0;i<3;i++){
		if(ROUTE[i][0]==1){
			for(j=i+1;j<4;j++){
				if(ROUTE[j][0]==1 && ROUTE[i][7]==ROUTE[j][7]) ROUTE[j][0]=0;
			}
		}
	}
	printf("\n");
	//进行最大时间的存储 
	max_time=0; 
	for(i=0;i<4;i++){
		if(ROUTE[i][0]==1 &&ROUTE[i][1]>max_time) max_time=ROUTE[i][1];
	}
	//按照时间顺序输出
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("以下路径推荐按总时间由小到大排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	//按照票价进行输出 
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("以下推荐路径按票价由低到高排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
	//按照心理时间进行输出
	for(i=0;i<4;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("以下路径推荐按心理时间由小到大排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	} 
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	printf("如您想要避开拥挤程度较高的路段,请按6以设置能够容忍的最大拥挤度，我们将为您重新进行路线推荐！\n");
	}//end of else
	goto transfer;
	
		/*不需要调用优化图的情况*/ 
	hello:
	i=locate_station(b1,b2);
	j=locate_station(d1,d2);
	if(no_transfer(i,j)==0) printf("由于地铁将关闭，建议换乘其他交通工具！\n\n\n");
	transfer:
	break;
	}//end of case 4换乘查询 
	
	/*---功能5:手动配置人流量---*/ 
	case 5:{
	printf("请手动配置人流量 ,以*开始,以#结束(格式为:地铁线路号,开始时间,结束时间,拥挤程度)\n");
	for(i=0;i<7;i++) mannul_crowding[i][0]=0;//设置清0 
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
	
	/*---功能6：避开拥堵---*/ 
	case 6:{
	printf("请输入最大容忍的拥挤度:"); 
	scanf("%d",&tolerance);
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,1); 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_distance,1);
	set_crowding();
	update_djs_time();
	//更新完时间矩阵后，再次进行线路的增加 
	Dijkstra(dimension,order_of_start,order_of_finish,djs_time,2); 
	//处理重复路段
	for(i=0;i<5;i++){
	if(ROUTE[i][0]==1){
		for(j=i+1;j<6;j++){
			if(ROUTE[j][0]==1 && ROUTE[i][7]==ROUTE[j][7]) ROUTE[j][0]=0;
			}
		}
	}
	if(ROUTE[0][0]==0 &&ROUTE[1][0]==0 &&ROUTE[2][0]==0 &&ROUTE[3][0]==0 && ROUTE[4][0]==0 &&ROUTE[5][0]==0) printf("对不起，没有满足您要求的路径推荐！\n\n");
	else{
	//按时间进行输出 
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("以下路径推荐按时间由小到大排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	//按票价输出
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("以下路径推荐按票价由低到高排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	//按心理时间排序输出 
	for(i=0;i<6;i++) ROUTE[i][8]=1;
	k=1;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	printf("以下路径推荐按心理时间由小到大排序!\n");
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
			printf("总时间为 %g 预计到达时刻%g:%g\n总距离为 %g 票价为:%g\n综合拥挤度为 %g 心理时间为 %g\n",ROUTE[min_num][1],ROUTE[min_num][4],ROUTE[min_num][5],ROUTE[min_num][7],ROUTE[min_num][3],ROUTE[min_num][6],ROUTE[min_num][2]);
			while((c=fgetc(fp))!=EOF){
			printf("%c",c);
			}
			printf("********************************************************************\n\n\n\n");
			fclose(fp);
			ROUTE[min_num][8]=0;//标注这条线已经被访问 
	}
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"); 
	}//end of else
	break;
}//end of case 5

}//end of switch
	printf("1.线路信息查询 2.站点信息查询 3.设置起始站点和终点站 4.换乘查询 5.手工设置拥挤度 0.退出系统\n");
	scanf("%d",&option);
}//end of while


	/*以下free掉动态申请的空间*/
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

/*确定站点在Sta数组中的位置函数，输入为站点的线路号和序号，输出为该站点在站点数组Sta中的位置*/ 
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

/*匹配列车时刻表函数，根据当前时间hour，minute设置该站点的最近一班正向和反向车的到站时间和离站时间。输入为站点在Sta数组中的位置，输出为改变站点结构体中的正反向的到站和离站时间*/ 
int set_time_of_station(int total_sta){
	//正向到站时间的设置 
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
	
	//正向离站时间的设置
	Sta[total_sta].a_leave_hour=Sta[total_sta].a_arrive_hour;
	Sta[total_sta].a_leave_minute=Sta[total_sta].a_arrive_minute+1;
	
	//反向到站时间的设置
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
	
	//正向离站时间的设置
	Sta[total_sta].b_leave_hour=Sta[total_sta].b_arrive_hour;
	Sta[total_sta].b_leave_minute=Sta[total_sta].b_arrive_minute+1;
	return 1;
}


