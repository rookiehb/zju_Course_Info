/*
 * 	���ļ�Ϊ�Զ����ӵ�����ļ�
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

LinkList *creat();
void change(LinkList *list, int n, double x1, double x2, double y1, double y2);
void delet(LinkList *list);
void connect_pattern(LinkList *head);

//=============================================================================
// ����


/*
 * Function: creat
 * Usage: creat()
 * --------------------------------------------------------
 * ���ܣ�
 *		�����������ڼ�¼����ͼ����������Ϣ 
 */
LinkList * creat(){
	LinkList *head, *node, *end;//����ͷ�ڵ㣬��ͨ�ڵ㣬β���ڵ㣻
	head = (LinkList*)malloc(sizeof(LinkList));//�����ַ
	end = head;         //���ǿ�������ͷβ�ڵ�һ��
	int i;
	for (i = 0; i < 2; i++) 
		{
		node = (LinkList*)malloc(sizeof(LinkList));
		node->x1 = node->x2 = node->y1 = node->y2 =0;
		end->next = node;
		end = node;
		}
	end->next = NULL;//��������
	return head;
}

/*
 * Function: change
 * Usage: change(LinkList *list,int n,double x1,double x2,double y1,double y2) 
 * --------------------------------------------------------
 * ���ܣ�
 *		�ı�����ڵ����Ϣ 
 */
void change(LinkList *list,int n,double x1,double x2,double y1,double y2) 
{	
	//nΪ��n���ڵ�
	LinkList *t = list;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		t->x1 = x1;
		t->x2 = x2;
		t->y1 = y1;
		t->y2 = y2;
	}
}

/*
 * Function: delet
 * Usage:  delet(LinkList *list) 
 * --------------------------------------------------------
 * ���ܣ�
 *		������ߺ�ɾ������ 
 */
void delet(LinkList *list) 
{	
	//ֻ��������Ч��Ϣ 
	LinkList *t1=list,*t2,*t3;
	t2 = list->next;
	t3 = t2->next;
	
	t3->x1 = t3->x2 = t3->y1 = t3->y2 =0;
	t2->next =NULL;
	free(t3);
	
	t2->x1 = t2->x2 = t2->y1 = t2->y2 =0;
	t1->next = NULL;
	free(t2);
	
	list->next=NULL;
	free(list);
}

/*
 * Function: connect_pattern
 * Usage:  connect_pattern(LinkList *head)
 * --------------------------------------------------------
 * ���ܣ�
 *		�ж�λ�ã�������� 
 */
void connect_pattern(LinkList *head)
{
	LinkList *t1 = head,*t2,*t3;
	t2 = head->next;
	t3 = t2->next;
	
	if (( t3->x1-t2->x1>0.001 && t3->x1-t2->x2>0.001 )|| ( t3->x2-t2->x1>0.001 && t3->x2-t2->x2>0.001 ) )
		drawellcurve(MIN(t3->x1,t3->x2) ,(t3->y1+t3->y2)/2 ,MAX(t2->x1,t2->x2) ,(t2->y1+t2->y2)/2 ,-1,-1);
	else if (  (t2->x1-t3->x1>0.001 && t2->x1-t3->x2>0.001 )|| ( t2->x2-t3->x1>0.001 && t2->x2-t3->x2>0.001 ) )
		drawellcurve(MIN(t2->x1,t2->x2),(t2->y1+t2->y2)/2 ,MAX(t3->x1,t3->x2),(t3->y1+t3->y2)/2 ,-1,-1);
}


