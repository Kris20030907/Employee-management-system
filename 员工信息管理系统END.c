/*
	ʵѵ��Ŀ���ƣ�Ա����Ϣ����ϵͳ
	С���Ա�����ʤ����־��
	��ʼʱ�䣺2022��6��21��
	����ʱ�䣺(1)������ɱ�д���������ʱ��: 2022��6��23��
			  (2)���г�������������ƽ���ʱ�䣺2022��6��25��
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define N 100

int number; //ȫ�ֱ�������¼Ա������

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
				printf("\nϵͳ�ɹ��˳�!\n") ;
				exit(0);
			default:
				printf("����");
				break;
		}
	}
	return 0;
}

//ϵͳ�˵�������
int Meum() {
	printf("\n************************Ա����Ϣ����ϵͳ**********************\n");
	printf("\n  \t1.  ¼��ְ����Ϣ \t\t 5.  ɾ��ְ����Ϣ");
	printf("\n  \t2.  ���ְ����Ϣ \t\t 6.  ����ְ����Ϣ");
	printf("\n  \t3.  ��ѯְ����Ϣ \t\t 7.  ���ְ����Ϣ");
	printf("\n  \t4.  �޸�ְ����Ϣ \t\t 8.  �����������");
	printf("\n  \t0.  �˳�ϵͳ");
	printf("\n\n************************************************************");
	int n;
	printf("\n��������ʹ�õĹ�����ţ�");
	scanf("%d",&n);
	return n;
}


//����Ա����Ϣ���ṹ��������(����������)
void Input(EMP *p) {
	int i,j;   
	printf("������¼��Ա��������");
	scanf("%d",&number);    /*����forѭ����ÿһλԱ������Ϣ�������벢�洢��Ա����Ϣ�ṹ����*/ 
	for(i=0; i<number; i++) {
		printf("\n�������%dλԱ����Ա����:",i+1);
		scanf("%d",&p[i].id);
		printf("�������%dλԱ��������:",i+1);
		scanf("%s",&p[i].name);
		getchar();
		printf("�������%dλԱ�����Ա�:",i+1);
		scanf("%s",&p[i].gender);
		getchar();
		printf("�������%dλԱ��������:",i+1);
		scanf("%d",&p[i].age);
		getchar();
		printf("�������%dλԱ���Ĺ���:",i+1);
		scanf("%f",&p[i].wage);
		getchar();
		printf("�������%dλԱ����סַ:",i+1);
		scanf("%s",&p[i].address);
		getchar();
		printf("�������%dλԱ������ϵ�绰:",i+1);
		scanf("%s",&p[i].phonenumber);
		getchar();
	}
	system("cls");    //�����������Է�������ڷ��� 
	printf("\nԱ����Ϣ�ɹ�¼�룡\n");
	EMP t;  //����һ��EMP���ͱ�������Ϊ����EMP����Ա����Ϣ�ṹ�彻��ý�� 
	            //ð�����򷨽�Ա����Ϣ����Ա���Ŵ�С����������� 
	for(i=0; i<number-1; i++)
		for(j=0; j<number-1-i; j++) {
			if(p[j].id>p[j+1].id) {
				t=p[j];
				p[j]=p[j+1];
				p[j+1]=t;
			}
		}
		//��switch-case����е�"case 1��"������� Writefile(EMP *p);��Ա����Ϣд���ļ�"Ա����Ϣ����.txt"
}

//����ṹ�������е���Ϣ(���Ա����Ϣ)
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
	printf("\n\n����س��������˵�:");
	a=getchar();
	if(a=='\n')
		system("cls");//������Ա����Ϣ�����
}

//Ա����Ϣ��ͷ
void ShowHead() {
	printf("\t|Ա����\t|����\t|�Ա�\t|����\t|����\t|סַ\t\t|��ϵ�绰");
}

//�ָ���
void ShowLine() {
	printf("\t");
	for(int i=0; i<70; i++)
		printf("-");
}

//�ṹ������д���ļ���
void Writefile(EMP *p) {
	FILE *fp;   //�����ݿ���ʽ��Ա����Ϣд���ļ� 
	fp=fopen("E:/Ա����Ϣ����.txt","w");
	fwrite(p,sizeof(EMP),number,fp);
	fclose(fp);
}

//�ļ���Ϣ��ȡ���ṹ��������
void Readfile(EMP *p) {
	FILE *fp;
	fp=fopen("E:/Ա����Ϣ����.txt","r");
	if(fp==NULL) {
		printf("δ�ҵ��ļ�");
		exit(0);
	} else {
		for(int i=0; !feof(fp); i++)
			fread(&p[i],sizeof(EMP),1,fp);
	}
	fclose(fp);
}

//ɾ��Ա����Ϣ
void Delete(EMP *p) {
	int i,n;
	int g;//�����ж��Ƿ��������ɾ��Ա���Ĳ���
	printf("��������Ҫɾ����Ա���ţ�");
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
	if(flag==0) printf("�޴�Ա����");
	else {
		printf("\n��Ա������Ϣ���±�:\n");
		ShowHead();
		printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[k].id,p[k].name,p[k].gender,
		       p[k].age,p[k].wage,p[k].address,p[k].phonenumber);
		ShowLine();
		printf("\n\n��ȷ���Ƿ�ɾ����Ա����:(1ȷ�ϣ�0�������˵�)");
		scanf("%d",&g);
		if(g==1) {
			for(; i<number-1; i++) p[i]=p[i+1];
			number--;
			Writefile(p);
			system("cls");
			printf("\n\n��Ա����Ϣɾ���ɹ�\n\n") ;
		} else if(g==0) {
			system("cls");
		}	else {
			printf("�������˷Ƿ����֣������½��иò�����\n\n");
			Delete(p);
		}
	}
}


//����Ա������
void Searchbyname(EMP *p) {
	char name[20];
	int i;
	int flag =0;//flag �����ж��Ƿ�
	printf("��������Ҫ��ѯ��Ա��������");
	scanf("%s",name);
	getchar();
	//�ж��Ƿ��ҵ�������
	for(i=0; i<number; i++) {
		if(strcmp(p[i].name,name)==0) {
			flag=1;
			printf("\n���ҵ���Ϊ%s��Ա������/������Ϣ���£�\n\n",name);
			break;
		}
	}
	if(!flag) {
		printf("\n\n�ܱ�Ǹδ���ҵ�Ϊ%s��Ա�������������룡\n\n",name);
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
//����Ա����
void Searchbyid(EMP *p) {
	int id;
	int i;
	int flag =0;//flag �����ж��Ƿ��ҵ�������
	printf("��������Ҫ��ѯ��Ա���ţ�");
	scanf("%d",&id);
	//�ж��Ƿ��ҵ�������
	system("cls");
	for(i=0; i<number; i++) {
		if(p[i].id==id) {
			flag=1;
			printf("\n���ҵ�Ա����Ϊ%d��Ա������/������Ϣ���£�\n\n",id);
			break;
		}
	}
	if(!flag) {
		printf("\n\n�ܱ�Ǹδ���ҵ�Ϊ%d��Ա�������������룡\n\n",id);
		Searchbyid(p);
	}
	for(i=0; i<number; i++) {
		if(p[i].id==id) {
			printf("\n\nԱ����Ϊ%d��Ա����Ϣ���±�\n\n",id);
			ShowHead();
			printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%8s\t|%8s\n",p[i].id,p[i].name,p[i].gender,
			       p[i].age,p[i].wage,p[i].address,p[i].phonenumber);
			ShowLine();
		}
	}
}



void Search(EMP *emp) {
	printf("����������Ҫ�Ĳ�ѯ��ʽ(1:Ա���� 2������)��");
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
		printf("\n\n�������ȷ������,ϵͳ�ѷ��ص����˵�\n\n");
	}
	getchar();
	char a;
	printf("\n\n����س��������˵�:");
	a=getchar();
	if(a=='\n')
		system("cls");
}
//��ȡ�ļ������е�Ա������
int read(EMP *emp) {
	FILE*fp;
	int i=0;
	if((fp=fopen("E:/Ա����Ϣ����.txt","rb"))==NULL) {
		printf ("�ļ���ʧ��\n");
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

/*�����ļ�����*/
void save(int m,EMP *emp) {
	int i;
	FILE *fp;
	if ((fp=fopen("E:/Ա����Ϣ����.txt","wb"))==NULL) { /*�����ļ����ж��Ƿ��ܴ�*/
		printf ("�ļ���ʧ��!\n");
		exit(0);
	}
	for (i=0; i<m; i++) /*��Ա������Ϣ������ļ���*/
		if (fwrite(&emp[i],sizeof(EMP),1,fp)!=1)
			printf("�ļ�д��ʧ��!\n");
	fclose(fp);
}

void add(EMP *emp) {
	int n=read(emp);
	int i,m,num=0;
	printf("��������Ҫ�����Ϣ��Ա������: ");
	scanf("%d",&m);
	if(m+n>100)  {
		system("cls");
		printf("\n�Բ������������Ա������������Χ�����������루0��%d֮�䣩��\n\n",100-n);
		add(emp);
	} else {
		for (i=n; i<m+n; i++) {
			printf("��%d��Ա����Ϣ���루���س�ȷ�����룩�� \n", i+1);
			printf("������Ա���ţ� ");
			scanf("%d",&num);
			for(int j=0; j<i; j++)
				if(emp[j].id==num) {
					printf("ְ����Ϊ %d ��Ա���Ѵ��ڣ����������룺",num);
					scanf("%d",&num);
					j=0;
				}
			emp[i].id=num;
			printf("�������%d��Ա����������", i+1);
			scanf("%s",emp[i].name);
			printf("�������%d��Ա�����Ա�", i+1);
			getchar();
			scanf("%s",&emp[i].gender);
			printf("�������%d��Ա�������䣺", i+1);
			scanf("%d",&emp[i].age);
			printf("�������%d��Ա���Ĺ��ʣ� ", i+1);
			scanf("%f",&emp[i].wage);
			printf("�������%d��Ա����סַ�� ", i+1);
			scanf("%s",&emp[i].address);
			printf("�������%d��Ա������ϵ�绰�� ", i+1);
			scanf("%s",&emp[i].phonenumber);
			system("cls");
			printf("\nһ��Ա����Ϣ��ӳɹ�����������һ��Ա������Ϣ\n");
			printf("\n");
			number++;
		}
		save(m+n,emp);
		system("cls");
		printf("\n���Ա�����!  \n");
	}
}

//s���ڴ洢�������Ҫ�޸ĵ�Ա����Ա���ţ�j���ڴ洢��n��Ա����Ҫ�޸ĵ����n
void change(EMP *emp) {
	int s,j;
	printf("����������Ҫ�޸���Ϣ��Ա����Ա����:");
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
		printf("�Ҳ���Ա����Ϊ��%d��Ա��������������\n",s);
		change(emp);
	} else {
		int c;
		int id;//employee
		char name[20];
		char gender[20];
		int age;
		float wage;//����
		char address[20];
		char phonenumber[11];
		printf("\n���ҵ�Ա����Ϊ%d��Ա�������¼Ϊ��\n",emp[j].id);
		ShowHead();
		printf("\n\t|%d\t|%s\t|%s\t|%d\t|%.1f\t|%s\t|%s\n",emp[j].id,emp[j].name,emp[j].gender,
		       emp[j].age,emp[j].wage,emp[j].address,emp[j].phonenumber);
		ShowLine();
		printf("\n���Խ����޸ĵ�ѡ��\n 1.����  2.�Ա�  3.����  4.����  5.סַ  6.�绰  \n");
		printf("�����������޸ĵ���һ�����:  ");
		scanf("%d",&c);
		switch(c) {

			case 1:
				printf("������Ϊ: ");
				scanf("%s",name);
				strcpy(emp[j].name,name);
				break;
			case 2:
				printf("�Ա��Ϊ��");
				scanf("%s",&gender);
				strcpy(emp[j].gender,gender);
				break;
			case 3:
				printf("�����Ϊ: ");
				scanf("%d",&age);
				emp[j].age=age;
				break;

			case 4:
				printf("���ʸ�Ϊ: ");
				scanf("%f",&wage);
				emp[j].wage=wage;
				break;
			case 5:
				printf("סַ��Ϊ: ");
				scanf("%s",&address);
				strcpy(emp[j].address,address);
				break;
			case 6:
				printf("�绰��Ϊ: ");
				scanf("%s",phonenumber);
				strcpy(emp[j].phonenumber,phonenumber);
				break;
		}
		save(number,emp);
		system("cls");
		printf("�޸ĳɹ�! ���������Ա����Ϣ�����\n\n");
	}
}

void Sort(EMP *emp) {
	int x;
	printf("����������Ҫ������ʽ(1:���� 2������)��");
	scanf("%d",&x);
	if(x==1||x==2) {
		if(x==1) {
			sortwage(emp);
		} else if(x==2) {
			sortage(emp);
		}
	} else {
		system("cls");
		printf("\n�������ȷ������,ϵͳ�����ص����˵�\n\n");
	}
}
//н������
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
	printf("\n\nԱ��������������Ϊ�±�\n\n");
	Output(emp,number);
}

//��������
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
	printf("\n\nԱ�������������Ľ��Ϊ�±�\n\n");
	Output(emp,number);
}

//��¼ģ��
void Login() {
	//���ȼ����Ƿ������룬���򴴽���000000 �� ��ʼ���롣
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
	printf("************************Ա����Ϣ����ϵͳ**********************\n");
	printf("��ӭʹ��Ա����Ϣ����ϵͳ\n");
	printf("���������Ա���룺\n");
	for(i=0; i<3; i++) {
		scanf("%s",word);
		if(strcmp(word,password)==0) {
			system("cls");
			printf("��¼�ɹ���\n");
			break;
		} else {
			if(i!=2) {
				printf("��������������������루����%d�λ��ᣩ��\n",2-i);
			}
		}
	}
	if(3==i) {
		printf("��¼ʧ�ܣ������˳���\n");
		exit(0);
	}
}

void reset() {
	getchar();
	char password[15];
	printf("�����������룺");
	gets(password);
	FILE *fp;
	fp=fopen("E:/password.txt","w");
	fputs(password,fp);
	fclose(fp);
	system("cls");
	printf("��������ɹ���\n");
}

void Examine() {
	if(fopen("E:/Ա����Ϣ����.txt","r")==NULL) {
		fopen("E:/Ա����Ϣ����.txt","w");
	}
}

