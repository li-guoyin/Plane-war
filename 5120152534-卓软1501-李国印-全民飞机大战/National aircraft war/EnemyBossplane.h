/*@auther lgy
* time:1/5
*此类是飞机类派生的boss类
*/
#pragma once
#include "Plane.h"
//class CManager;
class CEnemyBossplane : public CPlane
{
public:
	CEnemyBossplane();
	CEnemyBossplane(IplImage *plane[], IplImage *bullet[]);
	~CEnemyBossplane();
	void InitData();
	//void SetNowImg(IplImage *plane[], IplImage *bullet[]);
	void Draw(IplImage *bg);
	void Move(int height, int width);
	void Attack(CManager *manger);
	//void Destory(int atk);
	//IplImage*GetNowImg();

	/*bool IsClear();
	int GetValue();
	int GetNowX();
	int GetNowY();
	int GetJudge();*/
private:
	IplImage *m_plane[3];
	IplImage *m_bullet[7];
	//IplImage *m_nowplane;
	int m_contral;


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

