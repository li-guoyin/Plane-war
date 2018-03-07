/*@auther lgy
* time:1/5
*/
#include "EnemyBossplane.h"
#include <time.h>
#include<iostream>
using namespace std;
#include "Manager.h"
CEnemyBossplane::CEnemyBossplane()
{
}
//重载函数 传入数据
CEnemyBossplane::CEnemyBossplane(IplImage *plane[], IplImage *bullet[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		m_plane[i] = plane[i];
	}
	for (i = 0; i < 7; i++)
	{
		m_bullet[i] = bullet[i];
	}
	InitData();
	
}

CEnemyBossplane::~CEnemyBossplane()
{
}

//为重玩游戏，初始化敌方boss飞机的属性 ，随机参生一种飞机
void CEnemyBossplane::InitData()
{
	m_pan = 0;
	m_timer = 0;
	m_pretimer = 0;
	m_timerCD = 5000;
	m_contral = 0;
	time_t t;
	srand((unsigned)time(&t));
	m_choose = rand() % 3;
	if (m_choose == 0)
	{
		m_posx = 250;
		m_posy = -105;
		m_dix = (1 - 2 * (rand() % 2)) * 2;
		m_diy = 1;
		m_blood = 5000;
		m_value = 500;
		m_attack = 100;
		m_Isclear = false;
	}
	if (m_choose == 1)
	{
		m_posx = 250;
		m_posy = -165;
		m_dix = (1 - 2 * (rand() % 2)) * 2;
		m_diy = 1;
		m_blood = 7000;
		m_value = 1000;
		m_attack = 150;
		m_Isclear = false;
	}
	if (m_choose == 2)
	{
		m_posx = 250;
		m_posy = -135;
		m_dix = (1 - 2 * (rand() % 2)) * 2;
		m_diy = 1;
		m_blood = 8000;
		m_value = 2000;
		m_attack = 200;
		m_Isclear = false;
	}
}

//绘制boss飞机
void CEnemyBossplane::Draw(IplImage *bg)
{
	if (m_Isclear == true) return;
	m_nowplane = m_plane[m_choose];
	int i, j;
	for (i = 0; i < m_nowplane->height;i++)
	{
		for (j = 0; j < m_nowplane->width;j++)
		{
			int b = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 2);
			if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
			if (i + m_posy<0 || i + m_posy>bg->height || j + m_posx<0 || j + m_posx>bg->width) continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
}

//飞机移动
void CEnemyBossplane::Move(int height, int width)
{
	m_posx += m_dix;
	m_posy += m_diy;
	if (m_posx == 10) m_dix = -m_dix;
	if (m_posx == width - m_nowplane->width - 10) m_dix = -m_dix;
	if (m_contral == 0 && m_posy == 10)
	{
		m_contral = 1;
	}
	if (m_contral == 1 && m_posy == 9) m_diy = -m_diy;
	if (m_posy == height/3) m_diy = -m_diy;
}

//攻击
void CEnemyBossplane::Attack(CManager *manger)
{
	if (m_timer >= m_timerCD)
	{
		m_timer = 0;
		time_t t;
		srand((unsigned)time(&t));
		int key = rand() % 3;
		//产生子弹，三种发弹方式
		if (key == 0)
		{
			manger->BullteCreat(m_bullet[6], m_posx - m_bullet[0]->width / 2, m_posy + m_nowplane->height / 2, -2, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + 2 * m_bullet[0]->width, m_posy + 3 * m_nowplane->height / 4, -1, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, 0, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + m_nowplane->width - 3 * m_bullet[0]->width, m_posy + 3 * m_nowplane->height / 4, 1, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + m_nowplane->width - m_bullet[0]->width, m_posy + m_nowplane->height / 2, 2, 5, m_attack, 2);
		}
		else if (key == 1)
		{
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, -5, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, -3, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, -1, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, 0, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, 1, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, 3, 5, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height, 5, 5, m_attack, 2);

		}
		else
		{
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, -2, -13, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, -4, 2, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, -3, 6, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, 0, 8, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, 3, 6, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, 4, 2, m_attack, 2);
			manger->BullteCreat(m_bullet[6], m_posx + (m_nowplane->width - m_bullet[0]->width) / 2, m_posy + m_nowplane->height / 2, 2, -13, m_attack, 2);
		}
	}
	m_timer += clock() - m_pretimer;
	m_pretimer = clock();
}
