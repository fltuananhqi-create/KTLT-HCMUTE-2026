#include<iostream>

using namespace std;

struct date1 {
    int day;
    int month;
    int year;
};

struct date2 {
    int day;
    int month;
    int year;
};

bool laNamNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

//hàm kiểm tra date hợp lệ
bool legitCheck1(date1 a) {
    
}

bool legitCheck2(date2 a) {
    
}