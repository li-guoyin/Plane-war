/*@auther lgy
* time:1/5
*该类为，星星奖励类
*/
#pragma once
#include <opencv2/opencv.hpp>
class CAward
{
public:
	CAward();
	CAward(IplImage *aw[],int speed);
	CAward(IplImage *bomb[],int model,int speed,int model1);
	CAward(IplImage *aw[],int posx,int posy);
	void Draw(IplImage *bg);
	void Move(int width, int height);
	void Destory();
	bool Isclear();
	int GetPosx(){ return m_posx; }
	int GetPosy() { return m_posy; }
	IplImage * GetNowImg(){ return m_awardti; }
	~CAward();
private:
	IplImage *m_award[7];
	IplImage *m_bomb[4];
	IplImage *m_awardti;
	bool m_Isclear;
	int m_choose;
	int m_posx, m_posy;
	int m_dix, m_diy;
};

