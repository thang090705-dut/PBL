# ✈️ ITF Airway - Airline Seat Booking Management System (PBL2 - DUT)

## 📖 Giới thiệu
Dự án **PBL2 - Dự án cơ sở lập trình** là ứng dụng Console quản lý đặt chỗ ngồi trên máy bay, được viết bằng ngôn ngữ **C++**. Hệ thống cho phép quản lý thông tin chuyến bay, sơ đồ ghế, thông tin hành khách và hỗ trợ xuất vé điện tử dưới dạng tệp văn bản.

## ✨ Các tính năng chính
- 🔐 **Hệ thống đăng nhập:** Bảo mật quyền truy cập cho quản trị viên (có ẩn mật khẩu).
- 💺 **Quản lý sơ đồ ghế:** Hiển thị trực quan sơ đồ ghế máy bay (60 ghế). Phân loại hạng ghế (Business/Economy).
- 🎟️ **Đặt chỗ & Xuất vé:** 
    - Kiểm tra mã vé hợp lệ từ danh sách có sẵn.
    - Cho phép hành khách chọn vị trí ghế trống.
    - Tự động xuất file vé riêng lẻ (.txt) cho từng hành khách.
- 🔍 **Tra cứu & Quản lý:** 
    - Tìm kiếm thông tin hành khách theo mã vé.
    - Xuất tổng hợp danh sách tất cả các vé đã đặt chỗ ra file `.txt`.
- ❌ **Hủy vé:** Hỗ trợ hủy từng vé đơn lẻ hoặc giải phóng toàn bộ sơ đồ ghế khi cần thiết.
- 💾 **Lưu trữ dữ liệu:** Tự động đồng bộ trạng thái ghế vào tệp tin sau mỗi phiên làm việc.

## 🛠 Công nghệ sử dụng
- **Ngôn ngữ:** C++ (Standard C++11 hoặc cao hơn).
- **Thư viện:** STL , `iostream`, `fstream`, `chrono`, `thread`.
- **Hệ điều hành hỗ trợ:** Windows (tối ưu hóa hiển thị UTF-8 và phím bấm), Linux/macOS.
- **Công cụ biên dịch:** `g++` hoặc `MinGW`.

## 📂 Cấu trúc thư mục chi tiết
```bash
PBL2_DUT-main/
├── data/                   # Dữ liệu đầu vào
│   ├── seats.txt           # Lưu trạng thái ghế hiện tại (Mã ghế - 1: Đã đặt, 0: Trống)
│   ├── users.txt           # Danh sách tài khoản admin
│   ├── tickets_list.txt    # Danh sách mã vé và thông tin khách hàng cơ sở
│   └── seat_template.txt   # Giao diện sơ đồ ghế dạng ASCII
├── export/                 # Dữ liệu đầu ra
│   ├── tickets/            # Thư mục chứa các file vé lẻ (.txt) khi xuất vé
│   └── booked_tickets.txt  # File tổng hợp danh sách hành khách đã có chỗ
├── include/                # File tiêu đề (.hpp)
│   ├── Constants.hpp       # Định nghĩa các hằng số (MAX_SEATS,...)
│   ├── ErrorHandler.hpp    # Xử lý ngoại lệ và làm sạch bộ đệm cin
│   ├── FileManager.hpp     # Lớp chuyên trách đọc/ghi tệp tin
│   ├── Flight.hpp          # Quản lý thông tin chuyến bay (Số hiệu, hành trình)
│   ├── ITF_airway.hpp      # Interface/Header tổng hợp các thư viện
│   ├── Login.hpp           # Xử lý xác thực người dùng
│   ├── Path.hpp            # Quản lý tập trung các đường dẫn file
│   ├── SeatManager.hpp     # Logic quản lý sơ đồ và trạng thái ghế
│   ├── SystemManager.hpp   # Lớp điều phối (Controller) toàn bộ ứng dụng
│   └── TicketManager.hpp   # Quản lý danh sách vé và thông tin hành khách
├── src/                    # Triển khai mã nguồn (.cpp)
│   ├── FileManager.cpp     
│   ├── Login.cpp           
│   ├── main.cpp            
│   ├── SeatManager.cpp     
│   ├── SystemManager.cpp   
│   └── TicketManager.cpp   
└── README.md
```

## 🔄 Quy trình hoạt động (Workflow)
1. **Khởi động & Đăng nhập:** 
   - Hệ thống yêu cầu xác thực người quản lý thông qua `Login`.
   - Sau khi đăng nhập thành công, `SystemManager` sẽ tải dữ liệu từ thư mục `data/`.
2. **Quản lý Chuyến bay:** 
   - Hệ thống nạp thông tin chuyến bay và sơ đồ ghế hiện tại vào bộ nhớ.
3. **Xử lý Nghiệp vụ:**
   - **Đặt chỗ:** Kiểm tra mã vé -> Chọn ghế trống từ sơ đồ -> Cập nhật trạng thái -> Xuất file vé lẻ vào `export/tickets/`.
   - **Tra cứu:** Hiển thị sơ đồ ghế trực quan (XX là ghế đã đặt) và thông tin hành khách.
   - **Hủy vé:** Giải phóng ghế đã chọn và cập nhật lại tệp dữ liệu.
4. **Kết thúc:** 
   - Lưu mã ghế vào `data/tickets_list.txt` ứng với hành khách đã đặt
   - Lưu toàn bộ trạng thái sơ đồ ghế mới nhất vào `data/seats.txt` trước khi đóng chương trình.

## Hướng dẫn cài đặt và chạy
1. Download toàn bộ dự án về máy của bạn.
2. Mở thư mục dự án bằng IDE của bạn.
3. Đảm bảo bạn đã cài đặt trình biên dịch C++ (ví dụ: `g++` hoặc `MinGW`).
4. Biên dịch và chạy file `main.cpp` trong thư mục `src`.

## Thành viên nhóm thực hiện
- **[Nguyễn Hữu Thắng]** - [MSSV : 123230128]
- **[Huỳnh Tuấn Khoa]** - [MSSV : 123230114]
- **[Trần Dương Hùng]** - [MSSV : 123230108]
- **Giảng viên hướng dẫn:** [Ths. Trần Hồ Thủy Tiên]
