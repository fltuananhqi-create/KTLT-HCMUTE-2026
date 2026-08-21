#include<iostream>
#include<string>

using namespace std;

//cấu trúc
struct DATE {
    int day;
    int month;
    int year;
};

struct hocsinh {
    string mshs;
    string hoten;
    DATE ngaysinh;
    string diachi;
    string gioitinh;
    float diemtb;
};

//hàm xử lí
void nhapdate(DATE &d) {
    char slash;
    cin >> d.day >> slash >> d.month >> slash >> d.year;
}

void xuatdate(DATE d) {
    if (d.day < 10) cout << "0";
    cout << d.day << "/";
    if (d.month < 10) cout << "0";
    cout << d.month << "/" << d.year << endl;
}

void nhap1hs(hocsinh &hs) {
    cin >> hs.mshs;
    getline(cin, hs.hoten);
    nhapdate(hs.ngaysinh);
    getline(cin, hs.diachi);
    cin >> hs.gioitinh;
    cin >> hs.diemtb;
}

void xuat1hs(hocsinh hs) {
    cout << hs.mshs << endl;
    cout << hs.hoten << endl;
    xuatdate(hs.ngaysinh);
    cout << hs.diachi << endl;
    cout << hs.gioitinh << endl;
    cout << hs.diemtb << endl;
}

void nhapdanhsach(hocsinh hs[], int n) {
    for (int i = 0; i < n; i++) {
        nhap1hs(hs[i]);
    }
}

void xuatdanhsach(hocsinh hs[], int n) {
    for (int i = 0; i < n; i++) {
        xuat1hs(hs[i]);
    }
}

int demlenlop(hocsinh hs[], int n) {
    int dem = 0;
    for (int i = 0; i < n; i++) {
        if (hs[i].diemtb >= 5.0) {
            dem++;
        }
    }
    return dem;
}

int main() {
    int siso;
    cin >> siso;
    hocsinh hs[50];
    nhapdanhsach(hs, siso);
    xuatdanhsach(hs, siso);
    cout << demlenlop(hs, siso) << endl;

    return 0;
}