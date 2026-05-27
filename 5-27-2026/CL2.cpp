// Họ và tên: Nguyễn Tuấn Anh
// MSSV: 25110008

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // a) Đọc dữ liệu từ tập tin INPUT.TXT
    int M, N;
    int a[100][100]; // Khai báo mảng tối đa 100x100 để chứa bãi mìn
    
    ifstream file("INPUT.TXT"); 
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return 0;
    }

    // Đọc 2 số đầu tiên là kích thước M (dòng) và N (cột)
    file >> M >> N;

    // Đọc ma trận bãi mìn
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            file >> a[i][j];
        }
    }
    cout << "Da doc xong ma tran " << M << "x" << N << " tu file." << endl;

    // b) Kiểm tra tính hợp lệ của bãi mìn
    bool hop_le = true;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Chỉ kiểm tra những ô KHÔNG CÓ mìn
            if (a[i][j] != -1) {
                int dem_min = 0;
                
                // Duyệt 8 ô lân cận xung quanh ô (i, j)
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        // Bỏ qua chính giữa (ô hiện tại)
                        if (di == 0 && dj == 0) continue;
                        
                        int toa_do_i = i + di;
                        int toa_do_j = j + dj;
                        
                        // Kiểm tra xem ô lân cận có bị tràn viền ma trận không
                        if (toa_do_i >= 0 && toa_do_i < M && toa_do_j >= 0 && toa_do_j < N) {
                            if (a[toa_do_i][toa_do_j] == -1) {
                                dem_min++;
                            }
                        }
                    }
                }
                
                // Nếu số lượng mìn xung quanh khác với con số ghi trên ô đó -> Không hợp lệ
                if (dem_min != a[i][j]) {
                    hop_le = false;
                    break; 
                }
            }
        }
        if (!hop_le) break; // Thoát vòng lặp ngoài nếu phát hiện lỗi
    }

    if (hop_le) {
        cout << "Bai min nay HOP LE." << endl;
    } else {
        cout << "Bai min nay KHONG hop le!" << endl;
    }

    // c) Cho biết bãi mìn có tất cả bao nhiêu quả mìn
    int tong_min = 0;
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            if(a[i][j] == -1) {
                tong_min++;
            }
        }
    }
    cout << "Tong so qua min trong bai la: " << tong_min << endl;

    // d) Tìm vùng d x c có chứa nhiều quả mìn nhất
    int d, c;
    cout << "Nhap so dong d: ";
    cin >> d;
    cout << "Nhap so cot c: ";
    cin >> c;

    int max_min = -1;   // Lưu số lượng mìn nhiều nhất tìm được
    int max_i = -1;     // Lưu tọa độ dòng của vùng đó
    int max_j = -1;     // Lưu tọa độ cột của vùng đó

    // Quét qua các vị trí có thể đặt góc trên cùng bên trái của vùng d x c
    for (int i = 0; i <= M - d; i++) {
        for (int j = 0; j <= N - c; j++) {
            
            // Đếm số mìn trong vùng d x c tính từ gốc (i, j)
            int dem_min_vung = 0;
            for (int r = i; r < i + d; r++) {
                for (int col = j; col < j + c; col++) {
                    if (a[r][col] == -1) {
                        dem_min_vung++;
                    }
                }
            }
            
            // Cập nhật lại kỷ lục nếu tìm thấy vùng nhiều mìn hơn
            if (dem_min_vung > max_min) {
                max_min = dem_min_vung;
                max_i = i;
                max_j = j;
            }
        }
    }

    cout << "Vung " << d << "x" << c << " co nhieu min nhat nam o vi tri (" 
         << max_i << ", " << max_j << ") voi " << max_min << " qua min." << endl;

    // Đóng file 
    file.close();
    return 0;
}