#pragma once
#include<iostream>
#include<mysql.h>
using namespace std;
class mysqlCon {
private:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	string id;
	string name;
	string pwd;
public:
	mysqlCon();
	~mysqlCon();
	//管理员操作文件
	void sign_up_stu();
	void sign_up_tea();
	bool varify_ma(string username, string password);
	bool varify_stu(string sid, string username, string password);
	bool varify_tea(string tid, string username, string password);
	void query_info();
	void del();
	bool query_id_stu(string id);
	bool query_id_tea(string id);
	void query_room();
	//学生操作文件
	void apply(string room,string id,string time);
	bool allOrder();
	bool myOrder(string id);
	void cancel(string id,string time);
	bool delorder(string id);
	//教师操作文件
	void verifyOrder(string room, string time, int c);
	bool verify(string room, string time);
};