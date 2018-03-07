/*@auther lgy
* time:1/5
*/
#include "EnemyPlane.h"
#include <time.h>
#include "Manager.h"
CEnemyPlane::CEnemyPlane()
{
}

//重载函数 
CEnemyPlane::CEnemyPlane(IplImage *plane[])
{
	int i;
	for (i = 0; i < 2; i++)
	{
		enemyplane[i] = plane[i];
	}
	InitData();
}

CEnemyPlane::~CEnemyPlane()
{
}

//初始化数据
void CEnemyPlane::InitData()
{
	m_pan = 2;
	time_t t;
	srand((unsigned)time(&t));
	m_Isclear = false;
	m_posx = 50;
	m_posy = -60;
	m_dix = (1 - 2 * (rand() % 2)) * 2;
	m_diy = 3;
	m_choose = rand() % 2;
	m_blood = 100;
	m_value = 10;
}

void  CEnemyPlane::Draw(IplImage *bg)
{
	
	if (m_Isclear == true) return;
	m_Isclear = false;
	m_nowplane = enemyplane[m_choose];
	int i, j;
	for (i = 0; i < m_nowplane->height; i++)
	{
		for (j = 0; j < m_nowplane->width; j++)
		{
			int b = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 2);
			if (b == 91 && g == 132 && r == 178)  continue;
			if (m_posy + i<0 || m_posy + i>bg->height || m_posx + j<0 || m_posx + j>bg->width) continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
}

void CEnemyPlane::Move(int height, int width)
{
	m_posx += m_dix;
	m_posy += m_diy;
	if (m_posx == 0) m_dix = -m_dix;
	if (m_posx == width - m_nowplane->width) m_dix = -m_dix;
	if (m_posy > height)
	{
		m_Isclear = true;
	}
}

void CEnemyPlane::Attack(CManager *manger)
{

}
