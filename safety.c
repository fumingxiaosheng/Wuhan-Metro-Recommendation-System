/*-----------------------------------------------------头文件区------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h> 
#include"dfstruct.h"
#include"exsta.h"

/*----------------------------------------------该c文件的全局变量区---------------------------------------------------------------*/ 
unsigned short int temp; //临时储存数据 
int length;  //储存原文件长度 

/*----------------------------------------函数区，主要包括encrypto和decrypto函数---------------------------------------------------*/
/*加密函数，将users文件中的数据加密存储入enusers文件中*/ 
void encrypto(){
	int i=0;
	FILE *fp1=fopen("users.txt","rb");
	FILE *fp2=fopen("enusers.txt","w");//清空原有的文件 
	fclose(fp2);
	fseek(fp1,0,2);//将指针偏移到文件尾处 
	length=ftell(fp1); 
	fseek(fp1,0,0);
	fp2=fopen("enusers.txt","wb");
	while(i<length/2) //循环将fp1的非加密数据写入fp2中  
   {
    fread(&temp,sizeof(unsigned short int),1,fp1);
    temp^=4143;
    fwrite(&temp,sizeof(unsigned short int),1,fp2);
    i++;
   }
   fclose(fp1);
   fclose(fp2);
}

/*解密函数，将enusers文件中的数据解密入users中*/ 
void decrypto(){
	int i=0;
	FILE *fp1=fopen("enusers.txt","rb");
	FILE *fp2=fopen("users.txt","wb");
	fseek(fp1,0,2);//将指针偏移到文件尾处 
	length=ftell(fp1);
	rewind(fp1); 
	while(i<length/2) //循环将fp1的非加密数据写入fp2中  
   {
    fread(&temp,sizeof(unsigned short int),1,fp1);
    temp^=4143;
    fwrite(&temp,sizeof(unsigned short int),1,fp2);
    i++;
   }
   fclose(fp1);
   fclose(fp2);
}
