#include "TicketManager.hpp"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Path.hpp"

void TicketManager::reset() { bookingCount = 0; }
bool TicketManager::isTicketExist(const char* newTicketCode){
    for(int i = 0; i < bookingCount; i++ ){
        if (strcmp(ticketCode[i],newTicketCode) == 0) return true;
    }
    return false;
}
void TicketManager::addTicket(const char *newTicketCode, int seat, const std::string& name, const std::string& phone){
    strcpy(ticketCode[bookingCount], newTicketCode);
    seatAssigned[bookingCount] = seat;
    passengerNames[bookingCount] = name;
    passengerPhones[bookingCount] = phone;
    bookingCount++;
}

void TicketManager::exportTicket(const char* code, const std::string& name, const std::string& phone,
                                 const std::string& fCode, const std::string& dep, const std::string& dest,
                                 const std::string& time, const std::string& seatStr, const std::string& seatClass) {
    std::string filename = std::string(PATH_TICKETS_TICKET) + code + ".txt" ;
    cout << filename;
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "============ THÔNG TIN VÉ MÁY BAY ============" << "\n";
        out << "Mã chuyến bay       : " << fCode << "\n";
        out << "Nơi đi              : " << dep << "\n";
        out << "Nơi đến             : " << dest << "\n";
        out << "Ngày/Giờ khởi hành  : " << time << "\n";
        out << "----------------------------------------------" << "\n";
        out << "Mã vé               : " << code << "\n";
        out << "Hành khách          : " << name << "\n";
        out << "Số điện thoại       : " << phone << "\n";
        out << "Mã ghế ngồi         : " << seatStr << "\n";
        out << "Hạng ghế            : " << seatClass << "\n";
        out << "==============================================" << "\n";
        out.close();
        std::cout << endl << "--- Đã xuất file vé ---  \n";
    }
    else {
        std::cout << "Lỗi: Không thể lưu vé! \n";
    }
}

void TicketManager::printTicketInfo(const char* searchCode) {
    for(int i = 0; i < bookingCount; i++) {
        if (strcmp(ticketCode[i], searchCode) == 0) {
            std::cout << "--- Thông tin vé ---" << std::endl;
            std::cout << "Mã vé: " << ticketCode[i] << std::endl;
            std::cout << "Hành khách: " << passengerNames[i] << std::endl;
            std::cout << "Số điện thoại: " << passengerPhones[i] << std::endl;
            int row = (seatAssigned[i] - 1) / 6 + 1;
            char col = 'A' + ((seatAssigned[i] - 1) % 6);
            std::string seatClass = (seatAssigned[i] <= 12) ? "Business Class" : "Economy Class";
            std::cout << "Mã ghế: ";
            if (row < 10) std::cout << "0" << row << col;
            else std::cout << row << col;
            std::cout << " (" << seatClass << ")" << std::endl;
            return;
        }
    }
    std::cout << "Không tìm thấy thông tin cho mã vé: " << searchCode << std::endl;
}

void TicketManager::exportAllTickets(const std::string& filename) {
    std::ofstream out(PATH_TICKETS);
    if (!out.is_open()) {
        std::cout << "Lỗi: Không thể mở file " << "danh_sach_ve.txt" << " để ghi!" << std::endl;
        return;
    }
    if (bookingCount == 0) {
        out << "Chưa có vé nào được đặt trong hệ thống.\n";
        std::cout << "Chưa có vé nào được đặt." << std::endl;
    } else {
        cout << "bookingCount: " << bookingCount << endl;
        out << "============ DANH SÁCH VÉ ĐÃ ĐẶT ============\n";
        for (int i = 0; i < bookingCount; i++) {
            out << "Mã vé        : " << ticketCode[i] << "\n";
            out << "Hành khách   : " << (passengerNames[i].empty() ? "N/A (Khách từ phiên làm việc trước)" : passengerNames[i]) << "\n";
            out << "Số điện thoại: " << (passengerPhones[i].empty() ? "N/A" : passengerPhones[i]) << "\n";
            int row = (seatAssigned[i] - 1) / 6 + 1;
            char col = 'A' + ((seatAssigned[i] - 1) % 6);
            std::string seatClass = (seatAssigned[i] <= 12) ? "Business Class" : "Economy Class";
            out << "Ghế          : " << (row < 10 ? "0" : "") << row << col << " (" << seatClass << ")\n";
            out << "---------------------------------------------\n";
        }
        std::cout << "--- Đã xuất danh sách vé ra file --- ";
    }
    out.close();
}

int TicketManager::getSeatByTicketCode(const char* code) {
    for(int i = 0; i < bookingCount; i++) {
        if (strcmp(ticketCode[i], code) == 0) {
            return seatAssigned[i];
        }
    }
    return -1;
}

bool TicketManager::removeTicket(const char* code) {
    int index = -1;
    for(int i = 0; i < bookingCount; i++) {
        if (strcmp(ticketCode[i], code) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    std::string filename = PATH_TICKETS_TICKET + std::string(code) + ".txt";
    std::remove(filename.c_str());

    for(int i = index; i < bookingCount - 1; i++) {
        strcpy(ticketCode[i], ticketCode[i+1]);
        seatAssigned[i] = seatAssigned[i+1];
        passengerNames[i] = passengerNames[i+1];
        passengerPhones[i] = passengerPhones[i+1];
    }
    bookingCount--;
    return true;
}
