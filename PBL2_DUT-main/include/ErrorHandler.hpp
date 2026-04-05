#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <iostream>
#include <limits>
#include <string>

class ErrorHandler {
public:
    // Xóa lỗi và làm sạch bộ đệm nhập, chống trôi lệnh/lặp vô hạn
    static void clearInputBuffer() {
        if (std::cin.fail()) {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Chuẩn hóa định dạng hiển thị thông báo lỗi trên toàn hệ thống
    static void printError(const std::string& message) {
        std::cout << "          [!] LỖI: " << message << "\n";
    }
};

#endif