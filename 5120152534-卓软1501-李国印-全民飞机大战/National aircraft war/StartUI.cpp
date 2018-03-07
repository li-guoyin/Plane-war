/*@auther lgy
* time:1/5
*/
#include "StartUI.h"
#include<windows.h>
#include <iostream>
using namespace std;
CStartUI::CStartUI()
{
	m_choose = -1;
}

CStartUI::~CStartUI()
{
}

void CStartUI::SetIplimage(IplImage *str,IplImage *UI[])
{
	startui = str;
	for (int i = 0; i < 8;i++)
	{
		ui[i] = UI[i];
	}
}

void CStartUI::Show()
{
	cvShowImage("全民飞机大战",startui);
	cvWaitKey(0);
}
//用于绘制控件
void CStartUI::Draw(int posx, int posy,int count)
{
	
	int pox = posx, poy = posy ,counter = count;
	IplImage *img[2];
	IplImage *imgti;
	img[0] = ui[counter];
	img[1] = ui[counter + 1];
	if (m_choose != -1 && m_choose == counter + 1)
	{
		imgti = img[1];
	}
	else imgti = img[0];
	int i, j;
	for (i = 0; i < imgti->height; i++)
	{
		for (j = 0; j < imgti->width; j++)
		{
			int b = CV_IMAGE_ELEM(imgti, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(imgti, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(imgti, uchar, i, j * 3 + 2);
			if (b <= 255 && b>200 && g <= 255 && g>200 && r <= 255 && r>200)  continue;
			CV_IMAGE_ELEM(startui, uchar, i + poy, (j + pox) * 3 + 0) = b;
			CV_IMAGE_ELEM(startui, uchar, i + poy, (j + pox) * 3 + 1) = g;
			CV_IMAGE_ELEM(startui, uchar, i + poy, (j + pox) * 3 + 2) = r;
		}
	}
}
//此算法用来上下选择控件
int CStartUI::DrawAll()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_choose += 2;
		if (m_choose > 5)
		{
			m_choose = 5;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_choose -= 2;
		if (m_choose < -1)
		{
			m_choose = -1;
		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		return m_choose;
	}
	int posx = 165,posy = 250;
	for (int i = 0; i < 6;)
	{
		
		Draw(posx, posy, i);
		i += 2;
		posy += 70;
	}
	return 0;
}

void CStartUI::Initchoose()
{
	m_choose = -1;
}