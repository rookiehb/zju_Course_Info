/*
 * 	���ļ�Ϊ����
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
// ����

/*
 * Function: First_Style
 * Usage: First_Style()
 * --------------------------------------------------------
 * ���ܣ�
 *		�������������˸���
 */
void Second_Style()
{	
	style_two=1;
	startTimer(TIMER_BLINK1000,1000);//�����˸ 
}

/*
 * Function: generate_layer
 * Usage: generate_layer()
 * --------------------------------------------------------
 * ���ܣ�
 *		���ɷ����еĲ㼶
 */
void generate_layer() //directionΪ1ʱ��ʾ��zou Ϊ-1ʱ��ʾ���� 
{
	if ( topic == 1 )
		generate_bunch(1);
	else if ( topic==2 )
		generate_bunch(-1);
	else if ( topic == 3 )
		{
		generate_bunch(1);
		move_bunches("odd");//�����ɵ�����֧ʱ ��Ҫ����һ��֧������ �����ƶ� ��������֧�����������ƶ� 
		}
	else if ( topic == 4 )
		{
		generate_bunch(-1);
		move_bunches("even");//���ڶ���֧������ �����ƶ� �����ķ�֧�����������ƶ� 
		}
}

/*
 * Function: generate_bunch
 * Usage: generate_bunch(int direction)
 * --------------------------------------------------------
 * ���ܣ�
 *		���ɵ�һ����ڶ���ķ�֧
 */
void generate_bunch(int direction)
{	
	double gap = TextStringWidth(text[0].p)-TextStringWidth("���ı���");//��̬�ı�ڶ����ķ�֧����ʼλ�� 
	if (direction==1)
		gap=0;//������ ������ı�λ�� 
		
	drawline(4.8+gap-1.8*direction,4.05,4.8+gap-0.5*direction,4.05,topic,topic);
	if (layer_number[0] == 1) //ֻ��һ����֧ 
			{
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,4.2,topic,topic*10+1);
			drawline(4.8+gap-2.1*direction,4.2,4.8+gap-3.1*direction,4.2,topic,topic*10+1);
			generate_sub_bunch(4.8+gap-3.1*direction,4.2,layer_number[1],direction,topic*10+1);
			}
		else if ( layer_number[0]==2 )//������֧����� 
			{
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,4.6,topic,topic*10+1);
			drawline(4.8+gap-2.1*direction,4.6,4.8+gap-3.1*direction,4.6,topic,topic*10+1);
			generate_sub_bunch(4.8+gap-3.1*direction,4.6,layer_number[1],direction,topic*10+1);
			
			drawellcurve(4.8+gap-1.8*direction,4.05,4.8+gap-2.1*direction,3.5,topic,topic*10+2);
			drawline(4.8+gap-2.1*direction,3.5,4.8+gap-3.1*direction,3.5, topic,topic*10+2);
			generate_sub_bunch(4.8+gap-3.1*direction,3.5,layer_number[2],direction,topic*10+2);
			}
		else if (layer_number[0]==3)//������֧����� 
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
 * ���ܣ�
 *		 ���ɷ�֧���Ӵ������������֧ 
 */
void generate_sub_bunch(double x,double y,int layer_num,int direction,int layer) 
{		
		//��֧���Ӵ�
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
 * ���ܣ�
 *		 �ƶ���֧����̬�������������ص���֧��λ�� 
 */
void move_bunches(char *p)//�ƶ���֧���� 
{
	double gap = TextStringWidth(text[0].p)-TextStringWidth("���ı���");
	int i;int flag=1;
	if ( strcmp(p,"odd")==0 )
		{
		
		for (i=0; line[i].x1 > 0 ;i++)
			{
			if (line[i].belonging == 1)//��һ��֧�����ƶ� 
				{
				line[i].y2 += 1.7;
				line[i].y1 += 1.7;
				line[i].scope_y += 1.7;
				}
			else if (line[i].belonging == 3)//������֧�����ƶ� 
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
			if (line[i].belonging == 2)//�ڶ���֧�����ƶ� 
				{
				line[i].y2 += 1.7;
				line[i].y1 += 1.7;
				line[i].scope_y += 1.7;
				}
			else if (line[i].belonging == 4)//���ķ�֧�����ƶ� 
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
 * ���ܣ�
 *		 ����������ı��򳤶ȣ���̬���������֧��λ�� 
 */
void remove_graph(char *temptext,int ii)
{	
	int j;double change_x=0;
	if ( line[ii].x2 < 4.32 )
		{
		if (line[ii].x2<line[ii].x1)
			{
			change_x = line[ii].x1 - line[ii].x2 - TextStringWidth(temptext)-0.2;//��Ҫ�ƶ�x�ľ��� 
			line[ii].x2 = line[ii].x1 - TextStringWidth(temptext)-0.2;
			}
		else
			{
			change_x = line[ii].x2 - line[ii].x1 - TextStringWidth(temptext)-0.2;
			line[ii].x1 = line[ii].x2 - TextStringWidth(temptext)-0.2;
			}
			
		if (( line[ii].layer>10 && line[ii].layer<15 ) || ( line[ii].layer>30 && line[ii].layer<35 ))//��Ϊ�ڶ��㼶�������ڸõڶ��㼶�ĵ����㼶��֧�����ƶ� 
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
		else if (line[ii].layer==1 || line[ii].layer==3)//��Ϊ��һ�㼶 �����ڸò㼶���Ӳ㼶ȫ�������ƶ� 
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
		
		if ( (line[ii].layer>20 && line[ii].layer<25) || (line[ii].layer>40 && line[ii].layer<45) )//��Ϊ�ڶ��㼶 
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
 * ���ܣ�
 *		 ��¼���ṹ��,����������
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
 * ���ܣ�
 *		 ��¼���ṹ�壬����������
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
 * ���ܣ� 
 *		 ��¼���ṹ�壬����������
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

