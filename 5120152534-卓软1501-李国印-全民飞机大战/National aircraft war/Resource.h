/*@auther lgy
* time:1/5
*��Դ�࣬ͳһ����
*/
#pragma once
#include <opencv2/opencv.hpp>
class CResource
{
public:
	CResource();
	~CResource();
	void InitResource();
	void ReleaseIplimage();
	//IplImage *myplane[3];
	IplImage *myPuplane[9];//��ɫ�ɻ�
	IplImage *myGlplane[9];//��ɫ�ɻ�
	IplImage *myPlplane[9];//��ɫ�ɻ�
	IplImage *enemyplane[2];
	IplImage *enemyfightplane[4];
	IplImage *enemybossplane[3];
	IplImage *bultte[7];
	IplImage *number[10];
	IplImage *score[7];
	IplImage *texiao[4];
	IplImage *map[4];
	IplImage *buff[2];
	IplImage *blood;
	IplImage *startUI;
	IplImage *endUI;
	IplImage *ui[8];
	IplImage *m_award[7];
	IplImage *bomb[4];
	IplImage *star;
};

