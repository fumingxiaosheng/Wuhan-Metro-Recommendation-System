#ifndef _DFSTRUCT_H_
#define _DFSTRUCT_H_
/*------------------------------�ṹ��Ķ���----------------------------*/ 
typedef struct The_users   //typedef ���Զ���ṹ�����
{
    char id[11]; //�˺� 
    char pwd[20]; //���� 
    char name[15];//����Ϊ�ַ��� 
    char sex; //�Ա�Ϊ�����ַ�
	long phone; //�绰����Ϊ������ 
}users; 
struct linex{
	int num_of_line;//��ʶ��·��� 
	int ful_cap;//��ʶ��Ա����
	float total_line_len;//��·�ܳ��� 
	float ava_len;//ÿһ·�ε�ƽ������ 
	int nums_of_sta;//վ����Ŀ 
	int start;//��Ǹ�����·��վ�����鿪ʼ��λ��
	int start_of_trans;//��ʶ������·��һ�����˵��ڼ�����ʼ��λ�� 
	float cro_del;//��ʾ����·��ӵ���̶ȣ�����·�ε�ӵ���̶ȳ������̶̳ȣ�������Ϊ1000,����Ϊ1 
};
struct stationx{
	int num_of_line;int num_of_sta;
	char name[100];//վ��ı�ʶ����·�ţ����ƣ� 
	int exc;//�Ƿ񻻳�վ�㣬���ǣ���Ϊ1.����Ϊ0
	int a_start_hour;float a_start_minute;//�����г��״ε���ʱ�䣻
	int b_start_hour;float b_start_minute;//�����г��״ε���ʱ�� 
	int a_finish_hour;float a_finish_minute;//�����г����һ�ε���ʱ�䣻
	int b_finish_hour;float b_finish_minute;//�����г����һ�ε���ʱ��
	int a_arrive_hour;float a_arrive_minute;//���򼴽������ʱ�䣻 
	int a_leave_hour;float a_leave_minute;//�����г�����վʱ�䣻 
	int b_arrive_hour;float b_arrive_minute;//���򼴽������ʱ�䣻 
	int b_leave_hour;float b_leave_minute;//�����г�����վʱ�䣻
	struct roadx* road_f;//ָ��ǰ�ĵ�һ��·��
	struct roadx* road_l;//ָ��ǰ�����һ��·��
};
 struct roadx{	
	int num_of_line;int num_of_sta;//��ͷ�����к�  
	float tra_time;//��ʾ�����ڸ�·�εĳ˳�ʱ��
	float distance;//��ʾ��·�εĳ��ȣ����ǻ��ߵĻ����򳤶�Ϊ0 	
	struct roadx* road_n;//ָ����һ·�� 
};
#endif
