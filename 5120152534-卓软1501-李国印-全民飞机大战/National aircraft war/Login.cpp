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
//�û�ע��
void CLogin::Setlogin()
{
	cout << "ע�᣺" << endl;
	cout <<endl << "�������û�����" << "  ";
	cin >> m_users;
	cout << "���������룺" << "  ";
	cin >> m_password;
	ofstream fout;
	fout.open("Users.txt", ios_base::out | ios_base::app);
	fout << m_users << endl << m_password << endl;
	fout.close();
	cout << "ע��ɹ�����   ��ʼ��¼����Ϸ�ɣ���" << endl << endl;
}
//�û���¼
bool CLogin::UserLogin()
{
	string user, password;
	cout << "��¼��" << endl;
	cout << endl << "�������û�����" << "  ";
	cin >> m_users;
	cout << "���������룺" << "  ";
	cin >> m_password;

	int book1;  //����
	ifstream fin;
	fin.open("Users.txt", ios_base::in);

	while (getline(fin, user), getline(fin, password))
	{
		book1 = 0;
		if (user == m_users && password == m_password)
		{
			system("cls");//��������
			book1 = 1;
			m_loginsuccess = true;
			cout <<endl<<endl<< "��¼�ɹ�����  ��ʼð��֮�ðɣ���" << endl;
			break;
		}
	}
	fin.close();
	if (book1 == 0)
	{
		system("cls");//��������
		cout << "�û���������,���˺�������󣡣�" << endl;
		cout << "���������룺" << endl << endl;
	}
	return m_loginsuccess;
}

string CLogin::Getuser()
{
	return m_users;
}
