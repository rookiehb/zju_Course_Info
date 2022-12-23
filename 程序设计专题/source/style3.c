/*
 * 	该文件为风格三
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
void Third_Style();
void drawrectangle(double x0, double y0, double length, double width, char p[30], int layer);
void form_subtopic();
void form_blanks();
void bunch_one(int direction, int layer);
void bunch_two(int direction, int layer);
void bunch_three(int direction, int layer);

//=============================================================================
// 函数

/*
 * Function: Third_Style
 * Usage: Third_Style()
 * --------------------------------------------------------
 * 功能：
 *		进入风格三，绘制中心的Topic和图形
 */
void Third_Style()
{	
	drawrectangle(4.2,4.0,1.4,0.8,"Topic",0);
}

/*
 * Function: drawrectangle
 * Usage: drawrectangle(double x0, double y0, double length, double width, char p[30], int layer)
 * --------------------------------------------------------
 * 功能：
 *		绘制标题和子项的长方形框，并记录进结构体
 */
void drawrectangle(double x0,double y0,double length,double width,char p[30],int layer)
{
	rectangle[rec_num].x1=x0;
	rectangle[rec_num].y1=y0;
	rectangle[rec_num].x2=x0+length;
	rectangle[rec_num].y2=y0+width;
	strcpy(rectangle[rec_num].p,p);
	rectangle[rec_num].layer = layer;
	rec_num++;
}

/*
 * Function: form_subtopic
 * Usage: form_subtopic()
 * --------------------------------------------------------
 * 功能：
 *		生成六个一级标题
 */
void form_subtopic()
{
	sub_topic++;
	if (sub_topic==1)//左中 
		{
		drawline(4.2,4.4, 3.6 ,4.4,1,-1);
		drawrectangle(2.4,4.1,1.2,0.6,"sub topic1",1);
		}
	else if (sub_topic==2)//右中 
		{
		drawline(5.6,4.4, 6.2 ,4.4,2,-1);
		drawrectangle(6.2,4.1,1.2,0.6,"sub topic2",2);
		}
	else if (sub_topic==3)//左上 
		{
		drawline(4.0,4.4,4.0,6.8,3,-1);
		drawline(4.0,6.8,3.6,6.8,3,-1);
		drawrectangle(2.4,6.5,1.2,0.6,"sub topic3",3);
		}
	else if (sub_topic==4)//右上 
		{
		drawline(5.8,4.4,5.8,6.8,4,-1);
		drawline(5.8,6.8,6.2,6.8,4,-1);
		drawrectangle(6.2,6.5,1.2,0.6,"sub topic4",4);
		}
	else if (sub_topic==5)//左下 
		{
		drawline(4.0,4.4,4.0,2.0,5,-1);
		drawline(4.0,2.0,3.6,2.0,5,-1);
		drawrectangle(2.4,1.7,1.2,0.6,"sub topic5",5);
		}
	else if (sub_topic==6)//右下 
		{
		drawline(5.8,4.4,5.8,2.0,6,-1);
		drawline(5.8,2.0,6.2,2.0,6,-1);
		drawrectangle(6.2,1.7,1.2,0.6,"sub topic6",6);
		}
}



/*
 * Function: form_blanks
 * Usage: form_blanks()
 * --------------------------------------------------------
 * 功能：
 *		继续生成子标题的接口 
 */
void form_blanks()
{	
	blank[rectangle[to_form].layer]++;
	if ( to_form>=0 )
		if ( rectangle[to_form].layer%2==1 && blank[rectangle[to_form].layer]==1 )
			bunch_one(1,rectangle[to_form].layer);
		else if ( rectangle[to_form].layer%2==1 && blank[rectangle[to_form].layer]==2 )
			bunch_two(1,rectangle[to_form].layer);
		else if ( rectangle[to_form].layer%2==1 && blank[rectangle[to_form].layer]==3 )
			bunch_three(1,rectangle[to_form].layer);
		else if ( rectangle[to_form].layer%2==0 && blank[rectangle[to_form].layer]==1 )
			bunch_one(-1,rectangle[to_form].layer);
		else if ( rectangle[to_form].layer%2==0 && blank[rectangle[to_form].layer]==2 )
			bunch_two(-1,rectangle[to_form].layer);
		else if ( rectangle[to_form].layer%2==0 && blank[rectangle[to_form].layer]==3 )
			bunch_three(-1,rectangle[to_form].layer);
	to_form=-1;
}

/*
 * Function: bunch_one
 * Usage: bunch_one(int direction, int layer)
 * --------------------------------------------------------
 * 功能：
 *		生成一级标题的第一个子标题
 */
void bunch_one(int direction,int layer)
{	
	//一层中心点(4.9,4.4)  延伸点(2.4,4.4)  矩形大小为(1.0,0.5)  线长度0.6
	//不同的layer y值不同 因此要判断 
	if (layer==1 || layer==2)
		{
		drawline(4.9-2.5*direction,4.4,4.9-3.1*direction,4.4,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,4.15,1.0,0.5,"blank1",layer*10+1);
		else
			drawrectangle(4.9-3.1*direction,4.15,1.0,0.5,"blank1",layer*10+1);
		}
	else if (layer==5 || layer==6)
		{
		drawline(4.9-2.5*direction,2.0,4.9-3.1*direction,2.0,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,1.75,1.0,0.5,"blank1",layer*10+1);
		else
			drawrectangle(4.9-3.1*direction,1.75,1.0,0.5,"blank1",layer*10+1);
		}
	else if (layer==3 || layer==4)
		{
		drawline(4.9-2.5*direction,6.8,4.9-3.1*direction,6.8,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,6.55,1.0,0.5,"blank1",layer*10+1);
		else
			drawrectangle(4.9-3.1*direction,6.55,1.0,0.5,"blank1",layer*10+1);
		}
}

/*
 * Function: bunch_two
 * Usage: bunch_two(int direction, int layer)
 * --------------------------------------------------------
 * 功能:
 *		生成一级标题的第二个子标题
 */
void bunch_two(int direction,int layer)
{
	if (layer==1 || layer==2)
		{
		drawline(4.9-2.7*direction,4.4,4.9-2.7*direction,3.7,layer,-1 );
		drawline(4.9-2.7*direction,3.7,4.9-3.1*direction,3.7,layer,-1);
		if (direction==1)
			drawrectangle(4.9-4.1*direction,4.15-0.7,1.0,0.5,"blank2",layer*10+2);
		else
			drawrectangle(4.9-3.1*direction,4.15-0.7,1.0,0.5,"blank2",layer*10+2);
		}
	else if (layer==5 || layer==6)
		{
		drawline(4.9-2.7*direction,2.0,4.9-2.7*direction,1.3,layer,-1 );
		drawline(4.9-2.7*direction,1.3,4.9-3.1*direction,1.3,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,1.75-0.7,1.0,0.5,"blank2",layer*10+2);
		else
			drawrectangle(4.9-3.1*direction,1.75-0.7,1.0,0.5,"blank2",layer*10+2);
		}
	else if (layer==3 || layer==4)
		{
		drawline(4.9-2.7*direction,6.8,4.9-2.7*direction,6.1,layer,-1 );
		drawline(4.9-2.7*direction,6.1,4.9-3.1*direction,6.1,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,6.55-0.7,1.0,0.5,"blank2",layer*10+2);
		else
			drawrectangle(4.9-3.1*direction,6.55-0.7,1.0,0.5,"blank2",layer*10+2);
		}
}

/*
 * Function: bunch_three
 * Usage: bunch_three(int direction, int layer)
 * --------------------------------------------------------
 * 功能：
 *		生成一级标题的第三个子标题
 */
void bunch_three(int direction,int layer)
{
	if (layer==1 || layer==2)
		{
		drawline(4.9-2.7*direction,3.7,4.9-2.7*direction,3.0,layer,-1 );
		drawline(4.9-2.7*direction,3.0,4.9-3.1*direction,3.0,layer,-1);
		if (direction==1)
			drawrectangle(4.9-4.1*direction,4.15-0.7*2,1.0,0.5,"blank3",layer*10+3);
		else
			drawrectangle(4.9-3.1*direction,4.15-0.7*2,1.0,0.5,"blank3",layer*10+3);
		}
	else if (layer==5 || layer==6)
		{
		drawline(4.9-2.7*direction,1.3,4.9-2.7*direction,0.6,layer,-1 );
		drawline(4.9-2.7*direction,0.6,4.9-3.1*direction,0.6,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,1.75-0.7*2,1.0,0.5,"blank3",layer*10+3);
		else
			drawrectangle(4.9-3.1*direction,1.75-0.7*2,1.0,0.5,"blank3",layer*10+3);
		}
	else if (layer==3 || layer==4)
		{
		drawline(4.9-2.7*direction,6.1,4.9-2.7*direction,5.4,layer,-1 );
		drawline(4.9-2.7*direction,5.4,4.9-3.1*direction,5.4,layer,-1 );
		if (direction==1)
			drawrectangle(4.9-4.1*direction,6.55-0.7*2,1.0,0.5,"blank3",layer*10+3);
		else
			drawrectangle(4.9-3.1*direction,6.55-0.7*2,1.0,0.5,"blank3",layer*10+3);
		}
}



