/*@auther lgy
* time:1/5
*��¼��
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class CLogin
{
public:
	CLogin();
	~CLogin();
	string Getuser(); //��ȡ�û���
	void Setlogin(); //ע��
	bool UserLogin();//��¼
private:
	string m_users;   //�û���
	string m_password;  //����
	bool m_loginsuccess;  //�Ƿ��¼�ɹ�
};

