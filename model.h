#include <iostream>
#include <list>
#include "sqlite3.h"
#include <cstring>
#include <string>
#include <conio.h>
#include<stdio.h>

using namespace std;

class User {
public:
	string ten;
	int  id, status;
	char *username;
	char *password;
	char *birthday;
	char *fullName;
	char *Address;
	
public:
	void SignUp(); // dang ki
	void SignIn(); // dang nhap
	bool isSignin(); // kiem tra da dang nhap chua
	void SignOut(); // dang xuat
	void ShowMess(int id); // hien thi tin nhan
	void ShowMessDetail_rep(int id); // hien thi chi tiet tin nhan
	void SendMess(int id); // gui tin nhan
	void SendMess2(int id); //gui tin nhan khi nhan ctrl + l
	void AddFriend(int id); // them ban
	void ShowFriend(int id); // hien  thi ban be
	void BlockFriend(int id); // block ban be
	void Checkfrien(int id);
	void ShowMessDetail_sen(int id);

};

class ConnectSQL {
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt ;
	list<string> answer;
public:
	static int callback(void *, int, char **, char **);
	void Open();
	void InsertSQL(sqlite3 *db, char *, char *, char *, char *, char *); //  insert vao sql
	int SelectSQL(char *fn, char *ln);
	int TransNameToId(char *frien); 
	void SelectMessenger(sqlite3 *db, int id);
	void ShowMessDetail_rep(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time, int status);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ListFriend(sqlite3 *db, int id1);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void status(sqlite3 *db, int id1, int id2);
	void ListFriendSenMes(sqlite3 *db, int id1);
	void ShowMessDetail_sen(sqlite3 *db, int id1, int id2);
};