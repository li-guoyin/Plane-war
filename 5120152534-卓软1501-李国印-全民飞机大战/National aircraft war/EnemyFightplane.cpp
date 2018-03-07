/*@auther lgy
* time:1/5
*/
#include "EnemyFightplane.h"
#include <time.h>
#include <iostream>
using namespace std;
#include "Manager.h"

CEnemyFightplane::CEnemyFightplane()
{
	
}
//重载函数  传递数据
CEnemyFightplane::CEnemyFightplane(IplImage *plane[], IplImage *bullet[])
{
	int i;
	for (i = 0; i < 4; i++)
	{
		m_plane[i] = plane[i];
	}
	for (i = 0; i < 6; i++)
	{
		m_bullet[i] = bullet[i];
	}
	InitData();
}

CEnemyFightplane::~CEnemyFightplane()
{
}
//为重玩游戏 初始化数据，随机参生一种飞机
void CEnemyFightplane::InitData()
{
	m_pan = 1;
	time_t t;
	srand((unsigned)time(&t));
	m_choose = rand() % 4;
	m_timer = 0;
	m_pretimer = 0;
	if (m_choose == 0)
	{
		m_posx = (150 * (rand() % 2 + 1));
		m_posy = -60;
		m_dix = 0;
		m_diy = 4;
		m_blood = 200;
		m_value = 30;
		m_attack = 50;
		m_Isclear = false;
		m_timerCD = 2000;
	}
	if (m_choose == 1)
	{
		m_posx = rand() % (512 - 100) + 10;
		m_posy = -60;
		m_dix = (1 - 2 * (rand() % 2)) * 2;
		m_diy = 4;
		m_blood = 200;
		m_value = 50;
		m_attack = 50;
		m_Isclear = false;
		m_timerCD = 2000;
	}
	if (m_choose == 2)
	{
		m_posx = rand() % (512 - 100) + 10;
		m_posy = -65;
		m_dix = (1 - 2 * (rand() % 2)) * 2;
		m_diy = 4;
		m_blood = 300;
		m_value = 100;
		m_attack = 100;
		m_Isclear = false;
		m_timerCD = 3000;
	}
	if (m_choose == 3)
	{
		m_posx = rand() % (512 - 100) + 10;
		m_posy = -80;
		m_dix = 0;
		m_diy = 4;
		m_blood = 400;
		m_value = 100;
		m_attack = 200;
		m_Isclear = false;
		m_timerCD = 1500;
	}
}

//绘制飞机
void CEnemyFightplane::Draw(IplImage *bg)
{
	if (m_Isclear == true) return;
	m_nowplane = m_plane[m_choose];
	m_Isclear = false;
	int i, j;
	for (i = 0; i < m_nowplane->height;i++)
	{
		for (j = 0; j < m_nowplane->width;j++)
		{
			int b = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 2);
			if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
			if (i + m_posy < 0 || i + m_posy > bg->height || j + m_posx < 0 || j + m_posx > bg->width) continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
}
//移动飞机
void CEnemyFightplane::Move(int height, int width)
{
	m_posx += m_dix;
	m_posy += m_diy;
	if (m_posx <= 5) m_dix = -m_dix;
	if (m_posx >= width - m_nowplane->width-10) m_dix = -m_dix;
	if (m_posy > height)
	{
		m_Isclear = true;
	}
}

void CEnemyFightplane::Attack(CManager *manger)
{
	if (m_timer>=m_timerCD)
	{
		m_timer = 0;
		//各类飞机有自己的发弹方式
		if (m_choose == 0)
		{
			manger->BullteCreat(m_bullet[0], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height , 0, 5, m_attack, 1);
		}
		if (m_choose == 1)
		{
			manger->BullteCreat(m_bullet[0], m_posx - m_bullet[0]->width / 2, m_posy + m_nowplane->height, 0,4 , m_attack, 1);
			manger->BullteCreat(m_bullet[0], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height , 0, 4, m_attack, 1);
			manger->BullteCreat(m_bullet[0], m_posx + m_nowplane->width - m_bullet[0]->width/2, m_posy + m_nowplane->height , 0, 4, m_attack, 1);
		}
		if (m_choose == 2)
		{
			manger->BullteCreat(m_bullet[0], m_posx + (m_nowplane->width - m_bullet[0]->width) / 4, m_posy + m_nowplane->height, 0, 4, m_attack, 1);
			manger->BullteCreat(m_bullet[0], m_posx + m_nowplane->width - (m_nowplane->width - m_bullet[0]->width) / 4, m_posy + m_nowplane->height, 0, 4, m_attack, 1);
		}
		if (m_choose == 3)
		{
			manger->BullteCreat(m_bullet[5], m_posx +m_bullet[4]->width/2, m_posy + m_nowplane->height , 0, 7, m_attack, 3);
			manger->BullteCreat(m_bullet[5], m_posx + m_nowplane->width - 3*m_bullet[4]->width/2 , m_posy + m_nowplane->height, 0, 7, m_attack, 3);
		}
	}
	m_timer += clock() - m_pretimer;
	m_pretimer = clock();
}
