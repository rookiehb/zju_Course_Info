/*
 * 	该文件为回调函数的定义
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
void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

//=============================================================================
// 变量声明
static bool isDisplay = FALSE;		//编辑模式下光标显示标志
static double textmx, textmy;		//确定文本框生成的位置 
static int ii;		//传递当前的text
static int jj;		//传递当前编辑的text

//=============================================================================
// 函数定义 

//判断鼠标点击位置是否在区域内部 
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2)
{
	return (x0 >= x1 && x0 <= x2 && y0 >= y1 && y0 <= y2);
}



/*
 * Function: KeyboardEventProcess
 * Usage: KeyboardEventProcess(int key, int event)
 * --------------------------------------------------------
 * 功能： 
 *		键盘消息回调函数
 */
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	display();

	switch (event) {
	case KEY_DOWN:
		switch (key) {
		case VK_ESCAPE://若为ESC键则直接退出程序 
			exit(0);
			break;
		default:
			break;
		}
	case KEY_UP:
		break;
	}
}

/*
 * Function: CharEventProcess
 * Usage: CharEventProcess(char c)
 * --------------------------------------------------------
 * 功能： 
 *		输入字符的回调函数 
 */
void CharEventProcess(char c)
{
	uiGetChar(c); // GUI字符输入
	display(); //字符消息回调函数

	static char temptext[200]; //输入的字符串缓冲区
	static int textlen = 0;//输入的字符串长度
	static double x0, y0;

	if (style_choice == 1 && can_connect == 1) //第一风格中 连接图案功能 
		if (c == '\r')//此为enter键标志 
		{
			connect_pattern(head);
			delet(head);
			head = creat();
			form_num = to_num = -1;
			strcpy(form_pattern,"");
			strcpy(to_pattern,"");
		}

	// 文本修改
	if (selectable[1][jj] == 1)
	{
		strcpy(temptext, text[jj].p);
		textlen = strlen(temptext);
		if (c == '\r')
		{
			if (style_choice == 2)
			{
				remove_graph(temptext, text[jj].connection); //同步修改各个线条的长度 
				if (topic == 3 || topic == 1)
					text[jj].x1 = text[jj].x2 - TextStringWidth(temptext);
				else if (topic == 2 || topic == 4)
					text[jj].x2 = text[jj].x1 + TextStringWidth(temptext);
			}
			else if (style_choice == 1) //同步修改connection对应图案的字符串值，形成联动 
			{
				if (strcmp(text[jj].belonging, "rectangle") == 0)
					strcpy(rectangle[text[jj].connection].p, temptext);
				else if (strcmp(text[jj].belonging, "ellipse") == 0)
					strcpy(ellipse[text[jj].connection].p, temptext);
				else if (strcmp(text[jj].belonging, "circle") == 0)
					strcpy(circle[text[jj].connection].p, temptext);
				else if (strcmp(text[jj].belonging, "runway") == 0)
					strcpy(runway[text[jj].connection].p, temptext);
			}
			else if (style_choice == 3) //同步修改connection对应图案的字符串值，形成联动 
				if (strcmp(text[jj].belonging, "rectangle") == 0)
					strcpy(rectangle[text[jj].connection].p, temptext);
						
			textlen = 0;
			selectable[1][jj] = 0;
			cancelTimer(TIMER_BLINK250);
			imper_p = NULL;
		}
		else if (c == '\b')//撤销键 
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
			strcpy(text[jj].p, temptext);
		}
		else//其余任意字符 
		{
			temptext[textlen++] = c;
			temptext[textlen] = '\0';
			imper_p = temptext;
			strcpy(text[jj].p, temptext);
		}
	}
	
	//风格二的输入方式 
	if (start_texting == 1)
	{
		imper_x = MIN(line[ii].x1, line[ii].x2) + 0.1;
		imper_y = line[ii].y1 + 0.1;

		if (c == '\r')
		{
			remove_graph(temptext, ii);
			x0 = MIN(line[ii].x1, line[ii].x2) + 0.1;
			y0 = line[ii].y1 + 0.1;
			drawtext(x0, y0, temptext, line[ii].layer, ii);
			textlen = 0;
			start_texting = 0;
			cancelTimer(TIMER_BLINK500);//500ms定时器关闭
			imper_p = NULL;
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}
	
	//风格二 用于输入中心标题 
	if (style_two == 1)
	{
		imper_x = 4.4;
		imper_y = 4.0;
		if (c == '\r')
		{
			drawtext(imper_x, imper_y, temptext, 0, -1);
			textlen = 0;
			cancelTimer(TIMER_BLINK1000);//1000ms定时器关闭
			style_two = 0;
			imper_p = NULL;
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;//将当前字符加入到整个字符缓冲区中
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}

	//风格一 单独输入文本框 自定义模式下的编辑文本框 
	if (drawable[6] == 1) 
	{
		if (c == '\r')
		{
			cancelTimer(TIMER_BLINK250);
			drawtext(textmx, textmy, temptext, text[text_num].layer, -1);
			textlen = 0;
			drawable[6] = 0;
			imper_p = NULL;
		}
		else if (c >= '0' && c <= '9')
		{
			text[text_num].layer = text[text_num].layer * 10 + c - '0';
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;/*将当前字符加入到整个字符缓冲区中*/
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}

	//风格一下的图案与文本框联动 
	if (sub_texting[1] == 1)
	{
		double x1 = rectangle[rec_num - 1].x1, x2 = rectangle[rec_num - 1].x2, y1 = rectangle[rec_num - 1].y1, y2 = rectangle[rec_num - 1].y2;
		if (imper_p != NULL)
			imper_x = x1 + (x2 - x1 - TextStringWidth(imper_p)) / 2;//更改光标闪烁的位置 

		if (c == '\r')//enter 
		{
			strcpy(rectangle[rec_num - 1].p, temptext);
			//一些清零 初始化操作 
			textlen = 0;
			sub_texting[1] = 0;
			imper_p = NULL;
			cancelTimer(TIMER_BLINK250);
		}
		else if (c >= '0' && c <= '9')
		{	
			//若输入为数字 则自动认为输入layer 
			rectangle[rec_num - 1].layer = rectangle[rec_num - 1].layer * 10 + c - '0';
		}
		else if (c == '\b')
		{	
			//清除键 
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}
	else if (sub_texting[2] == 1)
	{
		double x1 = ellipse[ell_num - 1].x1, x2 = ellipse[ell_num - 1].x2, y1 = ellipse[ell_num - 1].y1, y2 = ellipse[ell_num - 1].y2;
		if (imper_p != NULL)
			imper_x = x1 + (x2 - x1 - TextStringWidth(imper_p)) / 2;
		if (c == '\r')
		{
			strcpy(ellipse[ell_num - 1].p, temptext);
			textlen = 0;
			sub_texting[2] = 0;
			imper_p = NULL;
			cancelTimer(TIMER_BLINK250);
		}
		else if (c >= '0' && c <= '9')
		{
			ellipse[ell_num - 1].layer = ellipse[ell_num - 1].layer * 10 + c - '0';
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;/*将当前字符加入到整个字符缓冲区中*/
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}
	else if (sub_texting[3] == 1)
	{
		double x1 = circle[cir_num - 1].x1, y1 = circle[cir_num - 1].y1, x2 = circle[cir_num - 1].x2, y2 = circle[cir_num - 1].y2;
		if (imper_p != NULL)
			imper_x = x1 + (x2 - x1 - TextStringWidth(imper_p)) / 2;
		if (c == '\r')
		{
			strcpy(circle[cir_num - 1].p, temptext);
			textlen = 0;
			sub_texting[3] = 0;
			imper_p = NULL;
			cancelTimer(TIMER_BLINK250);
		}
		else if (c >= '0' && c <= '9')
		{
			circle[cir_num - 1].layer = circle[cir_num - 1].layer * 10 + c - '0';
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;/*将当前字符加入到整个字符缓冲区中*/
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}
	else if (sub_texting[5] == 1)
	{
		double x1 = runway[run_num - 1].x1, y1 = runway[run_num - 1].y1, x2 = runway[run_num - 1].x2, y2 = runway[run_num - 1].y2;
		if (imper_p != NULL)
			imper_x = x1 + (x2 - x1 - TextStringWidth(imper_p)) / 2;
		if (c == '\r')
		{
			strcpy(runway[run_num - 1].p, temptext);
			textlen = 0;
			sub_texting[5] = 0;
			imper_p = NULL;
			cancelTimer(TIMER_BLINK250);
		}
		else if (c >= '0' && c <= '9')
		{
			runway[run_num - 1].layer = runway[run_num - 1].layer * 10 + c - '0';
		}
		else if (c == '\b')
		{
			temptext[--textlen] = '\0';
			imper_p = temptext;
		}
		else
		{
			temptext[textlen++] = c;/*将当前字符加入到整个字符缓冲区中*/
			temptext[textlen] = '\0';
			imper_p = temptext;
		}
	}
}

/*
 * Function: MouseEventProcess
 * Usage: MouseEventProcess(int x, int y, int button, int event)
 * --------------------------------------------------------
 * 功能： 
 *		鼠标移动的回调函数 
 */
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);  //GUI获取鼠标
	display();

	static double omx = 0.0, omy = 0.0;
	double mx, my;
	int i, j, m, n, p;
	
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	
	switch (event) {
	case BUTTON_DOWN:
		if (button == RIGHT_BUTTON) //  右键功能    
		{	
			//风格一中CAD画图  自由编辑 
			if (drawable[1] == 1)
			{
				changeable[1] = 1;
				rectangle[rec_num].x1 = mx;
				rectangle[rec_num].y1 = my;
				drawable[1] = 0;
			}
			else if (drawable[2] == 1)
			{
				changeable[2] = 1;
				ellipse[ell_num].x1 = mx;
				ellipse[ell_num].y1 = my;
				drawable[2] = 0;
			}
			else if (drawable[3] == 1)
			{
				changeable[3] = 1;
				circle[cir_num].x1 = mx;
				circle[cir_num].y1 = my;
				drawable[3] = 0;
			}
			else if (drawable[4] == 1)
			{
				strcpy(line[line_num].color, "Seagreen");
				changeable[4] = 1;
				line[line_num].x1 = mx;
				line[line_num].y1 = my;
				drawable[4] = 0;
			}
			else if (drawable[5] == 1)
			{
				changeable[5] = 1;
				runway[run_num].x1 = mx;
				runway[run_num].y1 = my;
				drawable[5] = 0;
			}
			else if (drawable[6] == 1)
			{
				textmx = mx;
				textmy = my;
				imper_x = textmx;
				imper_y = textmy;
				startTimer(TIMER_BLINK250, 500);
			}
			else if (drawable[7] == 1)//两半的椭圆曲线
			{
				strcpy(ell_curve[ell_cur_num].color, "Seagreen");
				changeable[7] = 1;
				ell_curve[ell_cur_num].x1 = mx;
				ell_curve[ell_cur_num].y1 = my;
				drawable[7] = 0;
			}
			else if (drawable[8] == 1)//四分之一圆 
			{
				strcpy(cir_curve[cir_cur_num].color, "Seagreen");
				changeable[8] = 1;
				cir_curve[cir_cur_num].x1 = mx;
				cir_curve[cir_cur_num].y1 = my;
				drawable[8] = 0;
			}

			if (eliminate == 1) // 若开始清楚图案功能 则会清除图案 
				for (p = 0; p < 50; p++)
				{
					if (inBox(mx, my, MIN(text[p].x1, text[p].x2), MAX(text[p].x1, text[p].x2), MIN(text[p].y1, text[p].y2), MAX(text[p].y1, text[p].y2)))//文本框 
					{
						update_pattern(6, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(rectangle[p].x1, rectangle[p].x2), MAX(rectangle[p].x1, rectangle[p].x2), MIN(rectangle[p].y1, rectangle[p].y2), MAX(rectangle[p].y1, rectangle[p].y2)))
					{
						update_pattern(1, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(ellipse[p].x1, ellipse[p].x2), MAX(ellipse[p].x1, ellipse[p].x2), MIN(ellipse[p].y1, ellipse[p].y2), MAX(ellipse[p].y1, ellipse[p].y2)))
					{
						update_pattern(2, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, circle[p].x1, circle[p].x2, circle[p].y1, circle[p].y2))
					{
						update_pattern(3, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(line[p].x1, line[p].x2), MAX(line[p].x1, line[p].x2), MIN(line[p].y1, line[p].y2), MAX(line[p].y1, line[p].y2)))
					{
						update_pattern(4, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(runway[p].x1, runway[p].x2), MAX(runway[p].x1, runway[p].x2), MIN(runway[p].y1, runway[p].y2), MAX(runway[p].y1, runway[p].y2)))
					{
						update_pattern(5, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(ell_curve[p].x1, ell_curve[p].x2), MAX(ell_curve[p].x1, ell_curve[p].x2), MIN(ell_curve[p].y1, ell_curve[p].y2), MAX(ell_curve[p].y1, ell_curve[p].y2)))
					{
						update_pattern(7, p); eliminate = 0; break;
					}
					else if (inBox(mx, my, MIN(cir_curve[p].x1, cir_curve[p].x2), MAX(cir_curve[p].x1, cir_curve[p].x2), MIN(cir_curve[p].y1, cir_curve[p].y2), MAX(cir_curve[p].y1, cir_curve[p].y2)))
					{
						update_pattern(8, p); eliminate = 0; break;
					}
				}

			//风格二下的编辑文本功能 
			if (editable == 1)
				for (ii = 0; line[ii].x1 != 0; ii++)
					if (inBox(mx, my, MIN(line[ii].x1, line[ii].x2), MAX(line[ii].x1, line[ii].x2), MIN(line[ii].y1, line[ii].y2), line[ii].scope_y))
					{
						start_texting = 1;
						startTimer(TIMER_BLINK500, 500);
						break;
					}

			//风格一中的自动连线
			if (style_choice == 1 && can_connect == 1)
				for (p = 0; p < 50; p++)
				{
					LinkList *pp = head->next;
					if (inBox(mx, my, MIN(rectangle[p].x1, rectangle[p].x2), MAX(rectangle[p].x1, rectangle[p].x2), MIN(rectangle[p].y1, rectangle[p].y2), MAX(rectangle[p].y1, rectangle[p].y2)))
					{
						if (pp->x1 < 0.1)
						{
							form_num = p;//记录起始框 
							strcpy(form_pattern,"rectangle");
							change(head, 1, rectangle[p].x1, rectangle[p].x2, rectangle[p].y1, rectangle[p].y2);
						}
						else
						{
							to_num = p;//记录连接框
							strcpy(to_pattern,"rectangle");
							change(head, 2, rectangle[p].x1, rectangle[p].x2, rectangle[p].y1, rectangle[p].y2);
						}
						break;
					}
					else if (inBox(mx, my, MIN(ellipse[p].x1, ellipse[p].x2), MAX(ellipse[p].x1, ellipse[p].x2), MIN(ellipse[p].y1, ellipse[p].y2), MAX(ellipse[p].y1, ellipse[p].y2)))
					{
						if (pp->x1 < 0.1)
						{
							form_num = p;
							strcpy(form_pattern,"ellipse");
							change(head, 1, ellipse[p].x1, ellipse[p].x2, ellipse[p].y1, ellipse[p].y2);
						}
						else
						{
							to_num = p;
							strcpy(to_pattern,"ellipse");
							change(head, 2, ellipse[p].x1, ellipse[p].x2, ellipse[p].y1, ellipse[p].y2);
						}
						break;
					}
					else if (inBox(mx, my, circle[p].x1, circle[p].x2, circle[p].y1, circle[p].y2))
					{
						if (pp->x1 < 0.1)
						{
							form_num = p;
							strcpy(form_pattern,"circle");
							change(head, 1, circle[p].x1, circle[p].x2, circle[p].y1, circle[p].y2);
						}
						else
						{
							to_num = p;
							strcpy(to_pattern,"circle");
							change(head, 2, circle[p].x1, circle[p].x2, circle[p].y1, circle[p].y2);
						}
						break;
					}
					else if (inBox(mx, my, MIN(runway[p].x1, runway[p].x2), MAX(runway[p].x1, runway[p].x2), MIN(runway[p].y1, runway[p].y2), MAX(runway[p].y1, runway[p].y2)))
					{
						if (pp->x1 < 0.1)
						{
							form_num = p;
							strcpy(form_pattern,"runway");
							change(head, 1, runway[p].x1, runway[p].x2, runway[p].y1, runway[p].y2);
						}
						else
						{
							to_num = p;
							strcpy(to_pattern,"runway");
							change(head, 2, runway[p].x1, runway[p].x2, runway[p].y1, runway[p].y2);
						}
						break;
					}
				}
		}

		if (button == LEFT_BUTTON) //左键功能 
			{
			
			for (j = 0; text[j].x1 > 0; j++)//编辑文本框内容 
				if (inBox(mx, my, MIN(text[j].x1, text[j].x2), MAX(text[j].x1, text[j].x2), MIN(text[j].y1, text[j].y2), MAX(text[j].y1, text[j].y2)))//文本框 
				{
					selectable[1][j] = 1;
					jj = j;
					imper_x = text[jj].x1;
					imper_y = text[jj].y1;
					imper_p = text[jj].p;
					startTimer(TIMER_BLINK250, 500);
					break;
				}
			
			for (j = 0; rectangle[j].x1 > 0; j++)//用于风格三下 表示当前选择的矩形框 
				if (inBox(mx, my, MIN(rectangle[j].x1, rectangle[j].x2), MAX(rectangle[j].x1, rectangle[j].x2), MIN(rectangle[j].y1, rectangle[j].y2), MAX(rectangle[j].y1, rectangle[j].y2)))
				{
					to_form = j;
					break;
				}

			if (can_move == 1)//打开移动团功能后，拖动图案实现移动 
				for (j = 0; j < 50; j++)
				{
					if (inBox(mx, my, MIN(text[j].x1, text[j].x2), MAX(text[j].x1, text[j].x2), MIN(text[j].y1, text[j].y2), MAX(text[j].y1, text[j].y2)))//文本框 
					{	
						moveable[6][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(rectangle[j].x1, rectangle[j].x2), MAX(rectangle[j].x1, rectangle[j].x2), MIN(rectangle[j].y1, rectangle[j].y2), MAX(rectangle[j].y1, rectangle[j].y2)))
					{
						moveable[1][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(ellipse[j].x1, ellipse[j].x2), MAX(ellipse[j].x1, ellipse[j].x2), MIN(ellipse[j].y1, ellipse[j].y2), MAX(ellipse[j].y1, ellipse[j].y2)))
					{
						moveable[2][j] = 1;
						break;
					}
					else if (inBox(mx, my, circle[j].x1, circle[j].x2, circle[j].y1, circle[j].y2))
					{
						moveable[3][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(line[j].x1, line[j].x2), MAX(line[j].x1, line[j].x2), MIN(line[j].y1, line[j].y2), MAX(line[j].y1, line[j].y2)))
					{
						moveable[4][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(runway[j].x1, runway[j].x2), MAX(runway[j].x1, runway[j].x2), MIN(runway[j].y1, runway[j].y2), MAX(runway[j].y1, runway[j].y2)))
					{
						moveable[5][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(ell_curve[j].x1, ell_curve[j].x2), MAX(ell_curve[j].x1, ell_curve[j].x2), MIN(ell_curve[j].y1, ell_curve[j].y2), MAX(ell_curve[j].y1, ell_curve[j].y2)))
					{
						moveable[7][j] = 1;
						break;
					}
					else if (inBox(mx, my, MIN(cir_curve[j].x1, cir_curve[j].x2), MAX(cir_curve[j].x1, cir_curve[j].x2), MIN(cir_curve[j].y1, cir_curve[j].y2), MAX(cir_curve[j].y1, cir_curve[j].y2)))
					{
						moveable[8][j] = 1;
						break;
					}
				}
			omx = mx; omy = my;
			break;
			}
	
	case MOUSEMOVE://鼠标移动功能 
		if (changeable[1] == 1)//记录下移动的位置 ，完成生成图案 
			{
			rectangle[rec_num].x2 = mx;
			rectangle[rec_num].y2 = my;
			}
		else if (changeable[2] == 1)
			{
			ellipse[ell_num].x2 = mx;
			ellipse[ell_num].y2 = my;
			}
		else if (changeable[3] == 1)
			{
			circle[cir_num].y2 = my;
			circle[cir_num].x2 = circle[cir_num].x1 + my-circle[cir_num].y1;
			}
		else if (changeable[4] == 1)
			{
			line[line_num].x2 = mx;
			line[line_num].y2 = my;
			}
		else if (changeable[5] == 1)
			{
			runway[run_num].x2 = mx;
			runway[run_num].y2 = my;
			}
		else if (changeable[7] == 1)
			{
			ell_curve[ell_cur_num].x2 = mx;
			ell_curve[ell_cur_num].y2 = my;
			}
		else if (changeable[8] == 1)
			{
			cir_curve[cir_cur_num].x2 = mx;
			cir_curve[cir_cur_num].y2 = my;
			}

		if (can_move == 1 && flag_can_move == 0)
			for (i = 0; i < 50; i++)
				if (moveable[1][i] == 1)
				{
					rectangle[i].x1 += mx - omx;
					rectangle[i].y1 += my - omy;
					rectangle[i].x2 += mx - omx;
					rectangle[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[2][i] == 1)
				{
					ellipse[i].x1 += mx - omx;
					ellipse[i].y1 += my - omy;
					ellipse[i].x2 += mx - omx;
					ellipse[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[3][i] == 1)
				{
					circle[i].x1 += mx - omx;
					circle[i].x2 += mx - omx;
					circle[i].y1 += my - omy;
					circle[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[4][i] == 1)
				{
					line[i].x1 += mx - omx;
					line[i].x2 += mx - omx;
					line[i].y1 += my - omy;
					line[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[5][i] == 1)
				{
					runway[i].x1 += mx - omx;
					runway[i].x2 += mx - omx;
					runway[i].y1 += my - omy;
					runway[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[6][i] == 1)
				{
					text[i].x1 += mx - omx;
					text[i].x2 += mx - omx;
					text[i].y1 += my - omy;
					text[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[7][i] == 1)
				{
					ell_curve[i].x1 += mx - omx;
					ell_curve[i].x2 += mx - omx;
					ell_curve[i].y1 += my - omy;
					ell_curve[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
				else if (moveable[8][i] == 1)
				{
					cir_curve[i].x1 += mx - omx;
					cir_curve[i].x2 += mx - omx;
					cir_curve[i].y1 += my - omy;
					cir_curve[i].y2 += my - omy;
					omx = mx;
					omy = my;
				}
		break;
	
	case BUTTON_UP://鼠标松开 
		if (button == RIGHT_BUTTON)
			if (changeable[1] == 1)//矩形 图案不再自由变换 并将数据记录到结构体中 
			{
				changeable[1] = 0;
				sub_texting[1] = 1;
				rec_num++;
				
				//开始进入编辑文本模式 
				double x1 = rectangle[rec_num - 1].x1, x2 = rectangle[rec_num - 1].x2, y1 = rectangle[rec_num - 1].y1, y2 = rectangle[rec_num - 1].y2;
				imper_x = x1 + (x2 - x1) / 2;
				imper_y = y1 + (y2 - y1) / 2 - fa / 2;
				startTimer(TIMER_BLINK250, 500);
				flag_can_move = 0;
			}
			else if (changeable[2] == 1)//椭圆 
			{
				changeable[2] = 0;
				sub_texting[2] = 1;
				ell_num++;
				double x1 = ellipse[ell_num - 1].x1, x2 = ellipse[ell_num - 1].x2, y1 = ellipse[ell_num - 1].y1, y2 = ellipse[ell_num - 1].y2;
				imper_x = x1 + (x2 - x1) / 2;
				imper_y = y1 + (y2 - y1) / 2 - fa / 2;
				startTimer(TIMER_BLINK250, 500);
				flag_can_move = 0;
			}
			else if (changeable[3] == 1)//圆形 
			{
				changeable[3] = 0;
				sub_texting[3] = 1;
				cir_num++;
				double x1 = circle[cir_num - 1].x1, y1 = circle[cir_num - 1].y1, x2 = circle[cir_num - 1].x2, y2 = circle[cir_num - 1].y2;
				imper_x = x1 + (x2 - x1) / 2;
				imper_y = y1 + (y2 - y1) / 2 - fa / 2;
				startTimer(TIMER_BLINK250, 500);
				flag_can_move = 0;
			}
			else if (changeable[4] == 1)//线条 
			{
				changeable[4] = 0;
				line_num++;
				flag_can_move = 0;
			}
			else if (changeable[5] == 1)//跑道型 
			{
				changeable[5] = 0;
				sub_texting[5] = 1;
				run_num++;
				double x1 = runway[run_num - 1].x1, y1 = runway[run_num - 1].y1, x2 = runway[run_num - 1].x2, y2 = runway[run_num - 1].y2;
				imper_x = x1 + (x2 - x1) / 2;
				imper_y = y1 + (y2 - y1) / 2 - fa / 2;
				startTimer(TIMER_BLINK250, 500);
				flag_can_move = 0;
			}
			else if (changeable[7] == 1)//曲线 
			{
				changeable[7] = 0;
				ell_cur_num++;
				flag_can_move = 0;
			}
			else if (changeable[8] == 1)
			{
				changeable[8] = 0;
				cir_cur_num++;
				flag_can_move = 0;
			}

		if (button == LEFT_BUTTON)//左键松开 关闭移动指定图案的权限 若需继续移动 需要再次选定 
			for (m = 1; m < 10; m++)
				for (n = 0; n < 50; n++)
					moveable[m][n] = 0;
		break;
	
		
	}
}

/*
 * Function: TimerEventProcess
 * Usage: TimerEventProcess(int timerID)
 * --------------------------------------------------------
 * 功能： 
 *		定时器的回调函数 
 */
void TimerEventProcess(int timerID)
{
	bool erasemode;

	switch (timerID) {
	case TIMER_BLINK500: //500ms文本闪烁定时器 用于风格二中 编辑功能下的光标闪烁 
		erasemode = GetEraseMode();
		if (imper_p != NULL)
			MovePen(imper_x + TextStringWidth(imper_p), imper_y);
		else
			MovePen(MIN(line[ii].x1, line[ii].x2) + 0.25, line[ii].y1 + 0.1);
		SetEraseMode(isDisplay);
		DrawLine(0, 0.2);
		SetEraseMode(erasemode);
		isDisplay = !isDisplay;
		break;

	case TIMER_BLINK1000://1000ms文本闪烁定时器 专门用于风格二中中心标题键入的光标闪烁 
		erasemode = GetEraseMode();
		if (imper_p != NULL)
			MovePen(imper_x + TextStringWidth(imper_p), imper_y);
		else
			MovePen(4.4, 4.0);
		SetEraseMode(isDisplay);
		DrawLine(0, 0.2);
		SetEraseMode(erasemode);
		isDisplay = !isDisplay;
		break;

	case TIMER_BLINK250://500ms文本闪烁定时器 用于风格一 风格三下的文本框光标闪烁 
		erasemode = GetEraseMode();
		if (imper_p != NULL)
			MovePen(imper_x + TextStringWidth(imper_p), imper_y);
		else
			MovePen(imper_x, imper_y);
		SetEraseMode(isDisplay);
		DrawLine(0, 0.2);
		SetEraseMode(erasemode);
		isDisplay = !isDisplay;
		break;

	default:
		break;
	}
}
