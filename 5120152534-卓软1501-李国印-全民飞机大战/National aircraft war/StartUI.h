/*@auther lgy
* time:1/5
*开始界面
*/
#pragma once
#include <opencv2/opencv.hpp>
class CStartUI
{
public:
	CStartUI();
	~CStartUI();
	void Draw(int posx,int posy,int count);
	int DrawAll();
	void Initchoose();
	void Show();
	void SetIplimage(IplImage *str,IplImage *UI[]);
private:
	IplImage *startui;
	IplImage *ui[8];
	int m_choose;
};

