#pragma once
#include<iostream>
#include"Identyfy.h"
#include"mysqlCon.h"
using namespace std;
class Manager :public Identyfy,mysqlCon {
public:
	Manager();
	Manager(string username, string password);
	void openMenu();
	void addPerson();
	void showPerson();
	void showRoom();
	void clearFile();
};