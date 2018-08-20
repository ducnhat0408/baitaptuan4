#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "model.h"
#include <string>
#include <cstring>
#include <list>
#include <ctime>
#include <sstream>
#include <string.h>
#include "sqlite3.h"
#include <stdio.h>
#include <conio.h>

using namespace std;

int flag = 0;
void User::SignUp() {
	ConnectSQL cn;
	cout << "Nhap thong tin dang ky!" << endl;
	username = new (char);
	birthday = new (char);
	password = new (char);
	fullName = new (char);
	Address = new (char);

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	cout << "Nhap birthday: ";
	cin >> birthday;
	cout << "Nhap fullname: ";
	cin.ignore(1);
	cin.get(fullName, 30);
	cout << "Nhap Address: ";
	cin.ignore(1);
	cin.get(Address, 30);

	cn.Open();

	cn.InsertSQL(cn.db, username, password, birthday, fullName, Address);
	cout << "\nDang ky thanh cong, moi ban dang nhap\n";
}

void User::SignIn() {

	username = new (char);
	password = new (char);
	cout << "Nhap vao user: ";
	cin >> username;
	cout << "Nhap pass: ";
	cin >> password;
	ConnectSQL cn;
	cn.Open();
	int kt = 0;
	kt = cn.SelectSQL(username, password);
	if (kt > 0) {
		flag = 1;
		id = kt;
		//cout << kt;
		//cout << flag << id;
		cout << "\nDang nhap thanh cong!\n";
	}
	else {
		cout << "Ten hoac mat khau khong dung!\n";
		flag = 0;
	}
}

void User::SignOut() {
	flag = 0;
	id = 0;
	cout << "Ban da dang xuat.\n";
}

bool User::isSignin() {
	if (flag == 1) return true;
	return false;
}

void User::ShowMess(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		cn.Open();
		cn.SelectMessenger(cn.db, id1);
	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}
}

void User::ShowMessDetail_rep(int id) {
	if (isSignin()) {
		int id2;
		cout << "Chon nguoi dung: \n";
		char *friends;
		friends = new char;
		ConnectSQL cn;
		cn.Open();

		cn.ListFriend(cn.db, id);
		cn.ListFriendSenMes(cn.db, id);
		memcpy(friends, ten.c_str(), sizeof(ten));
		id2 = cn.TransNameToId(friends);
		if (id2 > 0) {

			cout << "Gui tu *** " << friends << " ***den :\n";
			cn.ShowMessDetail_rep(cn.db, id2, id);
			cn.status(cn.db, id2, id);
			// khi an ctrl + r
			int guilai;
			char *mess, *dt;
			mess = new char;
			dt = new char;
			cout << "gui lai an ctrl + R \n";
			guilai = _getch();
			cout << guilai;
			if (guilai == 18) {
				//cout << guilai;
				cout << "To : " << friends << "\n";
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess, 200);
				//cout << mess;
				//cin >> mess;

				time_t hientai = time(0);
				dt = ctime(&hientai);
				int status = 0;
				cn.WriteToMess(cn.db, id, id2, mess, dt, status);
			}
			if (guilai != 18) {

				cout << "Da Thoat\n";
			}
		}
		else cout << "Tai khoan khong ton tai\n";

	}
	else {
		cout << "Ban chua dang nhap.\n";
	}
}

void User::ShowMessDetail_sen( int id) {
	if (isSignin()) {
		int id2;
		cout << "Chon nguoi dung: \n";
		char *friends;
		friends = new char;

		ConnectSQL cn;
		cn.Open();

		cn.ListFriend(cn.db, id);
		cn.ListFriendSenMes(cn.db, id);
		memcpy(friends, ten.c_str(), sizeof(ten));
		id2 = cn.TransNameToId(friends);
		if (id2 > 0) {

			cout << "Gui tu *** " << friends << " ***den :\n";
			cn.ShowMessDetail_sen(cn.db, id, id2);
			int guilai;
			char *mess, *dt;
			mess = new char;
			dt = new char;
			cout << "gui lai an ctrl + R \n";
			guilai = _getch();
			cout << guilai;
			if (guilai == 18) {

				cout << "To : " << friends << "\n";
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess, 200);

				time_t hientai = time(0);
				dt = ctime(&hientai);
				int status = 0;
				cn.WriteToMess(cn.db, id, id2, mess, dt, status);
			}
			if (guilai != 18) {

				cout << "Da Thoat\n";
			}
		}
		else cout << "Tai khoan khong ton tai\n";

	}
	else {
		cout << "Ban chua dang nhap.\n";
	}

}

void User::Checkfrien(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		int id2;
		cout << "chon nguoi dung: ";
		char *friends;
		friends = new char;
		cin >> friends;
		cn.Open();
		id2 = cn.TransNameToId(friends);
		if (id2 > 0) {
			if (cn.CheckFriend(cn.db, id1, id2)) {
				cout << "la banh be";
			}
			else
			{
				cout << "khong phai ban be";
			}
		}
		else {
			cout << "tai khoan khong ton tai";
		}
	}
}

// gửi tin nhắn kiểu thông thường
void User::SendMess(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		int id2;
		cout << "Chon nguoi dung: ";
		char *friends;
		friends = new char;
		cin >> friends;
		cn.Open();
		id2 = cn.TransNameToId(friends);
		//cout << id;
		//cout << id2;
		if (id2 > 0) {
			char mess[200], *dt;
			dt = new char;
			if (!cn.CheckFriend(cn.db, id1, id2)) {
				cout << " nguoi nay khong phai la ban\n";
			}
			else if (!cn.CheckBlock(cn.db, id1, id2)) {
				cout << "tai khoan bi block\n";
			}
			else {
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess,200);
				cout << "\ngui tin nhan thanh cong\n";
				cout << "tin nhan da gui la:\n"  << mess ;
				time_t hientai = time(0);
				dt = ctime(&hientai);
				status = 0;
				cn.WriteToMess(cn.db, id1, id2, mess, dt, status);
				//cn.ShowMessDetail(cn.db, id1, id2);
			}
		}
		else cout << "Tai khoan khong ton tai\n";

	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}

}

// gửi tn khi bấm ctrl + l
void User::SendMess2(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		int id2;
		char *friends;
		friends = new char;
		cout << "nhan ctrl +l de hien thi danh sach ban be";
		char nhap;
		nhap = _getch();
		if (nhap == 12) {
			cn.Open();
			cout << "Danh sach ban be la:  \n";
			cn.ListFriend(cn.db, id1);
			cn.ListFriendSenMes(cn.db, id1);
			memcpy(friends, ten.c_str(), sizeof(ten));
		}
		else
		{
			cout << "moi nhap lai!";
		}
		

		cout << "To: " << friends <<  "  \n";

		cn.Open();
		id2 = cn.TransNameToId(friends);

		if (id2 > 0) {
			char mess[200], *dt;
			dt = new char;
			if (!cn.CheckFriend(cn.db, id1, id2)) {
				cout << " nguoi nay khong phai la ban\n";
			}
			else if (cn.CheckBlock(cn.db, id1, id2)) {
				cout << "tai khoan bi block\n";
			}
			else {
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess, 200);
				cout << "\ngui tin nhan thanh cong\n";
				cout << "tin nhan da gui la:\n" << mess;
				time_t hientai = time(0);
				dt = ctime(&hientai);
				status = 0;
				cn.WriteToMess(cn.db, id1, id2, mess, dt, status);
			}
		}
		else cout << "Tai khoan khong ton tai\n";

	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}

}

void User::AddFriend(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		cout << "Nhap ten ban muon them: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		cn.Open();
		int id2 = cn.TransNameToId(newfr);
		//cout << id2;
		if (id2 > 0) {
			if (cn.CheckBlock(cn.db, id1, id2) && !cn.CheckFriend(cn.db, id1, id2)) {
				cn.WriteToFriend(cn.db, id1, id2);
				cout << "them ban thanh cong\n";
			}
			else {
				cout << "ban da bi chan hoac nguoi ay da la ban\n\n\n";
				cn.CheckFriend(cn.db, id1, id2);
			}
		}
		else cout << "Tai khoan khong ton tai\n";
	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}

}

void User::ShowFriend(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		cn.Open();
		cn.ListFriend(cn.db, id);
	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}
}

void User::BlockFriend(int id1) {
	ConnectSQL cn;
	if (isSignin()) {
		cout << "Chon nguoi block :( \n";
		char *name;
		name = new char;
		cin >> name;
		cn.Open();
		int id2 = cn.TransNameToId(name);
		if (id2 > 0) {
			cn.BlockFriend(cn.db, id1, id2);
			cout << "ban da block thanh cong nguoi nay\n";
			cn.ListFriend(cn.db, id1);
		}
		else cout << "tai khoan khong ton tai\n";
	}
	else {
		cout << "Ban chua dang nhap.\n\n";
	}
}
