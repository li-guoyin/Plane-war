/*@auther lgy
* time:1/5
*主函数
*此类是一个特效类，通过调用此类为飞机死亡制造爆炸特效
*/

#pragma once
#include <opencv2/opencv.hpp>
class CEffect
{
public:
	CEffect();
	CEffect(IplImage *eff[], int posx, int posy);
	~CEffect();
	void Draw(IplImage *bg);
	bool Isclear();
private:
	IplImage *effect[4];
	IplImage *bosseffect[6];
	int m_speed;
	int m_posx;
	int m_posy;
	int m_index;
	bool m_Isclear;
	int m_choose;
};

