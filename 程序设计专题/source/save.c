/*
 * 	���ļ�Ϊ�����ļ� 
 */



 //=============================================================================
 // ͷ�ļ� 


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "conio.h"

#include "extgraph.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "simpio.h"

#include "structure.h"
#include "function.h"


//=============================================================================
// �������� 

//ָ���Ŷ������ļ����ļ�ָ�� 
static FILE *fp1;

//�ֱ��¼����λ�õ����� 
static int text_layer[4]; 

//������outline�ĸ�����ε�label 
static struct sub_theme {
	char *topic;
	char *bunch[4][10];
}text_theme[8];

//ָ���ı��ļ����ļ�ָ�� 
static FILE *fp;


//=============================================================================
// ��������

void store_details();
void getlayer(int num);
void initlayer();
void sort();
void output();


//=============================================================================
// ����


/*
 * Function: store_details
 * Usage: store_details()
 * --------------------------------------------------------
 * ���ܣ�
 *		�����ݴ�ɶ������ļ� 
 */
void store_details()
{
	if (style_choice == 1)
	{
		if ((fp1 = fopen("detail\\details_first.bin", "wb")) == NULL)
		{
			printf("fp1 File open error!\n");
			exit(0);
		}
	}
	else if (style_choice == 2)
	{
		if ((fp1 = fopen("detail\\details_second.bin", "wb")) == NULL)
		{
			printf("fp1 File open error!\n");
			exit(0);
		}
	}
	else if (style_choice == 3)
	{
		if ((fp1 = fopen("detail\\details_third.bin", "wb")) == NULL)
		{
			printf("fp1 File open error!\n");
			exit(0);
		}
	}

	int a[10] = { rec_num ,ell_num ,cir_num ,run_num ,text_num ,line_num ,ell_cur_num ,cir_cur_num,topic,sub_topic };
	fwrite(a, sizeof(int), 10, fp1);
	fwrite(blank, sizeof(int), 7, fp1);

	int i;
	for (i = 0; rectangle[i].x1 > 0; i++)
		fwrite(&rectangle[i], sizeof(struct data_one), 1, fp1);
	for (i = 0; ellipse[i].x1 > 0; i++)
		fwrite(&ellipse[i], sizeof(struct data_one), 1, fp1);
	for (i = 0; circle[i].x1 > 0; i++)
		fwrite(&circle[i], sizeof(struct data_one), 1, fp1);
	for (i = 0; runway[i].x1 > 0; i++)
		fwrite(&runway[i], sizeof(struct data_one), 1, fp1);
	for (i = 0; text[i].x1 > 0; i++)
		fwrite(&text[i], sizeof(struct data_two), 1, fp1);
	for (i = 0; line[i].x1 > 0; i++)
		fwrite(&line[i], sizeof(struct data_three), 1, fp1);
	for (i = 0; ell_curve[i].x1 > 0; i++)
		fwrite(&ell_curve[i], sizeof(struct data_four), 1, fp1);
	for (i = 0; cir_curve[i].x1 > 0; i++)
		fwrite(&cir_curve[i], sizeof(struct data_five), 1, fp1);

	if (fclose(fp1))
	{
		printf("fp1 Can not close the file!\n");
		exit(0);
	}
}

/*
 * Function: getlayer
 * Usage: getlayer(int num)
 * --------------------------------------------------------
 * ���ܣ�
 *		ͨ��layer����ֵ��ø����㼶����ֵ  
 */
void getlayer(int num)
{
	int flag = 1, i = 0, j, digit, temp = num;
	while (num != 0)
	{
		i++;
		flag = flag * 10;
		num /= 10;
	}
	num = temp;
	for (j = i; j > 0; j--)
	{
		flag = flag / 10;
		//��һ�㼶����text_layer[1],�ڶ��㼶����text_layer[2],�����㼶����text_layer[3] 
		text_layer[i - j + 1] = (num / flag) % 10;
	}
}

/*
 * Function: initlayer
 * Usage: initlayer
 * --------------------------------------------------------
 * ���ܣ�
 *		ÿ�λ�ȡ��ֵ�� ����Ҫ����һ��text�Ĳ㼶��Ϣ ����
 */
void initlayer() 
{
	int i;
	for (i = 0; i <= 4; i++)
		text_layer[i] = 0;
}

/*
 * Function: sort
 * Usage: sort()
 * --------------------------------------------------------
 * ���ܣ� 
 *		��ÿһ��text��labelֵ �Ž���Ӧ�����λ���� 
 */
void sort()
{
	if (style_choice == 1)
	{
		if ((fp = fopen("outline\\outline_first.txt", "w")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
	}
	else if (style_choice == 2)
	{
		if ((fp = fopen("outline\\outline_second.txt", "w")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
	}
	else if (style_choice == 3)
	{
		if ((fp = fopen("outline\\outline_third.txt", "w")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
	}

	int i;
	for (i = 0; text[i].x1 > 0; i++)
	{
		getlayer(text[i].layer);
		if (text_layer[2] == 0)//˵���ǵ�һ��ϵ�ķ�֧ �� ������ 
			text_theme[text_layer[1]].topic = text[i].p;
		else
			text_theme[text_layer[1]].bunch[text_layer[2]][text_layer[3]] = text[i].p;//�����ڶ�Ӧ��λ���� 
		initlayer();
	}
	output();//������ 
	store_details();//����ϸ����Ϣ 
}

/*
 * Function: output 
 * Usage: output()
 * --------------------------------------------------------
 * ���ܣ� 
 *		����ŵ�labelֵ ����layer �����˼ά��ͼ��� 
 */
void output()
{
	int i, j, k; int flag = 0;
	fprintf(fp, "�����⣺%s\n", text_theme[0].topic);
	for (i = 1; text_theme[i].topic != NULL; i++)
	{
		fprintf(fp, "	��%d���ӱ���:%s\n", i, text_theme[i].topic);
		
		//��������֧�������� �����������N��֧ flagΪ1ʱ��ʾ��Ҫ���� 
		if (text_theme[i].bunch[1][1] != NULL || text_theme[i].bunch[2][1] != NULL || text_theme[i].bunch[3][1] != NULL) 
			flag = 1;
		for (j = 1; j <= 3; j++)
		{
			for (k = 0; text_theme[i].bunch[j][k] != NULL; k++)
				if (flag == 1)
					if (k == 0 && text_theme[i].bunch[j][k] != NULL)
						fprintf(fp, "		��%d��֧:%s\n", j, text_theme[i].bunch[j][0]);
					else
						fprintf(fp, "			%s\n", text_theme[i].bunch[j][k]);
				else//�������� 
					fprintf(fp, "		%s\n", text_theme[i].bunch[j][k]);
		}
	}
	if (fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
}



