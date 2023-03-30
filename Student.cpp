#include"Student.h"
#include<string>
#include"mysqlCon.h"

Student::Student()
{
}
Student::Student(string sid, string username, string password) {
	this->sid = sid;
	this->username = username;
	this->password = password;
}

void Student::openMenu()
{
	system("cls");
	cout << "\t\t\t\t" << " 欢迎" + this->username + "学生登录" << endl;
	cout << "\t\t\t\t" << "================================" << endl;
	cout << "\t\t\t\t" << "|       1. 申请预约            |" << endl;
	cout << "\t\t\t\t" << "|                              |" << endl;
	cout << "\t\t\t\t" << "|       2. 查看自身预约        |" << endl;
	cout << "\t\t\t\t" << "|                              |" << endl;
	cout << "\t\t\t\t" << "|       3. 查看所有预约        |" << endl;
	cout << "\t\t\t\t" << "|                              |" << endl;
	cout << "\t\t\t\t" << "|       4. 取消预约            |" << endl;
	cout << "\t\t\t\t" << "|                              |" << endl;
	cout << "\t\t\t\t" << "|       0. 注销登录            |" << endl;
	cout << "\t\t\t\t" << "================================" << endl;
}

void Student::applyOrder()
{
	mysqlCon::query_room();
	int r;
	cout << "\t\t请输入你要预约的机房：" ;
	cin >> r;
	
	if (!(r >= 1 && r <= 3)) {
		cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); 
		return;
	}
	string room = to_string(r);
	cout << "\t\t请输入你要预约的时间：周一至周五（1-5）：";
	int c;
	cin >> c;
	int c2;
	string id = this->sid;
	switch (c)
	{
	case 1:
		cout << "\t\t选择具体时间：1.上午\t2.下午：";
		cin >> c2;
		if (c2 == 1) {
			mysqlCon::apply(room, id,"周一上午");
		}
		else if (c2 == 2) {
			mysqlCon::apply(room, id, "周一下午");
		}
		else cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
		break;
	case 2:
		cout << "\t\t选择具体时间：1.上午\t2.下午：";
		cin >> c2;
		if (c2 == 1) {
			mysqlCon::apply(room, id, "周二上午");
		}
		else if (c2 == 2) {
			mysqlCon::apply(room, id, "周二下午");
		}
		else cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
		break;
	case 3:
		cout << "\t\t选择具体时间：1.上午\t2.下午：";
		cin >> c2;
		if (c2 == 1) {
			mysqlCon::apply(room, id, "周三上午");
		}
		else if (c2 == 2) {
			mysqlCon::apply(room, id, "周三下午");
		}
		else cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
		break;
	case 4:
		cout << "\t\t选择具体时间：1.上午\t2.下午：";
		cin >> c2;
		if (c2 == 1) {
			mysqlCon::apply(room, id, "周四上午");
		}
		else if (c2 == 2) {
			mysqlCon::apply(room, id, "周四下午");
		}
		else cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
		break;
	case 5:
		cout << "\t\t选择具体时间：1.上午\t2.下午：";
		cin >> c2;
		if (c2 == 1) {
			mysqlCon::apply(room, id, "周五上午");
		}
		else if (c2 == 2) {
			mysqlCon::apply(room, id, "周五下午");
		}
		else cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
		break;
	default:cout << "\t\t输入有误，请重新选择！" << endl; system("pause"); return; break;
	}
}

void Student::showAllorder()
{
	mysqlCon::allOrder();
}

void Student::showMyorder()
{
	string id = this->sid;
	mysqlCon::myOrder(id);
}

void Student::cancelOrder()
{
	string id = this->sid;
	if (mysqlCon::delorder(id)) {
		string room;
		cout << "\t\t请选择你要删除的预约机房：";
		cin >> room;
		cout << "\t\t请输入你要删除的预约时间：";
		string time;
		cin >> time;
		if (mysqlCon::verify(room, time)) {
			int c;
			cout << "\t\t是否确认要删除？输入1确认：";
			cin >> c;
			if (c == 1) {
				mysqlCon::cancel(id, time);
			}
			else {
				cout << "\t\t\t\t\t取消删除。";
				system("pause");
			}
		}
		else {
			cout << "\t\t您的输入有误，请重新输入！" << endl;
			system("pause");
			return;
		}
	}
}
