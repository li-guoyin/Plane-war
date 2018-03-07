/*@auther lgy
* time:1/5
*������Ϸ������
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Resource.h"
#include "GameUI.h"
#include "Plane.h"
#include "Myplane.h"
#include "EnemyPlane.h"
#include "EnemyFightplane.h"
#include "EnemyBossplane.h"
#include "Bullet.h"
#include "Effect.h"
#include "StartUI.h"
#include "EndUI.h"
#include "BuffTool.h"
#include "Award.h"
class CManager
{
public:
	CManager();
	CManager(string user);
	~CManager();
	void InitGameResource();
	void ReleaseGameRes();
	void Run();
	void MyplaneUpdata();
	void EnemyPlaneUpdata();
	//void EnemyPlaneUpdata();
	//void EnemyFightplUpdata();
	//void EnemyBossPlUpdata();
	void AwardUpdata();
	void EffectUpdata();
	void BuffUpdata();
	void BullteCreat(IplImage *bulltImg, int posx, int posy, int dix, int diy, int attack,int type);
	void BullteDraw();
	void BullteMove();
	void BullteClear();
	void BullteUpdata();
	void AddEnemyPlane();
	void TimeUpdata();
	void Timeupdata_1();
	void Crash();
	int GetGrade();
	int GetWJGrade();
	int GetStarnum();
	string GetName();
	void ResterGameInit();
	enum GameState { GameStart, GameRunning, GameEnd };
private:
	string m_name;
	int n;
	int m_timer, m_pretimer, m_timerCD;  //����ʱ�����
	int m_timer1, m_timerCD1;
	int m_timer2, m_timerCD2;
	int m_timer3, m_timerCD3;
	int m_timer4, m_timerCD4;
	int m_GradeNumber;     //����
	int m_Starnumber;     //��������
	int m_buffnumber;     //�Ե�buff������
	int m_bgChoose;      //��������
	int m_beclearednum;  //������ĵл�����
	bool m_bossAlive;    //�ж�boss�Ƿ�����
	bool m_buffAlive;    //�ж�buff�Ƿ񱻳Ե�
	bool m_buffaccpet;   //�ж��ҷ��ɻ��Ƿ�Ե�buff
	bool m_IsSaveTxt;    //���������жϣ�
	int m_starspeed;
	CStartUI m_startui;
	CEndUI m_endui;
	GameState m_state;
	CResource m_resource;
	CGameUI m_gameUI;
	//CPlane *m_plane;
	CMyplane m_myplane;
	CEnemyPlane* m_enemyplane;
	CEnemyFightplane*  m_fightplane;
	CEnemyBossplane *m_bossplane;
	vector <CPlane *> m_plane;

	vector <CAward *> m_award;
	vector <CAward *> m_bomb;
	vector <CBullet*> m_myplaneBullet;
	//vector <CBullet*> m_fightplBullet;
	//vector <CBullet*> m_bossplBullet;
	vector <CBullet*> m_Bullet;
	CBuffTool *m_buff;
	vector <CEffect*> m_effect;
};



