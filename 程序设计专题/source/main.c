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
//回调函数声明 
void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

//=============================================================================
// 主程序入口

void Main()
{
	SetWindowTitle("MIND MAP");
	SetWindowSize(10, 8);
	InitGraphics();

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerCharEvent(CharEventProcess);        	// 注册字符
	registerKeyboardEvent(KeyboardEventProcess);	// 注册键盘
	registerMouseEvent(MouseEventProcess);      	// 注册鼠标
	registerTimerEvent(TimerEventProcess);      	// 注册定时器

	Colormap();//初始化调色盘 
	draw_interface();//画出开始界面 
}

