/*@auther lgy
* time:1/5
*/
#include "GameUI.h"
#include "Manager.h"
#include "Myplane.h"
#include <ctime>
//重载函数
CGameUI::CGameUI()
{
	mpos = 0;
	speed = 2;
	timer = 0;
	timercd = 500;
	pretimer = 0;
	passUIclear = false;
	m_choose = 0;
}

CGameUI::~CGameUI()
{
}


//设置背景图片
void CGameUI::SetBgImage(IplImage * map[], IplImage *num1[], IplImage *blood1,IplImage *st)
{
	int i;
	for (i = 0; i < 10;i++)
	{
		num[i] = num1[i];
	}
	for (i = 0; i < 4;i++)
	{
		bg[i] = map[i];
	}
	blood = blood1;
	star = st;
	nowbg = map[0];
	clonebg = cvCloneImage(nowbg);
	clonebg1 = clonebg;
}
//初始化
void CGameUI::InitBg()
{
	//nowbg = bg[0];
	clonebg = clonebg1; //cvCloneImage(clonebg1);
}
//图像滚动
void CGameUI::Build()
{
	mpos -= speed;
	if (mpos < 0) mpos += clonebg->height;
	for (int i = 0; i < clonebg->height; i++)
	{
		for (int j = 0; j < clonebg->width; j++)
		{
			int b = CV_IMAGE_ELEM(clonebg, uchar, (mpos + i) % clonebg->height, j * 3);
			int g = CV_IMAGE_ELEM(clonebg, uchar, (mpos + i) % clonebg->height, j * 3 + 1);
			int r = CV_IMAGE_ELEM(clonebg, uchar, (mpos + i) % clonebg->height, j * 3 + 2);

			CV_IMAGE_ELEM(nowbg, uchar, i, j * 3 + 0) = b;
			CV_IMAGE_ELEM(nowbg, uchar, i, j * 3 + 1) = g;
			CV_IMAGE_ELEM(nowbg, uchar, i, j * 3 + 2) = r;
		}
	}
}
//绘制在界面的分数

void CGameUI::NumberDraw(int numb, int x, int y)
{
	int number = numb;
	int pox = x, poy = y;
	int yu, i, j;
	do
	{
		yu = number % 10;
		number = number / 10;
		for (i = 0; i < num[yu]->height; i++)
		{
			for (j = 0; j < num[yu]->width; j++)
			{
				int b = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 0);
				int g = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 1);
				int r = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 2);
				if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
				CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 0) = b;
				CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 1) = g;
				CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 2) = r;
			}
		}
		pox -= num[yu]->width;
	} while (number != 0);
}

void CGameUI::ScoreDraw(CManager *manger)
{
	NumberDraw(manger->GetGrade(), 480, 10);
}
//绘制星星得分前的那颗星星
void CGameUI::StarDraw(CManager *manger)
{
	int m_posx = 480, m_posy = 50;
	int i, j;
	for (i = 0; i < star->height; i++)
	{
		for (j = 0; j < star->width; j++)
		{
			int b = CV_IMAGE_ELEM(star, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(star, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(star, uchar, i, j * 3 + 2);
			if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 185) continue;
			//if (i + m_posy < 0 || i + m_posy > bg->height || j + m_posx < 0 || j + m_posx > bg->width) continue;
			CV_IMAGE_ELEM(nowbg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(nowbg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(nowbg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
	NumberDraw(manger->GetStarnum(), 440, 50);
}

//绘制血量
void CGameUI::BloodDraw(int freeblood,int allblood)
{
	int width = freeblood * (blood->width - 60) / allblood + 60;
	int pox = 10, poy = 10;
	int i, j;
	for (i = 0; i < blood->height;i++)
	{
		for (j = 0; j < width;j++)
		{
			int b = CV_IMAGE_ELEM(blood, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(blood, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(blood, uchar, i, j * 3 + 2);
			if (b == 91 && g == 132 && r == 178)  continue;
			CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 0) = b;
			CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 1) = g;
			CV_IMAGE_ELEM(nowbg, uchar, i + poy, (j + pox) * 3 + 2) = r;
		}
	}
}

void CGameUI::ShowNowbg()
{
	cvShowImage("全民飞机大战",nowbg);
}

IplImage * CGameUI::GetNowbg()
{
	return nowbg;
}

void CGameUI::SetBgPass(int key)
{
	clonebg = bg[key];
}



