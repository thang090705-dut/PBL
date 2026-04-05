#include "ITF_airway.hpp"
#ifdef _WIN32
#include <windows.h>
#endif
#include <limits>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    Login log;
    if (!log.performLogin()) {
        return 0;
    }

    cout << "          Đang vào hệ thống...";
    this_thread::sleep_for(chrono::seconds(2));
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    string cmd;
    SystemManager sys;

    cout << "\n                             --- KHỞI TẠO HỆ THỐNG ---" << endl;
    sys.openFlight();

    int choice;
    do {
        cout << "\n\n";
        cout << "          ╔════════════════════════════════════════════════════════════╗\n";
        cout << "          ║               HỆ THỐNG QUẢN LÝ ĐẶT VÉ MÁY BAY              ║\n";
        cout << "          ╠════════════════════════════════════════════════════════════╣\n";
        cout << "          ║  1. Chọn chỗ ngồi                                          ║\n";
        cout << "          ║  2. Kiểm tra sơ đồ ghế                                     ║\n";
        cout << "          ║  3. Xuất danh sách vé đã chọn chỗ                          ║\n";
        cout << "          ║  4. Hủy vé                                                 ║\n";
        cout << "          ║  5. Thoát chương trình                                     ║\n";
        cout << "          ╚════════════════════════════════════════════════════════════╝\n";
        cout << "          Lựa chọn của bạn: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        cout << "\n";
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
        switch (choice) {
            case 1: sys.bookingProcess(); break;
            case 2: sys.displaySeatMap(); break;
            case 3: sys.exportBookedTickets(); break;
            case 4: sys.cancelTicketProcess(); break;
            case 5: 
                sys.closeFlight(); 
                cout << "          Thoát chương trình. Tạm biệt!\n"; 
                break;
            default: cout << "          Lựa chọn không hợp lệ. Vui lòng thử lại!\n"; break;
        }
    } while (choice != 5);

    return 0;
}