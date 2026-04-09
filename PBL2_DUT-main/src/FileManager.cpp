#include "FileManager.hpp"
#include "Path.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

bool FileManager::loadTicketsData(const std::string& path, TicketManager &tm) {
    ifstream fin(path);
    if (!fin.is_open()) return false;
    
    string line;
    string currentCode, currentName, currentPhone;
    
    while (getline(fin, line)) {
        if (line.find("Mã vé") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                currentCode = line.substr(pos + 1);
                currentCode.erase(0, currentCode.find_first_not_of(" \t"));
                currentCode.erase(currentCode.find_last_not_of(" \n\r\t") + 1);
            }
        } else if (line.find("Hành khách") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                currentName = line.substr(pos + 1);
                currentName.erase(0, currentName.find_first_not_of(" \t"));
                currentName.erase(currentName.find_last_not_of(" \n\r\t") + 1);
            }
        } else if (line.find("Số điện thoại") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                currentPhone = line.substr(pos + 1);
                currentPhone.erase(0, currentPhone.find_first_not_of(" \t"));
                currentPhone.erase(currentPhone.find_last_not_of(" \n\r\t") + 1);
            }
        } else if (line.find("Ghế") != string::npos) {
            if (!currentCode.empty()) {
                if (!tm.isTicketExist(currentCode.c_str())) {
                    tm.addTicket(currentCode.c_str(), -1, currentName, currentPhone);
                }
                currentCode = ""; currentName = ""; currentPhone = "";
            }
        }
    }
    fin.close();
    return true;
}

bool FileManager::loadSeatMap(const std::string& path, SeatManager &sm, TicketManager &tm){
    ifstream fin(path);
    if (!fin.is_open()) return false;
    int total;
    fin >> total;
    sm.settotalSeats(total);
    for (int i = 0; i < total; i++){
        string seatStr;
        int status;
        fin >> seatStr;
        
        int row = stoi(seatStr.substr(0, seatStr.length() - 1));
        char colChar = toupper(seatStr.back());
        int no = (row - 1) * 6 + (colChar - 'A') + 1;
        
        fin >> status;
        if (status == 1) {
            char code[10];
            fin >> code;
            sm.setSeatCode(i, code);
            if (tm.isTicketExist(code)) {
                tm.updateTicketSeat(code, no);
            } else {
                tm.addTicket(code, no);
            }
        }
        sm.setSeats(i, no, status);
    }
    fin.close();
    return true;
}
bool FileManager::saveSeatMap(const std::string& path, const SeatManager &sm){
    ofstream fout(path);
    if(!fout.is_open()) return false;
    int total = sm.gettotalSeats();
    fout << total << endl;
    for(int i = 0; i < total; i++){
        int no = sm.getseatNo(i);
        int row = (no - 1) / 6 + 1;
        char col = 'A' + ((no - 1) % 6);
        string seatStr = (row < 10 ? "0" : "") + to_string(row) + col;
        
        fout << seatStr << " " << sm.getseatStatus(i);
        if (sm.getseatStatus(i) == 1) {
            fout << " " << sm.getSeatCode(i);
        }
        fout << endl;
    }
    fout.close();
    return true;
}
void FileManager::printFileContent(const std::string& path){
    ifstream fin(path);
    if (!fin.is_open()) return;
    cout << endl << "--- Nội dung file ---" << endl;
    char ch;
    while(fin.get(ch)){
        cout << ch;
    }
    cout << "--------------------------------------------------" << endl;
    fin.close();
}