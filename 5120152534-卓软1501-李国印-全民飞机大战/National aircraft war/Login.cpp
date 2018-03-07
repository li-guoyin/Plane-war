/*@auther lgy
* time:1/5
*/
#include "Login.h"
#include <stdlib.h>

CLogin::CLogin()
{
	m_loginsuccess = false;
}


CLogin::~CLogin()
{
}
//用户注册
void CLogin::Setlogin()
{
	cout << "注册：" << endl;
	cout <<endl << "请输入用户名：" << "  ";
	cin >> m_users;
	cout << "请输入密码：" << "  ";
	cin >> m_password;
	ofstream fout;
	fout.open("Users.txt", ios_base::out | ios_base::app);
	fout << m_users << endl << m_password << endl;
	fout.close();
	cout << "注册成功！！   开始登录玩游戏吧！！" << endl << endl;
}
//用户登录
bool CLogin::UserLogin()
{
	string user, password;
	cout << "登录：" << endl;
	cout << endl << "请输入用户名：" << "  ";
	cin >> m_users;
	cout << "请输入密码：" << "  ";
	cin >> m_password;

	int book1;  //打标记
	ifstream fin;
	fin.open("Users.txt", ios_base::in);

	while (getline(fin, user), getline(fin, password))
	{
		book1 = 0;
		if (user == m_users && password == m_password)
		{
			system("cls");//清屏函数
			book1 = 1;
			m_loginsuccess = true;
			cout <<endl<<endl<< "登录成功！！  开始冒险之旅吧！！" << endl;
			break;
		}
	}
	fin.close();
	if (book1 == 0)
	{
		system("cls");//清屏函数
		cout << "用户名不存在,或账号密码错误！！" << endl;
		cout << "请重新输入：" << endl << endl;
	}
	return m_loginsuccess;
}

string CLogin::Getuser()
{
	return m_users;
}
