#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "model.h"
#include <string>
#include <list>
#include <ctime>
#include <sstream>
#include <string.h>
#include "sqlite3.h"
#include <stdio.h>
#include <conio.h>

using namespace std;

int ConnectSQL::callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void ConnectSQL::Open() {
	rc = sqlite3_open("appchat.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		//  fprintf(stderr, "Opened database successfully\n");

	}

}

void ConnectSQL::InsertSQL(sqlite3 *db, char *fn, char *pa, char *bir, char *name, char *add) {
	if (!db) return;

	szSQL = "insert into user1 (username, password, birthday, fullName, Address) values (?,?,?,?,?)";

	int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK) {

		sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
		sqlite3_bind_text(stmt, 3, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 4, name, strlen(name), 0);
		sqlite3_bind_text(stmt, 5, add, strlen(add), 0);


		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}

int ConnectSQL::SelectSQL(char *us, char *pa) {
	int id1 = 0;
	if (!db)return 0;

	szSQL = "SELECT * FROM  user1 WHERE username = ? and password = ? ";

	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id1;
			cout << id1;
		}
		sqlite3_finalize(stmt);
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return id1;
}


int ConnectSQL::TransNameToId(char *friends) {
	int id2 = -1;
	szSQL = "SELECT id FROM user1 WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, friends, strlen(friends), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	else {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return id2;
}

void ConnectSQL::SelectMessenger(sqlite3 *db, int id) {
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
	"(SELECT * FROM messenger where (idsen = ? or idrec = ?) ) as A LEFT JOIN user1 ON (A.idrec = user1.id OR A.idsen = user1.id)";
	//szSQL = "select contend from messenger where idrec = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----Danh sach tin nhan-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout << *it << endl;

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}

void ConnectSQL::ShowMessDetail_rep(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	cout << "Chi tiet\n";
	szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? AND idrec = ? ) ) as B LEFT JOIN  user1 ON (B.idrec = user1.id ) ";

	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	// cout << id1 << id2;
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
//		sqlite3_bind_int(stmt, 3, id1);
//q		sqlite3_bind_int(stmt, 4, id2);

		int status;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << "Nguoi gui den : " << string((const char *)sqlite3_column_text(stmt, 6)) << endl;
			cout << "noi dung tin nhan: " << string((const char *)sqlite3_column_text(stmt, 2)) << endl;
			cout << "thoi gian: " << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			status =  sqlite3_column_int(stmt, 4);
			if (status = 0)
			{
				cout << "                       \n";
			}
			else if (status = 1)
			{
				
				cout << "					    da xem\n";
			}
		}
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}

void ConnectSQL::ShowMessDetail_sen(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	cout << "Chi tiet\n";
	szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? AND idrec = ? ) ) as B LEFT JOIN  user1 ON (B.idsen = user1.id ) ";

	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	// cout << id1 << id2;
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id1);
		sqlite3_bind_int(stmt, 4, id2);

		int status;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << "Nguoi nhan: " << string((const char *)sqlite3_column_text(stmt, 6)) << endl;
			cout << "noi dung tin nhan: " << string((const char *)sqlite3_column_text(stmt, 2)) << endl;
			cout << "thoi gian: " << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			status = sqlite3_column_int(stmt, 4);
			if (status = 0)
			{
				cout << "                       da gui\n";
			}
			else if (status = 1)
			{

				cout << "                       da xem \n";
			}
		}
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}

bool ConnectSQL::CheckBlock(sqlite3 *db, int id1, int id2) {
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?) OR (id2 = ? AND id1 = ?)";
	// hiển thị cột block trong bảng friend với điều kiện điều kiện id1 = id đăng nhập và id2 trùng với id2 tương ứng với cột id1 đang đăng nhập
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		//sqlite3_bind_int(stmt, 2, id2);
		//sqlite3_bind_int(stmt, 1, id1);



		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
			sqlite3_finalize(stmt);
		}
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
	return !isblock;
}

void ConnectSQL::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time, int status) {
	szSQL = "INSERT INTO messenger VALUES (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, time, strlen(time), 0);
		sqlite3_bind_int(stmt, 5, status);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}

}

bool ConnectSQL::CheckFriend(sqlite3 *db, int id1, int id2) {
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id2 = ? AND id1 = ?)";
	// Hiểu thị tất cả các bản ghi trong bảng friend với điều kiện id1 = id đăng nhập và id2 trùng với id2 tương ứng với cột id1 đang đăng nhập
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;

			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;

			sqlite3_finalize(stmt);
		}
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return isFriend;
}

void ConnectSQL::WriteToFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}

// hiển thị bạn bè
void ConnectSQL::ListFriend(sqlite3 *db, int id1) {
	cout << "Danh sach ban be\n";
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM friend where (id1 = ? OR id2 = ?) AND isblock = 0) as A LEFT JOIN user1 ON (A.id2 = user1.id OR A.id1 = user1.id) ";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		//sqlite3_bind_int(stmt, 1, id2);
		int i = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			i++;
			cout << i << ".  " << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		}
		sqlite3_finalize(stmt);

		cout << "*********************\n";
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

// hiển thị bạn bè sau đó chọn để nhắn tin
void ConnectSQL::ListFriendSenMes(sqlite3 *db, int id1) {
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM friend where (id1 = ? OR id2 = ?) AND isblock = 0) as A LEFT JOIN user1 ON (A.id2 = user1.id OR A.id1 = user1.id) ";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		
		int a;
		cin >> a;
		int i = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			i++;
			if (a == i) {
				User us;
				us.ten = string((const char *)sqlite3_column_text(stmt, 0));
			}
		}
		sqlite3_finalize(stmt);

		cout << "*********************\n";
	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void ConnectSQL::BlockFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {

		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void ConnectSQL::status(sqlite3 *db, int id1, int id2) {
	szSQL = "UPDATE messenger SET status = 1 WHERE (idsen = ? AND idrec = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);

		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

