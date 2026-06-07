# PBL2_DUT - Hệ thống quản lý đặt chỗ ngồi trên máy bay

## 📖 Giới thiệu
Đây là Đồ án môn học PBL 2 - Dự án cơ sở lập trình.
Mô phỏng hệ thống quản lý và đặt chỗ ngồi máy bay cơ bản.
Dự án là một ứng dụng Console viết bằng ngôn ngữ **C++**.

## Tính năng chính
- **Đăng nhập hệ thống:** Bảo mật cơ bản cho người quản lý.
- **Chọn & Đặt ghế ngồi:** Giao diện đặt ghế mô phỏng theo thực tế chuyến bay.
- **Kiểm tra sơ đồ ghế:** Hiển thị trực quan các ghế còn trống / đã đặt.

## 🛠 Công nghệ sử dụng (Tech Stack)
- **Ngôn ngữ:** C++ (Standard C++11 trở lên).
- **Thư viện:** Standard Template Library (STL), `iostream`, `fstream`, `chrono`, `thread`.
- **Hệ điều hành hỗ trợ:** Windows (tối ưu hóa hiển thị UTF-8 và phím bấm), Linux/macOS.
- **Công cụ biên dịch:** `g++` hoặc `MinGW`.

## 📂 Cấu trúc thư mục
```text
PBL2_DUT-main/
├── data/                   # Chứa các tệp dữ liệu đầu vào (.txt)
│   ├── seats.txt           # Trạng thái sơ đồ ghế
│   ├── users.txt           # Thông tin tài khoản quản lý
│   ├── tickets_list.txt    # Danh sách vé cơ sở
│   └── seat_template.txt   # Mẫu hiển thị sơ đồ ghế trực quan
├── export/                 # Dữ liệu đầu ra của hệ thống
│   ├── tickets/            # Thư mục chứa các file vé lẻ cho khách hàng
│   └── booked_tickets.txt  # Tổng hợp danh sách đã chọn chỗ
├── include/                # Các tệp tiêu đề (.hpp)
│   ├── Constants.hpp       # Các hằng số định nghĩa hệ thống
│   ├── ErrorHandler.hpp    # Xử lý lỗi nhập liệu và ngoại lệ
│   ├── FileManager.hpp     # Giao tiếp đọc/ghi tệp tin
│   ├── Flight.hpp          # Thông tin chuyến bay
│   ├── Path.hpp            # Quản lý đường dẫn tệp tin
│   ├── SystemManager.hpp   # Điều phối toàn bộ quy trình logic
│   └── ...                 # Các lớp thực thể khác (Seat, Ticket, Login)
├── src/                    # Mã nguồn triển khai (.cpp)
│   ├── main.cpp            # Điểm bắt đầu của ứng dụng
│   ├── SystemManager.cpp   # Logic xử lý nghiệp vụ chính
│   └── ...                 # Triển khai các lớp tương ứng
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
   - Lưu toàn bộ trạng thái sơ đồ ghế mới nhất vào `data/seats.txt` trước khi đóng chương trình.

## Hướng dẫn cài đặt và chạy
1. Clone repository này về máy tính của bạn:
   ```bash
   git clone <https://github.com/thang090705-dut/PBL>
   ```
2. Mở thư mục dự án bằng IDE của bạn.
3. Đảm bảo bạn đã cài đặt trình biên dịch C++ (ví dụ: `g++` hoặc `MinGW`).
4. Biên dịch và chạy file `main.cpp` trong thư mục `src`.

## Thành viên nhóm thực hiện
- **[Nguyễn Hữu Thắng]** - [MSSV : 123230128]
- **[Huỳnh Tuấn Khoa]** - [MSSV : ]
- **[Trần Dương Hùng]** - [MSSV : ]
- **Giảng viên hướng dẫn:** [Ths. Trần Hồ Thủy Tiên]
