/*
 * 	���ļ�Ϊ�����ͼ�λ���
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

void display();
void draw_interface();
void DrawMenu();
void update_pattern(int i, int j);

//=============================================================================
// ����


/*
 * Function: display
 * Usage: display()
 * --------------------------------------------------------
 * ���ܣ�
 *		��ʼ�������ñ�������ʾ��ť
 *		�������ַ�����Ʋ˵�����ǩ��ͼ��
 */

void display()
{	
	DisplayClear();
	ClearBackGroundImg();//�˴�����graphics.c�к������������ͼƬ
	
	if ( style_choice==0) //��ʼ���� 
		{
		DisplayBackGroundImg("render\\img.bmp",0,0,810,560,0,0,900,800);//�˴�����graphics.c�к��������뱳��ͼƬ 
		draw_interface();
		}
	else //��������˼ά��ͼ���� 
		{
		DrawPattern();
		DrawMenu();
		drawLabel(imper_x,imper_y,imper_p);//��̬��ʾ��ǰ�༭���ı�����Ϣ 
		}
}

/*
 * Function: draw_interface
 * Usage: draw_interface()
 * --------------------------------------------------------
 * ���ܣ�
 *		���ƿ�ʼ������ĸ���ť��ʵ����ӿڹ���
 */
void draw_interface()
{		
	Initial_Style();
	if( button(GenUIID(0),1.2,5.3,1.3,0.7,"�����ԭ") ) //CAD
		{
		style_choice=1;
		change_color();//�˺���������д��imgui.c�У����ڸı�˵�����������ɫ�����ɫ 
		}
	
	if( button(GenUIID(0),1.2,3.8,1.3,0.7,"��Լ�칫") ) 
		{
		style_choice=2;
		Second_Style();
		change_color();
		}
	
	if( button(GenUIID(0),1.2,2.3,1.3,0.7,"��ϵ��Ů") ) 
		{
		style_choice=3;
		Third_Style();
		change_color();
		}
	
	if( button(GenUIID(0),1.2,0.8,1.3,0.7,"�˳�����") ) 
		{
		exit(0);
		}
}

/*
 * Function: DrawMenu
 * Usage: DrawMenu()
 * --------------------------------------------------------
 * ���ܣ�
 *		���Ʋ˵���
 */
void DrawMenu()//���˵� 
{	
	//һЩ���˵�������
	static char * editmenulist[] = {"�༭�˵�","����","��Բ","Բ��","ֱ��","�ܵ���","�ı���","��Բ����","��Բ����"};
	static char * eliminatemenulist[] = {"��������","����ͼ��","����ͼ��","ɾ��ͼ��","�ƶ�ͼ��","ȡ���ƶ�","����ͼ��","ȡ������"} ;
	static char * exitmenulist[] = {"����ѡ��","�ص���ʼ����","�˳�����"};
	static char * generatetheme[] = {"�ڶ�����","����������","��ʼ�༭�ı�","ֹͣ�༭�ı�"};
	static char * sublayer_one[] = {"��֧��Ŀ","һ","��","��"};
	static char * sublayer_one_one[] = {"һ����Ŀ","��","һ","��","��"};
	static char * sublayer_one_two[] = {"������Ŀ","��","һ","��","��"};
	static char * sublayer_one_three[] = {"������Ŀ","��","һ","��","��"};
	static char * whitecolumn[] = {"��������","�α���","�Ǳ���"};
	 
	double fH = GetFontHeight();
	double x = 0.75; //fH/8;
	double y = winheight-0.05;
	double h = fH*1.5; // �ؼ��߶�
	double w = TextStringWidth(editmenulist[0])*1.2; // ���˵����
	double wlist = TextStringWidth(editmenulist[1])*3.5;
	double xindent = winheight/20; // ����
	int selection,i;
	
	beautify_menu(w);
	
	selection = menuList(GenUIID(0),x,y-h,w,wlist,h,editmenulist,sizeof(editmenulist)/sizeof(editmenulist[0]));//�༭�˵� 
	if (selection>0)//����ѡ�� �� ��Ӧͼ����drawable���Ը�ֵΪ0 
		{
		flag_can_move=1;
		drawable[selection]=1;
		}
		
	selection = menuList(GenUIID(0),x+w,y-h,w,wlist,h,eliminatemenulist,sizeof(eliminatemenulist)/sizeof(eliminatemenulist[0]));//�������ܲ˵� 
	if (selection==1) 
		{
		load_model();//����ģ�� 
		style_two=0;//ȡ�����Ĺ����˸ 
		cancelTimer(TIMER_BLINK1000);/*1000ms��ʱ���ر�*/
		}
	else if (selection==2)
		sort();//��������ģ��
	else if (selection==3)
		eliminate=1;//����ɾ��ͼ��ģʽ �Ҽ��㵽��Ҫɾ����ͼ�����ɽ���ɾ�� 
	else if (selection==4)
		can_move=1;//�����ƶ�ģʽ ����㵽��Ҫ�ƶ���ͼ�����ɽ����ƶ� 
	else if (selection==5)
		can_move=0;//�ر��ƶ�ģʽ 
	else if (selection==6)
		{
		head = creat();//����һ������ 
		can_connect=1;//������ͼ������ 
		}
	else if (selection==7)
		{
		can_connect=0;//�ر�����ͼ������ 
		delet(head);//������� 
		}
	
	selection = menuList(GenUIID(0),x+w*2,y-h,w,wlist,h,exitmenulist,sizeof(exitmenulist)/sizeof(exitmenulist[0]));//�˳��˵� 
	if (selection==1)
		{
		clear_all();//��ʼ��һ��ȫ�ֱ��� 
		style_choice=0;
		style_two = 0;
		cancelTimer(TIMER_BLINK1000);
		}
		//�ص�ǰ�� 
	else if (selection==2)
		exit(0);//ֱ���˳����� 
	
	//���ڷ����ı༭ 
	if (generate_stage==0)//���� �ӱ������Ŀ 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,generatetheme,sizeof(generatetheme)/sizeof(generatetheme[0]));
		for (i=0;i<=3;i++) //��ʼѡ��ʱ ��ʼ������ 
			layer_number[i]=0;
		if (selection==1)
			{
			generate_stage=1;
			topic++;//��¼�ڶ��ַ���� topic������ 
			}
		else if (selection==2)
			editable=1; //�򿪱༭���� 
		else if (selection==3)
			editable=0;//�رձ༭���� 
		}
	else if (generate_stage==1) // ѡ�������ӱ���� ��ʼѡ���ӱ����֧����Ŀ  
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one,sizeof(sublayer_one)/sizeof(sublayer_one[0]));
		if (selection>0) 
			{
			generate_stage=2;
			layer_number[0]=selection;
			}
		}
	else if (generate_stage==2) // ��һ������  �����û�ѡ�� ���ɲ�ͬ��֧��Ŀ  ��һ����֧��Ŀ  
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_one,sizeof(sublayer_one_one)/sizeof(sublayer_one_one[0]));
		if (selection>0 && layer_number[0]>1)
			{
			generate_stage=3;
			layer_number[1]=selection-1;
			}
		else if (selection>0 && layer_number[0]==1)//��ֻ��һ����֧�򷵻�  
			{
			layer_number[1]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	else if (generate_stage==3 )//�ڶ�����֧��Ŀ 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_two,sizeof(sublayer_one_two)/sizeof(sublayer_one_two[0]));
		if (selection>0 && layer_number[0]>2)
			{
			layer_number[2]=selection-1;
			generate_stage=4;
			}
		else if (layer_number[0]==2 && selection>0)//��ֻ��������֧ �򷵻� 
			{
			layer_number[2]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	else if (generate_stage==4)//��������֧��Ŀ 
		{
		selection = menuList(GenUIID(0),x+w*3,y-h,w,wlist,h,sublayer_one_three,sizeof(sublayer_one_three)/sizeof(sublayer_one_three[0]));
		if (selection>0)
			{
			layer_number[3]=selection-1;
			generate_stage=0;
			generate_layer();
			}
		}
	
	//���ڷ����������༭ 
	selection = menuList(GenUIID(0),x+4*w,y-h,w,wlist,h,whitecolumn,sizeof(whitecolumn)/sizeof(whitecolumn[0]));
	if (selection==1)
		form_subtopic();//�����ӱ��� 
	else if (selection==2)
		form_blanks(); //�����Ǳ��� 
}


/*
 * Function: DrawPattern
 * Usage: DrawPattern()
 * --------------------------------------------------------
 * ���ܣ�
 *		����˼ά��ͼ
 */
void DrawPattern()
{
	int i;double fa =GetFontAscent();
	
	for (i=0;rectangle[i].x1 > 0;i++)//�������ɾ���  
		{
		double x1=rectangle[i].x1,x2=rectangle[i].x2,y1=rectangle[i].y1,y2=rectangle[i].y2;char p[50];
		strcpy(p,rectangle[i].p);
		//����������� 
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
		
		//��������ɫ 
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
		
		//�����ⲿ����
		MovePen(x1,y1);
		DrawLine(0,y2-y1);
		DrawLine(x2-x1,0);
		DrawLine(0,y1-y2);
		DrawLine(x1-x2,0);
		
		if ( p && strlen(p)>0 )//����и����ı��� 
			if ( rectangle[i].sub_text == -1 ) //��һ�������ı��� ��ͨ��sub_text��¼��Ӧ��text��ǩ 
				{
				rectangle[i].sub_text = drawtext(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,p,rectangle[i].layer);
				text[rectangle[i].sub_text].connection = i;
				strcpy(text[rectangle[i].sub_text].belonging,"rectangle");
				}
			else//ʵʱ�ƶ��ı��� 
				update_text(x1+(x2-x1-TextStringWidth(p))/2,y1+(y2-y1)/2-fa/2,rectangle[i].sub_text);
			
		//���㼶��Ϣ���������Ͻ� 
		char temp_layer[4];
		itoa(rectangle[i].layer,temp_layer,10);
		drawLabel(x1,y2-fa,temp_layer);
		}

	for (i=0;ellipse[i].x1 > 0;i++)//����������Բ 
		{
		double x1=ellipse[i].x1,x2=ellipse[i].x2,y1=ellipse[i].y1,y2=ellipse[i].y2;char p[50];
		strcpy(p,ellipse[i].p);

		StartFilledRegion(1);//����������� 
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
		
		//�����ⲿ���� 
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
	
	for (i=0;circle[i].x1 > 0;i++)//��������Բ 
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
		
		//�����ⲿ���� 
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
	
	for (i=0;line[i].x1 > 0;i++) //������  
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
		
	for (i=0;runway[i].x1 > 0;i++)//���ܵ��� 
		{
		double x1=runway[i].x1,y1=runway[i].y1,x2=runway[i].x2,y2=runway[i].y2;char p[50];
		strcpy(p,runway[i].p);
		
		//���ͼ�� 
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
		
		//�����ⲿ���� 
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
	
	for (i=0;text[i].x1 > 0;i++)//�ı��� 
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
	
	for (i=0;ell_curve[i].x1 > 0;i++)//����Բ���� 
		{
		double x1=ell_curve[i].x1,x2=ell_curve[i].x2,y1=ell_curve[i].y1,y2=ell_curve[i].y2;
		
		char color[15];
		strcpy(color,ell_curve[i].color);
		SetPenColor(color);
		if (style_choice==1)
			SetPenColor("Forest"); 
		
		//�ж����� ���� ���� ���� ���������� 
		double rx,ry;
		if ( y1 < y2 )
			{
			if ( x2>x1 )//���� 
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
	
	for (i=0;cir_curve[i].x1 > 0;i++)//����Բ���� 
		{
		
		double x1=cir_curve[i].x1,x2=cir_curve[i].x2,y1=cir_curve[i].y1,y2=cir_curve[i].y2;
		
		char color[15];
		strcpy(color,cir_curve[i].color);
		SetPenColor(color);
		
		//�ж����� ���� ���� ���� ���������� 
		double rx,ry;
		if ( y2 > y1 )
			{
			if ( x2 > x1 )//���� 
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
 * ���ܣ�
 *		ɾ��ͼ��ʱ�����½ṹ��
 */
void update_pattern(int i,int j)
{
	if (i==1)//���¾������� 
		{
		while (rectangle[j].x1!=0)
			{rectangle[j]=rectangle[j+1];j++;}
		rec_num--;
		}
	else if (i==2)//��Բ 
		{
		while (ellipse[j].x1 != 0)
			{ellipse[j]= ellipse[j+1];j++;}
		ell_num--;
		}
	else if (i==3)//Բ 
		{
		while (circle[j].x1 != 0)
			{circle[j]=circle[j+1];j++;}
		cir_num--;
		}
	else if (i==4)//���� 
		{
		while (  line[j].x1 != 0 )
			{line[j]= line[j+1];j++;}
		line_num--;
		}	
	else if (i==5)//�ܵ��� 
		{
		while (runway[j].x1 != 0)
			{runway[j] = runway[j+1];j++;}
		run_num--;
		}
	else if (i==6) //�ı��� 
		{
		while (text[j].x1 != text[j].x2)
			{text[j] = text[j+1];j++;}
		text_num--;
		}
	else if (i==7)//���� 
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

