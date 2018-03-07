/*@auther lgy
* time:1/5
*/
#include "EndUI.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include<algorithm>
using namespace std;
#include <cv.h>

/*typedef struct userScore
{
	string name;
	int score;
}uS;*/
//结构体排序使用
bool Comp(const uS &r, const uS &s)
{
	return r.score > s.score;
}
//一般整型使用
/*bool Comp(const int a, const int b)
{
	return a > b;
}*/
CEndUI::CEndUI()
{
}

CEndUI::~CEndUI()
{
}

void CEndUI::SetIplimage(IplImage *Endui,IplImage *num1[])
{
	endui = Endui;
	for (int i = 0; i < 10;i++)
	{
		num[i] = num1[i];
	}
	clone = cvCloneImage(Endui);
}
//为重玩游戏更新界面
void CEndUI::InitEndUI()
{
	cvCopyImage(clone, endui);
	Ranking.clear();
	//endui = clone;
}

void CEndUI::Show()
{
	cvShowImage("全民飞机大战",endui);
	cvWaitKey(0);
}
//绘制分数
void CEndUI::ShowGrade(CManager *manger)
{
	ifstream fin;
	ofstream fout;
	//打开文件，写入当前分数数据
	fout.open("data.txt", ios_base::out|ios_base::app);
	fout << manger->GetName() << endl << manger->GetGrade() << endl;
	fout.close();
	//绘制当前分数
	DrawGrade(manger->GetGrade(),280 ,145);
	//打开文件，读取数据到vector
	fin.open("data.txt", ios_base::in);
	string grade;
	string grade1;
	while (getline(fin, grade), getline(fin, grade1))
	{
		uS user;
		user.name = grade;
		user.score = atoi(grade1.c_str());
		
		Ranking.push_back(user);
	}
	//对vector内的数据排序
	sort(Ranking.begin(), Ranking.end(),Comp); 
	//sort(Ranking.begin(), Ranking.end());
	//绘制前九名的数据分数
	int sum = Ranking.size();
	if (sum>9)
	{
		sum = 9;
	}
	int posy = 255;
	for (int i = 0; i < sum;i++)
	{
		DrawGrade(Ranking[i].score, 400 ,posy);
		DrawName(Ranking[i].name, 150, posy);
		posy += 66;
	}
	

}
//提供绘制分数方法
void CEndUI::DrawGrade(int Grade,int posx,int posy)
{
	int number = Grade;
	int i, j, yu ,pox = posx,poy = posy;
	do
	{
		yu = number % 10;
		number = number / 10;
		for (i = 0; i < num[yu]->height; i++)
		{
			for (j = 0; j < num[yu]->width; j++)
			{
				int b = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 0);
				int g = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 1);
				int r = CV_IMAGE_ELEM(num[yu], uchar, i, j * 3 + 2);
				if (b > 85 && b < 95 && g > 128 && g < 135 && r > 175 && r < 180) continue;
				CV_IMAGE_ELEM(endui, uchar, i + poy, (j + pox) * 3 + 0) = b;
				CV_IMAGE_ELEM(endui, uchar, i + poy, (j + pox) * 3 + 1) = g;
				CV_IMAGE_ELEM(endui, uchar, i + poy, (j + pox) * 3 + 2) = r;
			}
		}
		pox -= num[yu]->width;
	} while (number != 0);
}
//绘制用户名
void CEndUI::DrawName(string str, int posx, int posy)
{
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 0, 1, CV_AA);
	char*p = (char*)str.data();
	cvPutText(endui, p, cvPoint(posx, posy+25), &font, CV_RGB(255, 20, 136));//输出值
}
//绘制无尽模式下分数
void CEndUI::DrawwjGrade(CManager *manger)
{
	DrawGrade(manger->GetWJGrade(), 280, 145);
}
