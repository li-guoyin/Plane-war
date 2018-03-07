/*@auther lgy
* time:1/5
*此类为游戏界面
*/
#pragma once
#include <opencv2/opencv.hpp>
class CManager;
class CGameUI
{
public:
	CGameUI();
	~CGameUI();
	// 设置背景图片
	void SetBgImage(IplImage * map[], IplImage *num1[], IplImage *blood1,IplImage *st);
	void Build();
	void ShowNowbg();
	void NumberDraw(int numb, int x, int y);
	IplImage* GetNowbg();
	void ScoreDraw(CManager *manger);
	void StarDraw(CManager *manger);
	void BloodDraw(int freeblood,int allblood);
	void SetBgPass(int key);
	void InitBg();
private:
	IplImage *nowbg;
	IplImage *bg[4];
	IplImage *num[10];
	IplImage *blood;
	IplImage *star;
	IplImage *clonebg;
	IplImage *clonebg1;
	int mpos;
	int speed;
	int timer,pretimer,timercd;
	int m_choose;
	bool passUIclear;
	
};

