#include"Teacher.h"
#include"mysqlCon.h"
Teacher::Teacher()
{
}

Teacher::Teacher(string tid, string username, string password)
{
	this->tid = tid;
	this->username = username;
	this->password = password;
}

void Teacher::openMenu()
{
	system("cls");
	cout << "\t\t\t\t" << " 欢迎" + this->username + "教师登录" << endl;
	cout << "\t\t\t\t" << "===============================" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "|       1. 查看所有预约       |" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "|       2. 审核预约           |" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "|       0. 注销登录           |" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "|                             |" << endl;
	cout << "\t\t\t\t" << "===============================" << endl;
}

bool Teacher::showAllorder()
{
	return mysqlCon::allOrder();
}

void Teacher::verifyOrder()
{
	if (showAllorder()) {
		string room;
		cout << "\t\t请输入要审核的机房号：";
		cin >> room;
		string time;
		cout << "\t\t请输入要审核的时间：";
		cin >> time;
		if (mysqlCon::verify(room, time)) {
			int c;
			cout << "\t\t是否同意该申请？输入1同意申请，输入2拒绝申请：";
			cin >> c;
			mysqlCon::verifyOrder(room, time, c);
		}
		else {
			cout << "\t\t您输入的预约记录有误，请重新输入！" << endl;
			system("pause");
			return;
		}
	}
}
