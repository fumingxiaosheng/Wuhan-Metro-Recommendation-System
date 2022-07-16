#ifndef _GLOBAL_H_
#define _GLOBAL_H_
/*-------------------ȫ�ֱ���������-------------------------*/ 
	struct linex Line[7];//��· 
	struct stationx Sta[230];//վ�� 
	int Total_sta=0;//��վ���� 
	int key[56][2];//��¼�ɻ���վ�����кŵļ����� 
	float djs_time[58][58];//��ͼ��ʱ�����
	float djs_distance[58][58];//��ͼ�ľ������ 
	int hour;//���µ�Сʱ�� 
	float minute; //���µķ����� 
	int start_hour;
	float start_minute;//�տ�ʼ��ʱ�� 
	float ROUTE[6][9];//�ֱ��Ӧ��������·��,�ֱ�Ϊ0��������� 1����ʱ�� 2����Ȩʱ�� 3: Ʊ�� 4: �����ʱ��֮ʱ 5�������ʱ��֮�� 6���ܾ��� 
	int mannul_crowding[9][6];//�����ֶ����õ��������Ĵ洢���ֱ�Ϊ�Ƿ�洢����·�ţ���ʼʱ����ʼ�֣�����ʱ�������֣�ӵ���� 
	int b1,b2,d1,d2;//��ʼ���յ�ľ���λ�� 
	int order_of_start,order_of_finish;//��ʼ����յ���ھ����е����к� 
	int tolerance;//�˿͵ĳ˳����̶� 
	float max_time;//�洢�������̶�ǰ����ȡ·���Ĵ����ʱ�� 
/*-------------------������������--------------------------*/
extern int read(void);
extern int optimization(void);
extern int add_points(int,int);
extern int Dijkstra(int,int,int,float (*)[58],int);
extern int set_crowding();
extern int update_djs_time();
extern int no_transfer(int,int);
extern void Create_File();
extern void registers();
extern int Input_login();
extern void reback();
#endif
