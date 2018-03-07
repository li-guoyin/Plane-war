/*@auther lgy
 * time:1/5
 *此类是一个buff类，给我方飞机提供道具
*/
#pragma once
#include <opencv2/opencv.hpp>
class CBuffTool
{
public:
	CBuffTool();
	CBuffTool(IplImage *buff[]);
	~CBuffTool();
	void Draw(IplImage *bg);
	void Move(int height, int width);
	int GetNowX();
	int GetNowY();
	int GetChoose();   //用来判断是哪一种道具
	IplImage *GetNowImg();
private:
	IplImage *bufftool[2];
	IplImage *buffnow;
	int m_posx, m_posy;
	int m_dix, m_diy;
	int m_choose;
	bool m_Isclear;
};

