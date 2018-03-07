/*@auther lgy
* time:1/5
*/
#include "Effect.h"
CEffect::CEffect()
{
}
//重载函数  属性从外部传递
CEffect::CEffect(IplImage *eff[], int posx, int posy)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		effect[i] = eff[i];
	}
	m_posx = posx;
	m_posy = posy;
	m_speed = 2;
	m_index = 0;
	m_Isclear = false;
}

CEffect::~CEffect()
{
}
//特效绘制，几张图片，通过index控制时间间隔，分别加载绘制，最后体现爆炸效果
void CEffect::Draw(IplImage *bg)
{
	if (m_Isclear == true) return;
	int i, j;
		int posx = m_posx - effect[m_index / m_speed]->width / 2;
		int posy = m_posy - effect[m_index / m_speed]->height / 2;
		for (i = 0; i < effect[m_index / m_speed]->height; i++)
		{
			for (j = 0; j < effect[m_index / m_speed]->width; j++)
			{
				int b = CV_IMAGE_ELEM(effect[m_index / m_speed], uchar, i, j * 3 + 0);
				int g = CV_IMAGE_ELEM(effect[m_index / m_speed], uchar, i, j * 3 + 1);
				int r = CV_IMAGE_ELEM(effect[m_index / m_speed], uchar, i, j * 3 + 2);
				if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
				if (i + posy<0 || i + posy>bg->height || j + posx<0 || j + posx>bg->width) continue;
				CV_IMAGE_ELEM(bg, uchar, i + posy, (j + posx) * 3 + 0) = b;
				CV_IMAGE_ELEM(bg, uchar, i + posy, (j + posx) * 3 + 1) = g;
				CV_IMAGE_ELEM(bg, uchar, i + posy, (j + posx) * 3 + 2) = r;
			}
		}
		m_index++;
		if (m_index / m_speed >= 4) m_Isclear = true;
	
}

bool CEffect::Isclear()
{
	return m_Isclear;
}
