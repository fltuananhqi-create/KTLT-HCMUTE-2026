// Họ và tên: Nguyễn Tuấn Anh
// MSSV: 25110008

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int a[9][9];
    // Mở file để đọc
    ifstream file("INPUT.TXT"); 
    
    // Kiểm tra xem file có mở thành công không
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return 0;
    }

    // Đọc dữ liệu từ file vào mảng
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            file >> a[i][j];
        }
    }

    // Đếm số ô trống (giá trị bằng 0)
    int count = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(a[i][j] == 0) {
                count++;
            }
        }
    }

    double percentage = (double)count / 81 * 100; // Tính phần trăm ô trống
    cout << "Ti le o trong: " << percentage << "%" << endl; // In ra phần trăm ô trống

    cout << "Nhap 1 so x" << endl;
    int x;
    cin >> x; // Nhập số x từ người dùng
    
    // Đếm số lần xuất hiện của x trong mảng
    int countx = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(a[i][j] == x) {
                countx++;
            }
        }
    }
    cout << "So lan xuat hien cua " << x << ": " << countx << endl;
    
    // Kiểm tra xem x có vi phạm quy tắc Sudoku không
    bool invalid = false;
    
    // Kiểm tra hàng
    for (int i = 0; i < 9; i++) {
        int rowcountx = 0;
        for (int j = 0; j < 9; j++) {
            if (a[i][j] == x) {
                rowcountx++;
            }
        }
        if (rowcountx > 1) {
            invalid = true;
            break;
        }
    }
    
    // Kiểm tra cột
    for (int j = 0; j < 9; j++) {
        int colcountx = 0;
        for (int i = 0; i < 9; i++) {
            if (a[i][j] == x) {
                colcountx++;
            }
        }
        if (colcountx > 1) {
            invalid = true;
            break;
        }
    }

    // Kiểm tra ô 3x3
    for (int r = 0; r < 9; r+= 3) {
        for (int c = 0; c < 9; c+= 3) {
            int boxcountx = 0;
            for (int i = r; i < r + 3; i++) {
                for (int j = c; j < c + 3; j++) {
                    if (a[i][j] == x) {
                        boxcountx++;
                    }
                }
            }
            if (boxcountx > 1) {
                invalid = true;
                break;
            }
        }
    }

    // In kết quả kiểm tra
    if (invalid) {
        cout << x << " vi pham quy tac Sudoku!" << endl;
    }
    else  {
        cout << x << " khong vi pham quy tac Sudoku!" << endl;
    }

    // Kiểm tra dòng ít trống nhất
    int mintrong = 9;
    int dongit = -1;
    for (int i = 0; i < 9; i++) {
        int counttrong = 0;
        for (int j = 0; j < 9; j++) {
            if (a[i][j] == 0) {
                counttrong++;
            }
        }
        if (counttrong > 0 && counttrong < mintrong) {
            mintrong = counttrong;
            dongit = i;
        }
    }
    cout << "Dong it trong nhat la dong " << dongit + 1 << " voi " << mintrong << " o trong." << endl;

    // Nếu dòng ít trống nhất chỉ có 1 ô trống, in ra số phù hợp cho ô trống
    if (mintrong == 1) {
        int tong = 0;
        for (int j = 0; j < 9; j++) {
            tong += a[dongit][j];
        }
        int thieu = 45 - tong; // Tổng của các số từ 1 đến 9 là 45 nên số thiếu sẽ là 45 trừ đi tổng hiện tại của dòng đó
        cout << "So phu hop cho o trong la: " << thieu << endl;
    }

    // Đóng file sau khi đọc xong
    file.close(); 
    return 0;
}