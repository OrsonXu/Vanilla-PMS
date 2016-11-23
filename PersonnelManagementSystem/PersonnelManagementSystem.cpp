/*
�󲿷ֱ��������Ҷ�ʹ��������,��Ȼ��֮��Ĳ����з����˺ܶ�,����ҪĿ����ʹ���Լ����Ӳ��׷���,��Ϊ����̫��,
�������û�����г���,���Ƚ��е���,�����������Ա���������
��������ȫ���Լ���д,δ��ͬ��,����Ϯ.
�����򲻿������κ���ҵ��;.
��ϵ��ʽ:
Tel:	13588550938
Email:	orson.xu@foxmail.com
*/
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <conio.h> //����getch()����
#define MAX 100
struct job1  //���徭���λ��ͬʱ��ֵ���������Ÿ�λ
{
	char ��λ����[10];
	char �ȼ�;
	float ��������;
	char ��˾�ɷ�[10];  //���Ǳ���ͨ��λ������Ĳ���
	int �ڸ�����;
	int ӦƸ����;
}�����λ[3] = { { "��������", 'A', 12000, "1.0%", 0, 0 }, { "�з�����", 'B', 10000, "0.6%", 0, 0 }, { "��������", 'B', 9000, "0.3%", 0, 0 } };
struct job2  //������ͨ��λ��ͬʱ��ֵ���;����λ�����֣��в�ͬ��Ŀ�Ĳ�����
{
	char ��λ����[10];
	char �ȼ�;
	float ��������;
	int �ڸ�����;
	int ӦƸ����;
}��ͨ��λ[7] = { { "���", 'C', 7000, 0, 0 }, { "�ɹ�Ա", 'C', 6000, 0, 0 }, { "����Ա", 'C', 7500, 0, 0 }, { "˾��", 'D', 4000, 0, 0 }, { "��ʦ", 'D', 4000, 0, 0 }, { "����", 'E', 3000, 0, 0 }, { "��๤", 'E', 3000, 0, 0 } };
struct people1  //�ڸ���Ա
{
	char ����[20];
	char �Ա�[4];
	int ����;
	char �ڸ�����[10];
	int ���;
}�ڸ���Ա[MAX];
struct people2 //ӦƸ��Ա���ڸ���Ա�ֿ���¼,�ֱ���������ļ���
{
	char ����[20];
	char �Ա�[4];
	int ����;
	char ӦƸ����[10];
	int ���;
}ӦƸ��Ա[MAX];
FILE *fpeople1, *fpeople2;//ָ�����ڴ��� �ڸ���Ա �� ӦƸ��Ա �������ļ�
FILE *fp1, *fp2;
int numberpeople1 = 0, numberpeople2 = 0, NO1 = 100000, NO2 = 200000; //numberpeople1��2 �ֱ��¼�ڸں�ӦƸ��Ա������  ��NO1 2 �ֱ��������˵ı�� ǰ��1��ͷ ����2��ͷ
void prepare()  //�����ڳ���ʼʱ���г�ʼ׼�������������λ���ڸڡ�ӦƸ���������Ҵ浽job�ṹ�����鵱�С�ͬʱ�����������������š�Ϊ֮����׼����
{
	int calculatezg(int), calculateyp(int);
	int i, j;
	for (i = 0; i<3; i++)
	{
		�����λ[i].�ڸ����� = calculatezg(i); numberpeople1 += calculatezg(i);
	}
	for (j = 0; j<7; j++)
	{
		��ͨ��λ[j].�ڸ����� = calculatezg(j + 3); numberpeople1 += calculatezg(j + 3);
	}
	for (i = 0; i<3; i++)
	{
		�����λ[i].ӦƸ���� = calculateyp(i); numberpeople2 += calculateyp(i);
	}
	for (j = 0; j<7; j++)
	{
		��ͨ��λ[j].ӦƸ���� = calculateyp(j + 3); numberpeople2 += calculateyp(j + 3);
	}
	if ((fp1 = fopen("NO1.txt", "r")) == NULL)					// ��һ���ֵĴ���Ŀ����ר��Ϊ����������õġ�
	{
		printf("�ļ�N01.txt�޷��򿪣�\n"); exit(1);
	}			// ��һ���ļ��洢��ţ���������Ա��ɾ��֮�󣬱��Ҳ������ֱ�С�����⡣
	fscanf(fp1, "%d", &NO1);
	fclose(fp1);
	if ((fp2 = fopen("NO2.txt", "r")) == NULL)
	{
		printf("�ļ�N02.txt�޷��򿪣�\n"); exit(1);
	}
	fscanf(fp2, "%d", &NO2);
	fclose(fp2);
}
int calculateyp(int n) //����ӦƸ�����ĺ���, n��1-10 ��Ӧʮ����ͬ��ְλ
{
	int i, j, k, result[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if ((fpeople2 = fopen("people2.txt", "r")) == NULL)
	{
		perror("���ļ� people2.txt �޷���\n"); exit(1);
	}
	for (i = 0; i<MAX; i++)
		fscanf(fpeople2, "%s %s %d %s %d", &ӦƸ��Ա[i].����, &ӦƸ��Ա[i].�Ա�, &ӦƸ��Ա[i].����, &ӦƸ��Ա[i].ӦƸ����, &ӦƸ��Ա[i].���);
	for (j = 0; j<MAX; j++)
	{
		for (k = 0; k<3; k++)
		if (strcmp(ӦƸ��Ա[j].ӦƸ����, �����λ[k].��λ����) == 0)
			result[k]++;
		for (k = 0; k<7; k++)
		if (strcmp(ӦƸ��Ա[j].ӦƸ����, ��ͨ��λ[k].��λ����) == 0)
			result[k + 3]++;
	}
	fclose(fpeople2);
	return(result[n]);
}
int calculatezg(int n)//�����ڸ������ĺ���, n��1-10 ��Ӧʮ����ͬ��ְλ
{
	int i, j, k, result[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if ((fpeople1 = fopen("people1.txt", "r")) == NULL)
	{
		perror("���ļ� people1.txt �޷���\n"); exit(1);
	}
	for (i = 0; i<MAX; i++)
		fscanf(fpeople1, "%s %s %d %s %d", &�ڸ���Ա[i].����, &�ڸ���Ա[i].�Ա�, &�ڸ���Ա[i].����, &�ڸ���Ա[i].�ڸ�����, &�ڸ���Ա[i].���);
	for (j = 0; j<MAX; j++)
	{
		for (k = 0; k<3; k++)
		if (strcmp(�ڸ���Ա[j].�ڸ�����, �����λ[k].��λ����) == 0)
			result[k]++;
		for (k = 0; k<7; k++)
		if (strcmp(�ڸ���Ա[j].�ڸ�����, ��ͨ��λ[k].��λ����) == 0)
			result[k + 3]++;
	}
	fclose(fpeople1);
	return(result[n]);
}
void input() // ����������Ϣ�ĺ���
{
	int judge, i, i1, i2, j, k, l, n, m = 0;
	for (;;) // ����ѭ���ķ�ʽ�����ظ����� ����ѭ����ʽ�� continue �� break ʵ��. ֮����ע��
	{
		printf("-----------------------------------------\n");
		printf("|\t  ��ӭ������Ϣ¼��ģ�飡 \t|\n");
		printf("|\t ��ѡ�����ƻ�¼���˵���� \t|\n|\t ������ �ڸ���Ա ������1 \t|\n|\t ������ ӦƸ��Ա ������2 \t|\n");
		printf("-----------------------------------------\n");
		printf("���������֣�");
		judge = 0;//��֤ÿ�ε��������ֶ�����ʼ��
		scanf("%d", &judge); // ���� 1 �� 2 ��Ӧ�����ڸ���Ա��ӦƸ��Ա����Ϣ��
		fflush(stdin);
		if (judge == 1)
		{
			if ((fpeople1 = fopen("people1.txt", "a")) == NULL)
			{
				perror("���ļ� person1.txt �޷���\n"); exit(1);
			}
			i = numberpeople1;
			printf("������������");
			scanf("%s", &�ڸ���Ա[i].����);
			fflush(stdin);
			for (;;) // �ݴ� ֮��Ҳ������ע��
			{
				printf("�������Ա𣨡��С���Ů������");
				scanf("%s", &�ڸ���Ա[i].�Ա�);
				fflush(stdin);
				if ((strcmp(�ڸ���Ա[i].�Ա�, "��") != 0) && (strcmp(�ڸ���Ա[i].�Ա�, "Ů") != 0))
				{
					printf("�Բ�����������Ա���������������\n"); continue;
				}
				else break;
			}
			printf("���������䣺");
			for (;;)
			{
				�ڸ���Ա[i].���� = 0;
				scanf("%d", &�ڸ���Ա[i].����);
				fflush(stdin);
				if (�ڸ���Ա[i].���� <= 17 || �ڸ���Ա[i].���� >= 70)
				{
					printf("�Բ�������������䲻���Ϲ�����ع涨�����������룺"); continue;
				}
				else break;
			}
			printf("\n");
			printf("�������λ��\n");
			for (i1 = 0; i1<3; i1++)
				printf("����ϣ������ĸ�λ�� %s\t������ %d\n", �����λ[i1].��λ����, i1 + 1);
			for (i2 = 0; i2<7; i2++)
				printf("����ϣ������ĸ�λ�� %s\t������ %d\n", ��ͨ��λ[i2].��λ����, i2 + 4);
			printf("\n��������Ӧ�ĸ�λ��Ӧ�����֣�");
			for (;;)
			{
				n = 0;
				scanf("%d", &n);
				fflush(stdin);
				if (n<1 || n>10)
				{
					printf("�Բ���������������������������룺\n"); continue;
				}
				else break;
			}
			n = n - 1;
			if (n <= 2)
			{
				strcpy(�ڸ���Ա[i].�ڸ�����, �����λ[n].��λ����); numberpeople1++; �����λ[n].�ڸ�����++;
			}
			else if (n >= 3)
			{
				strcpy(�ڸ���Ա[i].�ڸ�����, ��ͨ��λ[n - 3].��λ����); numberpeople1++; ��ͨ��λ[n - 3].�ڸ�����++;
			}
			NO1++;
			�ڸ���Ա[i].��� = NO1;
			fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", �ڸ���Ա[i].����, �ڸ���Ա[i].�Ա�, �ڸ���Ա[i].����, �ڸ���Ա[i].�ڸ�����, �ڸ���Ա[i].���);
			fclose(fpeople1);
			if ((fp1 = fopen("NO1.txt", "w")) == NULL)		//��ʱ��NO1�ĸ��±��浽����ĵ��У���֤��ŵ�ͳһ�ԡ�
			{
				printf("�ļ�N01.txt�޷��򿪣�\n"); exit(1);
			}
			fprintf(fp1, "%d", NO1);
			fclose(fp1);
		}
		else if (judge == 2)  // ��judge==1�����ݼ�����ȫ��ͬ�����沿�ֲ���׸���ˡ�
		{
			if ((fpeople2 = fopen("people2.txt", "a")) == NULL)
			{
				perror("���ļ� people2.txt �޷���\n"); exit(1);
			}
			i = numberpeople2;
			printf("������������");
			scanf("%s", &ӦƸ��Ա[i].����);
			fflush(stdin);
			for (;;)
			{
				printf("�������Ա𣨡��С���Ů������");
				scanf("%s", &ӦƸ��Ա[i].�Ա�);
				fflush(stdin);
				if ((strcmp(ӦƸ��Ա[i].�Ա�, "��") != 0) && (strcmp(ӦƸ��Ա[i].�Ա�, "Ů") != 0))
				{
					printf("�Բ�����������Ա�����\n"); continue;
				}
				else break;
			}
			printf("���������䣺");
			for (;;)
			{
				ӦƸ��Ա[i].���� = 0;
				scanf("%d", &ӦƸ��Ա[i].����);
				fflush(stdin);
				if (ӦƸ��Ա[i].���� <= 17 || ӦƸ��Ա[i].���� >= 70)
				{
					printf("�Բ�������������䲻���Ϲ�����ع涨�����������룺"); continue;
				}
				else break;
			}
			printf("\n");
			printf("�������λ��\n");
			for (i1 = 0; i1<3; i1++)
				printf("����ϣ������ĸ�λ�� %s\t������ %d\n", �����λ[i1].��λ����, i1 + 1);
			for (i2 = 0; i2<7; i2++)
				printf("����ϣ������ĸ�λ�� %s\t������ %d\n", ��ͨ��λ[i2].��λ����, i2 + 4);
			printf("\n��������Ӧ�ĸ�λ��Ӧ�����֣�");
			for (;;)
			{
				n = 0;
				scanf("%d", &n);
				fflush(stdin);
				if (n<1 || n>10)
				{
					printf("�Բ���������������������������룺\n"); continue;
				}
				else break;
			}
			n = n - 1;
			if (n <= 2)
			{
				strcpy(ӦƸ��Ա[i].ӦƸ����, �����λ[n].��λ����); numberpeople2++; �����λ[n].ӦƸ����++;
			}
			else if (n >= 3)
			{
				strcpy(ӦƸ��Ա[i].ӦƸ����, ��ͨ��λ[n - 3].��λ����); numberpeople2++; ��ͨ��λ[n - 3].ӦƸ����++;
			}
			NO2++;
			ӦƸ��Ա[i].��� = NO2;
			fprintf(fpeople2, "%-10s %-10s %-10d %-10s %-10d", ӦƸ��Ա[i].����, ӦƸ��Ա[i].�Ա�, ӦƸ��Ա[i].����, ӦƸ��Ա[i].ӦƸ����, ӦƸ��Ա[i].���);
			numberpeople2++;
			fclose(fpeople2);
			if ((fp2 = fopen("NO2.txt", "w")) == NULL)
			{
				printf("�ļ�N02.txt�޷��򿪣�\n"); exit(1);
			}
			fprintf(fp2, "%d", NO2);
			fclose(fp2);
		}
		else
		{
			printf("�Բ���������������������������룺\n"); continue;
		}
		printf("�����Ա�ɹ���\n�������Ҫ����������Ա��Ϣ��������1\n������Ҫ�˳���Ϣ¼��ģ�飬������0\n");
		printf("���������֣�"); // ѡ���Ƿ��������
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("���������������Ĭ����Ϊ�˳� ��Ϣ¼�� ģ�飡\n"); break; }
	}
}

void search() // ��ѯ�ڸ���Ա����ĺ���
{
	int judge, i, j, k, n;
	char goal[10];
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t   ��ӭ�����ѯ�ڸ���Աģ�飡   \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", �����λ[i].��λ����, i + 1);
		for (i = 0; i<6; i++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", ��ͨ��λ[i].��λ����, i + 4);
		printf("|\t ����ϣ������ %s\t������10 \t|\n", ��ͨ��λ[6].��λ����);//���䵥���ó���,��Ϊ 10 ��ռ��λ�ò�ͬ��1-9, ����������\t����.���滹��������Ƶ����,����׸��.
		printf("-------------------------------------------------\n");
		printf("���������֣�");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else break;
		}
		n = n - 1; // ������������������� �����λ ���� ��ͨ��λ, �ֱ������λ�ṹ���ڵĲ���,
		if (n <= 2)
		{
			printf("�����ҵĸ�λ����Ϊ\t\t%s\n�ø�λ�ĵȼ�Ϊ\t\t\t%c\n�ø�λ�Ļ�������Ϊ\t\t%f\n�ø�λ�ܹ�ռ�еĹ�˾�ɷ�Ϊ\t%s\n�ø�λĿǰ���ڸ�����\t\t%d\n�ø�λĿǰ��ӦƸ����\t\t%d\n", �����λ[n].��λ����, �����λ[n].�ȼ�, �����λ[n].��������, �����λ[n].��˾�ɷ�, �����λ[n].�ڸ�����, �����λ[n].ӦƸ����);
			printf("�����ǹ��ڴ˸�λ���ڸ���Ա�������\n");
			printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(�ڸ���Ա[j].�ڸ�����, �����λ[n].��λ����) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].�Ա�, �ڸ���Ա[j].����, �ڸ���Ա[j].���);
			printf("\n");
		}
		else if (n >= 3)
		{
			n = n - 3;
			printf("�����ҵĸ�λ����Ϊ\t\t%s\n�ø�λ�ĵȼ�Ϊ\t\t\t%c\n�ø�λ�Ļ�������Ϊ\t\t%f\n�ø�λĿǰ���ڸ�����\t\t%d\n�ø�λĿǰ��ӦƸ����\t\t%d\n", ��ͨ��λ[n].��λ����, ��ͨ��λ[n].�ȼ�, ��ͨ��λ[n].��������, ��ͨ��λ[n].�ڸ�����, ��ͨ��λ[n].ӦƸ����);
			printf("�����ǹ��ڴ˸�λ���ڸ���Ա�������\n");
			printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(�ڸ���Ա[j].�ڸ�����, ��ͨ��λ[n].��λ����) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].�Ա�, �ڸ���Ա[j].����, �ڸ���Ա[j].���);
			printf("\n");
		}
		printf("����ϣ���������в�ѯ��������1\n����ϣ���˳���ѯ�ڸ����ģ�飬������0\n");
		printf("���������֣�");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("���������������Ĭ��Ϊ�˳� ��ѯ�ڸ����� ģ�飡\n"); break; }
	}
}
void calc() //  ����ӦƸ���� ���Ҳ�ѯӦƸ��Ա�����
{
	int calculateyp(int);
	int i, j, k, n, result;
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t    ��ӭ�����ѯӦƸ��Աģ�飡  \t|\n");
		printf("|\t ��������ϣ����ѯӦƸ��Ա�ĸ�λ \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", �����λ[i].��λ����, i + 1);
		for (j = 0; j<6; j++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", ��ͨ��λ[j].��λ����, j + 4);
		printf("|\t ����ϣ������ %s\t������10 \t|\n", ��ͨ��λ[6].��λ����);
		printf("-------------------------------------------------\n");
		printf("���������֣�");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else break;
		}
		n = n - 1;
		printf("�ø�λ ");
		if (n <= 2)
		{
			printf("%s", �����λ[n].��λ����); result = �����λ[n].ӦƸ����;
		}
		else if (n >= 3)
		{
			printf("%s", ��ͨ��λ[n - 3].��λ����); result = ��ͨ��λ[n - 3].ӦƸ����;
		}
		printf(" ��ӦƸ����Ϊ %d\n", result);
		printf("�����ǹ��ڴ˸�λ��ӦƸ��Ա�������\n");
		if (n <= 2)
		{
			printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
			for (j = 0; j<numberpeople2; j++)
			if (strcmp(ӦƸ��Ա[j].ӦƸ����, �����λ[n].��λ����) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", ӦƸ��Ա[j].����, ӦƸ��Ա[j].�Ա�, ӦƸ��Ա[j].����, ӦƸ��Ա[j].���);
			printf("\n");
		}
		else if (n >= 3)
		{
			printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
			for (j = 0; j<numberpeople2; j++)
			if (strcmp(ӦƸ��Ա[j].ӦƸ����, ��ͨ��λ[n - 3].��λ����) == 0)
				printf("\t%-10s %-10s %-10d %-10d\n", ӦƸ��Ա[j].����, ӦƸ��Ա[j].�Ա�, ӦƸ��Ա[j].����, ӦƸ��Ա[j].���);
			printf("\n");
		}
		printf("����ϣ����������������λ��ӦƸ������������1\n����ϣ���˳���ѯӦƸ��Աģ�飬������0\n");
		printf("���������֣�");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("���������������Ĭ��Ϊ�˳� ��ѯӦƸ���� ģ��\n"); break; }
	}
}
void sort()//���������������
{
	int i, j, k, tempnum;
	char temppos[10];
	struct number
	{
		int num;		//��Ÿ�λ��ӦƸ����
		char pos[10];	//��Ÿ�λ����
		struct number *next;
	}*head, *cursor, *tempnode, *compare;
	head = (struct number *)malloc(sizeof(struct number)); // ͷ�������ڴ�
	if (head == NULL)
	{
		printf("���󣬱�ͷ����ڴ����ʧ�ܣ�"); exit(1);
	}
	head->next = NULL;
	cursor = head;
	for (i = 0; i<10; i++)
	{
		tempnode = (struct number *)malloc(sizeof(struct number));
		if (tempnode == NULL)
		{
			printf("�����м����ڴ����ʧ�ܣ�"); exit(1);
		}
		if (i <= 2)
		{
			tempnode->num = �����λ[i].ӦƸ����; strcpy(tempnode->pos, �����λ[i].��λ����);
		}
		else if (i >= 3)
		{
			tempnode->num = ��ͨ��λ[i - 3].ӦƸ����; strcpy(tempnode->pos, ��ͨ��λ[i - 3].��λ����);
		}
		tempnode->next = NULL;
		cursor->next = tempnode;
		cursor = cursor->next;
	}
	for (j = 0; j<9; j++) //����ð������
	for (cursor = head->next; cursor->next != NULL; cursor = cursor->next)
	if (cursor->num<cursor->next->num)
	{
		tempnum = cursor->num; cursor->num = cursor->next->num; cursor->next->num = tempnum;
		strcpy(temppos, cursor->pos); strcpy(cursor->pos, cursor->next->pos); strcpy(cursor->next->pos, temppos);
	}
	printf("�����Ǹ���λ��ְ�ȶ�����\n");
	for (k = 0, cursor = head->next; k<9; k++)
	{
		printf("�� %d ��\t  %s  \tӦƸ������%d\n", k + 1, cursor->pos, cursor->num);
		cursor = cursor->next;
	}
	printf("�� %d��\t  %s  \tӦƸ������%d\n", k + 1, cursor->pos, cursor->num);
	printf("�밴���������...");
	getch(); //��ȡ������ʾ ����ʵ�ְ����������
	printf("\n");
}
void change() // ��Ա�������� ��Ҫ˼·Ϊ�ı� ��������Ա �� "�ڸ���Ա[].�ڸ�����"
{
	int i, j, k, b, judge = 0, n, m, p, buf;
	int bufnum[MAX];
	for (;;)
	{
		printf("-------------------------------------------------\n");
		printf("|\t      ��ӭ������Ա����ģ�飡    \t|\n");
		printf("|\t ��������ϣ��������Աԭ����λ   \t|\n");
		for (i = 0; i<3; i++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", �����λ[i].��λ����, i + 1);
		for (j = 0; j<6; j++)
			printf("|\t ����ϣ������ %s\t������%d  \t|\n", ��ͨ��λ[j].��λ����, j + 4);
		printf("|\t ����ϣ������ %s\t������10 \t|\n", ��ͨ��λ[6].��λ����);
		printf("-------------------------------------------------\n");
		printf("���������֣�");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n<1 || n>10)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else break;
		}
		n = n - 1;
		b = 0;//��֤��һ���Ժ�Ĵ�����bufnum����Ч��
		printf("���ڸø�λ����Ա��\n");//������еĸø�λ����Ա�������Ͷ�Ӧ�ı��
		if (n <= 2)
		{
			printf("\t%-10s %-10s\n\n", "����", "���");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(�ڸ���Ա[j].�ڸ�����, �����λ[n].��λ����) == 0)
			{
				printf("\t%-10s %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].���); bufnum[b] = �ڸ���Ա[j].���; b++;
			}//������ʱ��¼���ڸø�λ����Ա��ţ���ͬ
		}
		else if (n >= 3)
		{
			printf("\t%-10s %-10s\n\n", "����", "���");
			for (j = 0; j<numberpeople1; j++)
			if (strcmp(�ڸ���Ա[j].�ڸ�����, ��ͨ��λ[n - 3].��λ����) == 0)
			{
				printf("\t%-10s %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].���); bufnum[b] = �ڸ���Ա[j].���; b++;
			}
		}
		if (b == 0) // ������Ϊ��,�����������
		{
			printf("\n�ø�λ���ڸ���Ա��Ϊ�㣡�밴���������...\n"); getch(); continue;
		}
		printf("\n��������ϣ�����ڵ���Ա�ı�ţ�");
		for (;;)
		{
			scanf("%d", &buf);
			fflush(stdin);
			for (i = 0; i<b; i++)
			if (bufnum[i] == buf)
				judge++;
			if (judge == 0)
			{
				printf("�Բ����������ŵĶ�Ӧ��Ա���ڴ˸�λ�ϣ����������룺"); continue;
			}
			else break;
		}judge = 0;//��֤judge����Ч�ԡ�
		printf("��������ϣ��������Ա����Ҫȥ�ĸ�λ\n");
		for (i = 0; i<3; i++)
			printf("����λ�� %s\t������ %d\n", �����λ[i].��λ����, i + 1);
		for (j = 0; j<7; j++)
			printf("����λ�� %s\t\t������ %d\n", ��ͨ��λ[j].��λ����, j + 4);
		printf("���������֣�");
		for (;;)
		{
			m = 0;
			scanf("%d", &m);
			fflush(stdin);
			m = m - 1;
			if (m<0 || m>9)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else if (n == m)
			{
				printf("�Բ�������������ֺ�֮ǰ��������ͬ�����������룺"); continue;
			}
			else break;
		}
		if (n <= 2)
		{
			�����λ[n].�ڸ�����--;
			if (�����λ[n].�ڸ�����<3)//�жϸ�λ�����Ƿ���������
				printf("\n��ע�⣡%s ���ڸ�����Ϊ %d���Ѿ��������ˣ�\n\n", �����λ[n].��λ����, �����λ[n].�ڸ�����);
		}
		else if (n >= 3)
		{
			��ͨ��λ[n - 3].�ڸ�����--;
			if (��ͨ��λ[n - 3].�ڸ�����<3)
				printf("\n��ע�⣡%s ���ڸ�����Ϊ %d���Ѿ��������ˣ�\n\n", ��ͨ��λ[n - 3].��λ����, ��ͨ��λ[n - 3].�ڸ�����);
		}
		if (m <= 2)
			�����λ[m].�ڸ�����++;
		else if (m >= 3)
			��ͨ��λ[m - 3].�ڸ�����++;
		for (p = 0; p<MAX; p++)
		if (�ڸ���Ա[p].��� == buf)
		{
			if (m <= 2)
				strcpy(�ڸ���Ա[p].�ڸ�����, �����λ[m].��λ����);
			if (m >= 3)
				strcpy(�ڸ���Ա[p].�ڸ�����, ��ͨ��λ[m - 3].��λ����);
			break;
		}
		if ((fpeople1 = fopen("people1.txt", "w+")) == NULL)
		{
			perror("���ļ� people1.txt �޷���\n"); exit(1);
		}
		for (i = 0; i<numberpeople1; i++)
			fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", �ڸ���Ա[i].����, �ڸ���Ա[i].�Ա�, �ڸ���Ա[i].����, �ڸ���Ա[i].�ڸ�����, �ڸ���Ա[i].���);
		fclose(fpeople1);
		printf("������Ա�ɹ�������ϣ������������Ա��������1\n����ϣ���˳�����ģ�飬������0\n");
		printf("���������֣�");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("���������������Ĭ��Ϊ�˳� ��Ա���� ģ�� \n"); break; }
	}
}
void delete_p() //ɾ���κ�һ����Ա��Ϣ
{
	int i, j, k, n, m, tempNO, temp, b, judge = 0;
	int bufnum[MAX];
	for (;;)
	{
		printf("-----------------------------------------\n");
		printf("|\t  ��ӭ������Աɾ��ģ�飡 \t|\n");
		printf("|\t ��ѡ�����ƻ�ɾ���˵���� \t|\n|\t ������ �ڸ���Ա ������1 \t|\n|\t ������ ӦƸ��Ա ������2 \t|\n");
		printf("-----------------------------------------\n");
		printf("���������֣�");
		for (;;)
		{
			n = 0;
			scanf("%d", &n);
			fflush(stdin);
			if (n != 1 && n != 2)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else break;
		}
		printf("��������ϣ��ɾ����Ա���ڵĸ�λ\n");
		for (i = 0; i<3; i++)
			printf("����λ�� %s\t������ %d\n", �����λ[i].��λ����, i + 1);
		for (j = 0; j<7; j++)
			printf("����λ�� %s\t\t������ %d\n", ��ͨ��λ[j].��λ����, j + 4);
		printf("\n���������֣�");
		for (;;)
		{
			m = 0;
			scanf("%d", &m);
			fflush(stdin);
			m = m - 1;
			if (m<0 || m>9)
			{
				printf("�Բ���������������������������룺"); continue;
			}
			else break;
		}
		if (n == 1)
		{
			b = 0; //��֤��һ���Ժ�Ĵ�����bufnum����Ч��
			printf("�������ڸ���Ա����Ϣ��\n");
			if (m <= 2)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
				for (j = 0; j<numberpeople1; j++)
				if (strcmp(�ڸ���Ա[j].�ڸ�����, �����λ[m].��λ����) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].�Ա�, �ڸ���Ա[j].����, �ڸ���Ա[j].���); bufnum[b] = �ڸ���Ա[j].���; b++;
				}
				printf("\n"); //bufnum������ʱ��¼���ڸø�λ����Ա��ţ���ͬ
			}
			else if (m >= 3)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
				for (j = 0; j<numberpeople1; j++)
				if (strcmp(�ڸ���Ա[j].�ڸ�����, ��ͨ��λ[m - 3].��λ����) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", �ڸ���Ա[j].����, �ڸ���Ա[j].�Ա�, �ڸ���Ա[j].����, �ڸ���Ա[j].���); bufnum[b] = �ڸ���Ա[j].���; b++;
				}
				printf("\n");
			}
			if (b == 0) // ������Ϊ��,�����������
			{
				printf("\n�ø�λ���ڸ���Ա��Ϊ�㣡�밴���������...\n"); getch(); continue;
			}
			printf("��������ϣ��ɾ����Ա�ı�ţ�");
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
					printf("�Բ����������ŵĶ�Ӧ��Ա���ڴ˸�λ�ϣ����������룺"); continue;
				}
				else break;
			}judge = 0;//��֤judge����Ч�ԡ�
			for (temp = 0; temp<numberpeople1; temp++)
			if (tempNO == �ڸ���Ա[temp].���)
				break;
			numberpeople1--;   //��֤��������ͬ���仯
			if (m <= 2)
				�����λ[m].�ڸ�����--;
			else if (m >= 3)
				��ͨ��λ[m - 3].�ڸ�����--;
			if (temp == (numberpeople1 + 1)) //��ɾ����������󣬽�����ϢĨȥ
			{
				strcpy(�ڸ���Ա[temp].����, "\0");
				strcpy(�ڸ���Ա[temp].�Ա�, "\0");
				�ڸ���Ա[temp].���� = 0;
				strcpy(�ڸ���Ա[temp].�ڸ�����, "\0");
				�ڸ���Ա[temp].��� = 0;
			}
			else
			{
				for (j = temp; j<numberpeople1; j++) // ��������󣬽���֮���ȫ����ǰŲһλ
				{
					strcpy(�ڸ���Ա[j].����, �ڸ���Ա[j + 1].����);
					strcpy(�ڸ���Ա[j].�Ա�, �ڸ���Ա[j + 1].�Ա�);
					�ڸ���Ա[j].���� = �ڸ���Ա[j + 1].����;
					strcpy(�ڸ���Ա[j].�ڸ�����, �ڸ���Ա[j + 1].�ڸ�����);
					�ڸ���Ա[j].��� = �ڸ���Ա[j + 1].���;
				}
				strcpy(�ڸ���Ա[numberpeople1 + 1].����, "\0"); //���ҽ����һλ�������ϢĨȥ
				strcpy(�ڸ���Ա[numberpeople1 + 1].�Ա�, "\0");
				�ڸ���Ա[numberpeople1 + 1].���� = 0;
				strcpy(�ڸ���Ա[numberpeople1 + 1].�ڸ�����, "\0");
				�ڸ���Ա[numberpeople1 + 1].��� = 0;
			}
			if ((fpeople1 = fopen("people1.txt", "w+")) == NULL)
			{
				printf("�ļ�people1.txt�޷��򿪣�\n"); exit(1);
			}
			for (i = 0; i<numberpeople1; i++)
				fprintf(fpeople1, "%-10s %-10s %-10d %-10s %-10d", �ڸ���Ա[i].����, �ڸ���Ա[i].�Ա�, �ڸ���Ա[i].����, �ڸ���Ա[i].�ڸ�����, �ڸ���Ա[i].���);
			fclose(fpeople1);//���½����ݸ�ֵ���ļ���
		}
		else if (n == 2) // �ò�����n==1������ȫ��ͬ����Ϊ�ļ�������ͬ���Ե�����дһ�顣�����ע�;���ȥ�ˡ�
		{
			b = 0;
			printf("������ӦƸ��Ա����Ϣ��\n");
			if (m <= 2)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
				for (j = 0; j<numberpeople2; j++)
				if (strcmp(ӦƸ��Ա[j].ӦƸ����, �����λ[m].��λ����) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", ӦƸ��Ա[j].����, ӦƸ��Ա[j].�Ա�, ӦƸ��Ա[j].����, ӦƸ��Ա[j].���); bufnum[b] = ӦƸ��Ա[j].���; b++;
				}
				printf("\n");
			}
			else if (m >= 3)
			{
				printf("\t%-10s %-10s %-10s %-10s\n\n", "����", "�Ա�", "����", "���");
				for (j = 0; j<numberpeople2; j++)
				if (strcmp(ӦƸ��Ա[j].ӦƸ����, ��ͨ��λ[m - 3].��λ����) == 0)
				{
					printf("\t%-10s %-10s %-10d %-10d\n", ӦƸ��Ա[j].����, ӦƸ��Ա[j].�Ա�, ӦƸ��Ա[j].����, ӦƸ��Ա[j].���); bufnum[b] = �ڸ���Ա[j].���; b++;
				}
				printf("\n");
			}
			if (b == 0)
			{
				printf("\n�ø�λ���ڸ���Ա��Ϊ�㣡�밴���������..."); getch(); continue;
			}
			printf("��������ϣ��ɾ����Ա�ı�ţ�");
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
					printf("�Բ����������ŵĶ�Ӧ��Ա���ڴ˸�λ�ϣ����������룺"); continue;
				}
				else break;
			}judge = 0;
			for (temp = 0; temp<numberpeople2; temp++)
			if (tempNO == ӦƸ��Ա[temp].���)
				break;
			numberpeople2--;
			if (m <= 2)
				�����λ[m].ӦƸ����--;
			else if (m >= 3)
				��ͨ��λ[m - 3].ӦƸ����--;
			if (temp == (numberpeople2 + 1))
			{
				strcpy(ӦƸ��Ա[temp].����, "\0");
				strcpy(ӦƸ��Ա[temp].�Ա�, "\0");
				ӦƸ��Ա[temp].���� = 0;
				strcpy(ӦƸ��Ա[temp].ӦƸ����, "\0");
				ӦƸ��Ա[temp].��� = 0;
			}
			else
			{
				for (j = temp; j<numberpeople2; j++)
				{
					strcpy(ӦƸ��Ա[j].����, ӦƸ��Ա[j + 1].����);
					strcpy(ӦƸ��Ա[j].�Ա�, ӦƸ��Ա[j + 1].�Ա�);
					ӦƸ��Ա[j].���� = ӦƸ��Ա[j + 1].����;
					strcpy(ӦƸ��Ա[j].ӦƸ����, ӦƸ��Ա[j + 1].ӦƸ����);
					ӦƸ��Ա[j].��� = ӦƸ��Ա[j + 1].���;
				}
				strcpy(ӦƸ��Ա[numberpeople2 + 1].����, "\0");
				strcpy(ӦƸ��Ա[numberpeople2 + 1].�Ա�, "\0");
				ӦƸ��Ա[numberpeople2 + 1].���� = 0;
				strcpy(ӦƸ��Ա[numberpeople2 + 1].ӦƸ����, "\0");
				ӦƸ��Ա[numberpeople2 + 1].��� = 0;
			}
			if ((fpeople2 = fopen("people2.txt", "w+")) == NULL)
			{
				printf("�ļ�people2.txt�޷��򿪣�\n"); exit(1);
			}
			for (i = 0; i<numberpeople2; i++)
				fprintf(fpeople2, "%-10s %-10s %-10d %-10s %-10d", ӦƸ��Ա[i].����, ӦƸ��Ա[i].�Ա�, ӦƸ��Ա[i].����, ӦƸ��Ա[i].ӦƸ����, ӦƸ��Ա[i].���);
			fclose(fpeople2);
		}
		printf("ɾ����Ա�ɹ���\n����ϣ������ɾ����Ա��������1\n����ϣ���˳�ɾ��ģ�飬������0\n");
		printf("���������֣�");
		scanf("%d", &k);
		fflush(stdin);
		if (k == 1) continue;
		else if (k == 0) break;
		else { printf("���������������Ĭ��Ϊ�˳� ɾ����Ա ģ�� \n"); break; }
	}
}
void main()
{
	double  n;
	void(*oper[6])(void); //ָ������ָ�������
	oper[0] = input; oper[1] = search; oper[2] = calc; oper[3] = sort; oper[4] = change; oper[5] = delete_p;
	prepare();
	printf("-------------------------------------------------\n");
	printf("|\t %c                               %c \t|\n", 001, 001);
	printf("|\t      ��ӭ������ҵ���¹���ϵͳ��   \t|\n");
	printf("|\t                                   \t|\n");// ��ͬ���ֶ�Ӧ�Ų�ͬ�ĺ���
	printf("|\t ������Ҫ����������Ϣ      ������1 \t|\n");
	printf("|\t ������Ҫ��ѯ�ڸ���Ա���  ������2 \t|\n");
	printf("|\t ������Ҫ��ѯӦƸ��Ա���  ������3 \t|\n");
	printf("|\t ������Ҫ�鿴��λ�ȶ�����  ������4 \t|\n");
	printf("|\t ������Ҫ������Ա          ������5 \t|\n");
	printf("|\t ������Ҫɾ����Ա          ������6 \t|\n");
	printf("|\t ����ϣ���˳���ϵͳ        ������0 \t|\n");
	printf("|\t                                   \t|\n");
	printf("|\t                      ���ߣ����� \t|\n");
	printf("|\t             ��ϵ��ʽ��13588550938 \t|\n");
	printf("|\t    �������䣺orson.xu@foxmail.com \t|\n");
	printf("-------------------------------------------------\n");
	for (;;)
	{
		for (;;)
		{
			n = -1;
			printf("���������֣�");
			scanf("%lf", &n);
			fflush(stdin);
			if (n == 0)
				exit(0);
			else if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6)
			{
				(*oper[int(n - 1)])(); break;
			}    //�������������ΪС�������Խ�n�ȶ���Ϊdouble��֮����ǿ��ת��
			else
			{
				printf("�Բ���������������������������룺"); continue;
			}
		}
		printf("-------------------------------------------------\n");//���Ϻ���������֮��ص�ԭ������
		printf("|\t %c                               %c \t|\n", 001, 001);
		printf("|\t     ��ӭ�ص�������Ϣϵͳ�ܽ��棡  \t|\n");
		printf("|\t                                   \t|\n");
		printf("|\t ������Ҫ����������Ϣ      ������1 \t|\n");
		printf("|\t ������Ҫ��ѯ�ڸ���Ա���  ������2 \t|\n");
		printf("|\t ������Ҫ��ѯӦƸ��Ա���  ������3 \t|\n");
		printf("|\t ������Ҫ�鿴��λ�ȶ�����  ������4 \t|\n");
		printf("|\t ������Ҫ������Ա          ������5 \t|\n");
		printf("|\t ������Ҫɾ����Ա          ������6 \t|\n");
		printf("|\t ����ϣ���˳���ϵͳ        ������0 \t|\n");
		printf("-------------------------------------------------\n");
	}
}