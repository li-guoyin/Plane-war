/*@auther lgy
* time:1/5
*/
#include "BuffTool.h"
#include <ctime>

CBuffTool::CBuffTool()
{
}
//重载函数 随机生成一个道具
CBuffTool::CBuffTool(IplImage *buff[])
{
	for (int i = 0; i < 2;i++)
	{
		bufftool[i] = buff[i];
	}
	time_t t;
	srand((unsigned)time(&t));  //产生随机数
	m_choose = rand() % 2;
	buffnow = bufftool[m_choose];
	m_posx = rand() % (512 - 100) + 10;
	m_posy = -60;
	m_dix = (1 - 2 * (rand() % 2)) * 2;
	m_diy = 3;
	m_Isclear = false;
	
}

CBuffTool::~CBuffTool()
{
}
//绘制道具
void CBuffTool::Draw(IplImage *bg)
{
	int i, j;
	for (i = 0; i < buffnow->height;i++)
	{
		for (j = 0; j < buffnow->width;j++)
		{
			int b = CV_IMAGE_ELEM(buffnow, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(buffnow, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(buffnow, uchar, i, j * 3 + 2);
			if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
			if (i + m_posy < 0 || i + m_posy > bg->height || j + m_posx < 0 || j + m_posx > bg->width) continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
}
//道具的移动
void CBuffTool::Move(int height, int width)
{
	m_posx += m_dix;
	m_posy += m_diy;
	if (m_posx <= 5) m_dix = -m_dix;  //判断是否出界
	if (m_posx >= width - buffnow->width - 10) m_dix = -m_dix;
	if (m_Isclear == false && m_posy == 15)
	{
		m_Isclear = true;
	}
	if (m_Isclear == true && m_posy == 9) m_diy = -m_diy;
	if (m_posy >= height - buffnow->height - 15) m_diy = -m_diy;
}

int CBuffTool::GetNowX()
{
	return m_posx;
}

int CBuffTool::GetNowY()
{
	return m_posy;
}

IplImage *CBuffTool::GetNowImg()
{
	return buffnow;
}

int CBuffTool::GetChoose()
{
	return m_choose;
}