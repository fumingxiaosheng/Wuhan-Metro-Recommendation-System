/*-----------------------------------------------------ͷ�ļ���------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*----------------------------------------------��c�ļ���ȫ�ֱ�����---------------------------------------------------------------*/ 
unsigned short int temp; //��ʱ�������� 
int length;  //����ԭ�ļ����� 

/*----------------------------------------����������Ҫ����encrypto��decrypto����---------------------------------------------------*/
/*���ܺ�������users�ļ��е����ݼ��ܴ洢��enusers�ļ���*/ 
void encrypto(){
	int i=0;
	FILE *fp1=fopen("users.txt","rb");
	FILE *fp2=fopen("enusers.txt","w");//���ԭ�е��ļ� 
	fclose(fp2);
	fseek(fp1,0,2);//��ָ��ƫ�Ƶ��ļ�β�� 
	length=ftell(fp1); 
	fseek(fp1,0,0);
	fp2=fopen("enusers.txt","wb");
	while(i<length/2) //ѭ����fp1�ķǼ�������д��fp2��  
   {
    fread(&temp,sizeof(unsigned short int),1,fp1);
    temp^=4143;
    fwrite(&temp,sizeof(unsigned short int),1,fp2);
    i++;
   }
   fclose(fp1);
   fclose(fp2);
}

/*���ܺ�������enusers�ļ��е����ݽ�����users��*/ 
void decrypto(){
	int i=0;
	FILE *fp1=fopen("enusers.txt","rb");
	FILE *fp2=fopen("users.txt","wb");
	fseek(fp1,0,2);//��ָ��ƫ�Ƶ��ļ�β�� 
	length=ftell(fp1);
	rewind(fp1); 
	while(i<length/2) //ѭ����fp1�ķǼ�������д��fp2��  
   {
    fread(&temp,sizeof(unsigned short int),1,fp1);
    temp^=4143;
    fwrite(&temp,sizeof(unsigned short int),1,fp2);
    i++;
   }
   fclose(fp1);
   fclose(fp2);
}
