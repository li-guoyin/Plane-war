/*@auther lgy
* time:1/5
*/
#include "Resource.h"
#include <stdio.h>

CResource::CResource()
{
}


CResource::~CResource()
{
}
/*
初始化所有图片，其他类需要图片时调用resource类；
*/
void CResource::InitResource()
{
	char filename[100];
	int i;
	for (i = 0; i < 9; i++)
	{
		sprintf(filename, ".\\resource\\purpleplane\\%d.png", i);
		myPuplane[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 9; i++)
	{
		sprintf(filename, ".\\resource\\goldplane\\%d.png", i);
		myGlplane[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 9; i++)
	{
		sprintf(filename, ".\\resource\\paleplane\\%d.png", i);
		myPlplane[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 4; i++)
	{
		sprintf(filename, ".\\resource\\diplane\\%d.png", i);
		enemyfightplane[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 2; i++)
	{
		sprintf(filename, ".\\resource\\diplane1\\%d.png", i);
		enemyplane[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 3; i++)
	{
		sprintf(filename, ".\\resource\\bossplane\\%d.png", i);
		enemybossplane[i] = cvLoadImage(filename, 1);
	}

	for (i = 0; i < 7; i++)
	{
		sprintf(filename, ".\\resource\\bullte\\%d.png", i);
		bultte[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 10; i++)
	{
		sprintf(filename, ".\\resource\\nums\\%d.png", i);
		number[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 7; i++)
	{
		sprintf(filename, ".\\resource\\score\\%d.png", i);
		score[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 4; i++)
	{
		sprintf(filename, ".\\resource\\texiao\\%d.png", i);
		texiao[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 4; i++)
	{
		sprintf(filename, ".\\resource\\map\\%d.jpg", i);
		map[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 2;i++)
	{
		sprintf(filename, ".\\resource\\buff\\%d.png", i);
		buff[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 8; i++)
	{
		sprintf(filename, ".\\resource\\UI\\%d.png", i);
		ui[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 7; i++)
	{
		sprintf(filename, ".\\resource\\ward\\%d.png", i);
		m_award[i] = cvLoadImage(filename, 1);
	}
	for (i = 0; i < 4; i++)
	{
		sprintf(filename, ".\\resource\\bomb\\%d.png", i);
		bomb[i] = cvLoadImage(filename, 1);
	}
	star = cvLoadImage(".\\resource\\star.png");
	blood = cvLoadImage(".\\resource\\blood.png");
	startUI = cvLoadImage(".\\resource\\startui.png");
	endUI = cvLoadImage(".\\resource\\endui.png");
}
//释放图片指针
void CResource::ReleaseIplimage()
{
	int i;
	for (i = 0; i < 9; i++)
	{
		cvReleaseImage(&myPuplane[i]);
		cvReleaseImage(&myGlplane[i]);
		cvReleaseImage(&myPlplane[i]);
	}
	for (i = 0; i < 7; i++)
	{
		cvReleaseImage(&enemyplane[i]);
		cvReleaseImage(&bultte[i]);
		cvReleaseImage(&score[i]);
		cvReleaseImage(&m_award[i]);
	}
	for (i = 0; i < 2; i++)
	{
		cvReleaseImage(&enemyfightplane[i]);
	}
	for (i = 0; i < 10; i++)
	{
		cvReleaseImage(&number[i]);
	}
	for (i = 0; i < 4; i++)
	{
		cvReleaseImage(&texiao[i]);
		cvReleaseImage(&map[i]);
		cvReleaseImage(&bomb[i]);
	}
	for (i = 0; i < 2;i++)
	{
		cvReleaseImage(&buff[i]);
	}
	for (i = 0; i < 8; i++)
	{
		cvReleaseImage(&ui[i]);
	}
	cvReleaseImage(&star);
	cvReleaseImage(&blood);
	cvReleaseImage(&startUI);
	cvReleaseImage(&endUI);
}
