/*
 * 	该文件为界面和图形绘制
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

void display();
void draw_interface();
void DrawMenu();
void update_pattern(int i, int j);

//=============================================================================
// 函数


/*
 * Function: display
 * Usage: display()
 * --------------------------------------------------------
 * 功能：
 *		开始界面设置背景，显示按钮
 *		进入三种风格后绘制菜单、标签和图形
 */

void display()
{	
	DisplayClear();
	ClearBackGroundImg();//此处调用graphics.c中函数，清除背景图片
	
	if ( style_choice==0) //初始界面 
		{
		DisplayBackGroundImg("render\\img.bmp",0,0,810,560,0,0,900,800);//此处调用graphics.c中函数，调入背景图片 
		draw_interface();
		}
	else //进入制作思维导图界面 
		{
		DrawPattern();
		DrawMenu();
		drawLabel(imper_x,imper_y,imper_p);//动态表示当前编辑的文本框信息 
		}
}

/*
 * Function: draw_interface
 * Usage: draw_interface()
 * --------------------------------------------------------
 * 功能：
 *		绘制开始界面的四个按钮并实现其接口功能
 */
void draw_interface()
{		
	Initial_Style();
	if( button(GenUIID(0),1.2,5.3,1.3,0.7,"青青草原") ) //CAD
		{
		style_choice=1;
		change_color();//此函数由作者写在imgui.c中，用于改变菜单栏的字体颜色与框颜色 
		}
	
	if( button(GenUIID(0),1.2,3.8,1.3,0.7,"简约办公") ) 
		{
		style_choice=2;
		Second_Style();
		change_color();
		}
	
	if( button(GenUIID(0),1.2,2.3,1.3,0.7,"粉系少女") ) 
		{
		style_choice=3;
		Third_Style();
		change_color();
		}
	
	if( button(GenUIID(0),1.2,0.8,1.3,0.7,"退出程序") ) 
		{
		exit(0);
		}
}

/*
 * Function: DrawMenu
 * Usage: DrawMenu()
 * --------------------------------------------------------
 * 功能：
 *		绘制菜单栏
 */
void DrawMenu()//画菜单 
{	
	//一些画菜单的数据
	static char * editmenulist[] = {"编辑菜单","矩形","椭圆","圆形","直线","跑道型","文本框","椭圆曲线","半圆曲线"};
	static char * eliminatemenulist[] = {"其他功能","导入图表","保存图表","删除图案","移动图案","取消移动","连接图案","取消连接"} ;
	static char * exitmenulist[] = {"返回选项","回到开始界面","退出程序"};
	static char * generatetheme[] = {"第二主题","生成子主题","开始编辑文本","停止编辑文本"};
	static char * sublayer_one[] = {"分支数目","一","二","三"};
	static char * sublayer_one_one[] = {"一的数目","零","一","二","三"};
	static char * sublayer_one_two[] = {"二的数目","零","一","二","三"};
	static char * sublayer_one_three[] = {"三的数目","零","一","二","三"};
	static char * whitecolumn[] = {"第三主题","次标题","亚标题"};
	 
	double fH = GetFontHeight();
	double x = 0.75; //fH/8;
	double y = winheight-0.05;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(editmenulist[0])*1.2; // 主菜单宽度
	double wlist = TextStringWidth(editmenulist[1])*3.5;
	double xindent = winheight/20; // 缩进
	int selection,i;
	
	beautify_menu(w);
	
	selection = menuList(GenUIID(0),x,y-h,w,wlist,h,editmenulist,sizeof(editmenulist)/sizeof(editmenulist[0]));//编辑菜单 
	if (selection>0)//根据选择 将 对应图案的drawable属性赋值为0 
		{
		flag_can_move=1;
		drawable[selection]=1;
		}
		
	selection = menuList(GenUIID(0),x+w,y-h,w,wlist,h,eliminatemenulist,sizeof(eliminatemenulist)/sizeof(eliminatemenulist[0]));//其他功能菜单 
	if (selection==1) 
		{
		load_model();//导入模型 
		style_two=0;//取消中心光标闪烁 
		cancelTimer(TIMER_BLINK1000);/*1000ms定时器关闭*/
		}
	else if (selection==2)
		sort();//保存大纲与模型
	else if (selection==3)
		eliminate=1;//启动删除图案模式 右键点到需要删除的图案即可进行删除 
	else if (selection==4)
		can_move=1;//启动移动模式 左键点到需要移动的图案即可进行移动 
	else if (selection==5)
		can_move=0;//关闭移动模式 
	else if (selection==6)
		{
		head = creat();//生成一个链表 
		can_connect=1;//打开连接图案功能 
		}
	else if (selection==7)
		{
		can_connect=0;//关闭连接图案功能 
		delet(head);//清除链表 
		}
	
	selection = menuList(GenUIID(0),x+w*2,y-h,w,wlist,h,exitmenulist,sizeof(exitmenulist)/sizeof(exitmenulist[0]));//退出菜单 
	if (selection==1)
		{
		clear_all();//初始化一切全局变量 
		style_choice=0;
		style_two = 0;
		cancelTimer(TIMER_BLINK1000);
		}
		//回到前端 
	else if (selection==2)
		exit(0);//直接退出程序 
	
	//用于风格二的编辑 
	if (generate_stage==0)//生成 子标题的栏目 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,generatetheme,sizeof(generatetheme)/sizeof(generatetheme[0]));
		for (i=0;i<=3;i++) //开始选择时 初始化变量 
			layer_number[i]=0;
		if (selection==1)
			{
			generate_stage=1;
			topic++;//记录第二种风格中 topic的数量 
			}
		else if (selection==2)
			editable=1; //打开编辑功能 
		else if (selection==3)
			editable=0;//关闭编辑功能 
		}
	else if (generate_stage==1) // 选择生成子标题后 开始选择子标题分支的数目  
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one,sizeof(sublayer_one)/sizeof(sublayer_one[0]));
		if (selection>0) 
			{
			generate_stage=2;
			layer_number[0]=selection;
			}
		}
	else if (generate_stage==2) // 进一步生成  根据用户选择 生成不同分支数目  第一个分支数目  
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_one,sizeof(sublayer_one_one)/sizeof(sublayer_one_one[0]));
		if (selection>0 && layer_number[0]>1)
			{
			generate_stage=3;
			layer_number[1]=selection-1;
			}
		else if (selection>0 && layer_number[0]==1)//若只有一个分支则返回  
			{
			layer_number[1]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	else if (generate_stage==3 )//第二个分支数目 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_two,sizeof(sublayer_one_two)/sizeof(sublayer_one_two[0]));
		if (selection>0 && layer_number[0]>2)
			{
			layer_number[2]=selection-1;
			generate_stage=4;
			}
		else if (layer_number[0]==2 && selection>0)//若只有两个分支 则返回 
			{
			layer_number[2]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	else if (generate_stage==4)//第三个分支数目 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_three,sizeof(sublayer_one_three)/sizeof(sublayer_one_three[0]));
		if (selection>0)
			{
			layer_number[3]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	
	//用于风格三的主题编辑 
	selection = menuList(GenUIID(0),x+4*w,y-h,w,wlist,h,whitecolumn,sizeof(whitecolumn)/sizeof(whitecolumn[0]));
	if (selection==1)
		form_subtopic();//生成子标题 
	else if (selection==2)
		form_blanks(); //生成亚标题 
}


/*
 * Function: DrawPattern
 * Usage: DrawPattern()
 * --------------------------------------------------------
 * 功能：
 *		绘制思维导图
 */
void DrawPattern()
{
	int i;double fa =GetFontAscent();
	
	for (i=0;rectangle[i].x1 > 0;i++)//重新生成矩形  
		{
		double x1=rectangle[i].x1,x2=rectangle[i].x2,y1=rectangle[i].y1,y2=rectangle[i].y2;char p[50];
		strcpy(p,rectangle[i].p);
		//画出填充区域 
		if (style_choice==1)
			SetPenColor("Mint");
		else if (style_choice==3)
			SetPenColor("White");
		StartFilledRegion(1);
		MovePen(x1,y1);
		DrawLine(0,y2-y1);
		DrawLine(x2-x1,0);
		DrawLine(0,y1-y2);
		DrawLine(x1-x2,0);
		EndFilledRegion();
		
		//调画笔颜色 
		if (style_choice==1 && (form_num != i || strcmp(form_pattern,"rectangle")!=0 ) && ( to_num!=i ||strcmp(to_pattern,"rectangle")!=0)  )
			SetPenColor("Forest");
		else if (style_choice==3 && to_form != i)
			SetPenColor("HotPink"); 
		else if (style_choice==3 && to_form ==i)
			SetPenColor("Red");
		else if (style_choice==1 && i==form_num && strcmp(form_pattern,"rectangle")==0  )
			SetPenColor("Red");
		else if (style_choice==1 && i==to_num &&  strcmp(to_pattern,"rectangle")==0  )
			SetPenColor("Blue");
		
		//画出外部轮廓
		MovePen(x1,y1);
		DrawLine(0,y2-y1);
		DrawLine(x2-x1,0);
		DrawLine(0,y1-y2);
		DrawLine(x1-x2,0);
		
		if ( p && strlen(p)>0 )//如果有附属文本框 
			if ( rectangle[i].sub_text == -1 ) //第一次输入文本框 则通过sub_text记录对应的text标签 
				{
				rectangle[i].sub_text = drawtext(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,p,rectangle[i].layer);
				text[rectangle[i].sub_text].connection = i;
				strcpy(text[rectangle[i].sub_text].belonging,"rectangle");
				}
			else//实时移动文本框 
				update_text(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,rectangle[i].sub_text);
			
		//将层级信息表现在左上角 
		char temp_layer[4];
		itoa(rectangle[i].layer,temp_layer,10);
		drawLabel(x1,y2-fa,temp_layer);
		}

	for (i=0;ellipse[i].x1 > 0;i++)//重新生成椭圆 
		{
		double x1=ellipse[i].x1,x2=ellipse[i].x2,y1=ellipse[i].y1,y2=ellipse[i].y2;char p[50];
		strcpy(p,ellipse[i].p);

		StartFilledRegion(1);//画出填充区域 
		SetPenColor("Mint");
		MovePen(x1,(y1+y2)/2);
		DrawEllipticalArc( (x2-x1)/2,(y2-y1)/2,180,360 );
		EndFilledRegion();
		
		SetPenColor("Forest");
		if (style_choice==1 && (form_num != i ||strcmp(form_pattern,"ellipse")!=0)  && (to_num != i ||strcmp(to_pattern,"ellipse")!=0) )
			SetPenColor("Forest");
		else if (style_choice==1 && i==form_num && strcmp(form_pattern,"ellipse")==0)
			SetPenColor("Red");
		else if (style_choice==1 && i==to_num  && strcmp(to_pattern,"ellipse")==0)
			SetPenColor("Blue");
		
		//画出外部轮廓 
		MovePen(x1,(y1+y2)/2);
		DrawEllipticalArc( (x2-x1)/2,(y2-y1)/2,180,360 );
		
		if ( p && strlen(p)>0 )
			if ( ellipse[i].sub_text == -1 ) 
				{
				ellipse[i].sub_text = drawtext(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,p,ellipse[i].layer);
				text[ellipse[i].sub_text].connection = i;
				strcpy(text[ellipse[i].sub_text].belonging,"ellipse");
				}
			else 
				update_text(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,ellipse[i].sub_text);
		
		char temp_layer[4];
		itoa(ellipse[i].layer,temp_layer,10);
		drawLabel(x1,y2-fa,temp_layer);
		}
	
	for (i=0;circle[i].x1 > 0;i++)//重新生成圆 
		{
		double x1=circle[i].x1,y1=circle[i].y1,x2=circle[i].x2,y2=circle[i].y2;char p[50];
		strcpy(p,circle[i].p);
		StartFilledRegion(1);
		SetPenColor("Mint");
		MovePen(x1,(y1+y2)/2);
		DrawArc( (y2-y1)/2 , 180 ,360);
		EndFilledRegion();
		
		SetPenColor("Forest");
		if (style_choice==1 && (form_num != i || strcmp(form_pattern,"circle")!=0 ) && (to_num != i ||strcmp(to_pattern,"circle")!=0) )
			SetPenColor("Forest");
		else if (style_choice==1 && i==form_num && strcmp(form_pattern,"circle")==0 )
			SetPenColor("Red");
		else if (style_choice==1 && i==to_num && strcmp(to_pattern,"circle")==0)
			SetPenColor("Blue");
		
		//画出外部轮廓 
		MovePen(x1,(y1+y2)/2);
		DrawArc( (y2-y1)/2 , 180 ,360);

		if ( p && strlen(p)>0 )
			if ( circle[i].sub_text == -1 ) 
				{
				circle[i].sub_text = drawtext(x1-(y2-y1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,p,circle[i].layer);
				text[circle[i].sub_text].connection = i;
				strcpy(text[circle[i].sub_text].belonging,"circle");
				}
			else 
				update_text(x1+(y2-y1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,circle[i].sub_text);
		
		char temp_layer[4];
		itoa(circle[i].layer,temp_layer,10);
		drawLabel(x1,y2-fa,temp_layer);
		}
	
	for (i=0;line[i].x1 > 0;i++) //画线条  
		{
		double x1=line[i].x1,y1=line[i].y1,x2=line[i].x2,y2=line[i].y2;
		char color[15];
		strcpy(color,line[i].color);
		SetPenColor(color);
		if (style_choice==3)
			SetPenColor("HotPink");
		MovePen(x1,y1);
		DrawLine(x2-x1,y2-y1); 
		
		}
		
	for (i=0;runway[i].x1 > 0;i++)//画跑道型 
		{
		double x1=runway[i].x1,y1=runway[i].y1,x2=runway[i].x2,y2=runway[i].y2;char p[50];
		strcpy(p,runway[i].p);
		
		//填充图案 
		StartFilledRegion(1);
		SetPenColor("Mint");
		MovePen(x1+(y2-y1)/2,y1);
		DrawLine(0,y2-y1);
		DrawLine(x2-x1-(y2-y1),0);
		DrawLine(0,y1-y2);
		DrawLine(-(x2-x1-(y2-y1)),0);
		DrawArc((y2-y1)/2,270,-180);
		DrawLine(x2-x1-(y2-y1),0);
		DrawArc((y2-y1)/2,90,-180);
		EndFilledRegion();
		
		SetPenColor("Forest");
		if (style_choice==1 && (form_num != i  || strcmp(form_pattern,"runway")!=0) && (to_num != i || strcmp(to_pattern,"runway")!=0) )
			SetPenColor("Forest");
		else if (style_choice==1 && i==form_num && strcmp(form_pattern,"runway")==0)
			SetPenColor("Red");
		else if (style_choice==1 && i==to_num && strcmp(to_pattern,"runway")==0 )
			SetPenColor("Blue");
		
		//画出外部轮廓 
		MovePen(x1+(y2-y1)/2,y1);
		DrawArc((y2-y1)/2,270,-180);
		DrawLine(x2-x1-(y2-y1),0);
		DrawArc((y2-y1)/2,90,-180);
		DrawLine(-(x2-x1-(y2-y1)),0);
		
		if ( p && strlen(p)>0 )
			if ( runway[i].sub_text == -1 ) 
				{
				runway[i].sub_text = drawtext(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,p,runway[i].layer);
				text[runway[i].sub_text].connection = i;
				strcpy(text[runway[i].sub_text].belonging,"runway");
				}
			else 
				update_text(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,runway[i].sub_text);
		
		char temp_layer[4];
		itoa(runway[i].layer,temp_layer,10);
		drawLabel(x1,y2-fa,temp_layer);
		} 
	
	for (i=0;text[i].x1 > 0;i++)//文本框 
		{
		double x1=text[i].x1,y1=text[i].y1;char label[50];
		strcpy(label,text[i].p);
		
		if (style_choice==1)
			SetPenColor("Forest");
		else if (style_choice==2)
			SetPenColor("Dark gray");
		else if (style_choice==3)
			SetPenColor("HotPink");
		
		drawLabel(x1,y1,label);
		}
	
	for (i=0;ell_curve[i].x1 > 0;i++)//画椭圆曲线 
		{
		double x1=ell_curve[i].x1,x2=ell_curve[i].x2,y1=ell_curve[i].y1,y2=ell_curve[i].y2;
		
		char color[15];
		strcpy(color,ell_curve[i].color);
		SetPenColor(color);
		if (style_choice==1)
			SetPenColor("Forest"); 
		
		//判断左上 左下 右上 右下 ，生成曲线 
		double rx,ry;
		if ( y1 < y2 )
			{
			if ( x2>x1 )//右上 
				{
				rx = (x2-x1)/2;
				ry=(y2-y1)/2;
				MovePen(x1,y1);
				DrawEllipticalArc(rx,ry,270,90);
				DrawEllipticalArc(rx,ry,180,-90);
				}
			else if (x2<x1)
				{
				rx = (-x2+x1)/2;
				ry=(y2-y1)/2;
				MovePen(x1,y1);
				DrawEllipticalArc(rx,ry,270,-90);
				DrawEllipticalArc(rx,ry,0,90);
				}
			}
		else if (y1>y2)
				{
				if (x2>x1)
					{
					rx = (x2-x1)/2;
					ry=(-y2+y1)/2;	
					MovePen(x1,y1);
					DrawEllipticalArc(rx,ry,90,-90);
					DrawEllipticalArc(rx,ry,180,90);
					}
				else if (x2<x1)
					{
					rx = (x1-x2)/2;
					ry = (y1-y2)/2;
					MovePen(x1,y1);
					DrawEllipticalArc(rx,ry,90,90);
					DrawEllipticalArc(rx,ry,0,-90);
					}
				}
		else if (y1-y2 < 0.01)
				{
				MovePen(x1,y1);
				DrawLine(x2-x1,0);
				}
		}
	
	for (i=0;cir_curve[i].x1 > 0;i++)//画半圆曲线 
		{
		
		double x1=cir_curve[i].x1,x2=cir_curve[i].x2,y1=cir_curve[i].y1,y2=cir_curve[i].y2;
		
		char color[15];
		strcpy(color,cir_curve[i].color);
		SetPenColor(color);
		
		//判断左上 左下 右上 右下 ，生成曲线 
		double rx,ry;
		if ( y2 > y1 )
			{
			if ( x2 > x1 )//右上 
				{
				rx = x2-x1;
				ry = y2-y1;
				MovePen(x1,y1);
				DrawEllipticalArc(rx,ry,180,-90);
				}
			else if ( x2 < x1 )
				{
				rx = -x2+x1;
				ry = y2-y1;
				MovePen(x1,y1);
				DrawEllipticalArc(rx,ry,0,90);
				}
			}
		else if ( y1 > y2 )
				{
				if (x2>x1)
					{
					rx = x2 - x1;
					ry = y1 - y2;
					MovePen(x1,y1);
					DrawEllipticalArc(rx,ry,180,90);
					}
				else if ( x2 < x1 )
					{
					rx = x1-x2;
					ry = y1-y2;
					MovePen(x1,y1);
					DrawEllipticalArc(rx,ry,0,-90);
					}
				}
		else if (y1-y2<0.01)
				{
				MovePen(x1,y1);
				DrawLine(x2-x1,0);
				}
		}
}


/*
 * Function: update_pattern
 * Usage: update_pattern(int i, int j)
 * --------------------------------------------------------
 * 功能：
 *		删除图形时，更新结构体
 */
void update_pattern(int i,int j)
{
	if (i==1)//更新矩形数据 
		{
		while (rectangle[j].x1!=0)
			{rectangle[j]=rectangle[j+1];j++;}
		rec_num--;
		}
	else if (i==2)//椭圆 
		{
		while (ellipse[j].x1 != 0)
			{ellipse[j]= ellipse[j+1];j++;}
		ell_num--;
		}
	else if (i==3)//圆 
		{
		while (circle[j].x1 != 0)
			{circle[j]=circle[j+1];j++;}
		cir_num--;
		}
	else if (i==4)//线条 
		{
		while (  line[j].x1 != 0 )
			{line[j]= line[j+1];j++;}
		line_num--;
		}	
	else if (i==5)//跑道型 
		{
		while (runway[j].x1 != 0)
			{runway[j] = runway[j+1];j++;}
		run_num--;
		}
	else if (i==6) //文本框 
		{
		while (text[j].x1 != text[j].x2)
			{text[j] = text[j+1];j++;}
		text_num--;
		}
	else if (i==7)//曲线 
		{
		while (ell_curve[j].x1 !=0)
			{ell_curve[j] = ell_curve[j+1];j++;}
		ell_cur_num--;
		}
	else if (i==8)
		{
		while (cir_curve[j].x1 != 0)
			{cir_curve[j] = cir_curve[j+1];j++;}
		cir_cur_num--;
		}
}

