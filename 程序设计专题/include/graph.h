#ifndef __graph_h______________________
#define __graph_h______________________

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a>b?b:a
 
#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#define TIMER_BLINK1000 2

int rec_num,ell_num,cir_num,run_num,line_num,text_num,ell_cur_num,cir_cur_num;//记录各个图案当前的数量 

double winwidth,winheight;

struct data_one{
	double x1;
	double x2;
	double y1;
	double y2;
	char p[20];
	int layer;
	int sub_text; 
} rectangle[50],ellipse[50],circle[50],runway[50]; 

struct data_two{
	double x1;
	double x2;
	double y1;
	double y2;
	char p[20];
	int layer;	
}text[50];

struct data_three{
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	int layer;
	double scope_y;
	char color[15];
} line[200];

struct data_four{
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	int layer;
	char color[15];	
}ell_curve[200];

struct data_five{
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	char color[15];	
}cir_curve[200];


int drawable[10];//编辑菜单下的对应的图案 画画的标签 
int changeable[10];//用于CAD模式下的 生成图案 的标签 
int moveable[10][50]; // 移动模式下的 是否可动的标签 
int eliminate;//删除模式的标签 
int generate_stage;//用于模式二中的 动态菜单的改变 
int layer_number[4];//用于 模式二中 生成菜单  记录每个分支的数量 
int topic;//用于模式二 记录目前分支数目 
int editable;//菜单中选中开始编辑文本
int start_texting;//鼠标传给键盘的开始编辑文本的 flag 
int sub_texting[8];//用来使图案与文本框联动 
int style_two;//如是模式二 则刚开始会有光标闪烁 提示输入主标题  用于提示是否是导入的风格二 
int can_move;//用于移动图案 通过选择 打开移动模式 
int style_choice;//开始界面进入风格 

#endif 
