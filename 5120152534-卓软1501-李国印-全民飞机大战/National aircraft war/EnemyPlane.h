/*@auther lgy
* time:1/5
*此类是无攻击型飞机
*/
#pragma once
#include "Plane.h"
class CEnemyPlane : public CPlane
{
public:
	CEnemyPlane();
	CEnemyPlane::CEnemyPlane(IplImage *plane[]);
	~CEnemyPlane();
	void InitData();
	void Draw(IplImage*bg);
	void Move(int height, int width);
	void Attack(CManager *manger);
	//void Destory(int atk);
	//IplImage *GetNowImg();

	/*//void SetNowImg(IplImage *plane[],IplImage *bullet[]);
	bool IsClear();
	int GetNowX();
	int GetNowY();
	int GetValue();
	int GetJudge();*/
private:
	IplImage *enemyplane[2];
	//IplImage *nowenemyplane;
	
	/*int m_posx;
	int m_posy;
	int m_blood;
	int m_value;
	bool m_Isclear;
	int m_dix;
	int m_diy;
	int m_choose;*/
	
};

