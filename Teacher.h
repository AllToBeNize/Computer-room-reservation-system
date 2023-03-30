#pragma once
#include<iostream>
#include"Identyfy.h"
#include"mysqlCon.h"
class Teacher :public Identyfy,mysqlCon {
public:
	Teacher();
	Teacher(string tid, string username, string password);
	void openMenu();
	bool showAllorder();
	void verifyOrder();
	string tid;
};