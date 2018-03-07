/*@auther lgy
* time:1/5
*�������ҷ��ɻ�
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
	IplImage *myPuplane[9]; //��ɫ�ɻ�
	IplImage *myGlplane[9];  //��ɫ�ɻ�
	IplImage *myPlplane[9];  //��ɫ�ɻ�
	IplImage *myplane[9];   //�������ѭ���ķɻ�
	IplImage *m_bullte[5];  //����ӵ�
	//IplImage *m_nowplane;  
	//int m_defence;
	int Speed;  //�ɻ��ƶ��ٶ�
	int m_index,m_speed; //�л���Ƭ
	bool panduan;  //��ȷ��ʲôʱ����Ƭ�÷����л�

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

