#include "Login.hpp"
#include "Path.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

void clearScreen() {
    system("cls");
}

void Login::input() {
    clearScreen();
    
    // Hiển thị khung đẹp - căn giữa
    cout << "\n\n";
    cout << "                        ╔════════════════════════════════════════╗\n";
    cout << "                        ║                                        ║\n";
    cout << "                        ║      *** HỆ THỐNG ĐĂNG NHẬP ***        ║\n";
    cout << "                        ║                                        ║\n";
    cout << "                        ╠════════════════════════════════════════╣\n";
    cout << "                        ║                                        ║\n";
    cout << "                        ║  Tên đăng nhập: ";
    
    getline(cin, Username);
    
    cout << "                        ║                                        ║\n";
    cout << "                        ║  Mật khẩu: ";
    
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
    cout << "                        ║                                        ║\n";
    cout << "                        ╚════════════════════════════════════════╝\n";
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
            cout << "\n";
            cout << "                        ╔════════════════════════════════════════╗\n";
            cout << "                        ║                                        ║\n";
            cout << "                        ║     [✗] KHÓA ĐĂNG NHẬP                 ║\n";
            cout << "                        ║  Bạn đã nhập sai quá 3 lần!            ║\n";
            cout << "                        ║                                        ║\n";
            cout << "                        ╚════════════════════════════════════════╝\n";
            cout << "\n";
            return false;
        }
        cout << "                        ╔════════════════════════════════════════╗\n";
        cout << "                        ║                                        ║\n";
        cout << "                        ║  [!] Đăng nhập thất bại!               ║\n";
        cout << "                        ║      Vui lòng nhập lại                 ║\n";
        cout << "                        ║  [*] Bạn còn " << 3 - i << " lần thử                   ║\n";
        cout << "                        ║                                        ║\n";
        cout << "                        ╚════════════════════════════════════════╝\n\n";
        input();
    }
    cout << "                        ╔════════════════════════════════════════╗\n";
    cout << "                        ║                                        ║\n";
    cout << "                        ║    [✓] ĐĂNG NHẬP THÀNH CÔNG!           ║\n";
    cout << "                        ║                                        ║\n";
    cout << "                        ╚════════════════════════════════════════╝\n\n";
    return true;
}