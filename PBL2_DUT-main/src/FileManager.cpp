#include "FileManager.hpp"
#include <iostream>
#include <fstream>
#include "Path.hpp"
using namespace std;

bool FileManager::loadSeatMap(const std::string& path, SeatManager &sm, TicketManager &tm){
    ifstream fin(PATH_SEATS);
    if (!fin.is_open()) return false;
    tm.reset();
    int total;
    fin >> total;
    sm.settotalSeats(total);
    for (int i = 0; i < total; i++){
        int no, status;
        fin >> no;
        fin >> status;
        if (status == 1) {
            char code[10];
            fin >> code;
            sm.setSeatCode(i, code);
            tm.addTicket(code, no);
        }
        sm.setSeats(i, no, status);
    }
    fin.close();
    return true;
}
bool FileManager::saveSeatMap(const std::string& path, const SeatManager &sm){
    ofstream fout(PATH_SEATS);
    if(!fout.is_open()) return false;
    int total = sm.gettotalSeats();
    fout << total << endl;
    for(int i = 0; i < total; i++){
        fout << sm.getseatNo(i) << " " << sm.getseatStatus(i);
        if (sm.getseatStatus(i) == 1) {
            fout << " " << sm.getSeatCode(i);
        }
        fout << endl;
    }
    fout.close();
    return true;
}
void FileManager::printFileContent(const std::string& path){
    ifstream fin(PATH_SEATS);
    if (!fin.is_open()) return;
    cout << endl << "--- Nội dung file ---" << endl;
    char ch;
    while(fin.get(ch)){
        cout << ch;
    }
    cout << "--------------------------------------------------" << endl;
    fin.close();
}