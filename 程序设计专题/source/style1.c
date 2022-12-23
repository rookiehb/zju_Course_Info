/*
 * 	该文件为风格一
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
// 函数声明

void Initial_Style();
int drawtext(double x0, double y0, char *p, int layer, int connection);
void update_text(double x0, double y0, int i);


//=============================================================================
// 函数


/*
 * Function: Initial_Style
 * Usage: Initial_Style()
 * --------------------------------------------------------
 * 功能：
 *		初始化 结构一的sub_text 和 结构二的connection
 *		初始化 结构变量 form_pattern 和 to_pattern
 */
void Initial_Style()
{
	//因为要记录每个图案对应的text 因此sub_text的值不能为0 
	int i;
	for (i=0;i<50;i++)
		{
		rectangle[i].sub_text = -1;
		ellipse[i].sub_text = -1;
		circle[i].sub_text = -1;
		runway[i].sub_text = -1;
		text[i].connection = -1;
		}
	form_num = to_num=-1;
}

/*
 * Function: drawtext
 * Usage: drawtext(double x0, double y0, char *p, int layer, int connection)
 * --------------------------------------------------------
 * 功能：
 *		生成新的text，记录到结构体中 
 */
int drawtext(double x0,double y0,char *p,int layer,int connection)//生成新的text 
{
	text[text_num].x1=x0;
 	text[text_num].y1=y0;
 	text[text_num].x2=TextStringWidth(p)+x0;
	text[text_num].y2=y0+GetFontAscent();
 	strcpy(text[text_num].p,p);
 	text[text_num].layer = layer;
 	text[text_num].connection = connection;
	text_num++;
	int temp;
	temp = text_num-1;
	return temp;
}

/*
 * Function: update_text
 * Usage: update_text(double x0, double y0, int i)
 * --------------------------------------------------------
 * 功能：
 *		调整text的位置，移动text
 */
void update_text(double x0,double y0,int i)
{
	text[i].x1 = x0;
	text[i].y1 = y0;
	text[i].x2 = TextStringWidth(text[i].p)+x0;
	text[i].y2 = y0 + GetFontAscent();
}
