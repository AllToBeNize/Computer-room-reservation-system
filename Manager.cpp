#include"Manager.h"
Manager::Manager()
{
}

Manager::Manager(string username, string password)
{
	this->username = username;
	this->password = password;
}

void Manager::openMenu()
{
	system("cls");
	cout << "\t\t\t\t" << " 欢迎"+this->username+"管理员登录" << endl;
	cout << "\t\t\t\t" << "============================" << endl;
	cout << "\t\t\t\t" << "|       1. 添加账号        |" << endl;
	cout << "\t\t\t\t" << "|                          |" << endl;
	cout << "\t\t\t\t" << "|       2. 查看账户        |" << endl;
	cout << "\t\t\t\t" << "|                          |" << endl;
	cout << "\t\t\t\t" << "|       3. 查看机房        |" << endl;
	cout << "\t\t\t\t" << "|                          |" << endl;
	cout << "\t\t\t\t" << "|       4. 清空预约        |" << endl;
	cout << "\t\t\t\t" << "|                          |" << endl;
	cout << "\t\t\t\t" << "|       0. 注销登录        |" << endl;
	cout << "\t\t\t\t" << "============================" << endl;
}

void Manager::addPerson()
{
	int c;
	cout << "\t\t      1.学生" << endl;
	cout << "\t\t      2.教师" << endl;
	cout << "\t\t请输入您要添加的账号类型：";
	cin >> c;
	string id;
	switch (c)
	{
	case 1:
		mysqlCon::sign_up_stu(); break;
	case 2:
		mysqlCon::sign_up_tea(); break;
	default:cout << "\t\t您的输入有误,请重新输入！" << endl; system("pause"); system("cls"); break;
	}
}

void Manager::showPerson()
{
	mysqlCon::query_info();
}

void Manager::showRoom()
{
	mysqlCon::query_room();
}

void Manager::clearFile()
{
	mysqlCon::del();
}
