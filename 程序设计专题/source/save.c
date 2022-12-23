/*
 * 	该文件为保存文件 
 */



 //=============================================================================
 // 头文件 


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
// 变量定义 

//指向存放二进制文件的文件指针 
static FILE *fp1;

//分别记录各个位置的数字 
static int text_layer[4]; 

//存放输出outline的各个层次的label 
static struct sub_theme {
	char *topic;
	char *bunch[4][10];
}text_theme[8];

//指向文本文件的文件指针 
static FILE *fp;


//=============================================================================
// 函数声明

void store_details();
void getlayer(int num);
void initlayer();
void sort();
void output();


//=============================================================================
// 函数


/*
 * Function: store_details
 * Usage: store_details()
 * --------------------------------------------------------
 * 功能：
 *		将数据存成二进制文件 
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
 * 功能：
 *		通过layer的数值获得各个层级的数值  
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
		//第一层级存在text_layer[1],第二层级存在text_layer[2],第三层级存在text_layer[3] 
		text_layer[i - j + 1] = (num / flag) % 10;
	}
}

/*
 * Function: initlayer
 * Usage: initlayer
 * --------------------------------------------------------
 * 功能：
 *		每次获取赋值完 都需要将上一个text的层级信息 清零
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
 * 功能： 
 *		将每一个text的label值 放进对应输出的位置中 
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
		if (text_layer[2] == 0)//说明是第一派系的分支 或 主标题 
			text_theme[text_layer[1]].topic = text[i].p;
		else
			text_theme[text_layer[1]].bunch[text_layer[2]][text_layer[3]] = text[i].p;//储存在对应的位置上 
		initlayer();
	}
	output();//输出大纲 
	store_details();//储存细节信息 
}

/*
 * Function: output 
 * Usage: output()
 * --------------------------------------------------------
 * 功能： 
 *		将存放的label值 按照layer 输出成思维导图大纲 
 */
void output()
{
	int i, j, k; int flag = 0;
	fprintf(fp, "主标题：%s\n", text_theme[0].topic);
	for (i = 1; text_theme[i].topic != NULL; i++)
	{
		fprintf(fp, "	第%d个子标题:%s\n", i, text_theme[i].topic);
		
		//若三个分支均无延申 则无需输出第N分支 flag为1时表示需要延申 
		if (text_theme[i].bunch[1][1] != NULL || text_theme[i].bunch[2][1] != NULL || text_theme[i].bunch[3][1] != NULL) 
			flag = 1;
		for (j = 1; j <= 3; j++)
		{
			for (k = 0; text_theme[i].bunch[j][k] != NULL; k++)
				if (flag == 1)
					if (k == 0 && text_theme[i].bunch[j][k] != NULL)
						fprintf(fp, "		第%d分支:%s\n", j, text_theme[i].bunch[j][0]);
					else
						fprintf(fp, "			%s\n", text_theme[i].bunch[j][k]);
				else//无需延申 
					fprintf(fp, "		%s\n", text_theme[i].bunch[j][k]);
		}
	}
	if (fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
}



