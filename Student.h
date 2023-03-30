#pragma once
#include<iostream>
#include"Identyfy.h"
#include"mysqlCon.h"
class Student :public Identyfy,mysqlCon{
public:
	Student();
	Student(string sid, string username, string password);
	void openMenu();
	void applyOrder();
	void showAllorder();
	void showMyorder();
	void cancelOrder();
	string sid;
};