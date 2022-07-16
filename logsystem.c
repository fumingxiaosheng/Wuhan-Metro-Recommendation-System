/*---------------------------------头文件声明区--------------------------------------------------------------*/ 
#include<stdio.h>
#include<stdlib.h>
#include"dfstruct.h"
#include"exsta.h"

/*------------------------------------函数声明区------------------------------------------------------------*/ 
extern void encrypto();
extern void decrypto();

/*------------------------函数区，主要包括registers、Input_login和reback函数--------------------------------*/ 
/*注册账号函数，先将加密后的文件enusers进行解密为users，利用users文件进行注册操作，注册成功后根据已经写入新用户的users文件对enusers文件
进行更新，最后清除users文件*/ 
void registers()  //按结构体的大小，一次写入或者读入1个结构体大小
     {    
         users a,b;//结构体 The_users 重命名定义
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("欢迎来到注册界面！\n");
         decrypto();//将解密的数据暂时存放在users文件中 
         fp = fopen("users.txt","r");
         fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 到b
          printf("请输入账号\n");
         scanf("%s",&a.id);
         while (1)
         {    
             if (strcmp(a.id, b.id)) /*如果两串不相等*/
             {
                 if (!feof(fp))    /*如果未到文件尾*/  
                 {
                     fread(&b, sizeof(struct The_users), 1, fp);
                 }
                 else
                     break;
             }
             else

             {   
                 printf("此用户名已存在！请重新注册！\n"); 
                 fclose(fp);
                 return;      
             }
         }
         printf("请输入姓名：\n");
         scanf("%s",&a.name);
         printf("请输入性别(f(女)/m(男))：\n");
         scanf(" %c",&a.sex);
         do{
         	if(a.sex != 'f' && a.sex != 'm'){
			 	printf("性别输入错误！请重新输入！\n");
		        scanf("%c",&a.sex);
			 }
		 }while(a.sex != 'f' && a.sex != 'm');
		 getchar();
         printf("请输入电话号码：\n");
         scanf("%ld",&a.phone);
         printf("请输入密码\n");
         scanf(" %s",&a.pwd);
         printf("请确认密码\n");
         scanf(" %s",&temp);
		 do{
         	if(!strcmp(a.pwd,temp)){
         		fp = fopen("users.txt","a");
		         fwrite(&a, sizeof(struct The_users), 1, fp);
		         printf("账号注册成功，请登录！\n"); 
		         fclose(fp);
				 goto jiami;
			 }else{
			 	printf("两次密码不匹配！请重新输入！\n");
		         scanf("%s",&a.pwd);
		         printf("请确认密码\n");
		         scanf("%s",&temp);
			 }
		 }while(1);
		 //将新存储的数据加密到enusers中
		 jiami:encrypto();
		 //清除users文件中的内容，销毁证据 
		fp=fopen("users.txt","w");
		fclose(fp);
		return ;
     }

/*登录函数，先将加密后的文件enusers进行解密为users，利用users文件进行登录操作，函数返回之前清空users文件中的内容*/ 
int Input_login()
{
    users a,b;//定义结构体The_users别名
    FILE *fp;
    printf("欢迎来到登录界面！\n");
    decrypto();//将加密内容进行解密到users文件中 
    fp = fopen("users.txt","r");
    fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 写入b
    printf("请输入账号\n");
    scanf("%s",&a.id);   
    while (1)
           {   
	           if (strcmp(a.id, b.id)==0)         //如果有此用户名
	           {
	               break;       
	           }
	           else 
	           {
	               if (!feof(fp))  //如果文件没有读完                            
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }
	               else
	               {
	                   printf("此用户名不存在!\n");
	                   fclose(fp);  
					   goto qingchu;        
	               }
	           }
       }
       printf("请输入密码\n");
       	scanf("%s",&a.pwd); 
       	int k=3;
    do{   
		if (strcmp(a.pwd, b.pwd)==0)            /*如果密码匹配*/ 
	       {  
	          fclose(fp);
	          Sleep(500);
	          fp=fopen("users.txt","w"); 
				fclose(fp);
				return 1;
	          }
	       else  
	       {    printf("密码不正确!请重新输入密码\n");
	       		scanf("%s",&a.pwd);         
	       }
	       k--;//多次输入错误提示找回密码 
	}while(strcmp(a.pwd, b.pwd)==0 && k);
    printf("建议输入3以找回密码！\n");
    //清空users文件中的内容 
	qingchu:
	fp=fopen("users.txt","w"); 
	fclose(fp);
	return 0;
}

/*找回密码函数，先将加密后的文件enusers进行解密为users，利用users文件进行找回密码操作，函数返回之前清空users文件中的内容*/ 
void reback()  //按结构体的大小，一次写入或者读入1个结构体大小
     {    
         users a,b;//结构体 The_users 重命名定义
         FILE *fp;
         char temp[20];
         int count = 0;
         printf("欢迎来到找回密码界面！\n");
         decrypto();//将加密内容进行解密到users文件中
         fp = fopen("users.txt","r");
    	fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块 写入b
    	printf("请输入账号\n");
    	scanf("%s",&a.id);   
             while (1)
           {   
	           if (strcmp(a.id, b.id)==0)//如果有此用户名
	           {
	               break;       
	           }       
	           else 
	           {
	               if (!feof(fp))//如果文件没有读完                        
	               {
	                   fread(&b, sizeof(struct The_users), 1, fp);
	               }   
	               else
	               {
	                   printf("此用户名不存在，请重新输入！\n");
	                   fclose(fp);  
					   goto xiaoshi;   
	               }
	           }
       }
         printf("请输入姓名：\n");
         scanf("%s",&a.name);
         do{
         	if(strcmp(a.name,b.name)){
			 	printf("姓名输入错误！\n");
		        goto xiaoshi;
			 }
		 }while(strcmp(a.name,b.name));
         printf("请输入电话号码：\n");
         scanf("%ld",&a.phone);
         do{
         	if(a.phone != b.phone){
			 	printf("电话号码输入错误！\n");
		        goto xiaoshi;
			 }
		 }while(a.phone != b.phone);
        printf("您的密码是：%s\n",b.pwd);
        xiaoshi://销毁users文件  
        fp=fopen("users.txt","w"); 
		fclose(fp);
		return;
}
