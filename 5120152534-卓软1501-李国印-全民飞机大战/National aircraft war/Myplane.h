/*@auther lgy
* time:1/5
*此类是我方飞机
*/
#pragma once
#include "Plane.h"
#include <opencv2/opencv.hpp>
class CManager;
class CMyplane : public CPlane
{
public:
	CMyplane();
	~CMyplane();
	void SetNowImg(IplImage *planepu[], IplImage *planegl[], IplImage *planepl[], IplImage *bullet[]);
	void InitData();
	void PlaneChoose(int buffnumber);
	void Draw(IplImage *bg);
	void Move(int height,int width);
	void Attack(CManager * manger);
	int GetBlood();
	void AddBlood();
	/*void Destory(int atk);
	IplImage *GetNowImg();
	bool IsClear();
	int GetNowX();
	int GetNowY();
	
	int GetValue();
	int GetJudge();*/
private:
	IplImage *myPuplane[9]; //紫色飞机
	IplImage *myGlplane[9];  //金色飞机
	IplImage *myPlplane[9];  //土色飞机
	IplImage *myplane[9];   //存放正在循环的飞机
	IplImage *m_bullte[5];  //存放子弹
	//IplImage *m_nowplane;  
	//int m_defence;
	int Speed;  //飞机移动速度
	int m_index,m_speed; //切换照片
	bool panduan;  //来确定什么时候照片该反着切换

	/*int m_attack;
	int m_blood;
	int m_posx;
	int m_posy;
	bool m_isclear;
	int m_timer;
	int m_pretimer;
	int m_timerCD;
	int m_choose;*/
};

