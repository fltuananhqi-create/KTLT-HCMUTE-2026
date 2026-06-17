// Nguyen Tuan Anh
#include <iostream>
#include <stdio.h>

using namespace std;

struct SV {
    char mssv[15];
    char hoten[50];
    int tuoi;
    float diemtb;
};

void docfile(char filename[], SV &s) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        cout << "Khong the mo file!" << endl;
        return;
    }
    fscanf(f, "%[^\n]\n", s.mssv);
    fscanf(f, "%[^\n]\n", s.hoten);
    fscanf(f, "%d\n", &s.tuoi);
    fscanf(f, "%f\n", &s.diemtb);
    fclose(f);
}

int main() {
    SV x;
    docfile("data.txt", x);
    
    cout << "MSSV: " << x.mssv << endl;
    cout << "Ho ten: " << x.hoten << endl;
    cout << "Tuoi: " << x.tuoi << endl;
    cout << "Diem TB: " << x.diemtb << endl;
    
    return 0;
}