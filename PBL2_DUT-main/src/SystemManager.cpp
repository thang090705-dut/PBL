#include "SystemManager.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <cstring>
#include "Path.hpp"
#include "SeatManager.hpp"
using namespace std;

void SystemManager::openFlight(){
    flight.inputFlight();
    if (!fileManager.loadSeatMap(PATH_SEATS, seatManager, ticketManager)) {
        cout << "Khong the tai du lieu ghe tu file!" << endl;
    }
}
void SystemManager::displaySeatMap(){
    flight.displayFlightInfo();
    cout << "------------------" <<endl;
    seatManager.displaySeats();
    cout << "------------------" <<endl;
    cout << "Tổng số ghế còn trống: " << seatManager.countEmptySeats() << endl;
    cout << "------------------" << endl;
}

void SystemManager::bookingProcess() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int count_empty = seatManager.countEmptySeats();
    
    if (count_empty <= 0) {
        cout << "CHUYẾN BAY ĐÃ HẾT GHẾ TRỐNG!" << endl;
        return;
    }

    displaySeatMap();

    int numSeats = 0;
    while (true) {
        cout << "\nNhập số lượng ghế muốn đặt (Nhấn Enter để thoát): ";
        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << "Đã hủy thao tác đặt vé." << endl;
            return;
        }

        bool isValidNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isValidNumber = false;
                break;
            }
        }

        if (!isValidNumber) {
            cout << "=> Lỗi: Vui lòng chỉ nhập số!" << endl;
            continue; 
        }

        numSeats = stoi(input);

        if (numSeats <= 0) {
            cout << "=> Lỗi: Số lượng phải lớn hơn 0!" << endl;
        } else if (numSeats > count_empty) {
            cout << "=> Lỗi: Không đủ ghế trống! (Chỉ còn " << count_empty << " ghế)." << endl;
        } else {
            break;
        }
    }
    for (int i = 0; i < numSeats; ++i) {
        string seatInput;
        int seatNum = -1;
        
        cout << "\n--- Đặt vé thứ " << i + 1 << " ---" << endl;
        cout << "Nhập mã ghế (VD: 01A, 12F...): ";
        cin >> seatInput;

        if (seatInput.length() >= 2) {
            char colChar = toupper(seatInput.back());
            if (colChar >= 'A' && colChar <= 'F') {
                try {
                    int row = stoi(seatInput.substr(0, seatInput.length() - 1));
                    seatNum = (row - 1) * 6 + (colChar - 'A') + 1;
                } catch (...) {
                    seatNum = -1;
                }
            }
        }

        if (seatNum != -1 && seatManager.assignSeats(seatNum)) {
            string name, phone;
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            validateNameAndPhoneNumber(name, phone);

            char TicketCode[10];
            string generatedCode = flight.getFlightCode() + seatInput;
            strncpy(TicketCode, generatedCode.c_str(), 9);
            TicketCode[9] = '\0'; // Đảm bảo kết thúc chuỗi an toàn

            ticketManager.addTicket(TicketCode, seatNum, name, phone);
            seatManager.setTicketCodeForSeat(seatNum, TicketCode);
            
            string seatClass = (seatNum <= 12) ? "Business Class" : "Economy Class";
            ticketManager.exportTicket(TicketCode, name, phone, flight.getFlightCode(), flight.getDeparture(), flight.getDestination(), flight.getFlightTime(), seatInput, seatClass);
            
            cout << "=> Đặt thành công ghế: " << seatInput << " | Mã vé: " << TicketCode << endl;
        } else {
            cout << "=> Lỗi: Mã ghế '" << seatInput << "' không hợp lệ hoặc đã có người đặt. Vui lòng chọn lại!" << endl;
        }
    }
    fileManager.saveSeatMap(PATH_SEATS, seatManager);
    cout << "\n=> HOÀN TẤT ĐẶT " << numSeats << " VÉ VÀ LƯU DỮ LIỆU!" << endl;
}

void SystemManager::checkTicket(){
    string code;
    cout << "Nhập mã vé cần kiểm tra: ";
    cin >> code;
    string command = "start " + string(PATH_TICKETS_TICKET) + code + ".txt"; 
    system(command.c_str());
    // ticketManager.printTicketInfo(code.c_str());
}

void SystemManager::exportBookedTickets(){
    ticketManager.exportAllTickets(PATH_TICKETS);
    string command = "start " + PATH_TICKETS; 
    system(command.c_str());
}

void SystemManager::cancelTicketProcess() {
    char input;
    cout << "Hủy toàn bộ vé (Nhấn X)" << endl << "Hủy toàn bộ (Nhấn bất kỳ)" << endl;
    cin >> input;
    if (input == 'X') {
        cancelAllTickets();
        return;
    }    
    string code;
    cout << "Nhập mã vé cần hủy: ";
    cin >> code;

    int seatNum = ticketManager.getSeatByTicketCode(code.c_str());
    if (seatNum != -1) {
        ticketManager.removeTicket(code.c_str());
        seatManager.unassignSeat(seatNum);
        fileManager.saveSeatMap(PATH_SEATS, seatManager);
        cout << "Đã hủy vé " << code << endl;
    } else {
        cout << "Không tìm thấy mã vé: " << code << " trong hệ thống!" << endl;
    }
}

void SystemManager::cancelAllTickets() {
    char seats[MAX][10]; 
    int count = 0;
    
    seatManager.getAllBookedSeat(seats, count);
    
    if (count == 0) {
        cout << "Hệ thống hiện không có vé nào được đặt!" << endl;
        return;
    }

    char confirm;
    cout << "CẢNH BÁO: Bạn đang chuẩn bị hủy TOÀN BỘ " << count << " vé trên chuyến bay." << endl;
    cout << "Bạn có chắc chắn muốn tiếp tục không? (Y/N): ";
    cin >> confirm;
    
    if (toupper(confirm) != 'Y') {
        cout << "=> Đã hủy thao tác xóa toàn bộ vé." << endl;
        return;
    }

    int successCount = 0;
        for (int i = 0; i < count; i++) {
        string code(seats[i]);
        
        int seatNum = ticketManager.getSeatByTicketCode(code.c_str());
        
        if (seatNum != -1) {
            ticketManager.removeTicket(code.c_str());
            
            seatManager.unassignSeat(seatNum);
            successCount++;
        }
    }

    if (successCount > 0) {
        fileManager.saveSeatMap(PATH_SEATS, seatManager);
        cout << "=> THÀNH CÔNG: Đã hủy toàn bộ " << successCount << " vé và lưu lại dữ liệu!" << endl;
    } else {
        cout << "=> Lỗi: Không thể hủy vé do có vấn đề với dữ liệu." << endl;
    }
}

void SystemManager::closeFlight(){
    if (fileManager.saveSeatMap(PATH_SEATS, seatManager)) {
        cout << "Đã lưu file" << endl;            
    }
    else {
        cout << "Lỗi lưu file" << endl;
    }
}

void SystemManager::validateNameAndPhoneNumber(string& name, string& phoneNumber) {
    while (true) {
        cout << "Nhập tên hành khách: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "=> Lỗi: Tên không được để trống. Vui lòng nhập lại!\n";
            continue;
        }

        if (name.length() < 2) {
            cout << "=> Lỗi: Tên phải chứa ít nhất 2 chữ cái!\n";
            continue;
        }

        bool isValidName = true;
        for (char c : name) {
            if (!isalpha(c) && c != ' ') { 
                isValidName = false;
                break;
            }
        }

        if (!isValidName) {
            cout << "=> Lỗi: Tên chỉ được chứa chữ cái và khoảng trắng. Vui lòng nhập lại!\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "Nhập số điện thoại (10 số, bắt đầu bằng 0): ";
        getline(cin, phoneNumber);

        if (phoneNumber.empty()) {
            cout << "=> Lỗi: Số điện thoại không được để trống. Vui lòng nhập lại!\n";
            continue;
        }

        bool isValidPhone = true;
        for (char c : phoneNumber) {
            if (!isdigit(c)) {
                isValidPhone = false;
                break;
            }
        }

        if (!isValidPhone) {
            cout << "=> Lỗi: Số điện thoại chỉ được chứa các chữ số. Vui lòng nhập lại!\n";
            continue;
        }

        if (phoneNumber.length() != 10 || phoneNumber[0] != '0') {
            cout << "=> Lỗi: Số điện thoại phải dài đúng 10 chữ số và bắt đầu bằng '0'. Vui lòng nhập lại!\n";
        } else {
            break; 
        }
    }    
}