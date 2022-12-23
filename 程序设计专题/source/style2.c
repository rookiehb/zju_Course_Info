/*
 * 	该文件为风格二
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

void Second_Style();
void generate_layer();
void generate_bunch(int direction);
void generate_sub_bunch(double x, double y, int layer_num, int direction, int layer);
void move_bunches(char *p);
void remove_graph(char *temptext, int ii);
void drawellcurve(double x0, double y0, double x1, double y1, int belonging, int layer);
void drawline(double x0, double y0, double x1, double y1, int belonging, int layer);
void drawcircurve(double x0, double y0, double x1, double y1, int belonging);


//=============================================================================
// 函数

/*
 * Function: First_Style
 * Usage: First_Style()
 * --------------------------------------------------------
 * 功能：
 *		进入风格二，并闪烁光标
 */
void Second_Style()
{	
	style_two=1;
	startTimer(TIMER_BLINK1000,1000);//光标闪烁 
}

/*
 * Function: generate_layer
 * Usage: generate_layer()
 * --------------------------------------------------------
 * 功能：
 *		生成风格二中的层级
 */
void generate_layer() //direction为1时表示向zou 为-1时表示向右 
{
	if ( topic == 1 )
		generate_bunch(1);
	else if ( topic==2 )
		generate_bunch(-1);
	else if ( topic == 3 )
		{
		generate_bunch(1);
		move_bunches("odd");//在生成第三分支时 需要将第一分支的线条 向上移动 ，第三分支的线条向下移动 
		}
	else if ( topic == 4 )
		{
		generate_bunch(-1);
		move_bunches("even");//将第二分支的线条 向上移动 ，第四分支的线条向下移动 
		}
}

/*
 * Function: generate_bunch
 * Usage: generate_bunch(int direction)
 * --------------------------------------------------------
 * 功能：
 *		生成第一层与第二层的分支
 */
void generate_bunch(int direction)
{	
	double gap = TextStringWidth(text[0].p)-TextStringWidth("中心标题");//动态改变第二、四分支的起始位置 
	if (direction==1)
		gap=0;//若向左 则无需改变位置 
		
	drawline(4.8+gap-1.8*direction,4.05,4.8+gap-0.5*direction,4.05,topic,topic);
	if (layer_number[0] == 1) //只有一个分支 
			{
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,4.2,topic,topic*10+1);
			drawline(4.8+gap-2.1*direction,4.2,4.8+gap-3.1*direction,4.2,topic,topic*10+1);
			generate_sub_bunch(4.8+gap-3.1*direction,4.2,layer_number[1],direction,topic*10+1);
			}
		else if ( layer_number[0]==2 )//两个分支的情况 
			{
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,4.6,topic,topic*10+1);
			drawline(4.8+gap-2.1*direction,4.6,4.8+gap-3.1*direction,4.6,topic,topic*10+1);
			generate_sub_bunch(4.8+gap-3.1*direction,4.6,layer_number[1],direction,topic*10+1);
			
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,3.5,topic,topic*10+2);
			drawline(4.8+gap-2.1*direction,3.5,4.8+gap-3.1*direction,3.5, topic,topic*10+2);
			generate_sub_bunch(4.8+gap-3.1*direction,3.5,layer_number[2],direction,topic*10+2);
			}
		else if (layer_number[0]==3)//三个分支的情况 
			{	
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,5.2, topic,topic*10+1);
			drawline(4.8+gap-2.1*direction,5.2,4.8+gap-3.1*direction,5.2, topic,topic*10+1);
			generate_sub_bunch(4.8+gap-3.1*direction,5.2,layer_number[1],direction,topic*10+1);
			
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,4.05, topic,topic*10+2);
			drawline(4.8+gap-2.1*direction,4.05,4.8+gap-3.1*direction,4.05, topic,topic*10+2);
			generate_sub_bunch(4.8+gap-3.1*direction,4.05,layer_number[2],direction,topic*10+2);
			
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,2.9, topic,topic*10+3);
			drawline(4.8+gap-2.1*direction,2.9,4.8+gap-3.1*direction,2.9, topic,topic*10+3);
			generate_sub_bunch(4.8+gap-3.1*direction,2.9,layer_number[3],direction,topic*10+3);
			}
}

/*
 * Function: generate_sub_bunch
 * Usage: generate_sub_bunch(double x, double y, int layer_num, int direction, int layer)
 * --------------------------------------------------------
 * 功能：
 *		 生成分支的子串，即第三层分支 
 */
void generate_sub_bunch(double x,double y,int layer_num,int direction,int layer) 
{		
		//分支的子串
		if (layer==0)
			;
		else if (layer_num==1)
			{
			drawellcurve(x,y,x-0.3*direction,y+0.3,topic,layer*10+1);
			drawline(x-0.3*direction,y+0.3,x-1.3*direction,y+0.3,topic,layer*10+1);
			}
		else if ( layer_num==2 )
			{
			drawellcurve(x,y,x-0.3*direction,y+0.25,topic,layer*10+1);
			drawline(x-0.3*direction,y+0.25,x-1.5*direction,y+0.25,topic,layer*10+1);
			
			drawellcurve(x,y,x-0.3*direction,y-0.25,topic,layer*10+2);
			drawline(x-0.3*direction,y-0.25,x-1.5*direction,y-0.25,topic,layer*10+2);
			}
		else if (layer_num==3 )
			{
			drawellcurve(x,y,x-0.3*direction,y+0.4,topic,layer*10+1);
			drawline(x-0.3*direction,y+0.4,x-1.5*direction,y+0.4,topic,layer*10+1);
			
			drawellcurve(x,y,x-0.3*direction,y,topic,layer*10+2);
			drawline(x-0.3*direction,y,x-1.5*direction,y,topic,layer*10+2);
			
			drawellcurve(x,y,x-0.3*direction,y-0.4,topic,layer*10+3);
			drawline(x-0.3*direction,y-0.4,x-1.5*direction,y-0.4,topic,layer*10+3);
			}
			
}


/*
 * Function: move_bunches
 * Usage: move_bunches(char *p)
 * --------------------------------------------------------
 * 功能：
 *		 移动分支，动态调整各个可能重叠分支的位置 
 */
void move_bunches(char *p)//移动分支功能 
{
	double gap = TextStringWidth(text[0].p)-TextStringWidth("中心标题");
	int i;int flag=1;
	if ( strcmp(p,"odd")==0 )
		{
		
		for (i=0; line[i].x1 > 0 ;i++)
			{
			if (line[i].belonging == 1)//第一分支向上移动 
				{
				line[i].y2 += 1.7;
				line[i].y1 += 1.7;
				line[i].scope_y += 1.7;
				}
			else if (line[i].belonging == 3)//第三分支向下移动 
				{
				line[i].y1 -= 2.0;
				line[i].y2 -= 2.0;
				line[i].scope_y -= 2.0 ;
			 	}
			}
		for (i=0;ell_curve[i].x1 > 0;i++)
			{
			if (ell_curve[i].belonging ==1 )
				{
				ell_curve[i].y1 += 1.7;
				ell_curve[i].y2 += 1.7;
				}
			else if (ell_curve[i].belonging==3)
				{
				ell_curve[i].y1 -= 2.0;
				ell_curve[i].y2 -= 2.0;
				}		
			}
		for (i=0;text[i].x1>0;i++)
			{
			if (text[i].layer/10==1 || text[i].layer/100==1 || text[i].layer==1)
				{
				text[i].y1 +=1.7;
				text[i].y2 +=1.7;
				}
			else if (text[i].layer/10==3 || text[i].layer/100==3 || text[i].layer==3)
				{
				text[i].y1 +=1.7;
				text[i].y2 +=1.7;
				}
			}
		drawcircurve(text[0].x1+0.1,4.3,4.3,5.75,1);
		drawcircurve(text[0].x1+0.1,3.8,4.3,2.05,3);
		
		}
	else
		{
		for (i=0; line[i].x1 > 0 ;i++)
			{
			if (line[i].belonging == 2)//第二分支向上移动 
				{
				line[i].y2 += 1.7;
				line[i].y1 += 1.7;
				line[i].scope_y += 1.7;
				}
			else if (line[i].belonging == 4)//第四分支向下移动 
				{
				line[i].y1 -=2.0;
				line[i].y2 -=2.0;
				line[i].scope_y -=2.0;
				}
			}
	
		for (i=0;ell_curve[i].x1 > 0;i++)
			{
			if (ell_curve[i].belonging ==2 )
				{
				ell_curve[i].y1 += 1.7;
				ell_curve[i].y2 += 1.7;
				}
			else if (ell_curve[i].belonging==4)
				{
				ell_curve[i].y1 -= 2.0;
				ell_curve[i].y2 -= 2.0;
				}
			}
		for (i=0;text[i].x1>0;i++)
			{
			if (text[i].layer/10==2 || text[i].layer/100==2 || text[i].layer==2)
				{
				text[i].y1 +=1.7;
				text[i].y2 +=1.7;
				}
			else if (text[i].layer/10==4 || text[i].layer/100==4 || text[i].layer==4)
				{
				text[i].y1 +=1.7;
				text[i].y2 +=1.7;
				}
			}	
		drawcircurve(text[0].x2-0.1,4.3,5.3+gap,5.75,2);
		drawcircurve(text[0].x2-0.1,3.8,5.3+gap,2.05,4);
		}

}

/*
 * Function:remove_graph
 * Usage: remove_graph(char *temptext,int ii)
 * --------------------------------------------------------
 * 功能：
 *		 根据输入的文本框长度，动态调整整体分支的位置 
 */
void remove_graph(char *temptext,int ii)
{	
	int j;double change_x=0;
	if ( line[ii].x2 < 4.32 )
		{
		if (line[ii].x2<line[ii].x1)
			{
			change_x = line[ii].x1 - line[ii].x2 - TextStringWidth(temptext)-0.2;//需要移动x的距离 
			line[ii].x2 = line[ii].x1 - TextStringWidth(temptext)-0.2;
			}
		else
			{
			change_x = line[ii].x2 - line[ii].x1 - TextStringWidth(temptext)-0.2;
			line[ii].x1 = line[ii].x2 - TextStringWidth(temptext)-0.2;
			}
			
		if (( line[ii].layer>10 && line[ii].layer<15 ) || ( line[ii].layer>30 && line[ii].layer<35 ))//若为第二层级，则属于该第二层级的第三层级分支进行移动 
			{
			for (j=0;line[j].x1>0;j++)
				if ( line[j].layer>line[ii].layer*10 && line[j].layer<line[ii].layer*10+5 )
					{
					line[j].x1 += change_x;
					line[j].x2 += change_x;
					}
			
			for (j=0;ell_curve[j].x1>0;j++)
				if (ell_curve[j].layer>line[ii].layer*10 && ell_curve[j].layer<line[ii].layer*10+5)
					{
					
					ell_curve[j].x1 += change_x;
					ell_curve[j].x2 += change_x;
					}
			for (j=0;text[j].x1>0;j++)
				if (text[j].layer>line[ii].layer*10 && text[j].layer<line[ii].layer*10+5)
					{
					text[j].x1 += change_x;
					text[j].x2 += change_x;
					}
			}
		else if (line[ii].layer==1 || line[ii].layer==3)//若为第一层级 则将属于该层级的子层级全部进行移动 
			{
			for (j=0;line[j].x1>0;j++)
				if (( line[j].layer >line[ii].layer*10 && line[j].layer<line[ii].layer*10+5 ) ||( line[j].layer >line[ii].layer*100 && line[j].layer<line[ii].layer*100+50 ))
					{
					line[j].x1 +=change_x;
					line[j].x2 +=change_x;
					}
			for (j=0;ell_curve[j].x1>0;j++)
				if (( ell_curve[j].layer >line[ii].layer*10 && ell_curve[j].layer<line[ii].layer*10+5 ) ||( ell_curve[j].layer >line[ii].layer*100 && ell_curve[j].layer<line[ii].layer*100+50 ))
					{
					ell_curve[j].x1 += change_x;
					ell_curve[j].x2 += change_x;
					}
			for (j=0;text[j].x1>0;j++)
				if (( text[j].layer >line[ii].layer*10 && text[j].layer<line[ii].layer*10+5 ) ||( text[j].layer >line[ii].layer*100 && text[j].layer<line[ii].layer*100+50 ))
					{
					text[j].x1 += change_x;
					text[j].x2 += change_x;
					}
			}
		}
	else 
		{
		if (line[ii].x2-line[ii].x1 < 0)
			{
			change_x = line[ii].x1 - line[ii].x2 - TextStringWidth(temptext)-0.2;
			line[ii].x1 = line[ii].x2 + TextStringWidth(temptext)+0.2;
			}
		else
			{
			change_x = line[ii].x2 - line[ii].x1 - TextStringWidth(temptext) - 0.2;	
			line[ii].x2 = line[ii].x1 + TextStringWidth(temptext) + 0.2;
			}
		
		if ( (line[ii].layer>20 && line[ii].layer<25) || (line[ii].layer>40 && line[ii].layer<45) )//若为第二层级 
			{
			for (j=0;line[j].x1>0;j++)
				if ( line[j].layer> line[ii].layer*10 && line[j].layer< line[ii].layer*10+5 )
					{	
					line[j].x1 -= change_x;
					line[j].x2 -= change_x;	
					}
			for (j=0;ell_curve[j].x1>0;j++)
				if (ell_curve[j].layer>line[ii].layer*10 && ell_curve[j].layer<line[ii].layer*10+5)
					{
					ell_curve[j].x1 -= change_x;
					ell_curve[j].x2 -= change_x;
					}
			for (j=0;text[j].x1>0;j++)
				if (text[j].layer>line[ii].layer*10 && text[j].layer<line[ii].layer*10+5)
					{
					text[j].x1 -= change_x;
					text[j].x2 -= change_x;
					}
			}
		else if (line[ii].layer==2 || line[ii].layer==4 )
			{
			for (j=0;line[j].x1>0;j++)
				if (( line[j].layer >line[ii].layer*10 && line[j].layer<line[ii].layer*10+5 ) ||( line[j].layer >line[ii].layer*100 && line[j].layer<line[ii].layer*100+50 ))
					{
					line[j].x1 -=change_x;
					line[j].x2 -=change_x;
					}
			for (j=0;ell_curve[j].x1>0;j++)
				if (( ell_curve[j].layer >line[ii].layer*10 && ell_curve[j].layer<line[ii].layer*10+5 ) ||( ell_curve[j].layer >line[ii].layer*100 && ell_curve[j].layer<line[ii].layer*100+50 ))
					{
					ell_curve[j].x1 -= change_x;
					ell_curve[j].x2 -= change_x;
					}
			for (j=0;text[j].x1>0;j++)
				if (( text[j].layer >line[ii].layer*10 && text[j].layer<line[ii].layer*10+5 ) ||( text[j].layer >line[ii].layer*100 && text[j].layer<line[ii].layer*100+50 ))
					{
					text[j].x1 -= change_x;
					text[j].x2 -= change_x;
					}
			}
		}
}


/*
 * Function: drawellcurve
 * Usage: drawellcurve(double x0, double y0, double x1, double y1, int belonging, int layer)
 * --------------------------------------------------------
 * 功能：
 *		 记录到结构体,绘制连接线
 */
void drawellcurve(double x0,double y0,double x1,double y1,int belonging,int layer)
{
	ell_curve[ell_cur_num].x1 = x0;
	ell_curve[ell_cur_num].x2 = x1;
	ell_curve[ell_cur_num].y1 = y0;
	ell_curve[ell_cur_num].y2 = y1;
	ell_curve[ell_cur_num].belonging = belonging;
	strcpy(ell_curve[ell_cur_num].color,"Dark gray");
	ell_curve[ell_cur_num].layer = layer;
	ell_cur_num++;
}

/*
 * Function: drawline
 * Usage: drawline(double x0, double y0, double x1, double y1, int belonging, int layer)
 * --------------------------------------------------------
 * 功能：
 *		 记录到结构体，绘制连接线
 */
void drawline(double x0,double y0,double x1,double y1,int belonging,int layer)
{
	line[line_num].x1 = x0;
	line[line_num].x2 = x1;
	line[line_num].y1 = y0;
	line[line_num].y2 = y1;
	line[line_num].belonging = belonging;
	line[line_num].layer = layer;
	line[line_num].scope_y = y0 + 0.2;
	strcpy(line[line_num].color,"Dark gray");
	line_num++;
}


/*
 * Function: drawcircurve
 * Usage: drawcircurve(double x0, double y0, double x1, double y1, int belonging)
 * --------------------------------------------------------
 * 功能： 
 *		 记录到结构体，绘制连接线
 */
void drawcircurve(double x0,double y0,double x1,double y1,int belonging)
{
	cir_curve[cir_cur_num].x1 = x0;
	cir_curve[cir_cur_num].y1 = y0;
	cir_curve[cir_cur_num].x2 = x1;
	cir_curve[cir_cur_num].y2 = y1;
	cir_curve[cir_cur_num].belonging = belonging;
	strcpy(cir_curve[cir_cur_num].color,"Dark gray");
	cir_cur_num++;
}

