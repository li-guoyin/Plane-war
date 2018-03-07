/*@auther lgy
* time:1/5
*登录类
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
	string Getuser(); //获取用户名
	void Setlogin(); //注册
	bool UserLogin();//登录
private:
	string m_users;   //用户名
	string m_password;  //密码
	bool m_loginsuccess;  //是否登录成功
};

