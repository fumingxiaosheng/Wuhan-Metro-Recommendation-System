/*---------------------------------ͷ�ļ�������--------------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h>
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------����������------------------------------------------------------------*/ 
extern void encrypto();
extern void decrypto();

/*------------------------����������Ҫ����registers��Input_login��reback����--------------------------------*/ 
/*ע���˺ź������Ƚ����ܺ���ļ�enusers���н���Ϊusers������users�ļ�����ע�������ע��ɹ�������Ѿ�д�����û���users�ļ���enusers�ļ�
���и��£�������users�ļ�*/ 
void registers()  //���ṹ��Ĵ�С��һ��д����߶���1���ṹ���С
     {    
         users a,b;//�ṹ�� The_users ����������
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("��ӭ����ע����棡\n");
         decrypto();//�����ܵ�������ʱ�����users�ļ��� 
         fp = fopen("users.txt","r");
         fread(&b, sizeof(struct The_users), 1, fp); //����һ���ṹ���ַ��� ��b
          printf("�������˺�\n");
         scanf("%s",&a.id);
         while (1)
         {    
             if (strcmp(a.id, b.id)) /*������������*/
             {
                 if (!feof(fp))    /*���δ���ļ�β*/  
                 {
                     fread(&b, sizeof(struct The_users), 1, fp);
                 }
                 else
                     break;
             }
             else

             {   
                 printf("���û����Ѵ��ڣ�������ע�ᣡ\n"); 
                 fclose(fp);
                 return;      
             }
         }
         printf("������������\n");
         scanf("%s",&a.name);
         printf("�������Ա�(f(Ů)/m(��))��\n");
         scanf(" %c",&a.sex);
         do{
         	if(a.sex != 'f' && a.sex != 'm'){
			 	printf("�Ա�����������������룡\n");
		        scanf("%c",&a.sex);
			 }
		 }while(a.sex != 'f' && a.sex != 'm');
		 getchar();
         printf("������绰���룺\n");
         scanf("%ld",&a.phone);
         printf("����������\n");
         scanf(" %s",&a.pwd);
         printf("��ȷ������\n");
         scanf(" %s",&temp);
		 do{
         	if(!strcmp(a.pwd,temp)){
         		fp = fopen("users.txt","a");
		         fwrite(&a, sizeof(struct The_users), 1, fp);
		         printf("�˺�ע��ɹ������¼��\n"); 
		         fclose(fp);
				 goto jiami;
			 }else{
			 	printf("�������벻ƥ�䣡���������룡\n");
		         scanf("%s",&a.pwd);
		         printf("��ȷ������\n");
		         scanf("%s",&temp);
			 }
		 }while(1);
		 //���´洢�����ݼ��ܵ�enusers��
		 jiami:encrypto();
		 //���users�ļ��е����ݣ�����֤�� 
		fp=fopen("users.txt","w");
		fclose(fp);
		return ;
     }

/*��¼�������Ƚ����ܺ���ļ�enusers���н���Ϊusers������users�ļ����е�¼��������������֮ǰ���users�ļ��е�����*/ 
int Input_login()
{
    users a,b;//����ṹ��The_users����
    FILE *fp;
    printf("��ӭ������¼���棡\n");
    decrypto();//���������ݽ��н��ܵ�users�ļ��� 
    fp = fopen("users.txt","r");
    fread(&b, sizeof(struct The_users), 1, fp); //����һ���ṹ���ַ��� д��b
    printf("�������˺�\n");
    scanf("%s",&a.id);   
    while (1)
           {   
	           if (strcmp(a.id, b.id)==0)         //����д��û���
	           {
	               break;       
	           }
	           else 
	           {
	               if (!feof(fp))  //����ļ�û�ж���                            
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }
	               else
	               {
	                   printf("���û���������!\n");
	                   fclose(fp);  
					   goto qingchu;        
	               }
	           }
       }
       printf("����������\n");
       	scanf("%s",&a.pwd); 
       	int k=3;
    do{   
		if (strcmp(a.pwd, b.pwd)==0)            /*�������ƥ��*/ 
	       {  
	          fclose(fp);
	          Sleep(500);
	          fp=fopen("users.txt","w"); 
				fclose(fp);
				return 1;
	          }
	       else  
	       {    printf("���벻��ȷ!��������������\n");
	       		scanf("%s",&a.pwd);         
	       }
	       k--;//������������ʾ�һ����� 
	}while(strcmp(a.pwd, b.pwd)==0 && k);
    printf("��������3���һ����룡\n");
    //���users�ļ��е����� 
	qingchu:
	fp=fopen("users.txt","w"); 
	fclose(fp);
	return 0;
}

/*�һ����뺯�����Ƚ����ܺ���ļ�enusers���н���Ϊusers������users�ļ������һ������������������֮ǰ���users�ļ��е�����*/ 
void reback()  //���ṹ��Ĵ�С��һ��д����߶���1���ṹ���С
     {    
         users a,b;//�ṹ�� The_users ����������
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("��ӭ�����һ�������棡\n");
         decrypto();//���������ݽ��н��ܵ�users�ļ���
         fp = fopen("users.txt","r");
    	fread(&b, sizeof(struct The_users), 1, fp); //����һ���ṹ���ַ��� д��b
    	printf("�������˺�\n");
    	scanf("%s",&a.id);   
             while (1)
           {   
	           if (strcmp(a.id, b.id)==0)//����д��û���
	           {
	               break;       
	           }       
	           else 
	           {
	               if (!feof(fp))//����ļ�û�ж���                        
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }   
	               else
	               {
	                   printf("���û��������ڣ����������룡\n");
	                   fclose(fp);  
					   goto xiaoshi;   
	               }
	           }
       }
         printf("������������\n");
         scanf("%s",&a.name);
         do{
         	if(strcmp(a.name,b.name)){
			 	printf("�����������\n");
		        goto xiaoshi;
			 }
		 }while(strcmp(a.name,b.name));
         printf("������绰���룺\n");
         scanf("%ld",&a.phone);
         do{
         	if(a.phone != b.phone){
			 	printf("�绰�����������\n");
		        goto xiaoshi;
			 }
		 }while(a.phone != b.phone);
        printf("���������ǣ�%s\n",b.pwd);
        xiaoshi://����users�ļ�  
        fp=fopen("users.txt","w"); 
		fclose(fp);
		return;
}
