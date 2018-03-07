/*@auther lgy
* time:1/5
*/
#include "Award.h"
#include <ctime>
CAward::CAward()
{
}
CAward::CAward(IplImage *aw[],int speed)//无尽模式星星
{
	for (int i = 0; i < 7;i++)
	{
		m_award[i] = aw[i];
	}
	time_t t;
	srand((unsigned)time(&t));
	m_choose = rand() % 7;
	m_Isclear = false;
	m_awardti = m_award[m_choose];
	m_posx = rand() % 400 + 60;
	m_posy = -70;
	m_diy = speed;
	m_dix = 0;
}

CAward::CAward(IplImage *bomb[],int model,int speed,int model1)//model用来区分是星星还是炸弹
{
	for (int i = 0; i < 4;i++)
	{
		m_award[i] = bomb[i];
	}
	time_t t;
	srand((unsigned)time(&t));
	int key = rand() % 7;
	m_Isclear = false;
	switch (key)
	{
	case 0:m_posx = 10; break;
	case 1:m_posx = 80; break;
	case 2:m_posx = 150; break;
	case 3:m_posx = 220; break;
	case 4:m_posx = 290; break;
	case 5:m_posx = 360; break;
	case 6:m_posx = 410; break;
	case 7:m_posx = 480; break;
	}
	m_choose = key % 4;
	m_awardti = m_award[m_choose];
	m_posy = -70;
	m_diy = speed;
	m_dix = 0;
}

CAward::CAward(IplImage *aw[], int posx, int posy)//普通模式
{
	for (int i = 0; i < 7; i++)
	{
		m_award[i] = aw[i];
	}
	time_t t;
	srand((unsigned)time(&t));
	m_choose = rand() % 7;
	m_Isclear = false;
	m_awardti = m_award[m_choose];
	m_posx = posx;
	m_posy = posy;
	m_diy = 5;
	m_dix = 0;
}

CAward::~CAward()
{
}

void CAward::Draw(IplImage *bg)
{
	if (m_Isclear == true) return;
	m_Isclear = false;
	m_awardti = m_award[m_choose];
	int i, j;
	for (i = 0; i < m_awardti->height; i++)
	{
		for (j = 0; j < m_awardti->width; j++)
		{
			int b = CV_IMAGE_ELEM(m_awardti, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(m_awardti, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(m_awardti, uchar, i, j * 3 + 2);
			if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 185) continue;
			if (i + m_posy<0 || i + m_posy>bg->height || j + m_posx<0 || j + m_posx>bg->width) continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
}

void CAward::Move(int width, int height)
{
	m_posx = m_posx;
	m_posy += m_diy;
	if (m_posy > height - m_awardti->height) m_Isclear = true;  //出界就销毁
}

void CAward::Destory()
{
	m_Isclear = true;
}

bool CAward::Isclear()
{
	return m_Isclear;
}
