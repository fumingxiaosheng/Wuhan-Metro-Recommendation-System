#ifndef _EXSTA_H_
#define _EXSTA_H_
/*-------------------ȫ�ֱ����ⲿ������-------------------------*/ 
	extern struct linex Line[7];//��· 
	extern struct stationx Sta[230];//վ�� 
	extern int Total_sta;//��վ���� 
	extern int key[56][2];//��¼�ɻ���վ�����кŵļ����� 
	extern float djs_time[58][58];//��ͼ��ʱ�����
	extern float djs_distance[58][58];//��ͼ�ľ������ 
	extern int hour;//���µ�Сʱ�� 
	extern float minute; //���µķ����� 
	extern int start_hour;
	extern float start_minute;//�տ�ʼ��ʱ�� 
	extern float ROUTE[6][9];////�ֱ��Ӧ��������·��,�ֱ�Ϊ0��������� 1����ʱ�� 2����Ȩʱ�� 3: Ʊ�� 4: �����ʱ��֮ʱ 5�������ʱ��֮�� 6���ܾ��� 
	extern int mannul_crowding[8][6];//�����ֶ����õ��������Ĵ洢���ֱ�Ϊ�Ƿ�洢����·�ţ���ʼʱ����ʼ�֣�����ʱ�������֣�ӵ���� 
	extern int b1,b2,d1,d2;//��ʼ���յ�����к�
	extern int order_of_start,order_of_finish;//��ʼ����յ���ھ����е����к�
	extern int tolerance;//�˿͵ĳ˳����̶� 
	extern float max_time;//�洢�������̶�ǰ����ȡ·���Ĵ����ʱ�� 
#endif
