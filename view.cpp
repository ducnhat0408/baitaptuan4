#include <iostream>
#include <cstring>
#include<stdio.h>
#include "model.h"
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

void main() {
	User us = User();
	int flag;
	ConnectSQL cn;
	while (1) {

		cout << "******>>>>Chon chuc nang: <<<<******\n\n"
			"1.Dang ky!\n"
			"2.Dang nhap!\n"
			"3.Thoat!\n"
			"******<--------->******\n";
		char choose;
		bool ktdn = true;
		choose = _getch();
		//cin >> choose;
		switch (choose)
		{
		case 49:
			us.SignUp();
			break;
		case 50:
			us.SignIn();
			if (us.id > 0);
			{
				
				while (ktdn) {
					cout << "******>>>>Chon chuc nang: <<<<******\n"
						"1.Hien thi tin nhan!\n"
						"2.Hien thi tin nhan da gui!\n"
						"3.Gui tin nhan\n"
						"4.Them ban be\n"
						"5.Hien thi ban be\n"
						"6.Block\n"
						"7.kiem tra ban be!\n"
						"8.Dang xuat!\n"
						"9.Hien thi tin nhan den!\n"
						"Ctrl + C d hien thi thanh pho"
						"******<--------->******\n";
					char a;
					a = _getch();
					switch (a) {
					case 49:
						us.ShowMess(us.id);
						break;
					case 50:
						us.ShowMessDetail_sen(us.id);
						break;
					case 51: // gui tin nhan
					{
						bool ktguitn = true;
						while (ktguitn) {
							cout << "******>>>Chon chuc nang<<<******\n"
								"1. Gui tin nhan thong thuong!\n"
								"2. Gui tin nhan theo cach 2\n"
								"Ctrl +B de tro quay lai"
								"******<--------->******\n";
							char b;
							b = _getch();
							switch (b) {
							case 49:
								us.SendMess(us.id);
								break;
							case 50:
								us.SendMess2(us.id);
								break;
							case 2:
								choose = 50;
								ktguitn = false;
								break;
							default:
								cout << "Xin moi nhap lai!\n";
								break;
							}
						}
						break;
					}	// ket thuc case 3
						
					case 52:
						us.AddFriend(us.id);
						break;
					case 53:
						us.ShowFriend(us.id);
						break;
					case 54:
						us.BlockFriend(us.id);
						break;
					case 55:
						us.Checkfrien(us.id);
						break;
					case 56:
						us.SignOut();
						ktdn = false;
						break;
					case 57:
						us.ShowMessDetail_rep(us.id);
					case 2:
						ktdn = false;
						break;
					default:
						cout << "Xin moi nhap lai!\n";
						break;
						
					}
				} // ket thuc vong while ktdn
			} // ket thuc case 2 (dang nhap)
			break;
		case 51: exit(0);
		default:
			cout << "Xin moi nhap lai!\n";
			break;
		}
	}
}