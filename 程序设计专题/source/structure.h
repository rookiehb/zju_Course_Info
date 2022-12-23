/*
 * 	该文件为结构体和全局变量的头文件
 */



#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__


//=============================================================================
// 结构声明


// 结构一	方格、椭圆、圆、跑道
struct data_one {
	double x1;
	double x2;
	double y1;
	double y2;
	char p[50];
	int layer;
	int sub_text;
} rectangle[50], ellipse[50], circle[50], runway[50];

// 结构二	文本
struct data_two {
	double x1;
	double x2;
	double y1;
	double y2;
	char p[50];
	int layer;
	int connection;
	char belonging[15];
}text[50];

// 结构三	直分支线
struct data_three {
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	int layer;
	double scope_y;
	char color[15];
} line[200];

// 结构四	椭圆分支线
struct data_four {
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	int layer;
	char color[15];
}ell_curve[200];

// 结构五	圆分支线
struct data_five {
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	char color[15];
}cir_curve[200];

//用于风格一 存储自动连线的图案数据 
typedef struct connection {
	double x1,
		x2,
		y1,
		y2;
	struct connection *next;
} LinkList;


//=============================================================================
// 全局变量


// 默认窗口大小
double winwidth, winheight;

// 记录各个图案当前的数量 
int rec_num, ell_num, cir_num, run_num, line_num, text_num, ell_cur_num, cir_cur_num;

// 编辑菜单下的对应的图案 画画的标签
int drawable[10];
// 用于CAD模式下的 生成图案 的标签
int changeable[10];
// 移动模式下的 是否可动的标签
int moveable[10][50];
// 删除模式的标签
int eliminate;

// 用于模式二中的 动态菜单的改变
int generate_stage;
// 用于模式二中生成菜单，记录每个分支的数量 
int layer_number[4];
// 用于模式二，记录目前分支数目
int topic;
// 菜单中选中开始编辑文本
int editable;
// 鼠标传给键盘的开始编辑文本的 flag
int start_texting;
// 用来使图案与文本框联动
int sub_texting[8];
// 如是模式二 则刚开始会有光标闪烁 提示输入主标题  用于提示是否是导入的风格二
int style_two;
// 用于移动图案 通过选择 打开移动模式
int can_move;

// 开始界面进入风格 
int style_choice;
// 用于动态显示当前输入的文本
char *imper_p;
// 动态记录当前文本的位置
double imper_x, imper_y;
// 字体高度
double fa;
// button的按钮 一个是text的更改
int selectable[2][100];
// 用于风格三的生成子标题
int to_form;
// 用于风格三中的topic生成
int sub_topic;
// 存放风格三种各个分支的子分支数目
int blank[7];
// 防止移动模式下 无法生成图案的标签
int flag_can_move;

// 用于开启连线功能的标识 
int can_connect;
// 当前链的头 
LinkList *head;
// 记录从哪儿连到哪儿 
int form_num, to_num;
//记录从啥连到啥 
char form_pattern[15],to_pattern[15];

#endif // !__STRUCTURE_H__
