#include<iostream>
#include<mysql.h>
#include"mysqlCon.h"
#include"Identyfy.h"
#include"Manager.h"
#include"Student.h"
#include"Teacher.h"

using namespace std;

void managerMenu(Identyfy*& manager) {
	while (1) {
		manager->openMenu();
		//父类指针强转子类指针
		Manager* ma = (Manager*)manager;
		int select;
		cout << "\t\t输入您的选择：";
		cin >> select;
		switch (select)
		{
		case 1:ma->addPerson(); break;
		case 2:ma->showPerson(); break;
		case 3:ma->showRoom(); break;
		case 4:ma->clearFile(); break;
		case 0:cout << "\t\t\t\t\t注销成功！" << endl; system("pause"); system("cls"); delete manager; return; break;
		default:cout << "\t\t\t\t\t输入有误，请重新输入！" << endl; system("pause"); break;
		}
	}
}

void studentMenu(Identyfy*& student) {
	while (1) {
		student->openMenu();
		//父类指针强转子类指针
		Student* stu = (Student*)student;
		int select;
		cout << "\t\t输入您的选择：";
		cin >> select;
		switch (select)
		{
		case 1:stu->applyOrder(); break;
		case 2:stu->showMyorder(); break;
		case 3:stu->showAllorder(); break;
		case 4:stu->cancelOrder(); break;
		case 0:cout << "\t\t\t\t\t注销成功！" << endl; system("pause"); system("cls"); delete student; return; break;
		default:cout << "\t\t\t\t\t输入有误，请重新输入！" << endl; system("pause"); break;
		}
	}
}

void teacherMenu(Identyfy*& teacher) {
	while (1) {
		teacher->openMenu();
		//父类指针强转子类指针
		Teacher* tea = (Teacher*)teacher;
		int select;
		cout << "\t\t输入您的选择：";
		cin >> select;
		switch (select)
		{
		case 1:tea->showAllorder(); break;
		case 2:tea->verifyOrder(); break;
		case 0:cout << "\t\t\t\t\t注销成功！" << endl; system("pause"); system("cls"); delete teacher; return; break;
		default:cout << "\t\t\t\t\t输入有误，请重新输入！" << endl; system("pause"); break;
		}
	}
}

void login(int type) {
	Identyfy* person = NULL;
	mysqlCon* mc = new mysqlCon();
	string id;
	string username;
	string password;
	if (type == 1) {
		cout << "\t\t请输入用户名：";
		cin >> username;
		cout << "\t\t请输入密码：";
		cin >> password;
		if (mc->varify_ma(username, password)) {
			cout << "\t\t\t\t\t登陆成功！" << endl;
			system("pause");
			person = new Manager(username,password);
			managerMenu(person);
		}
		else {
			cout << "\t\t\t\t\t验证登录失败！" << endl;
			system("pause");
			system("cls");
		}
	}
	else if (type == 2) {
		cout << "\t\t请输入学号：";
		cin >> id;
		cout << "\t\t请输入用户名：";
		cin >> username;
		cout << "\t\t请输入密码：";
		cin >> password;
		if (mc->varify_stu(id,username, password)) {
			cout << "\t\t\t\t\t登陆成功！" << endl;
			system("pause");
			person = new Student(id,username,password);
			studentMenu(person);
		}
		else {
			cout << "\t\t\t\t\t验证登录失败！" << endl;
			system("pause");
			system("cls");
		}
	}
	else if (type == 3) {
		cout << "\t\t请输入工号：";
		cin >> id;
		cout << "\t\t请输入用户名：";
		cin >> username;
		cout << "\t\t请输入密码：";
		cin >> password;
		if (mc->varify_tea(id,username, password)) {
			cout << "\t\t\t\t\t登陆成功！" << endl;
			system("pause");
			person = new Teacher(id,username,password);
			teacherMenu(person);
		}
		else {
			cout << "\t\t\t\t\t验证登录失败！" << endl;
			system("pause");
			system("cls");
		}
	}
}

int main() {
	while (1) {
		system("cls");
		cout << "\t\t\t\t" << "    欢迎来到机房预约系统" << endl;
		cout << "\t\t\t\t" << "============================" << endl;
		cout << "\t\t\t\t" << "|      1. 管理员登录       |" << endl;
		cout << "\t\t\t\t" << "|                          |" << endl;
		cout << "\t\t\t\t" << "|      2. 学生登录         |" << endl;
		cout << "\t\t\t\t" << "|                          |" << endl;
		cout << "\t\t\t\t" << "|      3. 教师登录         |" << endl;
		cout << "\t\t\t\t" << "|                          |" << endl;
		cout << "\t\t\t\t" << "|      0.   退出           |" << endl;
		cout << "\t\t\t\t" << "============================" << endl;
		int key;
		cout << "\t\t输入您的选择：";
		cin >> key;
		switch (key)
		{
		case 1:login(1); break;
		case 2:login(2); break;
		case 3:login(3); break;
		case 0:cout << "\t\t\t\t\t欢迎下次使用!" << endl;system("pause"); return 0; break;
		default:cout << "\t\t\t\t\t输入有误，请重新输入！" << endl; system("pause"); break;
		}
	}
	return 0;
}