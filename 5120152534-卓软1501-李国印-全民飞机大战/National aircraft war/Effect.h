/*@auther lgy
* time:1/5
*������
*������һ����Ч�࣬ͨ�����ô���Ϊ�ɻ��������챬ը��Ч
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

