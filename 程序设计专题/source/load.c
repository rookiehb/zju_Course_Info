/*
 * 	该文件为主程序
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
// 变量声明
//用于读入二进制文件存储的细节 
static FILE *fp1;

//=============================================================================
// 函数声明
void load_model();

//=============================================================================
// 函数


void load_model()
{	
	if (style_choice==1)
		{
		if ( (fp1 = fopen("detail\\details_first.bin","rb"))==NULL )
			{
			printf("fp1 File open error!\n");
			exit(0);
			}
		}
	else if (style_choice==2)
		{
		if ( (fp1 = fopen("detail\\details_second.bin","rb"))==NULL )
			{
			printf("fp1 File open error!\n");
			exit(0);
			}
		}
	else if (style_choice==3)
		{
		if ( (fp1 = fopen("detail\\details_third.bin","rb"))==NULL )
			{
			printf("fp1 File open error!\n");
			exit(0);
			}
		}
	
	
	int a[10];
	fread(a,sizeof(int),10,fp1);
	rec_num = a[0];
	ell_num = a[1];
	cir_num = a[2];
	run_num = a[3];
	text_num = a[4];
	line_num = a[5];
	ell_cur_num = a[6];
	cir_cur_num = a[7];
	topic = a[8];
	sub_topic=a[9];
	
	fread(blank,sizeof(int),7,fp1);
	
	int i;
	for (i=0;i<rec_num;i++)
		fread(&rectangle[i],sizeof(struct data_one),1,fp1);
	for (i=0;i<ell_num;i++)
		fread(&ellipse[i],sizeof(struct data_one),1,fp1);
	for (i=0;i<cir_num;i++)
		fread(&circle[i],sizeof(struct data_one),1,fp1);
	for (i=0;i<run_num;i++)
		fread(&runway[i],sizeof(struct data_one),1,fp1);
	for (i=0;i<text_num;i++)
		fread(&text[i],sizeof(struct data_two),1,fp1);	
	for (i=0;i<line_num;i++)
		fread(&line[i],sizeof(struct data_three),1,fp1);
	for (i=0;i<ell_cur_num;i++)
		fread(&ell_curve[i],sizeof(struct data_four),1,fp1);
	for (i=0;i<cir_cur_num;i++)
		fread(&cir_curve[i],sizeof(struct data_five),1,fp1);

	
	if ( fclose(fp1) )	
		{
		printf("Can not close the file!\n");
		exit(0);
		}
}
