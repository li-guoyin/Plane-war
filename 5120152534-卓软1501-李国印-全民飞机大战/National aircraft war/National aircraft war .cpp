/*@auther lgy
 * time:1/5
 *������
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
	cout << "         ��¼����      " << endl;
	cout << endl << "��¼�밴 1     ע���밴 2    " << endl << endl;
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
		while (key == false)  //ѭ���ж�������û��������Ƿ���ȷ
		{
			key = login.UserLogin();
		}
		if (key == true)  //��½�ɹ�����ʼ��Ϸ
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