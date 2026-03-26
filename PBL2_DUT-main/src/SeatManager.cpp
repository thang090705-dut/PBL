#include "SeatManager.hpp"
#include <iostream>
#include <cstring>

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
    cout << endl << "Danh sách ghế ngồi của chuyến bay: " << endl;
    cout << "Tổng số ghế ngồi: " << totalSeats << endl;
    cout << endl << "========= SƠ ĐỒ GHẾ NGỒI =========" << endl;
    cout << "Tổng số ghế: " << totalSeats << " (12 Business Class, 48 Economy Class)" << endl;
    cout << "[XX] : Đã đặt    [Số] : Ghế trống" << endl;
    cout << "----------------------------------" << endl;

    if (totalSeats > 0) {
        cout << "         [ BUSINESS CLASS ]" << endl;
    }

    for(int i = 0; i < totalSeats; i++){
        if (i == 12 && totalSeats > 12) {
            cout << endl << "         [ ECONOMY CLASS ]" << endl;
        }

        int row = (i / 6) + 1;
        char col = 'A' + (i % 6);

        if (seatStatus[i] == 1) {
            cout << "[ XX ]  ";
        } else {
            if (row < 10) cout << "[ 0" << row << col << " ]  ";
            else cout << "[ " << row << col << " ]  ";
        }

        // Tạo lối đi sau cột C (vị trí thứ 3) và xuống dòng ở mỗi 6 ghế
        if ((i + 1) % 6 == 0) {
            cout << endl;
        } else if ((i + 1) % 6 == 3) {
            cout << "  ||    "; 
        }
    }
    if (totalSeats % 6 != 0) cout << endl;
    cout << "==================================" << endl;
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
