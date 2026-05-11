#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// Khai báo cấu trúc
struct MH {
    char mamh[15];
    char tenmh[50];
    int sotc;
    float diem;
};

struct SV {
    char mssv[10];
    char hoten[50];
    int tuoi;
    int somon;  
    MH kq[100]; 
    int tongtc, tongtctl;   
    float dtbc, dtbtl;  
};

// Khai báo các hàm thao tác
void docfile(char filename[], SV &s);
void insv(SV s);
void ghifile(char filename[], SV s);

// Định nghĩa hàm insv
void insv(SV s) {
    cout << "MSSV: " << s.mssv << endl;
    cout << "Ho ten: " << s.hoten << endl;
    cout << "Tuoi: " << s.tuoi << endl;
    cout << "So mon da hoc: " << s.somon << endl;
    cout << "Danh sach mon hoc:\n";
    for (int i = 0; i < s.somon; i++) {
        cout << "  Mon " << i + 1 << ": " << s.kq[i].tenmh 
             << " (Ma MH: " << s.kq[i].mamh 
             << ", So TC: " << s.kq[i].sotc 
             << ", Diem: " << s.kq[i].diem << ")\n";
    }
    cout << "Tong so tin chi: " << s.tongtc << endl;
    cout << "Tong so tin chi tich luy: " << s.tongtctl << endl;
    cout << "Diem trung binh chung: " << s.dtbc << endl;
    cout << "Diem trung binh tich luy: " << s.dtbtl << endl;
}

// Định nghĩa hàm docfile
void docfile(char filename[], SV &s) {
    char temp[100]; 
    FILE *fp;
    fp = fopen(filename, "rt");
    if (!fp) {  
        cout << "Khong mo duoc tap tin!\n"; 
        return;
    }

    // Đọc MSSV
    fgets(s.mssv, 10, fp);
    if(s.mssv[strlen(s.mssv) - 1] == '\n') 
        s.mssv[strlen(s.mssv) - 1] = '\0'; 

    // Đọc Họ tên
    fgets(s.hoten, 50, fp);
    if(s.hoten[strlen(s.hoten) - 1] == '\n') 
        s.hoten[strlen(s.hoten) - 1] = '\0'; 

    // Đọc tuổi và số môn
    fscanf(fp, "%d", &s.tuoi);
    fscanf(fp, "%d", &s.somon); 

    for (int i = 0; i < s.somon; i++) {
        fgets(temp, 100, fp); 
        fgets(temp, 100, fp); 

        // Đọc mã môn học và khử \n
        fgets(s.kq[i].mamh, 15, fp);
        if(s.kq[i].mamh[strlen(s.kq[i].mamh) - 1] == '\n')
            s.kq[i].mamh[strlen(s.kq[i].mamh) - 1] = '\0';

        // Đọc tên môn học và khử \n
        fgets(s.kq[i].tenmh, 50, fp);
        if(s.kq[i].tenmh[strlen(s.kq[i].tenmh) - 1] == '\n')
            s.kq[i].tenmh[strlen(s.kq[i].tenmh) - 1] = '\0';

        // Đọc số tín chỉ và điểm 
        fscanf(fp, "%d", &s.kq[i].sotc);
        fscanf(fp, "%f", &s.kq[i].diem);
    }
    
    fclose(fp);

    // Tính toán các thông số 
    int tong = 0, tongtl = 0;
    float td = 0, tdtl = 0;

    for (int i = 0; i < s.somon; i++) {
        tong += s.kq[i].sotc; 
        td += s.kq[i].sotc * s.kq[i].diem; 
        
        if (s.kq[i].diem >= 5.0) { 
            tongtl += s.kq[i].sotc; 
            tdtl += s.kq[i].sotc * s.kq[i].diem; 
        }
    }

    s.tongtc = tong; 
    s.tongtctl = tongtl; 
    s.dtbc = (tong > 0) ? td / tong : 0; 
    s.dtbtl = (tongtl > 0) ? tdtl / tongtl : 0; 
}
// Khai báo thêm nguyên mẫu hàm ghifile2 ở đầu chương trình
void ghifile2(char filename[], SV s);

// ---------------------------------------------------------
// 3. Ghi dữ liệu từ cấu trúc SV vào file (Định dạng đẹp)
void ghifile(char filename[], SV s) {
    FILE *fp = fopen(filename, "wt"); // "wt" là write text
    if (!fp) {
        cout << "Khong tao duoc tap tin " << filename << "!\n";
        return;
    }
    
    fprintf(fp, "MSSV: %s\n", s.mssv);
    fprintf(fp, "Ho ten: %s\n", s.hoten);
    fprintf(fp, "Tuoi: %d\n", s.tuoi);
    fprintf(fp, "So mon da hoc: %d\n", s.somon);
    fprintf(fp, "Danh sach mon hoc:\n");
    for (int i = 0; i < s.somon; i++) {
        fprintf(fp, "  Mon %d: %s (Ma MH: %s, So TC: %d, Diem: %.1f)\n", 
                i + 1, s.kq[i].tenmh, s.kq[i].mamh, s.kq[i].sotc, s.kq[i].diem);
    }
    fprintf(fp, "Tong so tin chi: %d\n", s.tongtc);
    fprintf(fp, "Tong so tin chi tich luy: %d\n", s.tongtctl);
    fprintf(fp, "Diem trung binh chung: %.1f\n", s.dtbc);
    fprintf(fp, "Diem trung binh tich luy: %.1f\n", s.dtbtl);
    
    fclose(fp);
    cout << "=> Da ghi file " << filename << " thanh cong (Dinh dang bao cao)!" << endl;
}

// ---------------------------------------------------------
// 4. Ghi dữ liệu từ cấu trúc SV vào file (Định dạng thô giống input)
void ghifile2(char filename[], SV s) {
    FILE *fp = fopen(filename, "wt");
    if (!fp) {
        cout << "Khong tao duoc tap tin " << filename << "!\n";
        return;
    }
    
    fprintf(fp, "%s\n", s.mssv);
    fprintf(fp, "%s\n", s.hoten);
    fprintf(fp, "%d\n", s.tuoi);
    fprintf(fp, "%d\n", s.somon);
    for (int i = 0; i < s.somon; i++) {
        fprintf(fp, "**************************\n");
        fprintf(fp, "%s\n", s.kq[i].mamh);
        fprintf(fp, "%s\n", s.kq[i].tenmh);
        fprintf(fp, "%d\n", s.kq[i].sotc);
        fprintf(fp, "%.1f\n", s.kq[i].diem);
    }
    
    fclose(fp);
    cout << "=> Da ghi file " << filename << " thanh cong (Dinh dang tho)!" << endl;
}

// ---------------------------------------------------------
int main() {
    SV a;
    
    // Đọc file
    docfile("C:\\Users\\DELL\\projects\\KTLT-HCMUTE-2026\\5-11-2026\\SV.TXT", a);
    
    // In ra màn hình kiểm tra
    cout << "\n--- THONG TIN SINH VIEN (IN RA MAN HINH) ---\n";
    insv(a);
    cout << "--------------------------------------------\n\n";
    
    // Ghi ra file OUTPUT1.TXT và OUTPUT2.TXT
    ghifile("C:\\Users\\DELL\\projects\\KTLT-HCMUTE-2026\\5-11-2026\\OUTPUT1.TXT", a);
    ghifile2("C:\\Users\\DELL\\projects\\KTLT-HCMUTE-2026\\5-11-2026\\OUTPUT2.TXT", a);
    
    return 0;
}