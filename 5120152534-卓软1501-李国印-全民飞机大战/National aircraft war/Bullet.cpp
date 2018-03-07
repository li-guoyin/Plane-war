/*@auther lgy
* time:1/5
*/
#include "Bullet.h"
#include <cmath>
#include <ctime>
# include <iostream>
using namespace std;
CBullet::CBullet()
{
	b_isclear = false;
}
//重载函数  ，通过参数传递将子弹的属性传递给子弹
CBullet::CBullet(IplImage *bulltImg, int posx, int posy, int dix, int diy, int attack,int tp)
{
	b_img = bulltImg;
	b_posx = posx;
	b_posy = posy;
	b_dix = dix;
	b_diy = diy;
	b_atck = attack;
	b_isclear = false;
	b_type = tp;
	b_speed = diy;
	timer = 0;
	timerCD = 2000;
	pretime = 0;
}

CBullet::~CBullet()
{
}
//子弹的绘制
void CBullet::Draw(IplImage *bg)
{
	if (b_isclear == true) return;
	b_isclear = false;
	int i, j;
	for (i = 0; i < b_img->height;i++)
	{
		for (j = 0; j < b_img->width;j++)
		{
			int b = CV_IMAGE_ELEM(b_img, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(b_img, uchar, i, j * 3 + 1);
			int r = CV_IMAGE_ELEM(b_img, uchar, i, j * 3 + 2);
			if (b > 80 && b < 100 && g > 125 && g < 140 && r > 170 && r < 185) continue;
			//if (b <= 255 && b>200 && g <= 255 && g>200 && r <= 255 && r>200)  continue;
			if (i + b_posy<0 || i + b_posy>bg->height || j + b_posx<0 || j + b_posx>bg->width)  continue;  //有一部分在界外时，不绘制
			CV_IMAGE_ELEM(bg, uchar, i + b_posy, (j + b_posx) * 3 + 0) = b;
			CV_IMAGE_ELEM(bg, uchar, i + b_posy, (j + b_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(bg, uchar, i + b_posy, (j + b_posx) * 3 + 2) = r;
		}
	}
}
//子弹的移动
void CBullet::Move(int height, int width,int posx2,int posy2)
{
	if (b_type == 2)//boss飞机子弹变换
	{
		//if (b_dix>0)  b_dix = b_dix + 0.6;
		//if (b_dix<0)  b_dix = b_dix - 0.6;
		b_diy += 0.5;
	}
	if (b_type == 1)//攻击型飞机的子弹变换
	{
		b_diy += 0.3;
		
	}
	if (b_type == 3)//敌方攻击型飞机的导弹变换
	{
		
		int posx = b_posx + b_img->width / 2;
		int posy = b_posy + b_img->height / 2;
		double angle = Angle(posx, posx2, posy, posy2);   //计算角度，单独的函数执行
		//b_img = ChangeAngle(b_img, angle);  //没有实现 图片旋转 单独的函数执行
		if (angle < 0) //角度取正
		{
			angle = -angle;
		}
		if (b_posx > posx2 && b_posy < posy2)  //子弹在飞机的右上角
		{
			b_dix = -b_speed *sin(angle);
			b_diy = b_speed *cos(angle);
		}
		else if (b_posx < posx2 && b_posy < posy2) //子弹在飞机的左上角
		{
			b_dix = b_speed *sin(angle);
			b_diy = b_speed * cos(angle);
		}
		else if (b_posx > posx2 && b_posy > posy2) //子弹在飞机的右下角
		{
			b_dix = -b_speed *sin(angle);
			b_diy = -b_speed *cos(angle);
		}
		else if (b_posx < posx2 && b_posy > posy2) //子弹在飞机的左下角
		{
			b_dix = b_speed *sin(angle);
			b_diy = -b_speed *cos(angle);
		}
	}
	b_posx += b_dix;
	b_posy += b_diy;
	if (b_posy >= height - b_img->height||b_posx >= width - b_img->width) b_isclear = true;
	if (b_posy < 0 || b_posx <0) b_isclear = true;
}

bool CBullet::IsClear()
{
	return b_isclear;
}

void CBullet::Destory()
{
	b_isclear = true;
}

IplImage *CBullet::GetNowImg()
{
	return b_img;
}

int CBullet::GetPosx()
{
	return b_posx;
}

int CBullet::GetPosy()
{
	return b_posy;
}
//提供子弹的攻击力
int CBullet::GetAttack()
{
	return b_atck;
}

double CBullet::Angle(int posx1, int posx2, int posy1, int posy2)  //计算角度
{
	//posx1,posy1是敌方飞机的坐标，posx2，posy2是我方飞机坐标
	double angle;
	double px1 = double(posx1);
	double py1 = double(posy1);
	double px2 = double(posx2);
	double py2 = double(posy2);
	//利用相对位置，及反三角函数计算角度
	if (py2 >= py1)
	{
		double dx = px2 - px1;
		double dy = py2 - py1;
		angle = atan(dx / dy);
	}
	else if (py2 < py1)
	{
		double dx = px2 - px1;
		double dy = py2 - py1;
		angle = CV_PI + atan(dx / dy);
	}
	return angle;
}

IplImage * CBullet::ChangeAngle(IplImage *img, double angle1)
{
	cv::Mat image;
	image = cv::Mat(img);
	cv::Point2f center = cv::Point2f(image.cols / 2, image.rows / 2); // 旋转中心  
	double angle = 50; // 旋转角度  
	double scale = 1; // 缩放尺度  
	cv::Mat rotateMat;
	rotateMat = cv::getRotationMatrix2D(center, angle, scale);
	cv::Mat rotateImg;
	cv::warpAffine(image, rotateImg, rotateMat, image.size());
	IplImage* img2 = new IplImage(rotateImg);;
	return img2;
}