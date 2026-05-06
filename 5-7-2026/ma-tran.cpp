#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    // --- BƯỚC 1: CHUẨN BỊ CÁI KHUNG ---
    int a[100][100]; 
    int r = 3; // Giả sử ma trận có 3 hàng
    int c = 3; // Và 3 cột
    FILE* fp;

    // --- BƯỚC 2: MỞ CỬA FILE ---
    // Lưu ý: File MATRIX.TXT sẽ nằm cùng thư mục với file .cpp của ông
    if (fopen_s(&fp, "MATRIX.TXT", "wt") != 0) {
        cout << "Khong the mo file de ghi!";
        return 1;
    }

    // --- BƯỚC 3: GHI BIỂN CHỈ DẪN (Số hàng, số cột) ---
    fprintf(fp, "%d %d\n", r, c);

    // --- BƯỚC 4: ĐỔ DỮ LIỆU VÀO (Vòng lặp lồng) ---
    cout << "Dang ghi ma tran vao file..." << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // Tạo dữ liệu giả: ví dụ ô (1,2) sẽ có giá trị 12
            a[i][j] = (i + 1) * 10 + (j + 1); 
            
            // Ghi con số vào file kèm khoảng cách \t
            fprintf(fp, "%d\t", a[i][j]);
        }
        fprintf(fp, "\n"); // Hết một hàng thì xuống dòng
    }

    // --- BƯỚC 5: ĐÓNG CỬA FILE ---
    fclose(fp);
    
    cout << "Da tao file MATRIX.TXT thanh cong!" << endl;
    cout << "Hay kiem tra folder 5-7-2026 cua ong nhe." << endl;

    return 0;
}