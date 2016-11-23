/*
大部分变量名称我都使用了中文,虽然在之后的操作中繁琐了很多,但主要目的是使得自己更加不易犯错,因为变量太多,
如果您还没有运行程序,请先进行调试,这有助于您对本程序的理解
本程序完全由自己编写,未经同意,请勿抄袭.
本程序不可用于任何商业用途.
联系方式:
Tel:	13588550938
Email:	orson.xu@foxmail.com
*/
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <conio.h> //用于getch()函数
#define MAX 100
struct job1  //定义经理岗位，同时赋值，属于热门岗位
{
	char 岗位名称[10];
	char 等级;
	float 基本工资;
	char 公司股份[10];  //这是比普通岗位多出来的参数
	int 在岗人数;
	int 应聘人数;
}经理岗位[3] = { { "行政经理", 'A', 12000, "1.0%", 0, 0 }, { "研发经理", 'B', 10000, "0.6%", 0, 0 }, { "生产经理", 'B', 9000, "0.3%", 0, 0 } };
struct job2  //定义普通岗位，同时赋值，和经理岗位相区分，有不同数目的参数。
{
	char 岗位名称[10];
	char 等级;
	float 基本工资;
	int 在岗人数;
	int 应聘人数;
}普通岗位[7] = { { "会计", 'C', 7000, 0, 0 }, { "采购员", 'C', 6000, 0, 0 }, { "销售员", 'C', 7500, 0, 0 }, { "司机", 'D', 4000, 0, 0 }, { "厨师", 'D', 4000, 0, 0 }, { "门卫", 'E', 3000, 0, 0 }, { "清洁工", 'E', 3000, 0, 0 } };
struct people1  //在岗人员
{
	char 姓名[20];
	char 性别[4];
	int 年龄;
	char 在岗名称[10];
	int 编号;
}在岗人员[MAX];
struct people2 //应聘人员和在岗人员分开记录,分别存在两个文件中
{
	char 姓名[20];
	char 性别[4];
	int 年龄;
	char 应聘名称[10];
	int 编号;
}应聘人员[MAX];
FILE *fpeople1, *fpeople2;//指向用于储存 在岗人员 和 应聘人员 的两个文件
FILE *fp1, *fp2;
int numberpeople1 = 0, numberpeople2 = 0, NO1 = 100000, NO2 = 200000; //numberpeople1和2 分别记录在岗和应聘人员的人数  而NO1 2 分别是两类人的编号 前者1开头 后者2开头
void prepare()  //用于在程序开始时进行初始准备，计算各个岗位的在岗、应聘人数，并且存到job结构体数组当中。同时计算总人数，计算编号。为之后做准备。
{
	int calculatezg(int), calculateyp(int);
	int i, j;
	for (i = 0; i<3; i++)
	{
		经理岗位[i].在岗人数 = calculatezg(i); numberpeople1 += calculatezg(i);
	}
	for (j = 0; j<7; j++)
	{
		普通岗位[j].在岗人数 = calculatezg(j + 3); numberpeople1 += calculatezg(j + 3);
	}
	for (i = 0; i<3; i++)
	{
		经理岗位[i].应聘人数 = calculateyp(i); numberpeople2 += calculateyp(i);
	}
	for (j = 0; j<7; j++)
	{
		普通岗位[j].应聘人数 = calculateyp(j + 3); numberpeople2 += calculateyp(j + 3);
	}
	if ((fp1 = fopen("NO1.txt", "r")) == NULL)					// 这一部分的代码目的是专门为编号问题设置的。
	{
		printf("文件N01.txt无法打开！\n"); exit(1);
	}			// 另开一个文件存储编号，这样在人员被删除之后，编号也不会出现变小的问题。
	fscanf(fp1, "%d", &NO1);
	fclose(fp1);
	if ((fp2 = fopen("NO2.txt", "r")) == NULL)
	{
		printf("文件N02.txt无法打开！\n"); exit(1);
	}
	fscanf(fp2, "%d", &NO2);
	fclose(fp2);
}
int calculateyp(int n) //计算应聘人数的函数, n从1-10 对应十个不同的职位
{
	int i, j, k, result[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if ((fpeople2 = fopen("people2.txt", "r")) == NULL)
	{
		perror("该文件 people2.txt 无法打开\n"); exit(1);
	}
	for (i = 0; i<MAX; i++)
		fscanf(fpeople2, "%s %s %d %s %d", &应聘人员[i].姓名, &应聘人员[i].性别, &应聘人员[i].年龄, &应聘人员[i].应聘名称, &应聘人员[i].编号);
	for (j = 0; j<MAX; j++)
	{
		for (k = 0; k<3; k++)
		if (strcmp(应聘人员[j].应聘名称, 经理岗位[k].岗位名称) == 0)
			result[k]++;
		for (k = 0; k<7; k++)
		if (strcmp(应聘人员[j].应聘名称, 普通岗位[k].岗位名称) == 0)
			result[k + 3]++;
	}
	fclose(fpeople2);
	return(result[n]);
}
int calculatezg(int n)//计算在岗人数的函数, n从1-10 对应十个不同的职位
{
	int i, j, k, result[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if ((fpeople1 = fopen("people1.txt", "r")) == NULL)
	{
		perror("该文件 people1.txt 无法打开\n"); exit(1);
	}
	for (i = 0; i<MAX; i++)
		fscanf(fpeople1, "%s %s %d %s %d", &在岗人员[i].姓名, &在岗人员[i].性别, &在岗人员[i].年龄, &在岗人员[i].在岗名称, &在岗人员[i].编号);
	for (j = 0; j<MAX; j++)
	{
		for (k = 0; k<3; k++)
		if (strcmp(在岗人员[j].在岗名称, 经理岗位[k].岗位名称) == 0)
			result[k]++;
		for (k = 0; k<7; k++)
		if (strcmp(在岗人员[j].在岗名称, 普通岗位[k].岗位名称) == 0)
			result[k + 3]++;
	}
	fclose(fpeople1);
	return(result[n]);
}
void input() // 输入人事信息的函数
{
	int judge, i, i1, i2, j, k, l, n, m = 0;
	for (;;) // 采用循环的方式可以重复输入 跳出循环方式由 continue 和 break 实现. 之后不做注释
	{
		printf("-----------------------------------------\n");
		printf("|\t  欢迎进入信息录入模块！ \t|\n");
		printf("|\t 请选择您计划录入人的类别 \t|\n|\t 若属于 在岗人员 请输入1 \t|\n|\t 若属于 应聘人员 请输入2 \t|\n");
		printf("-----------------------------------------\n");
		printf("请输入数字：");
		judge = 0;//保证每次的输入数字都被初始化
		scanf("%d", &judge); // 输入 1 和 2 对应输入在岗人员和应聘人员的信息、
		fflush(stdin);
		if (judge == 1)
		{
			if ((fpeople1 = fopen("people1.txt", "a")) == NULL)
			{
				perror("该文件 person1.txt 无法打开\n"); exit(1);
			}
			i = numberpeople1;
			printf("请输入姓名：");
			scanf("%s", &在岗人员[i].姓名);
			fflush(stdin);
			for (;;) // 容错 之后也不再做注释
			{
				printf("请输入性别（‘男’或‘女’）：");
				scanf("%s", &在岗人员[i].性别);
				fflush(stdin);
				if ((strcmp(在岗人员[i].性别, "男") != 0) && (strcmp(在岗人员[i].性别, "女") != 0))
				{
					printf("对不起您输入的性别有误！请重新输入\n"); continue;
				}
				else break;
			}
			printf("请输入年龄：");
			for (;;)
			{
				在岗人员[i].年龄 = 0;
				scanf("%d", &在岗人员[i].年龄);
				fflush(stdin);
				if (在岗人员[i].年龄 <= 17 || 在岗人员[i].年龄 >= 70)
				{
					printf("对不起您输入的年龄不符合国家相关规定！请重新输入："); continue;
				}
				else break;
			}
			printf("\n");
			printf("请输入岗位：\n");
			for (i1 = 0; i1<3; i1++)
				printf("若您希望输入的岗位是 %s\t请输入 %d\n", 经理岗位[i1].岗位名称, i1 + 1);
			for (i2 = 0; i2<7; i2++)
				printf("若您希望输入的岗位是 %s\t请输入 %d\n", 普通岗位[i2].岗位名称, i2 + 4);
			printf("\n请输入相应的岗位对应的数字：");
			for (;;)
			{
				n = 0;
				scanf("%d", &n);
				fflush(stdin);
				if (n<1 || n>10)
				{
					printf("对不起您输入的数字有误！请重新输入：\n"); continue;
				}
				else break;
			}
			n = n - 1;
			if (n <= 2)
			{
				strcpy(在岗人员[i].在岗名称, 经理岗位[n].岗位名称); numberpeople1++; 经理岗位[n].在岗人数++;
			}
			else if (n >= 3)
			{
				strcpy(在岗人员[i].在岗名称, 普通岗位[n - 3].岗位名称); numberpeople1++; 普通岗位[n - 3].在岗人数++;
			}
			NO1++;
			在岗人员[i].编号 = NO1;
			fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", 在岗人员[i].姓名, 在岗人员[i].性别, 在岗人员[i].年龄, 在岗人员[i].在岗名称, 在岗人员[i].编号);
			fclose(fpeople1);
			if ((fp1 = fopen("NO1.txt", "w")) == NULL)		//及时将NO1的更新保存到编号文档中，保证编号的统一性。
			{
				printf("文件N01.txt无法打开！\n"); exit(1);
			}
			fprintf(fp1, "%d", NO1);
			fclose(fp1);
		}
		else if (judge == 2)  // 与judge==1的内容几乎完全相同，下面部分不作赘述了。
		{
			if ((fpeople2 = fopen("people2.txt", "a")) == NULL)
			{
				perror("该文件 people2.txt 无法打开\n"); exit(1);
			}
			i = numberpeople2;
			printf("请输入姓名：");
			scanf("%s", &应聘人员[i].姓名);
			fflush(stdin);
			for (;;)
			{
				printf("请输入性别（‘男’或‘女’）：");
				scanf("%s", &应聘人员[i].性别);
				fflush(stdin);
				if ((strcmp(应聘人员[i].性别, "男") != 0) && (strcmp(应聘人员[i].性别, "女") != 0))
				{
					printf("对不起您输入的性别有误！\n"); continue;
				}
				else break;
			}
			printf("请输入年龄：");
			for (;;)
			{
				应聘人员[i].年龄 = 0;
				scanf("%d", &应聘人员[i].年龄);
				fflush(stdin);
				if (应聘人员[i].年龄 <= 17 || 应聘人员[i].年龄 >= 70)
				{
					printf("对不起您输入的年龄不符合国家相关规定！请重新输入："); continue;
				}
				else break;
			}
			printf("\n");
			printf("请输入岗位：\n");
			for (i1 = 0; i1<3; i1++)
				printf("若您希望输入的岗位是 %s\t请输入 %d\n", 经理岗位[i1].岗位名称, i1 + 1);
			for (i2 = 0; i2<7; i2++)
				printf("若您希望输入的岗位是 %s\t请输入 %d\n", 普通岗位[i2].岗位名称, i2 + 4);
			printf("\n请输入相应的岗位对应的数字：");
			for (;;)
			{
				n = 0;
				scanf("%d", &n);
				fflush(stdin);
				if (n<1 || n>10)
				{
					printf("对不起您输入的数字有误！请重新输入：\n"); continue;
				}
				else break;
			}
			n = n - 1;
			if (n <= 2)
			{
				strcpy(应聘人员[i].应聘名称, 经理岗位[n].岗位名称); numberpeople2++; 经理岗位[n].应聘人数++;
			}
			else if (n >= 3)
			{
				strcpy(应聘人员[i].应聘名称, 普通岗位[n - 3].岗位名称); numberpeople2++; 普通岗位[n - 3].应聘人数++;
			}
			NO2++;
			应聘人员[i].编号 = NO2;
			fprintf(fpeople2, "%-10s %-10s %-10d %-10s %-10d", 应聘人员[i].姓名, 应聘人员[i].性别, 应聘人员[i].年龄, 应聘人员[i].应聘名称, 应聘人员[i].编号);
			numberpeople2++;
			fclose(fpeople2);
			if ((fp2 = fopen("NO2.txt", "w")) == NULL)
			{
				printf("文件N02.txt无法打开！\n"); exit(1);
			}
			fprintf(fp2, "%d", NO2);
			fclose(fp2);
		}
		else
		{
			printf("对不起您输入的数字有误！请重新输入：\n"); continue;
		}
		printf("添加人员成功！\n如果您需要继续输入人员信息，请输入1\n若您需要退出信息录入模块，请输入0\n");
		printf("请输入数字："); // 选择是否继续输入
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("您输入的数字有误！默认认为退出 信息录入 模块！\n"); break; }
	}
}

void search() // 查询在岗人员情况的函数
{
	int judge, i, j, k, n;
	char goal[10];
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t   欢迎进入查询在岗人员模块！   \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t 若您希望查找 %s\t请输入%d  \t|\n", 经理岗位[i].岗位名称, i + 1);
		for (i = 0; i<6; i++)
			printf("|\t 若您希望查找 %s\t请输入%d  \t|\n", 普通岗位[i].岗位名称, i + 4);
		printf("|\t 若您希望查找 %s\t请输入10 \t|\n", 普通岗位[6].岗位名称);//将其单独拿出来,因为 10 所占的位置不同于1-9, 所以难以用\t对齐.后面还会出现类似的情况,不做赘述.
		printf("-------------------------------------------------\n");
		printf("请输入数字：");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
			else break;
		}
		n = n - 1; // 根据输入的数字是属于 经理岗位 还是 普通岗位, 分别输出岗位结构体内的参数,
		if (n <= 2)
		{
			printf("您查找的岗位名称为\t\t%s\n该岗位的等级为\t\t\t%c\n该岗位的基本工资为\t\t%f\n该岗位能够占有的公司股份为\t%s\n该岗位目前的在岗人数\t\t%d\n该岗位目前的应聘人数\t\t%d\n", 经理岗位[n].岗位名称, 经理岗位[n].等级, 经理岗位[n].基本工资, 经理岗位[n].公司股份, 经理岗位[n].在岗人数, 经理岗位[n].应聘人数);
			printf("以下是关于此岗位的在岗人员的情况：\n");
			printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(在岗人员[j].在岗名称, 经理岗位[n].岗位名称) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", 在岗人员[j].姓名, 在岗人员[j].性别, 在岗人员[j].年龄, 在岗人员[j].编号);
			printf("\n");
		}
		else if (n >= 3)
		{
			n = n - 3;
			printf("您查找的岗位名称为\t\t%s\n该岗位的等级为\t\t\t%c\n该岗位的基本工资为\t\t%f\n该岗位目前的在岗人数\t\t%d\n该岗位目前的应聘人数\t\t%d\n", 普通岗位[n].岗位名称, 普通岗位[n].等级, 普通岗位[n].基本工资, 普通岗位[n].在岗人数, 普通岗位[n].应聘人数);
			printf("以下是关于此岗位的在岗人员的情况：\n");
			printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(在岗人员[j].在岗名称, 普通岗位[n].岗位名称) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", 在岗人员[j].姓名, 在岗人员[j].性别, 在岗人员[j].年龄, 在岗人员[j].编号);
			printf("\n");
		}
		printf("若您希望继续进行查询，请输入1\n若您希望退出查询在岗情况模块，请输入0\n");
		printf("请输入数字：");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("您输入的数字有误！默认为退出 查询在岗人数 模块！\n"); break; }
	}
}
void calc() //  计算应聘人数 并且查询应聘人员的情况
{
	int calculateyp(int);
	int i, j, k, n, result;
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t    欢迎进入查询应聘人员模块！  \t|\n");
		printf("|\t 请输入您希望查询应聘人员的岗位 \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t 若您希望查找 %s\t请输入%d  \t|\n", 经理岗位[i].岗位名称, i + 1);
		for (j = 0; j<6; j++)
			printf("|\t 若您希望查找 %s\t请输入%d  \t|\n", 普通岗位[j].岗位名称, j + 4);
		printf("|\t 若您希望查找 %s\t请输入10 \t|\n", 普通岗位[6].岗位名称);
		printf("-------------------------------------------------\n");
		printf("请输入数字：");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
			else break;
		}
		n = n - 1;
		printf("该岗位 ");
		if (n <= 2)
		{
			printf("%s", 经理岗位[n].岗位名称); result = 经理岗位[n].应聘人数;
		}
		else if (n >= 3)
		{
			printf("%s", 普通岗位[n - 3].岗位名称); result = 普通岗位[n - 3].应聘人数;
		}
		printf(" 的应聘人数为 %d\n", result);
		printf("以下是关于此岗位的应聘人员的情况：\n");
		if (n <= 2)
		{
			printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
			for (j = 0; j<numberpeople2; j++)
			if (strcmp(应聘人员[j].应聘名称, 经理岗位[n].岗位名称) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", 应聘人员[j].姓名, 应聘人员[j].性别, 应聘人员[j].年龄, 应聘人员[j].编号);
			printf("\n");
		}
		else if (n >= 3)
		{
			printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
			for (j = 0; j<numberpeople2; j++)
			if (strcmp(应聘人员[j].应聘名称, 普通岗位[n - 3].岗位名称) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", 应聘人员[j].姓名, 应聘人员[j].性别, 应聘人员[j].年龄, 应聘人员[j].编号);
			printf("\n");
		}
		printf("若您希望继续计算其他岗位的应聘人数，请输入1\n若您希望退出查询应聘人员模块，请输入0\n");
		printf("请输入数字：");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("您输入的数字有误！默认为退出 查询应聘人数 模块\n"); break; }
	}
}
void sort()//利用链表进行排序
{
	int i, j, k, tempnum;
	char temppos[10];
	struct number
	{
		int num;		//存放岗位的应聘人数
		char pos[10];	//存放岗位名称
		struct number *next;
	}*head, *cursor, *tempnode, *compare;
	head = (struct number *)malloc(sizeof(struct number)); // 头结点分配内存
	if (head == NULL)
	{
		printf("错误，表头结点内存分配失败！"); exit(1);
	}
	head->next = NULL;
	cursor = head;
	for (i = 0; i<10; i++)
	{
		tempnode = (struct number *)malloc(sizeof(struct number));
		if (tempnode == NULL)
		{
			printf("错误，中间结点内存分配失败！"); exit(1);
		}
		if (i <= 2)
		{
			tempnode->num = 经理岗位[i].应聘人数; strcpy(tempnode->pos, 经理岗位[i].岗位名称);
		}
		else if (i >= 3)
		{
			tempnode->num = 普通岗位[i - 3].应聘人数; strcpy(tempnode->pos, 普通岗位[i - 3].岗位名称);
		}
		tempnode->next = NULL;
		cursor->next = tempnode;
		cursor = cursor->next;
	}
	for (j = 0; j<9; j++) //采用冒泡排序法
	for (cursor = head->next; cursor->next != NULL; cursor = cursor->next)
	if (cursor->num<cursor->next->num)
	{
		tempnum = cursor->num; cursor->num = cursor->next->num; cursor->next->num = tempnum;
		strcpy(temppos, cursor->pos); strcpy(cursor->pos, cursor->next->pos); strcpy(cursor->next->pos, temppos);
	}
	printf("以下是各岗位求职热度排序：\n");
	for (k = 0, cursor = head->next; k<9; k++)
	{
		printf("第 %d 名\t  %s  \t应聘人数：%d\n", k + 1, cursor->pos, cursor->num);
		cursor = cursor->next;
	}
	printf("第 %d名\t  %s  \t应聘人数：%d\n", k + 1, cursor->pos, cursor->num);
	printf("请按任意键继续...");
	getch(); //读取而不显示 用于实现按任意键继续
	printf("\n");
}
void change() // 人员流动函数 主要思路为改变 被流动人员 的 "在岗人员[].在岗名称"
{
	int i, j, k, b, judge = 0, n, m, p, buf;
	int bufnum[MAX];
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t      欢迎进入人员调整模块！    \t|\n");
		printf("|\t 请输入您希望调节人员原本岗位   \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t 若您希望调动 %s\t请输入%d  \t|\n", 经理岗位[i].岗位名称, i + 1);
		for (j = 0; j<6; j++)
			printf("|\t 若您希望调动 %s\t请输入%d  \t|\n", 普通岗位[j].岗位名称, j + 4);
		printf("|\t 若您希望查找 %s\t请输入10 \t|\n", 普通岗位[6].岗位名称);
		printf("-------------------------------------------------\n");
		printf("请输入数字：");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
			else break;
		}
		n = n - 1;
		b = 0;//保证第一次以后的次数中bufnum的有效性
		printf("处在该岗位的人员有\n");//输出所有的该岗位的人员的姓名和对应的编号
		if (n <= 2)
		{
			printf("\t%-10s %-10s\n\n", "姓名", "编号");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(在岗人员[j].在岗名称, 经理岗位[n].岗位名称) == 0)
			{
				printf("\t%-10s %-10d\n", 在岗人员[j].姓名, 在岗人员[j].编号); bufnum[b] = 在岗人员[j].编号; b++;
			}//用于临时记录处在该岗位的人员编号，下同
		}
		else if (n >= 3)
		{
			printf("\t%-10s %-10s\n\n", "姓名", "编号");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(在岗人员[j].在岗名称, 普通岗位[n - 3].岗位名称) == 0)
			{
				printf("\t%-10s %-10d\n", 在岗人员[j].姓名, 在岗人员[j].编号); bufnum[b] = 在岗人员[j].编号; b++;
			}
		}
		if (b == 0) // 若人数为零,则按任意键返回
		{
			printf("\n该岗位的在岗人员数为零！请按任意键继续...\n"); getch(); continue;
		}
		printf("\n请输入您希望调节的人员的编号：");
		for (;;)
		{
			scanf("%d", &buf);
			fflush(stdin);
			for (i = 0; i<b; i++)
			if (bufnum[i] == buf)
				judge++;
			if (judge == 0)
			{
				printf("对不起您输入编号的对应人员不在此岗位上！请重新输入："); continue;
			}
			else break;
		}judge = 0;//保证judge的有效性。
		printf("请输入您希望调节人员即将要去的岗位\n");
		for (i = 0; i<3; i++)
			printf("若岗位是 %s\t请输入 %d\n", 经理岗位[i].岗位名称, i + 1);
		for (j = 0; j<7; j++)
			printf("若岗位是 %s\t\t请输入 %d\n", 普通岗位[j].岗位名称, j + 4);
		printf("请输入数字：");
		for (;;)
		{
			m = 0;
			scanf("%d", &m);
			fflush(stdin);
			m = m - 1;
			if (m<0 || m>9)
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
			else if (n == m)
			{
				printf("对不起您输入的数字和之前的数字相同！请重新输入："); continue;
			}
			else break;
		}
		if (n <= 2)
		{
			经理岗位[n].在岗人数--;
			if (经理岗位[n].在岗人数<3)//判断岗位人数是否少于三人
				printf("\n请注意！%s 的在岗人数为 %d，已经不足三人！\n\n", 经理岗位[n].岗位名称, 经理岗位[n].在岗人数);
		}
		else if (n >= 3)
		{
			普通岗位[n - 3].在岗人数--;
			if (普通岗位[n - 3].在岗人数<3)
				printf("\n请注意！%s 的在岗人数为 %d，已经不足三人！\n\n", 普通岗位[n - 3].岗位名称, 普通岗位[n - 3].在岗人数);
		}
		if (m <= 2)
			经理岗位[m].在岗人数++;
		else if (m >= 3)
			普通岗位[m - 3].在岗人数++;
		for (p = 0; p<MAX; p++)
		if (在岗人员[p].编号 == buf)
		{
			if (m <= 2)
				strcpy(在岗人员[p].在岗名称, 经理岗位[m].岗位名称);
			if (m >= 3)
				strcpy(在岗人员[p].在岗名称, 普通岗位[m - 3].岗位名称);
			break;
		}
		if ((fpeople1 = fopen("people1.txt", "w+")) == NULL)
		{
			perror("该文件 people1.txt 无法打开\n"); exit(1);
		}
		for (i = 0; i<numberpeople1; i++)
			fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", 在岗人员[i].姓名, 在岗人员[i].性别, 在岗人员[i].年龄, 在岗人员[i].在岗名称, 在岗人员[i].编号);
		fclose(fpeople1);
		printf("调整人员成功！若您希望继续调整人员，请输入1\n若您希望退出调整模块，请输入0\n");
		printf("请输入数字：");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("您输入的数字有误！默认为退出 人员调节 模块 \n"); break; }
	}
}
void delete_p() //删除任何一条人员信息
{
	int i, j, k, n, m, tempNO, temp, b, judge = 0;
	int bufnum[MAX];
	for (;;)
	{
		printf("-----------------------------------------\n");
		printf("|\t  欢迎进入人员删除模块！ \t|\n");
		printf("|\t 请选择您计划删除人的类别 \t|\n|\t 若属于 在岗人员 请输入1 \t|\n|\t 若属于 应聘人员 请输入2 \t|\n");
		printf("-----------------------------------------\n");
		printf("请输入数字：");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n != 1 && n != 2)
			{
				printf("对不起，您输入的数字有误！请重新输入："); continue;
			}
			else break;
		}
		printf("请输入您希望删除人员所在的岗位\n");
		for (i = 0; i<3; i++)
			printf("若岗位是 %s\t请输入 %d\n", 经理岗位[i].岗位名称, i + 1);
		for (j = 0; j<7; j++)
			printf("若岗位是 %s\t\t请输入 %d\n", 普通岗位[j].岗位名称, j + 4);
		printf("\n请输入数字：");
		for (;;)
		{
			m = 0;
			scanf("%d", &m);
			fflush(stdin);
			m = m - 1;
			if (m<0 || m>9)
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
			else break;
		}
		if (n == 1)
		{
			b = 0; //保证第一次以后的次数中bufnum的有效性
			printf("以下是在岗人员的信息：\n");
			if (m <= 2)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
				for (j = 0; j<numberpeople1; j++)
				if (strcmp(在岗人员[j].在岗名称, 经理岗位[m].岗位名称) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", 在岗人员[j].姓名, 在岗人员[j].性别, 在岗人员[j].年龄, 在岗人员[j].编号); bufnum[b] = 在岗人员[j].编号; b++;
				}
				printf("\n"); //bufnum用于临时记录处在该岗位的人员编号，下同
			}
			else if (m >= 3)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
				for (j = 0; j<numberpeople1; j++)
				if (strcmp(在岗人员[j].在岗名称, 普通岗位[m - 3].岗位名称) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", 在岗人员[j].姓名, 在岗人员[j].性别, 在岗人员[j].年龄, 在岗人员[j].编号); bufnum[b] = 在岗人员[j].编号; b++;
				}
				printf("\n");
			}
			if (b == 0) // 若人数为零,则按任意键返回
			{
				printf("\n该岗位的在岗人员数为零！请按任意键继续...\n"); getch(); continue;
			}
			printf("请输入您希望删除人员的编号：");
			for (;;)
			{
				tempNO = 0;
				scanf("%d", &tempNO);
				fflush(stdin);
				for (i = 0; i<b; i++)
				if (bufnum[i] == tempNO)
					judge++;
				if (judge == 0)
				{
					printf("对不起您输入编号的对应人员不在此岗位上！请重新输入："); continue;
				}
				else break;
			}judge = 0;//保证judge的有效性。
			for (temp = 0; temp<numberpeople1; temp++)
			if (tempNO == 在岗人员[temp].编号)
				break;
			numberpeople1--;   //保证各个参数同步变化
			if (m <= 2)
				经理岗位[m].在岗人数--;
			else if (m >= 3)
				普通岗位[m - 3].在岗人数--;
			if (temp == (numberpeople1 + 1)) //若删除的人在最后，将其信息抹去
			{
				strcpy(在岗人员[temp].姓名, "\0");
				strcpy(在岗人员[temp].性别, "\0");
				在岗人员[temp].年龄 = 0;
				strcpy(在岗人员[temp].在岗名称, "\0");
				在岗人员[temp].编号 = 0;
			}
			else
			{
				for (j = temp; j<numberpeople1; j++) // 若不在最后，将其之后的全部往前挪一位
				{
					strcpy(在岗人员[j].姓名, 在岗人员[j + 1].姓名);
					strcpy(在岗人员[j].性别, 在岗人员[j + 1].性别);
					在岗人员[j].年龄 = 在岗人员[j + 1].年龄;
					strcpy(在岗人员[j].在岗名称, 在岗人员[j + 1].在岗名称);
					在岗人员[j].编号 = 在岗人员[j + 1].编号;
				}
				strcpy(在岗人员[numberpeople1 + 1].姓名, "\0"); //并且将最后一位数组的信息抹去
				strcpy(在岗人员[numberpeople1 + 1].性别, "\0");
				在岗人员[numberpeople1 + 1].年龄 = 0;
				strcpy(在岗人员[numberpeople1 + 1].在岗名称, "\0");
				在岗人员[numberpeople1 + 1].编号 = 0;
			}
			if ((fpeople1 = fopen("people1.txt", "w+")) == NULL)
			{
				printf("文件people1.txt无法打开！\n"); exit(1);
			}
			for (i = 0; i<numberpeople1; i++)
				fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", 在岗人员[i].姓名, 在岗人员[i].性别, 在岗人员[i].年龄, 在岗人员[i].在岗名称, 在岗人员[i].编号);
			fclose(fpeople1);//重新将内容赋值给文件。
		}
		else if (n == 2) // 该部分与n==1几乎完全相同，因为文件操作不同所以导致重写一遍。下面的注释就略去了。
		{
			b = 0;
			printf("以下是应聘人员的信息：\n");
			if (m <= 2)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
				for (j = 0; j<numberpeople2; j++)
				if (strcmp(应聘人员[j].应聘名称, 经理岗位[m].岗位名称) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", 应聘人员[j].姓名, 应聘人员[j].性别, 应聘人员[j].年龄, 应聘人员[j].编号); bufnum[b] = 应聘人员[j].编号; b++;
				}
				printf("\n");
			}
			else if (m >= 3)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "姓名", "性别", "年龄", "编号");
				for (j = 0; j<numberpeople2; j++)
				if (strcmp(应聘人员[j].应聘名称, 普通岗位[m - 3].岗位名称) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", 应聘人员[j].姓名, 应聘人员[j].性别, 应聘人员[j].年龄, 应聘人员[j].编号); bufnum[b] = 在岗人员[j].编号; b++;
				}
				printf("\n");
			}
			if (b == 0)
			{
				printf("\n该岗位的在岗人员数为零！请按任意键继续..."); getch(); continue;
			}
			printf("请输入您希望删除人员的编号：");
			for (;;)
			{
				tempNO = 0;
				scanf("%d", &tempNO);
				fflush(stdin);
				for (i = 0; i<b; i++)
				if (bufnum[i] == tempNO)
					judge++;
				if (judge == 0)
				{
					printf("对不起您输入编号的对应人员不在此岗位上！请重新输入："); continue;
				}
				else break;
			}judge = 0;
			for (temp = 0; temp<numberpeople2; temp++)
			if (tempNO == 应聘人员[temp].编号)
				break;
			numberpeople2--;
			if (m <= 2)
				经理岗位[m].应聘人数--;
			else if (m >= 3)
				普通岗位[m - 3].应聘人数--;
			if (temp == (numberpeople2 + 1))
			{
				strcpy(应聘人员[temp].姓名, "\0");
				strcpy(应聘人员[temp].性别, "\0");
				应聘人员[temp].年龄 = 0;
				strcpy(应聘人员[temp].应聘名称, "\0");
				应聘人员[temp].编号 = 0;
			}
			else
			{
				for (j = temp; j<numberpeople2; j++)
				{
					strcpy(应聘人员[j].姓名, 应聘人员[j + 1].姓名);
					strcpy(应聘人员[j].性别, 应聘人员[j + 1].性别);
					应聘人员[j].年龄 = 应聘人员[j + 1].年龄;
					strcpy(应聘人员[j].应聘名称, 应聘人员[j + 1].应聘名称);
					应聘人员[j].编号 = 应聘人员[j + 1].编号;
				}
				strcpy(应聘人员[numberpeople2 + 1].姓名, "\0");
				strcpy(应聘人员[numberpeople2 + 1].性别, "\0");
				应聘人员[numberpeople2 + 1].年龄 = 0;
				strcpy(应聘人员[numberpeople2 + 1].应聘名称, "\0");
				应聘人员[numberpeople2 + 1].编号 = 0;
			}
			if ((fpeople2 = fopen("people2.txt", "w+")) == NULL)
			{
				printf("文件people2.txt无法打开！\n"); exit(1);
			}
			for (i = 0; i<numberpeople2; i++)
				fprintf(fpeople2, "%-10s %-10s %-10d %-10s %-10d", 应聘人员[i].姓名, 应聘人员[i].性别, 应聘人员[i].年龄, 应聘人员[i].应聘名称, 应聘人员[i].编号);
			fclose(fpeople2);
		}
		printf("删除人员成功！\n若您希望继续删除人员，请输入1\n若您希望退出删除模块，请输入0\n");
		printf("请输入数字：");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("您输入的数字有误！默认为退出 删除人员 模块 \n"); break; }
	}
}
void main()
{
	double  n;
	void(*oper[6])(void); //指向函数的指针的运用
	oper[0] = input; oper[1] = search; oper[2] = calc; oper[3] = sort; oper[4] = change; oper[5] = delete_p;
	prepare();
	printf("-------------------------------------------------\n");
	printf("|\t %c                               %c \t|\n", 001, 001);
	printf("|\t      欢迎进入企业人事管理系统！   \t|\n");
	printf("|\t                                   \t|\n");// 不同数字对应着不同的函数
	printf("|\t 若您需要输入人事信息      请输入1 \t|\n");
	printf("|\t 若您需要查询在岗人员情况  请输入2 \t|\n");
	printf("|\t 若您需要查询应聘人员情况  请输入3 \t|\n");
	printf("|\t 若您需要查看岗位热度排序  请输入4 \t|\n");
	printf("|\t 若您需要调动人员          请输入5 \t|\n");
	printf("|\t 若您需要删除人员          请输入6 \t|\n");
	printf("|\t 若您希望退出本系统        请输入0 \t|\n");
	printf("|\t                                   \t|\n");
	printf("|\t                      作者：徐栩海 \t|\n");
	printf("|\t             联系方式：13588550938 \t|\n");
	printf("|\t    电子邮箱：orson.xu@foxmail.com \t|\n");
	printf("-------------------------------------------------\n");
	for (;;)
	{
		for (;;)
		{
			n = -1;
			printf("请输入数字：");
			scanf("%lf", &n);
			fflush(stdin);
			if (n == 0)
				exit(0);
			else if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6)
			{
				(*oper[int(n - 1)])(); break;
			}    //考虑输入的数字为小数，所以将n先定义为double形之后再强制转换
			else
			{
				printf("对不起您输入的数字有误！请重新输入："); continue;
			}
		}
		printf("-------------------------------------------------\n");//以上函数运行完之后回到原来界面
		printf("|\t %c                               %c \t|\n", 001, 001);
		printf("|\t     欢迎回到管理信息系统总界面！  \t|\n");
		printf("|\t                                   \t|\n");
		printf("|\t 若您需要输入人事信息      请输入1 \t|\n");
		printf("|\t 若您需要查询在岗人员情况  请输入2 \t|\n");
		printf("|\t 若您需要查询应聘人员情况  请输入3 \t|\n");
		printf("|\t 若您需要查看岗位热度排序  请输入4 \t|\n");
		printf("|\t 若您需要调动人员          请输入5 \t|\n");
		printf("|\t 若您需要删除人员          请输入6 \t|\n");
		printf("|\t 若您希望退出本系统        请输入0 \t|\n");
		printf("-------------------------------------------------\n");
	}
}