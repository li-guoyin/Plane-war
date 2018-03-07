/*@auther lgy
* time:1/5
*/
#include "Myplane.h"
#include <windows.h>
#include <ctime>
#include "Manager.h"
//���캯��
CMyplane::CMyplane()
{
	InitData();
}

CMyplane::~CMyplane()
{
}
//��ʼ������
void CMyplane::InitData()
{
	for (int i = 0; i < 9; i++)
	{
		myplane[i] = myPlplane[i];
	}
	m_choose = 0;
	m_timer = 0;
	m_pretimer = 0;
	m_timerCD = 200;
	m_posx = 200;
	m_posy = 400;
	Speed = 7;
	m_attack = 100;
	m_blood = 3000;
	m_Isclear = false;
	panduan = true;
	m_index = 0;
	m_speed = 5;
}

//��ʼ��ͼƬ
void CMyplane::SetNowImg(IplImage *planepu[], IplImage *planegl[], IplImage *planepl[], IplImage *bullet[])
{
	int i;
	for (i = 0; i < 9;i++)
	{
		myPlplane[i] = planepl[i];
		myGlplane[i] = planegl[i];
		myPuplane[i] = planepu[i];
		myplane[i] = myPlplane[i];
	}
	
	for (i = 0; i < 5;i++)
	{
		m_bullte[i] = bullet[i];
	}
}

//�ɻ��ı仯����
void CMyplane::PlaneChoose(int buffnumber)
{
	if (buffnumber == 0)
	{
		//nowmyplane = myplane[0];
		for (int i = 0; i < 9; i++)
		{
			myplane[i] = myPlplane[i];
		}
		m_choose = 0;
		m_timer = 0;
		m_pretimer = 0;
		m_timerCD = 200;
		//m_blood = 5000;
		m_attack = 100;
	}
	if (buffnumber == 1 )
	{
		for (int i = 0; i < 9; i++)
		{
			myplane[i] = myGlplane[i];
		}
		m_nowplane = myplane[1];
		m_choose = 1;
		m_timer = 0;
		m_pretimer = 0;
		m_timerCD = 500;
		//m_blood = 5000;
		m_attack = 150;
	}
	if (buffnumber == 2)
	{
		for (int i = 0; i < 9; i++)
		{
			myplane[i] = myPuplane[i];
		}
		m_choose = 2;
		m_timer = 0;
		m_pretimer = 0;
		m_timerCD = 700;
		//m_blood = 5000;
		m_attack = 200;
	}
}

//���Ʒɻ�
void CMyplane::Draw(IplImage *bg)
{
	if (m_Isclear == true) return;
	m_Isclear = false;
	m_nowplane = myplane[m_index / m_speed];
	int i, j;
	for (i = 0; i < m_nowplane->height; i++)
	{
		for (j = 0; j < m_nowplane->width; j++)
		{
			int b = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(m_nowplane, uchar, i, j * 3 + 2);
			if (b <= 255 && b>200 && g <= 255 && g>200 && r <= 255 && r>200)  continue;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
	if(panduan == true) m_index++;
	else  m_index--;
	if (m_index / m_speed == 8) panduan = false;
	if (m_index / m_speed == 0) panduan = true;
}

//�ɻ����ƶ�
void CMyplane::Move(int height,int width)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_posy = m_posy - Speed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_posy = m_posy + Speed;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_posx = m_posx - Speed;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_posx = m_posx + Speed;
	}
	//�жϷɻ��Ƿ����
	if (m_posx < 0) m_posx = 0;
	if (m_posy < 0) m_posy = 0;
	if (m_posx >width - m_nowplane->width)  m_posx = width - m_nowplane->width;
	if (m_posy >height - m_nowplane->height) m_posy = height - m_nowplane->height;
}

//�ɻ��Ĺ���
void CMyplane::Attack(CManager * manger)
{
	if (GetAsyncKeyState('J') & 0x8000)
	{
		if (m_timer>=m_timerCD)
		{
			m_timer = 0;
			if (m_choose == 0)
			{
				manger->BullteCreat(m_bullte[1], m_posx + (m_nowplane->width - m_bullte[1]->width) / 2, m_posy - (m_bullte[1]->height), 0, -6, m_attack, 0);
			}
			if (m_choose == 1)
			{
				manger->BullteCreat(m_bullte[2], m_posx - m_bullte[2]->width / 2 + 10, m_posy - (m_bullte[2]->height), 0, -5, m_attack, 0);
				manger->BullteCreat(m_bullte[2], m_posx + (m_nowplane->width - m_bullte[1]->width) / 2, m_posy - (m_bullte[2]->height), 0, -5, m_attack, 0);
				manger->BullteCreat(m_bullte[2], m_posx + m_nowplane->width - m_bullte[2]->width / 2 - 10, m_posy - (m_bullte[2]->height), 0, -5, m_attack, 0);
			}
			if (m_choose == 2)
			{
				manger->BullteCreat(m_bullte[4], m_posx - m_bullte[4]->width / 2 + 10, m_posy - (m_bullte[4]->height), 0, -5, m_attack, 0);
				manger->BullteCreat(m_bullte[3], m_posx + (m_nowplane->width - m_bullte[3]->width) / 2, m_posy - (m_bullte[3]->height), 0, -5, m_attack, 0);
				manger->BullteCreat(m_bullte[4], m_posx + m_nowplane->width - m_bullte[4]->width / 2 - 10, m_posy - (m_bullte[4]->height), 0, -5, m_attack, 0);
			}
		}
	}
	m_timer += clock() - m_pretimer;
	m_pretimer = clock();
}

int CMyplane::GetBlood()
{
	return m_blood;
}

//�Ե����ߣ���Ѫ��
void CMyplane::AddBlood()
{
	m_blood += 500;
	if (m_blood >= 3000) m_blood = 3000;
}

