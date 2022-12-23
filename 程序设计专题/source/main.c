/*
 * 	���ļ�Ϊ������ 
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
//�ص��������� 
void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

//=============================================================================
// ���������

void Main()
{
	SetWindowTitle("MIND MAP");
	SetWindowSize(10, 8);
	InitGraphics();

	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	registerCharEvent(CharEventProcess);        	// ע���ַ�
	registerKeyboardEvent(KeyboardEventProcess);	// ע�����
	registerMouseEvent(MouseEventProcess);      	// ע�����
	registerTimerEvent(TimerEventProcess);      	// ע�ᶨʱ��

	Colormap();//��ʼ����ɫ�� 
	draw_interface();//������ʼ���� 
}

