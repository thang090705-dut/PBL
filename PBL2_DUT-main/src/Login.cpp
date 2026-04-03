#include "Login.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "Path.hpp"
using namespace std;


void Login::input() {
    cout << "\n\n          --- HỆ THỐNG ĐĂNG NHẬP ---\n\n";
    cout << "          Tên đăng nhập: ";
    getline(cin, Username);
    cout << "          Mật khẩu     : ";
    Password = "";
    char ch;
    
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b' || ch == 8) { 
            if (Password.length() > 0) {
                Password.pop_back(); 
                cout << "\b \b";    
            }
        } 
        else if (ch == 0 || ch == -32) {
            _getch(); 
        }
        else {
            Password += ch;
            cout << '*'; 
        }
    }
    cout << "\n";
}
string Login::getUsername() const{ return Username; }
string Login::getPassword() const{ return Password; }

bool Login::check(){
    ifstream fin(PATH_USERS);
    if (!fin.is_open()) {
        cout << "Lỗi tải file" << endl;
        return false;
    }
    string fileUser, filePass;
    while (fin >> fileUser >> filePass) {
        if (getUsername() == fileUser && getPassword() == filePass) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}
bool Login::performLogin() {
    input();
    int i = 0;
    while (!check()) {
        ++i;
        if (i == 3) {
            cout << "\n          [!] Khóa đăng nhập. Bạn đã nhập sai quá 3 lần!\n";
            return false;
        }
        cout << "\n          [!] Đăng nhập thất bại! Vui lòng nhập lại\n";
        cout << "          [*] Bạn còn " << 3 - i << " lần thử.\n";
        input();
    }
    cout << "\n          [+] Đăng nhập thành công!\n";
    return true;
}