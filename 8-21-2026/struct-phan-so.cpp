#include <iostream>
#include <utility> // dùng cho swap()

using namespace std;

struct phanSo {
    long long tu, mau;
};

// 1. Hàm UCLN tự xử lý dấu, không dùng abs() để tránh lỗi ép kiểu int
long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void rutGon(phanSo &p) {
    if (p.mau < 0) {
        p.tu = -p.tu;
        p.mau = -p.mau;
    }
    long long g = gcd(p.tu, p.mau);
    if (g > 0) { // Chống chia cho 0
        p.tu /= g;
        p.mau /= g;
    }
}

phanSo cong(phanSo a, phanSo b) {
    phanSo kq;
    kq.tu = a.tu * b.mau + a.mau * b.tu;
    kq.mau = a.mau * b.mau;
    rutGon(kq);
    return kq;
}

phanSo nhan(phanSo a, phanSo b) {
    // 2. Rút gọn chéo TRƯỚC KHI nhân để ngăn tràn số (Overflow)
    long long g1 = gcd(a.tu, b.mau);
    a.tu /= g1;
    b.mau /= g1;
    
    long long g2 = gcd(b.tu, a.mau);
    b.tu /= g2;
    a.mau /= g2;

    phanSo kq;
    kq.tu = a.tu * b.tu;
    kq.mau = a.mau * b.mau;
    rutGon(kq);
    return kq;
}

bool lonHon(phanSo a, phanSo b) {
    return (a.tu * b.mau > a.mau * b.tu);
}

phanSo nghichDao(phanSo a) {
    swap(a.tu, a.mau);
    rutGon(a);
    return a;
}

int main() {
    // Tối ưu I/O cho C++ (giúp code chạy nhanh hơn)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Bắt lỗi nếu file input rỗng hoặc n = 0
    if (!(cin >> n) || n == 0) return 0; 
    
    phanSo ps[105]; // 4. Khai báo dư mảng để phòng test case gài
    
    for(int i = 0; i < n; i++) {
        cin >> ps[i].tu >> ps[i].mau;
        rutGon(ps[i]);
    }
    
    phanSo maxVal = ps[0];
    phanSo tong = ps[0];
    phanSo tich = ps[0];

    for(int i = 1; i < n; i++) {
        if (lonHon(ps[i], maxVal)) {
            maxVal = ps[i];
        }
        tong = cong(tong, ps[i]);
        tich = nhan(tich, ps[i]);
    }

    // In kết quả
    cout << maxVal.tu << " " << maxVal.mau << "\n";
    cout << tong.tu << " " << tong.mau << "\n";
    cout << tich.tu << " " << tich.mau << "\n";
    
    for (int i = 0; i < n; i++) {
        phanSo kq = nghichDao(ps[i]);
        cout << kq.tu << " " << kq.mau;
        
        // 3. Khử khoảng trắng thừa ở phần tử cuối cùng
        if (i < n - 1) cout << " "; 
    }
    cout << "\n";

    return 0;
}