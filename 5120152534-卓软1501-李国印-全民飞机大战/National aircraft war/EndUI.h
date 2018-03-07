/*@auther lgy
* time:1/5
*此类提供结束界面
*/
#pragma once
#include <opencv2/opencv.hpp>
# include <string>
# include <vector>
using namespace std;
typedef struct userScore
{
	string name;
	int score;
}uS;
class CManager;
class CEndUI
{
public:
	CEndUI();
	~CEndUI();
	void Show();
	void SetIplimage(IplImage *Endui,IplImage *num1[]);
	void ShowGrade(CManager *manger);
	void DrawGrade(int Grade,int posx,int posy);
	void DrawName(string str, int posx, int posy);
	void InitEndUI();
	void DrawwjGrade(CManager *manger);

private:
	IplImage *endui;
	IplImage *clone;
	IplImage *clone1;
	IplImage *num[10];
	//vector <int> Ranking;
	vector <uS> Ranking;
};

