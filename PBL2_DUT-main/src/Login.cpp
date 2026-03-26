#include "Login.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "Path.hpp"
using namespace std;


void Login::input() {
    cout << "Tên đăng nhập: " << endl;
    getline(cin, Username);
    cout << "Mật khẩu: ";
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
    cout << endl;
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
            cout << "Khóa đăng nhập" << endl;
            return false;
        }
        cout << "Đăng nhập thất bại! Vui lòng nhập lại" << endl;
        cout << "Còn " << 3 - i << " lần đăng nhập" << endl;
        input();
    }
    cout << "Đăng nhập thành công" << endl;
    return true;
}