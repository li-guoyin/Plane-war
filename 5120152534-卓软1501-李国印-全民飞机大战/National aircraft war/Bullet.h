/*@auther lgy
* time:1/5
*此类是一个子弹类
*/

#pragma once
#include <opencv2/opencv.hpp>
class CBullet
{
public:
	CBullet();
	CBullet(IplImage *bulltImg,int posx,int posy,int dix,int diy,int attack,int tp);
	~CBullet();
	void Draw(IplImage *bg);
	void Move(int height, int width,int posx2,int posy2);
	double Angle(int posx1,int posx2,int posy1, int posy2);
	IplImage *ChangeAngle(IplImage *img, double angle1);
	bool IsClear();
	void Destory();
	IplImage * GetNowImg();
	int GetPosx();
	int GetPosy();
	int GetAttack();
private:
	int b_posx;
	int b_posy;
	int b_dix;
	int b_diy;
	int b_atck;
	int b_type;
	int b_speed;
	int timer, timerCD, pretime;
	IplImage *b_img;
	bool b_isclear;
};

