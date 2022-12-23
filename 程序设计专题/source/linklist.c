/*
 * 	该文件为自动连接的相关文件
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

LinkList *creat();
void change(LinkList *list, int n, double x1, double x2, double y1, double y2);
void delet(LinkList *list);
void connect_pattern(LinkList *head);

//=============================================================================
// 函数


/*
 * Function: creat
 * Usage: creat()
 * --------------------------------------------------------
 * 功能：
 *		生成链表，用于记录连接图案的坐标信息 
 */
LinkList * creat(){
	LinkList *head, *node, *end;//定义头节点，普通节点，尾部节点；
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	end = head;         //若是空链表则头尾节点一样
	int i;
	for (i = 0; i < 2; i++) 
		{
		node = (LinkList*)malloc(sizeof(LinkList));
		node->x1 = node->x2 = node->y1 = node->y2 =0;
		end->next = node;
		end = node;
		}
	end->next = NULL;//结束创建
	return head;
}

/*
 * Function: change
 * Usage: change(LinkList *list,int n,double x1,double x2,double y1,double y2) 
 * --------------------------------------------------------
 * 功能：
 *		改变链表节点的信息 
 */
void change(LinkList *list,int n,double x1,double x2,double y1,double y2) 
{	
	//n为第n个节点
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
 * 功能：
 *		完成连线后，删除链表 
 */
void delet(LinkList *list) 
{	
	//只有两层有效信息 
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
 * 功能：
 *		判断位置，完成连线 
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


