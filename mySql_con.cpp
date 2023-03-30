#include<iostream>
#include"mysqlCon.h"
#include<mysql.h>
#include<Windows.h>
using namespace std;

mysqlCon::mysqlCon()
{
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "030822", "bking", 3306, NULL, 0) == NULL) {
		cout << "错误原因：" << mysql_error(&mysql) << endl;
		cout << "连接失败！" << endl;
	}
}

mysqlCon::~mysqlCon()
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

bool mysqlCon::varify_ma(string username,string password)
{
	string ret = "select * from manager where user='" + username + "' and password='"+password+"';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	if (mysql_affected_rows(&mysql)) return true;
	else return false;
}

bool mysqlCon::varify_stu(string sid, string username, string password)
{
	string ret = "select * from student where id='" + sid + "' and name='" + username + "' and password='" + password + "';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	if (mysql_affected_rows(&mysql)) return true;
	else return false;
}

bool mysqlCon::varify_tea(string tid, string username, string password) {
	string ret = "select * from teacher where id='" + tid + "' and name='" + username + "' and password='" + password + "';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	if (mysql_affected_rows(&mysql)) return true;
	else return false;
}

bool mysqlCon::query_id_tea(string id)
{
	string ret = "select * from teacher where id='" + id + "';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	if (mysql_affected_rows(&mysql)) return true;
	else return false;
}

bool mysqlCon::query_id_stu(string id) {
	string ret = "select * from student where id='" + id + "';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	if (mysql_affected_rows(&mysql)) return true;
	else return false;
}

void mysqlCon::query_info()
{
	string ret = "select id,name from student";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	cout << "\t\t学生信息：" << endl;
	cout << "\t\t学号\t" << "账号" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << "\t\t" << row[0] << "\t" << row[1] << endl;
	}
	cout << endl;
	ret = "select id,name from teacher";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
	}
	res = mysql_store_result(&mysql);
	cout << "\t\t教师信息：" << endl;
	cout << "\t\t工号\t" << "账号" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << "\t\t" << row[0] << "\t" << row[1] << endl;
	}
	system("pause");
}


void mysqlCon::del()
{
	if (allOrder()) {
		cout << "\t\t确定要清除吗？输入数字1确认：";
		int c;
		cin >> c;
		if (c == 1) {
			string ret = "delete from booking_info;";
			if (mysql_query(&mysql, ret.c_str())) {
				cout << mysql_error(&mysql);
			}
			cout << "\t\t\t\t\t删除成功！" << endl;
			system("pause");
		}
		else {
			cout << "\t\t\t\t\t取消删除！" << endl;
			system("pause");
			return;
		}
	}
}

//
//bool mysqlCon::query_id_tea(string id)
//{
//	string ret = "select * from teacher where id='" + id + "';";
//	if (mysql_query(&mysql, ret.c_str())) {
//		cout << mysql_error(&mysql);
//	}
//	res = mysql_store_result(&mysql);
//	if (mysql_affected_rows(&mysql)) return true;
//	else return false;
//}
//
void mysqlCon::sign_up_stu()
{
	cout << "\t\t输入学号：";
	cin >> this->id;
	if (query_id_stu(id)) {
		cout << "\t\t该学生账号已存在！" << endl;
		system("pause");
		return;
	}
	cout << "\t\t输入账号：";
	cin >> this->name;
	cout << "\t\t输入密码：";
	cin >> this->pwd;
	string ret = "insert student values('" + id + "','" + name + "','" + pwd + "');";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << "\t\t插入失败，原因为：" << mysql_error(&mysql) << endl;
	}
	else {
		cout << "\t\t\t\t\t学生信息添加成功！" << endl;
	}
	system("pause");
}

void mysqlCon::sign_up_tea()
{
	cout << "\t\t输入工号：";
	cin >> this->id;
	if (query_id_tea(id)) {
		cout << "\t\t该教师账号已存在！" << endl;
		system("pause");
		return;
	}
	cout << "\t\t输入账号：";
	cin >> this->name;
	cout << "\t\t输入密码：";
	cin >> this->pwd;
	string ret = "insert teacher values('" + id + "','" + name + "','" + pwd + "');";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << "\t\t插入失败，原因为：" << mysql_error(&mysql) << endl;
	}
	else {
		cout << "\t\t\t\t\t教师信息添加成功！" << endl;
	}
	system("pause");
}

void mysqlCon::query_room()
{
	int ret = mysql_query(&mysql, "select * from room;");
	res = mysql_store_result(&mysql);
	cout << "\t\t\t\t机房编号\t容纳人数" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << "\t\t\t\t" << row[0] << "\t\t" << row[1] << endl;
	}
	system("pause");
}

void mysqlCon::apply(string room,string id,string time)
{
	string ret = "insert booking_info(id_r,id_s,time) values('" + room + "','" + id + "','" + time + "');";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << "\t\t插入失败，原因为：" << "机房" << room + "已在" + time + "被预约" << endl;
	}
	else {
		cout << "\t\t\t\t\t预约成功！" << endl;
	}
}

bool mysqlCon::allOrder()
{
	string ret = "select id_r,id_s,time,state from booking_info";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
		return false;
	}
	res = mysql_store_result(&mysql);
	if (row = mysql_fetch_row(res)) {
		cout << "\t\t预约信息：" << endl;
		cout << "\t\t机房编号\t" << "学生学号\t" << "预约时间\t" << "预约状态" << endl;
		cout << "\t\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t" << row[3] << endl;
		while (row = mysql_fetch_row(res)) {
			cout << "\t\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t" << row[3] << endl;
		}
		system("pause");
		return true;
	}
	else {
		cout << "\t\t\t\t\t暂无预约信息！" << endl;
		system("pause");
		return false;
	}
	return false;
}

bool mysqlCon::verify(string room, string time) {
	string ret = "select id_r,time,state from booking_info where id_r='" + room + "' and time='"+time+"'; ";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
		system("pause");
		return false;
	}
	res = mysql_store_result(&mysql);
	if (row = mysql_fetch_row(res)) return true;
	else return false;
}

bool mysqlCon::myOrder(string id)
{
	string ret = "select id_r,time,state from booking_info where id_s='"+id+"';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
		return false;
	}
	res = mysql_store_result(&mysql);
	if (row = mysql_fetch_row(res)) {
		cout << "\t\t预约信息：" << endl;
		cout << "\t\t机房编号\t" << "预约时间\t" << "预约状态" << endl;
		cout << "\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << endl;
		while (row = mysql_fetch_row(res)) {
			cout << "\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << endl;
		}
		system("pause");
		return true;
	}
	else {
		cout << "\t\t\t\t\t您暂无预约信息！" << endl;
		system("pause");
		return false;
	}
	return false;
}

void mysqlCon::cancel(string id,string time)
{
	string ret = "delete from booking_info where id_s='" + id + "' and time='"+time+"';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
		system("pause");
		return;
	}
	else {
		cout << "\t\t\t\t\t删除成功！" << endl;
	}
	system("pause");
}

bool mysqlCon::delorder(string id)
{
	string ret = "select id_r,time,state from booking_info where id_s='" + id + "' and state != '预约失败';";
	if (mysql_query(&mysql, ret.c_str())) {
		cout << mysql_error(&mysql);
		return false;
	}
	res = mysql_store_result(&mysql);
	if(row = mysql_fetch_row(res)){
		cout << "\t\t预约信息：" << endl;
		cout << "\t\t机房编号\t" << "预约时间\t" << "预约状态" << endl;
		cout << "\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << endl;
		while (row = mysql_fetch_row(res)) {
			cout << "\t\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << endl;
		}
		return true;
	}
	else {
		cout << "\t\t\t\t\t您暂无预约信息！" << endl;
		system("pause");
		return false;
	}
	return false;
}

void mysqlCon::verifyOrder(string room, string time, int c)
{
	if (c == 1) {
		string ret = "update booking_info set state='预约成功' where id_r = '" + room + "' and time = '" + time + "'; ";
		if (mysql_query(&mysql, ret.c_str())) {
			cout << mysql_error(&mysql);
			system("pause");
			return;
		}
		else {
			cout << "\t\t\t\t\t审核成功！" << endl;
		}
		system("pause");
	}
	else if (c == 2) {
		string ret = "update booking_info set state='预约失败' where id_r = '" + room + "' and time = '" + time + "'; ";
		if (mysql_query(&mysql, ret.c_str())) {
			cout << mysql_error(&mysql);
			system("pause");
			return;
		}
		else {
			cout << "\t\t\t\t\t审核成功！" << endl;
		}
		system("pause");
	}
	else {
		cout << "\t\t输入有误，请重新输入！" << endl;
		system("pause");
		return;
	}
}



//bool mysqlCon::verify_ad(string user, string password)
//{
//	string ret = "select * from manager where user='" + user + "' and password='"+password+"';";
//	if (mysql_query(&mysql, ret.c_str())) {
//		cout << mysql_error(&mysql);
//		return false;
//	}
//	res = mysql_store_result(&mysql);
//	if (mysql_affected_rows(&mysql)) return true;
//	else return false;
//}
//
//bool mysqlCon::verify_stu(string id, string user, string pass)
//{
//	string ret = "select * from student where id='" + id + "' and name='" + user + "' and password='"+pass+"';";
//	if (mysql_query(&mysql, ret.c_str())) {
//		cout << mysql_error(&mysql);
//		return false;
//	}
//	res = mysql_store_result(&mysql);
//	if (mysql_affected_rows(&mysql)) return true;
//	else return false;
//}


