/*@auther lgy
* time:1/5
*此类是攻击性敌机
*/
#pragma once
#include "Plane.h"
//class CManager;
class CEnemyFightplane :public CPlane
{
public:
	CEnemyFightplane();
	CEnemyFightplane(IplImage *plane[], IplImage *bullet[]);
	~CEnemyFightplane();
	void InitData();
	void Draw(IplImage *bg);
	void Move(int height, int width);
	void Attack(CManager *manger);
	//void Destory(int atk);
	//IplImage*GetNowImg();

	/*//void SetNowImg(IplImage *plane[], IplImage *bullet[]);
	bool IsClear();
	int GetNowX();
	int GetNowY();
	int GetValue();
	int GetJudge();*/
private:
	IplImage *m_plane[4];
	IplImage *m_bullet[6];
	//IplImage *m_nowplane;


	/*int m_posx;
	int m_posy;
	int m_blood;
	int m_value;
	int m_attack;
	bool m_Isclear;
    int m_dix;
	int m_diy;
	int m_choose;
	int m_timer;
	int m_pretimer;
	int m_timerCD;*/
};

