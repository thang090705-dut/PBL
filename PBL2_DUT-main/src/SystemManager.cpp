#include "SystemManager.hpp"
#include "Path.hpp"
#include "SeatManager.hpp"
#include "ErrorHandler.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <cstring>
#include <stdexcept>

using namespace std;

void SystemManager::openFlight(){
    flight.inputFlight();
    ticketManager.reset();
    if (!fileManager.loadTicketsData(PATH_TICKETS, ticketManager)) {
        cout << "=> Không thể tải danh sách 60 vé!" << endl;
    }
    if (!fileManager.loadSeatMap(PATH_SEATS, seatManager, ticketManager)) {
        cout << "Khong the tai du lieu ghe tu file!" << endl;
    }
}
void SystemManager::displaySeatMap(){
    cout << "          THÔNG TIN CHUYẾN BAY: " << flight.getFlightCode() << " | " << flight.getDeparture() << " -> " << flight.getDestination() << " | " << flight.getFlightTime() << "\n";
    seatManager.displaySeats();
    cout << "          => Tổng số ghế còn trống: " << seatManager.countEmptySeats() << endl;
}

void SystemManager::bookingProcess() {
    while (true) {
        int count_empty = seatManager.countEmptySeats();
        
        if (count_empty <= 0) {
            cout << "          [!] CHUYẾN BAY ĐÃ HẾT GHẾ TRỐNG!" << endl;
            return;
        }

        string code;
        cout << "          Nhập mã vé của bạn (hoặc nhập 'Q' để thoát ra menu): ";
        cin >> code;
        ErrorHandler::clearInputBuffer();

        if (code == "Q" || code == "q") {
            cout << "          Đã thoát quá trình đặt chỗ." << endl;
            return;
        }

        if (!ticketManager.isTicketExist(code.c_str())) {
            cout << "          [!] Lỗi: Mã vé không tồn tại trong hệ thống!" << endl;
            continue;
        }

        cout << "\n          [*] Hành khách: " << ticketManager.getPassengerName(code.c_str()) 
             << " | SĐT: " << ticketManager.getPassengerPhone(code.c_str()) << "\n\n";

        int currentSeat = ticketManager.getSeatByTicketCode(code.c_str());
        if (currentSeat > 0 && currentSeat <= 60) {
            cout << "          [!] Lỗi: Vé này đã được chọn chỗ (Ghế số " << currentSeat << ")!" << endl;
            continue;
        }

        displaySeatMap();

        while (true) {
            string seatInput;
            int seatNum = -1;
            
            cout << "\n          Nhập mã ghế muốn chọn (VD: 01A) hoặc nhập 'Q' để đổi vé: ";
            cin >> seatInput;
            ErrorHandler::clearInputBuffer();

            if (seatInput == "Q" || seatInput == "q") {
                cout << "          Đã hủy thao tác chọn ghế." << endl;
                break;
            }

            if (seatInput.length() >= 2) {
                char colChar = toupper(seatInput.back());
                if (colChar >= 'A' && colChar <= 'F') {
                    try {
                        int row = stoi(seatInput.substr(0, seatInput.length() - 1));
                        seatNum = (row - 1) * 6 + (colChar - 'A') + 1;
                    } catch (const std::invalid_argument&) {
                        seatNum = -1;
                    } catch (const std::out_of_range&) {
                        seatNum = -1;
                    } catch (...) {
                        seatNum = -1;
                    }
                }
            }

            if (seatNum != -1 && seatManager.assignSeats(seatNum)) {
                seatManager.setTicketCodeForSeat(seatNum, code.c_str());
                ticketManager.updateTicketSeat(code.c_str(), seatNum);
                
                fileManager.saveSeatMap(PATH_SEATS, seatManager);
                
                string name = ticketManager.getPassengerName(code.c_str());
                string phone = ticketManager.getPassengerPhone(code.c_str());
                string seatClass = (seatNum <= 12) ? "Business Class" : "Economy Class";
                
                cout << "\n          ╔════════════════════════════════════════════════════════════╗\n";
                cout << "          ║                   THÔNG TIN VÉ MÁY BAY                     ║\n";
                cout << "          ╠════════════════════════════════════════════════════════════╣\n";
                cout << "            Mã chuyến bay       : " << flight.getFlightCode() << "\n";
                cout << "            Nơi đi              : " << flight.getDeparture() << "\n";
                cout << "            Nơi đến             : " << flight.getDestination() << "\n";
                cout << "            Ngày/Giờ khởi hành  : " << flight.getFlightTime() << "\n";
                cout << "          ╠════════════════════════════════════════════════════════════╣\n";
                cout << "            Mã vé               : " << code << "\n";
                cout << "            Hành khách          : " << name << "\n";
                cout << "            Số điện thoại       : " << phone << "\n";
                cout << "            Mã ghế ngồi         : " << seatInput << "\n";
                cout << "            Hạng ghế            : " << seatClass << "\n";
                cout << "          ╚════════════════════════════════════════════════════════════╝\n";
                
                cout << "          [+] Chọn chỗ thành công! Ghế: " << seatInput << " | Mã vé: " << code << endl;
                
                char confirm;
                cout << "          Bạn có muốn in vé (xuất file .txt) không? (Y/N): ";
                cin >> confirm;
                ErrorHandler::clearInputBuffer();
                if (toupper(confirm) == 'Y') {
                    ticketManager.exportTicket(code.c_str(), name, phone, flight.getFlightCode(), flight.getDeparture(), flight.getDestination(), flight.getFlightTime(), seatInput, seatClass);
                }
                break;
            } else {
                cout << "          [!] Lỗi: Mã ghế '" << seatInput << "' không hợp lệ hoặc đã có người đặt!" << endl;
            }
        }
    }
}

void SystemManager::checkTicket(){
    string code;
    cout << "Nhập mã vé cần kiểm tra: ";
    cin >> code;
    ErrorHandler::clearInputBuffer();

    if (!ticketManager.isTicketExist(code.c_str())) {
        cout << "=> Lỗi: Mã vé không tồn tại trong hệ thống!" << endl;
        return;
    }
    ticketManager.printTicketInfo(code.c_str());
    
    int seat = ticketManager.getSeatByTicketCode(code.c_str());
    if (seat > 0) {
        string command = "start " + string(PATH_TICKETS_TICKET) + code + ".txt"; 
        system(command.c_str());
    } else {
        cout << "=> Vé này chưa được chọn chỗ ngồi nên chưa có file vé xuất ra." << endl;
    }
}

void SystemManager::exportBookedTickets(){
    string exportPath = PATH_EXPORTED_TICKETS;
    ticketManager.exportAllTickets(exportPath);
    string command = "start " + exportPath; 
    system(command.c_str());
}

void SystemManager::cancelTicketProcess() {
    char input;
    cout << "          Hủy toàn bộ vé (Nhấn X) | Hủy 1 vé (Nhấn Y) | Quay lại menu (Nhấn Q): ";
    cin >> input;
    ErrorHandler::clearInputBuffer();
    input = toupper(input);
    
    if (input == 'Q') {
        cout << "          Đã hủy thao tác, quay lại menu chính." << endl;
        return;
    } else if (input == 'X') {
        cancelAllTickets();
        return;
    } else if (input == 'Y') {
        string code;
        cout << "          Nhập mã vé cần hủy: ";
        cin >> code;
        ErrorHandler::clearInputBuffer();

        int seatNum = ticketManager.getSeatByTicketCode(code.c_str());
        if (seatNum != -1) {
            char confirm;
            cout << "          Bạn có chắc chắn muốn hủy vé " << code << " không? (Y/N): ";
            cin >> confirm;
            ErrorHandler::clearInputBuffer();
            
            if (toupper(confirm) == 'Y') {
                ticketManager.removeTicket(code.c_str());
                seatManager.unassignSeat(seatNum);
                fileManager.saveSeatMap(PATH_SEATS, seatManager);
                cout << "          [+] Đã hủy vé " << code << endl;
            } else {
                cout << "          Đã hủy thao tác xóa vé." << endl;
            }
        } else {
            cout << "          [!] Không tìm thấy mã vé: " << code << " trong hệ thống!" << endl;
        }
    } else {
        cout << "          [!] Lựa chọn không hợp lệ!" << endl;
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
    ErrorHandler::clearInputBuffer();
    
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