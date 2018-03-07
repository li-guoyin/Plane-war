/*@auther lgy
 * time:1/5
 *主函数
*/
# include <iostream>
# include <string>
# include <opencv2/opencv.hpp>
# include "Manager.h"
# include "Login.h"
# include <stdlib.h>
using namespace std;
int main()
{
	CLogin login;
	cout << "         登录界面      " << endl;
	cout << endl << "登录请按 1     注册请按 2    " << endl << endl;
	int contral;
	bool key = false;
	cin >> contral;
	cout << endl;
	if (contral == 2)
	{
		login.Setlogin();
		system("cls");
		contral = 1;
	}
	if (contral == 1)
	{
		while (key == false)  //循环判断输入的用户及密码是否正确
		{
			key = login.UserLogin();
		}
		if (key == true)  //登陆成功，开始游戏
		{
			string name = login.Getuser();
			CManager manage(name);
			manage.InitGameResource();
			manage.Run();
			manage.ReleaseGameRes();
		}
	}
	
	return 0;
}