/*@auther lgy
* time:1/5
*���зɻ��Ļ���
*/
#pragma once
#include <opencv2/opencv.hpp>
class CManager;
class CPlane
{
public:
	CPlane();
	~CPlane();
	virtual void Draw(IplImage *bg) = 0;  //�ɻ�����
	virtual void Move(int height,int width) = 0;  //�ɻ��ƶ�
	virtual void Attack(CManager *manger) = 0;  //�ɻ��Ĺ���
	//virtual void Destory(int atk) = 0;   
	void Destory(int atk){
		m_blood -= atk;
		if (m_blood <= 0)
		{
			m_Isclear = true;
		}
	}    //������ʧѪ
	IplImage* GetNowImg() { return m_nowplane; }
	bool IsClear(){ return m_Isclear; }          //�жϷɻ��Ƿ�����
	int GetNowX(){ return m_posx; }          //�õ��ɻ�������
	int GetNowY() { return m_posy; }
	int GetValue() { return m_value; }           //�������÷���
	int GetJudge() { return m_pan; }             //����ֵ�ж������ַɻ�

//��ǰ���麯��
	/*//
	//virtual IplImage* GetNowImg() = 0;    //�õ����ڷɻ���ͼƬ
	virtual void SetNowImg(IplImage *plane[],IplImage *bullet[]) = 0;  //����ͼƬ������
	virtual bool IsClear() = 0;          //�жϷɻ��Ƿ�����
	virtual int GetNowX() = 0;          //�õ��ɻ�������
	virtual int GetNowY() = 0;
	virtual int GetValue() = 0;           //�������÷���
	virtual int GetJudge() = 0;             //����ֵ�ж������ַɻ�*/
protected:
	int m_posx;     //����X
	int m_posy;     //����Y
	int m_blood;    //Ѫ��
	int m_value;    //��ֵ���ɵ÷���
	int m_attack;   //����ǿ��
	int m_pan;      //�ж������ַɻ�
	bool m_Isclear; //�жϷɻ��Ƿ����

	int m_dix;     //X��ƫ���� 
	int m_diy;     //Y��ƫ����
	int m_choose;  //�ж�һ��ɻ��µ���һ���ɻ�
	int m_timer;   //ʱ����
	int m_pretimer;//�洢��ǰʱ��
	int m_timerCD; //������ȴʱ��
	IplImage * m_nowplane;
};

