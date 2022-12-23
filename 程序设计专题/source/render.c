/*
 * 	该文件为渲染文件
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
void Colormap();
void beautify_menu(double w);
void clear_all();

//=============================================================================
// 函数


/*
 * Function: Colormap
 * Usage: Colormap()
 * --------------------------------------------------------
 * 功能：
 *		设置 开始界面背景
 * 		调整 笔和字体
 * 		设置 默认颜色
 */
void Colormap()
{
	// 设置开始界面背景
	DisplayBackGroundImg("render\\img.bmp", 0, 0, 810, 560, 0, 0, 900, 800);

	SetPenSize(2);			// 设置笔的粗细为2
	SetStyle(1);			// 将字体设置为加粗
	SetPointSize(15);		// 将字体设成15
	fa = GetFontAscent();	// 获取当前字体的高度

	to_form = -1;			// 设置默认值为 -1

	// 设置颜色
	DefineColor("Orange", 1, 0.647, 0);					// 橙色
	DefineColor("Egg", 0.989, 0.902, 0.788);			// 蛋青色
	DefineColor("Mint", 0.741, 0.989, 0.788);			// 薄荷色 
	DefineColor("Grass", 0.486, 0.989, 0);				// 草地色 
	DefineColor("Forest", 0.133, 0.545, 0.133);			// 森林色
	DefineColor("Seagreen", 0.329, 1, 0.624);			// 海绿色
	DefineColor("SpringGreen3", 0.0, 0.804, 0.4);		// 春绿色3
	DefineColor("AntiqueWhite", 0.98, 0.922, 0.843);	// 古董白
	DefineColor("Moccasin", 1.0, 0.894, 0.710);			// 鹿皮色
	DefineColor("Pink", 1.0, 0.753, 0.769);				// 粉色
	DefineColor("Firebrick", 1.0, 0.188, 0.188);		// 砖红色
	DefineColor("HotPink", 1.0, 0.412, 0.706);			// 瑰红色
}

/*
 * Function: beautify_menu
 * Usage: beautify_menu(w)
 * w: 主菜单宽度
 * --------------------------------------------------------
 * 功能：
 *		绘制三种风格默认界面
 */
void beautify_menu(double w)
{
	double fH = GetFontHeight();	// 字体高度
	double x = 0.75;				// 矩形横坐标，fH/8;
	double y = winheight - 0.05;		// 矩形纵坐标
	double h = fH * 1.5;				// 控件高度

	// 设置三种风格中笔的颜色
	if (style_choice == 1)
		SetPenColor("SpringGreen3");
	else if (style_choice == 2)
		SetPenColor("Dark gray");
	else
		SetPenColor("HotPink");

	// 绘制菜单栏
	drawRectangle(0, y - h - 0.05, x, 0.1 + h, 1);
	drawRectangle(x + 5 * w, y - h - 0.05, 10 - x - 5 * w, 0.1 + h, 1);
	drawRectangle(x, y, 5 * w, 0.05, 1);
	drawRectangle(x, y - h - 0.05, 5 * w, 0.05, 1);

	// 绘制上方菜单栏右侧矩形
	drawRectangle(9.7, 0, 0.3, 1.7, 1);

	// 绘制菜单栏左侧风格种类标志
	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(4.15, 4.78);
	DrawArc(0.22, -90, 180);
	EndFilledRegion();

	// 绘制上方菜单栏右侧Label “CREATIVITY”
	drawLabel(5.35, 7.75, "C");
	drawLabel(5.85, 7.75, "R");
	drawLabel(6.35, 7.75, "E");
	drawLabel(6.85, 7.75, "A");
	drawLabel(7.35, 7.75, "T");
	drawLabel(7.85, 7.75, "I");
	drawLabel(8.35, 7.75, "V");
	drawLabel(8.85, 7.75, "I");
	drawLabel(9.35, 7.75, "T");
	drawLabel(9.85, 7.75, "Y");

	// 绘制右下方Label “MIND MAP”
	drawLabel(9.8, 1.50, "M");
	drawLabel(9.8, 1.30, "I");
	drawLabel(9.8, 1.10, "N");
	drawLabel(9.8, 0.90, "D");
	drawLabel(9.8, 0.50, "M");
	drawLabel(9.8, 0.30, "A");
	drawLabel(9.8, 0.10, "P");

	// 绘制菜单栏左侧风格种类标志
	if (style_choice == 1 || style_choice == 3)	// 用于风格一与风格三
	{
		StartFilledRegion(1);
		MovePen(0.2, 7.80);
		DrawArc(0.17, 180, 360);
		EndFilledRegion();

		if (style_choice == 1)
		{
			SetPenColor("SpringGreen3");
			drawLabel(0.22, 7.75, "first");
		}
		else
		{
			SetPenColor("HotPink");
			drawLabel(0.20, 7.75, "three");
		}
	}
	else if (style_choice == 2)	//用于模式二 
	{
		StartFilledRegion(1);
		MovePen(0.18, 7.80);
		DrawArc(0.26, 180, 360);
		EndFilledRegion();

		SetPenColor("Dark gray");
		drawLabel(0.18, 7.75, "second");
	}
}

/*
 * Function: clear_all
 * Usage: clear_all()
 * --------------------------------------------------------
 * 功能：
 *		在更换风格时，初始化所有全局变量
 */
void clear_all()
{
	int i;
	for (i = 0; rectangle[i].x1 > 0; i++)
		rectangle[i] = rectangle[49];
	for (i = 0; ellipse[i].x1 > 0; i++)
		ellipse[i] = ellipse[49];
	for (i = 0; circle[i].x1 > 0; i++)
		circle[i] = circle[49];
	for (i = 0; runway[i].x1 > 0; i++)
		runway[i] = runway[49];
	for (i = 0; text[i].x1 > 0; i++)
		text[i] = text[49];
	for (i = 0; line[i].x1 > 0; i++)
		line[i] = line[150];
	for (i = 0; ell_curve[i].x1 > 0; i++)
		ell_curve[i] = ell_curve[150];
	for (i = 0; cir_curve[i].x1 > 0; i++)
		cir_curve[i] = cir_curve[150];
	topic = 0;
	sub_topic = 0;
	for (i = 0; i <= 6; i++)
		blank[i] = 0;
	to_form = -1;
	rec_num = ell_num = cir_num = run_num = line_num = text_num = ell_cur_num = cir_cur_num = 0;
}


