/*@auther lgy
* time:1/5
*/
#include "Manager.h"
#include<windows.h>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <cmath>
#include <iostream>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
using namespace std;
CManager::CManager()
{
	//cvNamedWindow("全民飞机大战-菜单");
	
}

CManager::CManager(string user)
{
	cvNamedWindow("全民飞机大战");
	m_state = GameStart;
	n = 0;
	m_name = user;
}

CManager::~CManager()
{
}
//初始化游戏图片资源
void CManager::InitGameResource()
{
	
	m_resource.InitResource();

	m_gameUI.SetBgImage(m_resource.map,m_resource.number,m_resource.blood,m_resource.star);
	m_myplane.SetNowImg(m_resource.myPuplane, m_resource.myGlplane,m_resource.myPlplane,m_resource.bultte);
	m_endui.SetIplimage(m_resource.endUI, m_resource.number);
}
//释放游戏图片资源指针
void CManager::ReleaseGameRes()
{
	m_resource.ReleaseIplimage();
}
//运行游戏
void CManager::Run()
{
	while (1)
	{
		switch (m_state)
		{
		case CManager::GameStart:  //游戏开始界面
			//PlaySound(TEXT(".\\resource\\music\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			m_startui.SetIplimage(m_resource.startUI, m_resource.ui);
		    n = m_startui.DrawAll();//选择模式
			if (n == 1)  ResterGameInit();    //无尽模式
			if (n == 3)  ResterGameInit();//普通模式
			if (n == 5)  return; //返回退出
			m_startui.Show();
			break;
		case CManager::GameRunning:  //游戏开始运行
			if (n == 3)//一般模式
			{
				m_gameUI.Build();
				if (m_beclearednum % 10 == 0 && m_GradeNumber != 0 && m_bossAlive == false)
				{
					m_GradeNumber += 100;
					m_bossplane = new CEnemyBossplane(m_resource.enemybossplane, m_resource.bultte);
					m_plane.push_back(m_bossplane);
					m_bossAlive = true;
				}
				TimeUpdata();
				EnemyPlaneUpdata();
				if (m_buffAlive == true) BuffUpdata();
				MyplaneUpdata();
				BullteUpdata();
				EffectUpdata();
				AwardUpdata();
				Crash();
				m_gameUI.ScoreDraw(this);
				m_gameUI.StarDraw(this);
				m_gameUI.BloodDraw(m_myplane.GetBlood(), 3000);
				m_gameUI.ShowNowbg();
			}
			else if ( n==1 )//无尽模式
			{
				m_gameUI.Build();
				Timeupdata_1();
				AwardUpdata();
				MyplaneUpdata();
				Crash();
				m_gameUI.StarDraw(this);
				m_gameUI.BloodDraw(m_myplane.GetBlood(), 3000);
				m_gameUI.ShowNowbg();
			}
			if (m_myplane.IsClear() == true || (m_bgChoose == 5&&m_bossAlive == false))
			{
				m_state = GameEnd;
			}
			break;
		case CManager::GameEnd:  //游戏结束
			PlaySound(TEXT(".\\resource\\music\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			if (m_IsSaveTxt == false)
			{
				if (n == 1)  m_endui.DrawwjGrade(this);
				m_endui.ShowGrade(this);
				m_IsSaveTxt = true;
			}
			m_endui.Show();
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				m_state = GameStart;
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				return;
			}
			break;
		}

		cvWaitKey(15);
	}
}

void CManager::MyplaneUpdata()  //我方飞机更新
{
	IplImage *bg = m_gameUI.GetNowbg();
	m_myplane.Draw(bg);
	m_myplane.Move(bg->height, bg->width);
	m_myplane.Attack(this);
}

void CManager::EnemyPlaneUpdata() //敌方飞机更新
{
	IplImage *bg = m_gameUI.GetNowbg();
	int i;
	for (i = 0; i < m_plane.size();i++)
	{
		m_plane[i]->Draw(bg);
		m_plane[i]->Move(bg->height, bg->width);
		m_plane[i]->Attack(this);
	}
}

//特效更新 
void CManager::EffectUpdata()
{
	int i;
	IplImage *bg = m_gameUI.GetNowbg();
	for (i = 0; i < m_effect.size();i++)
	{
		m_effect[i]->Draw(bg);
	}
	for (i = 0; i < m_effect.size();i++)
	{
		if (m_effect[i]->Isclear() == true)
		{
			delete m_effect[i];
			m_effect.erase(m_effect.begin() + i);
		}
	}
}
//星星,炸弹更新
void CManager::AwardUpdata()
{
	int i;
	IplImage *bg = m_gameUI.GetNowbg();
	for (i = 0; i < m_award.size(); i++)
	{
		m_award[i]->Draw(bg);
		m_award[i]->Move(bg->width, bg->height);
	}
	for (i = 0; i < m_award.size(); i++)
	{
		if (m_award[i]->Isclear() == true)
		{
			delete m_award[i];
			m_award.erase(m_award.begin() + i);
		}
	}
	for (i = 0; i < m_bomb.size();i++)
	{
		m_bomb[i]->Draw(bg);
		m_bomb[i]->Move(bg->width, bg->height);
	}
	for (i = 0; i < m_bomb.size();i++)
	{
		if (m_bomb[i]->Isclear() == true)
		{
			delete m_bomb[i];
			m_bomb.erase(m_bomb.begin() + i);
		}
	}
}
//buff更新
void CManager::BuffUpdata()
{
	IplImage *bg = m_gameUI.GetNowbg();
	m_buff->Draw(bg);
	m_buff->Move(bg->height, bg->width);
}
//子弹创建
void CManager::BullteCreat(IplImage *bulltImg, int posx, int posy, int dix, int diy, int attack,int type) //子弹的创建
{
	if (type == 0) //我方子弹
	{
		m_myplaneBullet.push_back(new CBullet(bulltImg, posx, posy, dix, diy, attack,type));
	}
	if (type == 1 || type == 3)//敌方子弹
	{
		m_Bullet.push_back(new CBullet(bulltImg, posx, posy, dix, diy, attack,type));
	}
	if (type == 2)//boss子弹
	{
		m_Bullet.push_back(new CBullet(bulltImg, posx, posy, dix, diy, attack,type));
	}
}
//子弹绘制
void CManager::BullteDraw()
{
	int i;
	IplImage *bg = m_gameUI.GetNowbg();
	for (i = 0; i < m_myplaneBullet.size(); i++)
	{
		m_myplaneBullet[i]->Draw(bg);
	}
	for (i = 0; i < m_Bullet.size();i++)
	{
		m_Bullet[i]->Draw(bg);
	}
}
//子弹移动
void CManager::BullteMove()
{
	int i;
	IplImage *bg = m_gameUI.GetNowbg();
	for (i = 0; i < m_myplaneBullet.size(); i++)
	{
		m_myplaneBullet[i]->Move(bg->height, bg->width, m_myplane.GetNowX()+m_myplane.GetNowImg()->width/2,m_myplane.GetNowY()+m_myplane.GetNowImg()->height/2);
	}
	for (i = 0; i < m_Bullet.size(); i++)
	{
		m_Bullet[i]->Move(bg->height, bg->width, m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2, m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2);
	}
	
}
//子弹清除
void CManager::BullteClear()
{
	int i;
	for (i = 0; i < m_myplaneBullet.size();i++)
	{
		if (m_myplaneBullet[i]->IsClear() == true)
		{
			delete m_myplaneBullet[i];
			m_myplaneBullet.erase(m_myplaneBullet.begin() + i);
		}
	}
	for (i = 0; i < m_Bullet.size(); i++)
	{
		if (m_Bullet[i]->IsClear() == true)
		{
			delete m_Bullet[i];
			m_Bullet.erase(m_Bullet.begin() + i);
		}
	}
}

void CManager::BullteUpdata()
{
	BullteMove();
	BullteDraw();
	BullteClear();
}
//动态生成敌方飞机
void CManager::AddEnemyPlane()
{
	m_enemyplane = new CEnemyPlane(m_resource.enemyplane);
	m_plane.push_back(m_enemyplane);
	m_fightplane = new CEnemyFightplane(m_resource.enemyfightplane, m_resource.bultte);
	m_plane.push_back(m_fightplane);
}
//时间更新
void CManager::TimeUpdata()
{
	if (m_timer>=m_timerCD)
	{
		m_timer = 0;
		AddEnemyPlane();
	}
	if (m_buffAlive == false)
	{
		if (m_timer1 >= m_timerCD1)
		{
			m_timer1 = 0;
			m_buffAlive = true;
			m_buff = new CBuffTool(m_resource.buff);
		}
		m_timer1 += clock() - m_pretimer;
	}
	
	if (m_buffaccpet == true)
	{
		if (m_timer2 >= m_timerCD2)
		{
			m_timer2 = 0;
			m_buffnumber = 0;
			m_myplane.PlaneChoose(m_buffnumber);
			m_buffaccpet = false;
		}
		m_timer2 += clock() - m_pretimer;
	}
	
	m_timer  += clock() - m_pretimer;
	m_pretimer = clock();
}

void CManager::Timeupdata_1()
{
	if (m_timer3 >= m_timerCD3)
	{
		m_timer3 = 0;
		m_award.push_back(new CAward(m_resource.m_award,m_starspeed));
		m_bomb.push_back(new CAward(m_resource.bomb,0,m_starspeed+2,1));
	}
	if (m_timer4 >= m_timerCD4)
	{
		m_timer4 = 0;
		m_starspeed++;
		m_timerCD3--;
	}
	m_timer3 += clock() - m_pretimer;
	m_timer4 += clock() - m_pretimer;
	m_pretimer = clock();
}
//普通模式碰撞函数
void CManager::Crash()
{
	int i, j;
	//敌机与我方飞机碰撞
	if (n == 3)
	{
		for (i = 0; i < m_plane.size(); i++)
		{
			int cx = m_plane[i]->GetNowX() + m_plane[i]->GetNowImg()->width / 2;
			int cy = m_plane[i]->GetNowY() + m_plane[i]->GetNowImg()->height / 2;

			int tx = m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2;
			int ty = m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2;
			if (abs(tx - cx) < m_plane[i]->GetNowImg()->width / 2 + m_myplane.GetNowImg()->width / 4 &&
				abs(ty - cy) < m_plane[i]->GetNowImg()->height / 2 + m_myplane.GetNowImg()->height / 4)
			{
				m_myplane.Destory(30);
				m_plane[i]->Destory(30);
				if (m_plane[i]->IsClear() == true)
				{
					if (m_plane[i]->GetJudge() == 0) //判断碰的的飞机是否是boss
					{
						if (m_bgChoose < 4) m_gameUI.SetBgPass(m_bgChoose);
						else  m_gameUI.SetBgPass(3);
						m_bgChoose += 1;
						m_timerCD -= 200;
						m_bossAlive = false;
						m_beclearednum = 0;
					}
					m_beclearednum += 1;
					m_GradeNumber += m_plane[i]->GetValue();
					m_effect.push_back(new CEffect(m_resource.texiao, tx, ty));
					delete m_plane[i];
					m_plane.erase(m_plane.begin() + i);
				}
			}
		}

		//我方子弹与敌机碰撞
		for (i = 0; i < m_myplaneBullet.size(); i++)
		{
			int cx = m_myplaneBullet[i]->GetPosx() + m_myplaneBullet[i]->GetNowImg()->width / 2;
			int cy = m_myplaneBullet[i]->GetPosy() + m_myplaneBullet[i]->GetNowImg()->height / 2;
			for (j = 0; j < m_plane.size(); j++)
			{
				int tx = m_plane[j]->GetNowX() + m_plane[j]->GetNowImg()->width / 2;
				int ty = m_plane[j]->GetNowY() + m_plane[j]->GetNowImg()->height / 2;
				if (abs(tx - cx) < m_myplaneBullet[i]->GetNowImg()->width / 2 + m_plane[j]->GetNowImg()->width / 2 &&
					abs(ty - cy) < m_myplaneBullet[i]->GetNowImg()->height / 2 + m_plane[j]->GetNowImg()->height / 2)
				{

					m_plane[j]->Destory(m_myplaneBullet[i]->GetAttack());
					m_myplaneBullet[i]->Destory();
					if (m_plane[j]->IsClear() == true)
					{
						if (m_plane[j]->GetJudge() == 0) //判断打的飞机是否是boss
						{
							if (m_bgChoose < 4) m_gameUI.SetBgPass(m_bgChoose);
							else  m_gameUI.SetBgPass(3);
							m_bgChoose += 1;
							m_timerCD -= 500;
							m_bossAlive = false;
							m_beclearednum = 0;
							m_award.push_back(new CAward(m_resource.m_award, tx - 30, ty - 30));
							m_award.push_back(new CAward(m_resource.m_award, tx - 50, ty));
							m_award.push_back(new CAward(m_resource.m_award, tx + 50, ty));
							m_award.push_back(new CAward(m_resource.m_award, tx + 50, ty + 50));
							m_award.push_back(new CAward(m_resource.m_award, tx - 50, ty + 50));
							m_award.push_back(new CAward(m_resource.m_award, tx + 50, ty - 50));
							m_award.push_back(new CAward(m_resource.m_award, tx + 90, ty));
						}
						m_beclearednum += 1;
						m_GradeNumber += m_plane[j]->GetValue();
						m_effect.push_back(new CEffect(m_resource.texiao, tx, ty));
						m_award.push_back(new CAward(m_resource.m_award, tx, ty));
						delete m_plane[j];
						m_plane.erase(m_plane.begin() + j);
					}
					break;
				}
			}
		}

		//敌方子弹与我方飞碰撞
		for (i = 0; i < m_Bullet.size(); i++)
		{
			int cx = m_Bullet[i]->GetPosx() + m_Bullet[i]->GetNowImg()->width / 2;
			int cy = m_Bullet[i]->GetPosy() + m_Bullet[i]->GetNowImg()->height / 2;

			int tx = m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2;
			int ty = m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2;
			if (abs(tx - cx) < m_Bullet[i]->GetNowImg()->width / 2 + m_myplane.GetNowImg()->width / 4 + 5 &&
				abs(ty - cy) < m_Bullet[i]->GetNowImg()->height / 2 + m_myplane.GetNowImg()->height / 4 + 5)
			{
				m_Bullet[i]->Destory();
				m_myplane.Destory(m_Bullet[i]->GetAttack());
			}
		}
		//BUFF与我方飞机碰撞
		if (m_buffAlive == true)
		{
			int cx = m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2;
			int cy = m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2;
			int tx = m_buff->GetNowX() + m_buff->GetNowImg()->width / 2;
			int ty = m_buff->GetNowY() + m_buff->GetNowImg()->height / 2;
			if (abs(tx - cx) < m_myplane.GetNowImg()->width / 4 + m_buff->GetNowImg()->width / 2 &&
				abs(ty - cy) < m_myplane.GetNowImg()->height / 4 + m_buff->GetNowImg()->height / 2)
			{
				if (m_buff->GetChoose() == 0)
				{
					m_buffnumber += 1;
					if (m_buffnumber >= 3) m_buffnumber = 2;
					m_myplane.PlaneChoose(m_buffnumber);
				}
				else  m_myplane.AddBlood();
				m_buffAlive = false;
				m_buffaccpet = true;
				m_timer2 = 0;
				delete m_buff;
			}
		}
	}
	else if (n==1)
	{
		for (i = 0; i < m_bomb.size();i++)
		{
			int cx = m_bomb[i]->GetPosx() + m_bomb[i]->GetNowImg()->width / 2;
			int cy = m_bomb[i]->GetPosy() + m_bomb[i]->GetNowImg()->height / 2;

			int tx = m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2;
			int ty = m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2;
			if (abs(tx - cx) < m_bomb[i]->GetNowImg()->width / 2 + m_myplane.GetNowImg()->width / 4 + 5 &&
				abs(ty - cy) < m_bomb[i]->GetNowImg()->height / 2 + m_myplane.GetNowImg()->height / 4 + 5)
			{
				m_bomb[i]->Destory();
				m_myplane.Destory(300);
			}
		}
	}
	//共有奖励星星碰撞
	for (i = 0; i < m_award.size(); i++)
	{
		int cx = m_award[i]->GetPosx() + m_award[i]->GetNowImg()->width / 2;
		int cy = m_award[i]->GetPosy() + m_award[i]->GetNowImg()->height / 2;

		int tx = m_myplane.GetNowX() + m_myplane.GetNowImg()->width / 2;
		int ty = m_myplane.GetNowY() + m_myplane.GetNowImg()->height / 2;
		if (abs(tx - cx) < m_award[i]->GetNowImg()->width / 2 + m_myplane.GetNowImg()->width / 4 + 5 &&
			abs(ty - cy) < m_award[i]->GetNowImg()->height / 2 + m_myplane.GetNowImg()->height / 4 + 5)
		{
			m_award[i]->Destory();
			m_Starnumber += 1;
		}
	}

	
} 

int CManager::GetGrade()
{
	return m_GradeNumber;
}

int CManager::GetWJGrade()
{
	return m_Starnumber;
}

int CManager::GetStarnum()
{
	return m_Starnumber;
}

string CManager::GetName()
{
	return m_name;
}
//初始化游戏资源
void CManager::ResterGameInit()
{
	PlaySound(TEXT(".\\resource\\music\\run.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	m_state = GameRunning;
	m_timer = 0;
	m_timer1 = 0;
	m_timer2 = 0;
	m_timer3 = 0;
	m_timer4 = 0;
	m_pretimer = 0;
	m_timerCD = 2500;
	m_timerCD1 = 10000;
	m_timerCD2 = 13000;
	m_timerCD3 = 500;
	m_timerCD4 = 2000;
	m_GradeNumber = 0;
	m_Starnumber = 0;
	m_buffnumber = 0;
	m_beclearednum = 0;
	m_starspeed = 5;
	m_bgChoose = 1;
	m_bossAlive = false;
	m_buffAlive = false;
	m_buffaccpet = false;
	m_IsSaveTxt = false;
	int i;
	//飞机初始化
	for (i = 0; i < m_plane.size(); i++) delete m_plane[i];
	m_plane.clear();
	//子弹初始化
	for (i = 0; i < m_myplaneBullet.size(); i++) delete m_myplaneBullet[i];
	for (i = 0; i < m_Bullet.size() ; i++)  delete m_Bullet[i];
	for (i = 0; i < m_award.size(); i++)  delete m_award[i];
	for (i = 0; i < m_bomb.size(); i++)  delete m_bomb[i];
	m_myplaneBullet.clear();
	m_Bullet.clear();
	m_award.clear();
	m_bomb.clear();
	m_myplane.InitData();
	m_startui.Initchoose();
	m_gameUI.InitBg();
	m_endui.InitEndUI();
}
