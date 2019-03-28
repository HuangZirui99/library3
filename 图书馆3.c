#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N sizeof(struct BOOK)
 
struct BOOK        //图书信息 
{
	char number[10];   //登录号 
	char name[10];     //书名 
	float price;       //价格 
	int num;         //数量 
	int x;
	struct BOOK *next;   //指针域 
};
typedef struct BOOK Book;
typedef Book *book;	 

struct STUDENT       
{
	char number[10];   //学号 
	char name[10];     //书名 
	char student_name[10];
	char username[10];
	char scert[10];
	struct STUDENT *next;
}; 
typedef struct STUDENT Student;
typedef Student *student;	

void menu();           //菜单 
void input_book();     //图书入库 
void input_student();  //xue sheng xin xi 
void save_book(book p);//将图书信息存入文件 
void save_student(student p);
void find_book();      //查询 
void print_book();    //图书总览 
void del_book();     //删除图书 
book ss();
student aa();
void print_student();
void stulogin();
void sturegist(); 

void menu()    
{   
	system("cls");  
	int t;
	printf("    LIBARRY MANAGEMENT SYSTEM   \n");	
	printf("|     【1】Student login       |\n");
	printf("|     【2】Student registe     |\n");	
	printf("|     【3】manager access      |\n");	
	scanf("%d",&t); 
	if(t==1) stulogin();
	if(t==2) sturegist();
	if(t==3){
		printf("[1]input book\n");
		printf("[2]delete book\n");
		scanf("%d",&t);
		if(t==1) input_book();
	    if(t==2)  del_book();
	}
}
book ss()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	int n=0;
	book head=NULL;
	book p2,p,pr=NULL;
	fp=fopen("mybook","ab+");     //以只读的方式打开文件 
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
		p=(book)malloc(N); //向内存申请一段空间 
	   fread(p,N,1,fp);     //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=p;
	      p2=p;
	    }
	    else             //创建链表 
	    {
	    	pr=p2;
	    	p2->next=p;//尾结点只向下一个新节点 
	    	p2=p;
		}
    }
    if(pr!=NULL) pr->next=NULL;
    else head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}

student aa()      //将文件中的内容读出到链表中，返回值为表头地址 
{
	FILE *fp;       //文件指针 
	int n=0;
	student head=NULL;
	student p2,p,pr=NULL;
	fp=fopen("Sinformation","ab+");     //以只读的方式打开文件 
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
	   	p=(student)malloc(N); //向内存申请一段空间 
	   fread(p,N,1,fp);     //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=p;
	      p2=p;
	    }
	    else             //创建链表 
	    {
	    	pr=p2;
	    	p2->next=p;
	    	p2=p;
		}
    }
    if(pr!=NULL) pr->next=NULL;
    else head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}
void input_book()    //图书录入 
{
	system("cls");
	char t;
	book p;
	p=(book)malloc(N);     //申请空间 
	printf("请输入图书登录号(小于10位数)：\n");    
	scanf("%s",&p->number);
	printf("请输入书名(小于10位数)：\n");
	scanf("%s",&p->name);
	printf("请输入图书价格：\n");
	scanf("%f",&p->price);
	printf("请输入图书数量：\n");
	scanf("%d",&p->num);
	save_book(p);
	system("cls");
	printf("| 保存成功！是否继续？  |\n");	
	printf("| 1.是             2.否 |\n");
	t=getch();
	if(t=='1')input_book();
	if(t=='2')menu();		 
} 

void input_student()    //学生信息录入 
{
	system("cls");
	student p;
	p=(student)malloc(N);     //申请空间 
	printf("请输入学号\n");    
	scanf("%s",&p->number);
	printf("请输入书名(小于10位数)：\n");
	scanf("%s",&p->name);
	printf("请输入姓名：\n");
	scanf("%s",&p->student_name);
	save_student(p);
	menu();		 
} 
void del_book()   //删除信息 
{
	do
	{
		system("cls");
		FILE *fp;
		book head,p,pre=NULL; 
		int j=0,x; 
		char name[10];
		char t,c,ch;
		head=ss();    //调用函数，返回表头地址 
		printf("请输入你要删除的图书的书名：");
		scanf("%s",name);
		p=head;
		while(p!=NULL)
		{
			p->x=0;
			p=p->next;
		}
		p=head;
		printf("**************图书信息*********************\n");
		printf("------------------------------------------\n");
		printf("登录号        书名          价格       数量\n");
		printf("---------------------------------------\n");
		while(p!=NULL)
		{
			if(p!=NULL&&strcmp(p->name,name)==0)
			{
				j++;
				printf("%d:%s%14s      %.2f%12d\n",j,p->number,p->name,p->price,p->num);
				p->x=j;
			}
			p=p->next;
		}
		if(j==0)                   //如果j=0，即没有进入前面的搜索循环，也就是没有找到相应的信息 
		{ 
			printf("没有找到相应的信息！(按0返回，按1重新搜索)");
			while(1)               //死循环是为了防止除0和1的其他按键干扰 
			{
				ch=getch();
				if(ch=='0')
				{
					menu();break;
				}
				else if(ch=='1')
				{
					break;
				}
			}
			if(ch=='1')     //如果输入的ch等于1，则结束本次循环 
			   continue;
		}
		while(1)
		{
			printf("请输入您要删除的图书的编号：");
			scanf("%d",&x);getchar();
			if(x>j||x==0)
			{
				printf("输入错误，请重新输入!");
			}
			else
			{
				break;
			}
		}
		printf("|     是否确认删除？ ");
		printf("| 1.是             2.否 |");
		printf("-------------------------");
		while(1)
		{
			t=getch();
			if(t=='1')
			{
				break;
			} 
			else if(t=='2')
			{
				menu();
			}
		}
		p=head;
		while(p!=NULL&&p->x!=x)
		{
			pre=p;
			p=p->next;
		}
		if(p!=NULL)
		{
			if(pre==NULL)
			{
				head=head->next;
			}
			else
			{
				pre->next=p->next;
			}
		}
		free(p);
		fp=fopen("mybook","wb");
		if(fp==NULL)
		{
			printf("cannot open file"); 
		}
		if(fwrite(head,N,1,fp)!=1)
		{
			printf("write error!"); 
		}
		fclose(fp);
		if(head!=NULL)
		{
			p=head->next;
			fp=fopen("mybook","ab");
			if(fp==NULL)
			{
				printf("cannot open file");
			}
			while(p!=NULL)
			{
				if(fwrite(p,N,1,fp)!=1)
				{
					printf("write error!");
				}
				p=p->next;
			}
			fclose(fp);
		}
		system("cls");
		printf("|  删除成功，是否继续？ |\n");
		printf("| 1.是             2.否 |\n");
		while(1)
		{
			c=getch();
			if(c=='1')
			{
				break;
			}
			else if(c=='2')
			{
				menu();
			}
		}
	}while(1);
}


 
void print_book()   //图书总览 
{
	system("cls");
	book head,p;
	int i=11;
	int sum=0;
	head=ss();
	printf("*********************图书总览*****************\n");
	printf("----------------------------------------------\n");
	printf("登录号        书名             价格        数量\n");
	printf("----------------------------------------------\n");
	p=head;
	while(p!=NULL)
	{
		printf("%s %14s             %.2f%   12d\n",p->number,p->name,p->price,p->num);
		i++;
		sum+=p->num;//计算图书总量 
		p=p->next;
	}
	printf("图书总量为：%d\n",sum);
	printf("按任意键返回");
	getch();//不回显函数
	menu(); 
}
void print_student()   //学生借书信息 
{
	system("cls");
	student head,p;
	head=aa();
	printf("---------------------------------\n");
	printf("学号        书名          姓名\n");
	printf("----------------------------------\n");
	p=head;
	while(p!=NULL)
	{
		printf("%s %14s             %s\n",p->number,p->name,p->student_name); 
		p=p->next;
	}
	printf("按任意键返回");
	getch();//不回显函数
	menu(); 
}
 
void find_book()  //查询图书 
{	
		system("cls");  //清屏 
		char t;
		printf(" 【1】图书查询\n");
		printf(" 【0】返回\n");
		t=getch();
		if(t=='0') menu();
	    if(t=='1')
	    {
	    	system("cls");
	  		book head,p;
			int i=11;
			head=ss();
			char name[10];
			printf("请输入您要查询图书的书名：\n");
			gets(name);
			p=head;	
			printf("登录号        书名          价格      数量\n");
			printf("----------------------------------------\n");
			while(p!=NULL)
			{
				if(p!=NULL&&strcmp(p->name,name)==0)
				{
			
					printf("%s%14s             %.2f%12d\n",p->number,p->name,p->price,p->num);
					i++;
				}
				p=p->next;
			}
			printf("按任意键返回！");
			getch();
			find_book();	
		}
}

void save_book(book p)   //将p中内容写入文件 
{
	FILE *fp;    //文件指针 
	fp=fopen("mybook","ab");   //以追加的方式打开名字为mybook的二进制文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fwrite(p,N,1,fp)!=1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中 
	{
		printf("write error");
	}
	fclose(fp);    //关闭文件  
 } 
void save_student(student p)   //将p中内容写入文件 
{
	FILE *fp;    //文件指针 
	fp=fopen("Sinformation","ab");   //以追加的方式打开名字为mybook的二进制文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fwrite(p,N,1,fp)!=1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中 
	{
		printf("write error");
	}
	fclose(fp);    //关闭文件  
 }
void sturegist()
{
	system("cls");
	printf("please input your user name");

}
void stulogin()
{
	system("cls");
	printf("please input your user name");
	
}
main()  
{
	menu();
}  
