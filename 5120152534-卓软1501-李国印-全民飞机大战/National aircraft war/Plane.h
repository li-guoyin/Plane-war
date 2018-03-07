/*@auther lgy
* time:1/5
*所有飞机的基类
*/
#pragma once
#include <opencv2/opencv.hpp>
class CManager;
class CPlane
{
public:
	CPlane();
	~CPlane();
	virtual void Draw(IplImage *bg) = 0;  //飞机绘制
	virtual void Move(int height,int width) = 0;  //飞机移动
	virtual void Attack(CManager *manger) = 0;  //飞机的攻击
	//virtual void Destory(int atk) = 0;   
	void Destory(int atk){
		m_blood -= atk;
		if (m_blood <= 0)
		{
			m_Isclear = true;
		}
	}    //被攻击失血
	IplImage* GetNowImg() { return m_nowplane; }
	bool IsClear(){ return m_Isclear; }          //判断飞机是否死亡
	int GetNowX(){ return m_posx; }          //得到飞机的坐标
	int GetNowY() { return m_posy; }
	int GetValue() { return m_value; }           //返回所得分数
	int GetJudge() { return m_pan; }             //返回值判断是那种飞机

//先前的虚函数
	/*//
	//virtual IplImage* GetNowImg() = 0;    //得到现在飞机的图片
	virtual void SetNowImg(IplImage *plane[],IplImage *bullet[]) = 0;  //传递图片参数，
	virtual bool IsClear() = 0;          //判断飞机是否死亡
	virtual int GetNowX() = 0;          //得到飞机的坐标
	virtual int GetNowY() = 0;
	virtual int GetValue() = 0;           //返回所得分数
	virtual int GetJudge() = 0;             //返回值判断是那种飞机*/
protected:
	int m_posx;     //坐标X
	int m_posy;     //坐标Y
	int m_blood;    //血量
	int m_value;    //价值·可得分数
	int m_attack;   //攻击强度
	int m_pan;      //判断是那种飞机
	bool m_Isclear; //判断飞机是否被清除

	int m_dix;     //X轴偏移量 
	int m_diy;     //Y轴偏移量
	int m_choose;  //判断一类飞机下的那一辆飞机
	int m_timer;   //时间间隔
	int m_pretimer;//存储当前时间
	int m_timerCD; //技能冷却时间
	IplImage * m_nowplane;
};

