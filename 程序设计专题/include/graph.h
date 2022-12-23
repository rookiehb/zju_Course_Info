#ifndef __graph_h______________________
#define __graph_h______________________

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a>b?b:a
 
#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
#define TIMER_BLINK1000 2

int rec_num,ell_num,cir_num,run_num,line_num,text_num,ell_cur_num,cir_cur_num;//��¼����ͼ����ǰ������ 

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


int drawable[10];//�༭�˵��µĶ�Ӧ��ͼ�� �����ı�ǩ 
int changeable[10];//����CADģʽ�µ� ����ͼ�� �ı�ǩ 
int moveable[10][50]; // �ƶ�ģʽ�µ� �Ƿ�ɶ��ı�ǩ 
int eliminate;//ɾ��ģʽ�ı�ǩ 
int generate_stage;//����ģʽ���е� ��̬�˵��ĸı� 
int layer_number[4];//���� ģʽ���� ���ɲ˵�  ��¼ÿ����֧������ 
int topic;//����ģʽ�� ��¼Ŀǰ��֧��Ŀ 
int editable;//�˵���ѡ�п�ʼ�༭�ı�
int start_texting;//��괫�����̵Ŀ�ʼ�༭�ı��� flag 
int sub_texting[8];//����ʹͼ�����ı������� 
int style_two;//����ģʽ�� ��տ�ʼ���й����˸ ��ʾ����������  ������ʾ�Ƿ��ǵ���ķ��� 
int can_move;//�����ƶ�ͼ�� ͨ��ѡ�� ���ƶ�ģʽ 
int style_choice;//��ʼ��������� 

#endif 
