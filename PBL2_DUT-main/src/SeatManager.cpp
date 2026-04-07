#include "SeatManager.hpp"
#include "Path.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void SeatManager::settotalSeats(int total){ totalSeats = total; }
void SeatManager::setSeats(int index, int no, int status){
    seatNo[index] = no;
    seatStatus[index] = status;
}
void SeatManager::setSeatCode(int index, const char* code) {
    strcpy(seatCodes[index], code);
}
const char* SeatManager::getSeatCode(int index) const { return seatCodes[index]; }
int SeatManager::gettotalSeats() const{ return totalSeats; }
int SeatManager::getseatNo(int index) const{ return seatNo[index]; }
int SeatManager::getseatStatus(int index) const{ return seatStatus[index]; }

void SeatManager::displaySeats() const{
    ifstream fin(PATH_SEAT_TEMPLATE);
    if (!fin.is_open()) {
        cout << "          Lỗi: Không tìm thấy file mẫu sơ đồ ghế tại " << PATH_SEAT_TEMPLATE << endl;
        return;
    }
    
    string templateContent((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();
    
    for(int i = 0; i < totalSeats; i++){
        if (seatStatus[i] == 1) {
            int row = (i / 6) + 1;
            char col = 'A' + (i % 6);
            string code = (row < 10 ? "0" : "") + to_string(row) + col;
            
            size_t pos = templateContent.find(code);
            if (pos != string::npos) {
                templateContent.replace(pos, 3, "XX ");
            }
        }
    }

    cout << "\n          --- SƠ ĐỒ GHẾ CHUYẾN BAY ---\n\n";
    
    size_t pos_nl = 0;
    string indent = "          ";
    string indentedTemplate = indent + templateContent;
    while ((pos_nl = indentedTemplate.find('\n', pos_nl)) != string::npos) {
        if (pos_nl + 1 < indentedTemplate.length()) {
            indentedTemplate.insert(pos_nl + 1, indent);
        }
        pos_nl += indent.length() + 1;
    }
    
    cout << indentedTemplate << "\n\n";
}
int SeatManager::countEmptySeats(){
    int count_empty = 0;
    for(int i = 0; i < totalSeats; i++) {
        if (seatStatus[i] == 0) ++count_empty;
    }
    return count_empty;
}
void SeatManager::findEmptySeats(int result[], int &count){
    count = 0;
    cout << "Danh sách các ghế còn trống: " << endl;
    for(int i = 0; i < totalSeats; i++){
        if(seatStatus[i] == 0){
            result[count] = seatNo[i];
            count++;
        }
    }
}
bool SeatManager::assignSeats(int seat){
    for(int i = 0; i < totalSeats; i++){
        if(seatNo[i] == seat){
            if (seatStatus[i] == 0) {
                seatStatus[i] = 1;
                seatCodes[i][0] = '\0';
                return true;
            }
            else return false;
        }
    }
    return false;
}
void SeatManager::setTicketCodeForSeat(int seat, const char* code){
    for(int i = 0; i < totalSeats; i++){
        if(seatNo[i] == seat){
            strcpy(seatCodes[i], code);
            return;
        }
    }
}

void SeatManager::unassignSeat(int seatNum) {
    if (seatNum >= 1 && seatNum <= 60) {
        seatStatus[seatNum - 1] = 0;
        strcpy(seatCodes[seatNum - 1], ""); 
    }
}

void SeatManager::getAllBookedSeat(char (&result)[MAX][10], int &count) {
    count = 0;
    for (int i = 0; i < totalSeats; i++) {
        if (seatStatus[i] == 1) { 
            strcpy(result[count], seatCodes[i]); 
            count++;
        }
    }
}
