/*
 * 	���ļ�Ϊ�ṹ���ȫ�ֱ�����ͷ�ļ�
 */



#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__


//=============================================================================
// �ṹ����


// �ṹһ	������Բ��Բ���ܵ�
struct data_one {
	double x1;
	double x2;
	double y1;
	double y2;
	char p[50];
	int layer;
	int sub_text;
} rectangle[50], ellipse[50], circle[50], runway[50];

// �ṹ��	�ı�
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

// �ṹ��	ֱ��֧��
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

// �ṹ��	��Բ��֧��
struct data_four {
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	int layer;
	char color[15];
}ell_curve[200];

// �ṹ��	Բ��֧��
struct data_five {
	double x1;
	double x2;
	double y1;
	double y2;
	int belonging;
	char color[15];
}cir_curve[200];

//���ڷ��һ �洢�Զ����ߵ�ͼ������ 
typedef struct connection {
	double x1,
		x2,
		y1,
		y2;
	struct connection *next;
} LinkList;


//=============================================================================
// ȫ�ֱ���


// Ĭ�ϴ��ڴ�С
double winwidth, winheight;

// ��¼����ͼ����ǰ������ 
int rec_num, ell_num, cir_num, run_num, line_num, text_num, ell_cur_num, cir_cur_num;

// �༭�˵��µĶ�Ӧ��ͼ�� �����ı�ǩ
int drawable[10];
// ����CADģʽ�µ� ����ͼ�� �ı�ǩ
int changeable[10];
// �ƶ�ģʽ�µ� �Ƿ�ɶ��ı�ǩ
int moveable[10][50];
// ɾ��ģʽ�ı�ǩ
int eliminate;

// ����ģʽ���е� ��̬�˵��ĸı�
int generate_stage;
// ����ģʽ�������ɲ˵�����¼ÿ����֧������ 
int layer_number[4];
// ����ģʽ������¼Ŀǰ��֧��Ŀ
int topic;
// �˵���ѡ�п�ʼ�༭�ı�
int editable;
// ��괫�����̵Ŀ�ʼ�༭�ı��� flag
int start_texting;
// ����ʹͼ�����ı�������
int sub_texting[8];
// ����ģʽ�� ��տ�ʼ���й����˸ ��ʾ����������  ������ʾ�Ƿ��ǵ���ķ���
int style_two;
// �����ƶ�ͼ�� ͨ��ѡ�� ���ƶ�ģʽ
int can_move;

// ��ʼ��������� 
int style_choice;
// ���ڶ�̬��ʾ��ǰ������ı�
char *imper_p;
// ��̬��¼��ǰ�ı���λ��
double imper_x, imper_y;
// ����߶�
double fa;
// button�İ�ť һ����text�ĸ���
int selectable[2][100];
// ���ڷ�����������ӱ���
int to_form;
// ���ڷ�����е�topic����
int sub_topic;
// ��ŷ�����ָ�����֧���ӷ�֧��Ŀ
int blank[7];
// ��ֹ�ƶ�ģʽ�� �޷�����ͼ���ı�ǩ
int flag_can_move;

// ���ڿ������߹��ܵı�ʶ 
int can_connect;
// ��ǰ����ͷ 
LinkList *head;
// ��¼���Ķ������Ķ� 
int form_num, to_num;
//��¼��ɶ����ɶ 
char form_pattern[15],to_pattern[15];

#endif // !__STRUCTURE_H__
