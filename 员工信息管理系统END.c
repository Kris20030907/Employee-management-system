/*
	实训项目名称：员工信息管理系统
	小组成员：杨国胜，王志创
	开始时间：2022年6月21日
	结束时间：(1)功能完成编写并整合完成时间: 2022年6月23日
			  (2)进行程序的美化和完善结束时间：2022年6月25日
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define N 100

int number; //全局变量，记录员工人数

typedef struct employee {
	int id;
	char name[20];
	char gender[10];
	int age;
	float wage;
	char address[30];
	char phonenumber[15];
} EMP;


int  Meum();
void Input(EMP *p);
void Output(EMP *p,int n);
void ShowHead();
void ShowLine();
int  read(EMP *emp);
void Writefile(EMP *p);
void Readfile(EMP *p);
void Delete(EMP *p);
void Searchbyid(EMP *p);
void Searchbyname(EMP *p);
void Search(EMP *p);
void add(EMP *emp);
void save(int m,EMP *emp);
void change(EMP *emp);
void sortwage(EMP *emp);
void sortage(EMP *emp);
void Sort(EMP *emp);
void Login();
void reset();
void Examine();

int main() {
	Login();
	EMP emp[N];
	Examine();
	number=read(emp);
	while(1) {
		int a=Meum();
		switch(a) {
			case 1:
				Input(emp);
				Writefile(emp);
				break;
			case 2:
				add(emp);
				break;
			case 3:
				Search(emp);
				break;
			case 4:
				change(emp);
				break;
			case 5:
				Readfile(emp);
				Delete(emp);
				break;
			case 6:
				Sort(emp);
				break;
			case 7:
				Readfile(emp);
				Output(emp,number);
				break;
			case 8:
				reset();
				break;
			case 0:
				printf("\n系统成功退出!\n") ;
				exit(0);
			default:
				printf("错误");
				break;
		}
	}
	return 0;
}

//系统菜单主界面
int Meum() {
	printf("\n************************员工信息管理系统**********************\n");
	printf("\n  \t1.  录入职工信息 \t\t 5.  删除职工信息");
	printf("\n  \t2.  添加职工信息 \t\t 6.  排序职工信息");
	printf("\n  \t3.  查询职工信息 \t\t 7.  浏览职工信息");
	printf("\n  \t4.  修改职工信息 \t\t 8.  重设管理密码");
	printf("\n  \t0.  退出系统");
	printf("\n\n************************************************************");
	int n;
	printf("\n请输入想使用的功能序号：");
	scanf("%d",&n);
	return n;
}


//输入员工信息到结构体数组中(按工号排序)
void Input(EMP *p) {
	int i,j;   
	printf("请输入录入员工人数：");
	scanf("%d",&number);    /*利用for循环对每一位员工的信息进行输入并存储到员工信息结构体中*/ 
	for(i=0; i<number; i++) {
		printf("\n请输入第%d位员工的员工号:",i+1);
		scanf("%d",&p[i].id);
		printf("请输入第%d位员工的姓名:",i+1);
		scanf("%s",&p[i].name);
		getchar();
		printf("请输入第%d位员工的性别:",i+1);
		scanf("%s",&p[i].gender);
		getchar();
		printf("请输入第%d位员工的年龄:",i+1);
		scanf("%d",&p[i].age);
		getchar();
		printf("请输入第%d位员工的工资:",i+1);
		scanf("%f",&p[i].wage);
		getchar();
		printf("请输入第%d位员工的住址:",i+1);
		scanf("%s",&p[i].address);
		getchar();
		printf("请输入第%d位员工的联系电话:",i+1);
		scanf("%s",&p[i].phonenumber);
		getchar();
	}
	system("cls");    //清屏操作，以防界面过于繁杂 
	printf("\n员工信息成功录入！\n");
	EMP t;  //定义一个EMP类型变量，作为两个EMP类型员工信息结构体交换媒介 
	            //冒泡排序法将员工信息按照员工号从小到大次序排列 
	for(i=0; i<number-1; i++)
		for(j=0; j<number-1-i; j++) {
			if(p[j].id>p[j+1].id) {
				t=p[j];
				p[j]=p[j+1];
				p[j+1]=t;
			}
		}
		//在switch-case语句中的"case 1："部分配合 Writefile(EMP *p);将员工信息写入文件"员工信息档案.txt"
}

//输出结构体数组中的信息(浏览员工信息)
void Output(EMP *p,int n) {
	int i;
	ShowHead();
	for(i=0; i<n; i++) {
		printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[i].id,p[i].name,p[i].gender,
		       p[i].age,p[i].wage
		       ,p[i].address,p[i].phonenumber);
		ShowLine();
	}
	getchar();
	char a;
	printf("\n\n输入回车返回主菜单:");
	a=getchar();
	if(a=='\n')
		system("cls");//输入完员工信息更简洁
}

//员工信息表头
void ShowHead() {
	printf("\t|员工号\t|姓名\t|性别\t|年龄\t|工资\t|住址\t\t|联系电话");
}

//分割线
void ShowLine() {
	printf("\t");
	for(int i=0; i<70; i++)
		printf("-");
}

//结构体数组写到文件中
void Writefile(EMP *p) {
	FILE *fp;   //按数据块形式将员工信息写入文件 
	fp=fopen("E:/员工信息档案.txt","w");
	fwrite(p,sizeof(EMP),number,fp);
	fclose(fp);
}

//文件信息读取到结构体数组中
void Readfile(EMP *p) {
	FILE *fp;
	fp=fopen("E:/员工信息档案.txt","r");
	if(fp==NULL) {
		printf("未找到文件");
		exit(0);
	} else {
		for(int i=0; !feof(fp); i++)
			fread(&p[i],sizeof(EMP),1,fp);
	}
	fclose(fp);
}

//删除员工信息
void Delete(EMP *p) {
	int i,n;
	int g;//用于判断是否继续进行删除员工的操作
	printf("请输入想要删除的员工号：");
	scanf("%d",&n);
	int flag=0;
	int k=0;
	for(i=0; i<number; i++) {
		if(p[i].id==n) {
			k=i;
			flag =1 ;
			break;
		}
	}
	if(flag==0) printf("无此员工号");
	else {
		printf("\n此员工的信息如下表:\n");
		ShowHead();
		printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[k].id,p[k].name,p[k].gender,
		       p[k].age,p[k].wage,p[k].address,p[k].phonenumber);
		ShowLine();
		printf("\n\n请确定是否删除此员工号:(1确认，0返回主菜单)");
		scanf("%d",&g);
		if(g==1) {
			for(; i<number-1; i++) p[i]=p[i+1];
			number--;
			Writefile(p);
			system("cls");
			printf("\n\n该员工信息删除成功\n\n") ;
		} else if(g==0) {
			system("cls");
		}	else {
			printf("你输入了非法数字，请重新进行该操作！\n\n");
			Delete(p);
		}
	}
}


//检索员工姓名
void Searchbyname(EMP *p) {
	char name[20];
	int i;
	int flag =0;//flag 用于判断是否
	printf("请输入想要查询的员工姓名：");
	scanf("%s",name);
	getchar();
	//判断是否找到并反馈
	for(i=0; i<number; i++) {
		if(strcmp(p[i].name,name)==0) {
			flag=1;
			printf("\n已找到名为%s的员工，他/她的信息如下：\n\n",name);
			break;
		}
	}
	if(!flag) {
		printf("\n\n很抱歉未能找到为%s的员工，请重新输入！\n\n",name);
		Search(p);
	}
	for(i=0; i<number; i++) {
		if(strcmp(p[i].name,name)==0) {
			ShowHead();
			printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[i].id,p[i].name,p[i].gender,
			       p[i].age,p[i].wage,p[i].address,p[i].phonenumber);
			ShowLine();
		}
	}
}
//检索员工号
void Searchbyid(EMP *p) {
	int id;
	int i;
	int flag =0;//flag 用于判断是否找到并反馈
	printf("请输入想要查询的员工号：");
	scanf("%d",&id);
	//判断是否找到并反馈
	system("cls");
	for(i=0; i<number; i++) {
		if(p[i].id==id) {
			flag=1;
			printf("\n已找到员工号为%d的员工，他/她的信息如下：\n\n",id);
			break;
		}
	}
	if(!flag) {
		printf("\n\n很抱歉未能找到为%d的员工，请重新输入！\n\n",id);
		Searchbyid(p);
	}
	for(i=0; i<number; i++) {
		if(p[i].id==id) {
			printf("\n\n员工号为%d的员工信息如下表：\n\n",id);
			ShowHead();
			printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[i].id,p[i].name,p[i].gender,
			       p[i].age,p[i].wage,p[i].address,p[i].phonenumber);
			ShowLine();
		}
	}
}



void Search(EMP *emp) {
	printf("请输入您想要的查询方式(1:员工号 2：姓名)：");
	int y;
	scanf("%d",&y);
	if(y==1||y==2) {
		if(y==1) {
			Searchbyid(emp);
		} else if(y==2) {
			Searchbyname(emp);
		}
	} else {
		system("cls");
		printf("\n\n请进行正确的输入,系统已返回到主菜单\n\n");
	}
	getchar();
	char a;
	printf("\n\n输入回车返回主菜单:");
	a=getchar();
	if(a=='\n')
		system("cls");
}
//读取文件中已有的员工人数
int read(EMP *emp) {
	FILE*fp;
	int i=0;
	if((fp=fopen("E:/员工信息档案.txt","rb"))==NULL) {
		printf ("文件打开失败\n");
		exit(0);
	} else {
		do {
			fread(&emp[i],sizeof(EMP),1,fp);
			i++;
		} while(feof(fp)==0);
	}
	fclose(fp);
	return(i-1);
}

/*保存文件函数*/
void save(int m,EMP *emp) {
	int i;
	FILE *fp;
	if ((fp=fopen("E:/员工信息档案.txt","wb"))==NULL) { /*创建文件并判断是否能打开*/
		printf ("文件打开失败!\n");
		exit(0);
	}
	for (i=0; i<m; i++) /*将员工的信息输出到文件中*/
		if (fwrite(&emp[i],sizeof(EMP),1,fp)!=1)
			printf("文件写入失败!\n");
	fclose(fp);
}

void add(EMP *emp) {
	int n=read(emp);
	int i,m,num=0;
	printf("请输入需要添加信息的员工人数: ");
	scanf("%d",&m);
	if(m+n>100)  {
		system("cls");
		printf("\n对不起，你所输入的员工人数超出范围。请重新输入（0至%d之间）：\n\n",100-n);
		add(emp);
	} else {
		for (i=n; i<m+n; i++) {
			printf("第%d个员工信息输入（按回车确认输入）： \n", i+1);
			printf("请输入员工号： ");
			scanf("%d",&num);
			for(int j=0; j<i; j++)
				if(emp[j].id==num) {
					printf("职工号为 %d 的员工已存在，请重新输入：",num);
					scanf("%d",&num);
					j=0;
				}
			emp[i].id=num;
			printf("请输入第%d个员工的姓名：", i+1);
			scanf("%s",emp[i].name);
			printf("请输入第%d个员工的性别：", i+1);
			getchar();
			scanf("%s",&emp[i].gender);
			printf("请输入第%d个员工的年龄：", i+1);
			scanf("%d",&emp[i].age);
			printf("请输入第%d个员工的工资： ", i+1);
			scanf("%f",&emp[i].wage);
			printf("请输入第%d个员工的住址： ", i+1);
			scanf("%s",&emp[i].address);
			printf("请输入第%d个员工的联系电话： ", i+1);
			scanf("%s",&emp[i].phonenumber);
			system("cls");
			printf("\n一个员的信息添加成功！请输入下一个员工的信息\n");
			printf("\n");
			number++;
		}
		save(m+n,emp);
		system("cls");
		printf("\n添加员工完成!  \n");
	}
}

//s用于存储输入的需要修改的员工的员工号，j用于存储第n个员工需要修改的序号n
void change(EMP *emp) {
	int s,j;
	printf("请输入你想要修改信息的员工的员工号:");
	scanf("%d",&s);
	int flag=0;
	for(int i=0; i<number; i++) {
		if(s==emp[i].id) {
			j=i;
			flag=1;
			break;
		}
	}
	if(flag==0) {
		printf("找不到员工号为：%d的员工，请重新输入\n",s);
		change(emp);
	} else {
		int c;
		int id;//employee
		char name[20];
		char gender[20];
		int age;
		float wage;//工资
		char address[20];
		char phonenumber[11];
		printf("\n已找到员工号为%d的员工，其记录为：\n",emp[j].id);
		ShowHead();
		printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%s\t|%s\n",emp[j].id,emp[j].name,emp[j].gender,
		       emp[j].age,emp[j].wage,emp[j].address,emp[j].phonenumber);
		ShowLine();
		printf("\n可以进行修改的选项\n 1.姓名  2.性别  3.年龄  4.工资  5.住址  6.电话  \n");
		printf("请输入你想修改的那一项序号:  ");
		scanf("%d",&c);
		switch(c) {

			case 1:
				printf("姓名改为: ");
				scanf("%s",name);
				strcpy(emp[j].name,name);
				break;
			case 2:
				printf("性别改为：");
				scanf("%s",&gender);
				strcpy(emp[j].gender,gender);
				break;
			case 3:
				printf("年龄改为: ");
				scanf("%d",&age);
				emp[j].age=age;
				break;

			case 4:
				printf("工资改为: ");
				scanf("%f",&wage);
				emp[j].wage=wage;
				break;
			case 5:
				printf("住址改为: ");
				scanf("%s",&address);
				strcpy(emp[j].address,address);
				break;
			case 6:
				printf("电话改为: ");
				scanf("%s",phonenumber);
				strcpy(emp[j].phonenumber,phonenumber);
				break;
		}
		save(number,emp);
		system("cls");
		printf("修改成功! 您可以浏览员工信息表查验\n\n");
	}
}

void Sort(EMP *emp) {
	int x;
	printf("请输入您想要的排序方式(1:工资 2：年龄)：");
	scanf("%d",&x);
	if(x==1||x==2) {
		if(x==1) {
			sortwage(emp);
		} else if(x==2) {
			sortage(emp);
		}
	} else {
		system("cls");
		printf("\n请进行正确的输入,系统将返回到主菜单\n\n");
	}
}
//薪资排序
void sortwage(EMP *emp) {
	int i,j;
	EMP t;
	for(i=0; i<number-1; i++) {
		for(j=0; j<number-1-i; j++) {
			if(emp[j].wage<emp[j+1].wage) {
				t=emp[j];
				emp[j]=emp[j+1];
				emp[j+1]=t;
			}
		}
	}
	system("cls");
	printf("\n\n员工按工资排序结果为下表\n\n");
	Output(emp,number);
}

//年龄排序
void sortage(EMP *emp) {
	int i,j;
	EMP t;
	for(i=0; i<number-1; i++) {
		for(j=0; j<number-1-i; j++) {
			if(emp[j].age>emp[j+1].age) {
				t=emp[j];
				emp[j]=emp[j+1];
				emp[j+1]=t;
			}
		}
	}
	system("cls");
	printf("\n\n员工按年龄排序后的结果为下表：\n\n");
	Output(emp,number);
}

//登录模块
void Login() {
	//首先检验是否有密码，无则创建“000000 ” 初始密码。
	FILE *fp;
	char a[10]= {"000000"};
	if(fopen("E:/password.txt","r")==NULL) {
		fp=fopen("E:/password.txt","w");
		fputs(a,fp);
		fclose(fp);
	}

	char password[15];
	char word[15];
	fp=fopen("E:/password.txt","r");
	fgets(password,14,fp);
	fclose(fp);
	int i=0;
	printf("************************员工信息管理系统**********************\n");
	printf("欢迎使用员工信息管理系统\n");
	printf("请输入管理员密码：\n");
	for(i=0; i<3; i++) {
		scanf("%s",word);
		if(strcmp(word,password)==0) {
			system("cls");
			printf("登录成功。\n");
			break;
		} else {
			if(i!=2) {
				printf("密码输入错误，请重新输入（还有%d次机会）：\n",2-i);
			}
		}
	}
	if(3==i) {
		printf("登录失败，程序退出。\n");
		exit(0);
	}
}

void reset() {
	getchar();
	char password[15];
	printf("请输入新密码：");
	gets(password);
	FILE *fp;
	fp=fopen("E:/password.txt","w");
	fputs(password,fp);
	fclose(fp);
	system("cls");
	printf("重置密码成功。\n");
}

void Examine() {
	if(fopen("E:/员工信息档案.txt","r")==NULL) {
		fopen("E:/员工信息档案.txt","w");
	}
}

