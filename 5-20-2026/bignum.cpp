#include <iostream>
#include <conio.h>
#include <cstring>
#include <cctype>
#include <algorithm> // Thư viện chứa hàm max()

using namespace std;

// Khai báo hằng
#define MAXDIGITS 100 /* maximum length */
#define PLUS 1        /* positive sign bit */
#define MINUS -1      /* negative sign bit */

// Khai báo cấu trúc
typedef struct {
    char digits[MAXDIGITS]; /* the number */
    int signbit;            /* PLUS or MINUS */
    int lastdigit;          /* index of high-order digit */
} bignum;

// Khai báo hàm
void scan_bignum(bignum &n);
void print_bignum(bignum n);
int kiemtra(char s[]);
void zero_justify(bignum &n);
int compare_bignum(bignum a, bignum b);
void add_bignum(bignum a, bignum b, bignum &c);
void subtract_bignum(bignum a, bignum b, bignum &c);

int main() // Sửa void main() thành int main() cho chuẩn C++ hiện đại
{
    do {
        bignum a, b, c;
        cout << "Nhap a:";
        scan_bignum(a);
        cout << "Nhap b:";
        scan_bignum(b);
        
        add_bignum(a, b, c);
        cout << "a+b=";
        print_bignum(c);
        cout << endl;
        
        subtract_bignum(a, b, c);
        cout << "a-b=";
        print_bignum(c);
        cout << endl;
        
        cout << "Nhan phim ESC de thoat...\n";
    } while (getch() != 27);
    
    return 0;
}

// ---------------- CÁC HÀM XỬ LÝ ----------------

void print_bignum(bignum n)
{
    int i;
    if (n.signbit == MINUS) cout << "-";
    for (i = n.lastdigit; i >= 0; i--)
        cout << int(n.digits[i]);
}

int kiemtra(char s[]) {
    // ktra ký tự đầu
    if (s[0] != '-' && !isdigit(s[0]))
        return 0;
    // ktra các ký tự tiếp theo
    int len = strlen(s);
    for (int i = 1; i < len; i++)
        if (!isdigit(s[i])) return 0;
    // không phát hiện vi phạm
    return 1;
}

void scan_bignum(bignum &n)
{
    // B1: Nhập chuỗi
    char temp[256];
    cin.getline(temp, 256);
    
    // Khởi tạo mảng digits bằng 0 để tránh rác bộ nhớ
    for (int i = 0; i < MAXDIGITS; i++) n.digits[i] = 0;
    
    // B2: Kiểm tra
    if (!kiemtra(temp)) { // không hợp lệ
        // gán bignum = 0
        n.signbit = PLUS;
        n.lastdigit = 0;
        n.digits[0] = 0;
    }
    else { // hợp lệ. B3: chuyển thành số bignum
        // xét 2 trường hợp
        if (temp[0] != '-') { // số dương
            n.signbit = PLUS;
            n.lastdigit = strlen(temp) - 1;
            for (int i = 0; i <= n.lastdigit; i++)
                n.digits[i] = temp[n.lastdigit - i] - 48;
        }
        else { // số âm
            n.signbit = MINUS;
            n.lastdigit = strlen(temp) - 2;
            for (int i = 0; i <= n.lastdigit; i++)
                n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
        }
    }
    zero_justify(n);
}

void zero_justify(bignum &n)
{
    while ((n.lastdigit > 0) && (n.digits[n.lastdigit] == 0))
        n.lastdigit--;
    if ((n.lastdigit == 0) && (n.digits[0] == 0))
        n.signbit = PLUS; /* hack to avoid -0 */
}

int compare_bignum(bignum a, bignum b)
{
    int i;
    if ((a.signbit == MINUS) && (b.signbit == PLUS)) return (MINUS);
    if ((a.signbit == PLUS) && (b.signbit == MINUS)) return (PLUS);
    if (b.lastdigit > a.lastdigit) return (PLUS * a.signbit);
    if (a.lastdigit > b.lastdigit) return (MINUS * a.signbit);
    for (i = a.lastdigit; i >= 0; i--) {
        if (a.digits[i] > b.digits[i]) return (MINUS * a.signbit);
        if (b.digits[i] > a.digits[i]) return (PLUS * a.signbit);
    }
    return 0;
}

void add_bignum(bignum a, bignum b, bignum &c)
{
    int carry; /* carry digit */
    int i; /* counter */
    
    // Khởi tạo c bằng 0
    for(i=0; i<MAXDIGITS; i++) c.digits[i] = 0;
    c.lastdigit = 0;
    c.signbit = PLUS;

    if (a.signbit == b.signbit)
        c.signbit = a.signbit;
    else { // cộng 2 số trái dấu
        if (a.signbit == MINUS) {
            a.signbit = PLUS;
            subtract_bignum(b, a, c);
            a.signbit = MINUS;
        }
        else {
            b.signbit = PLUS;
            subtract_bignum(a, b, c);
            b.signbit = MINUS;
        }
        return;
    }
    c.lastdigit = max(a.lastdigit, b.lastdigit) + 1;
    // điều chỉnh lại a, b: thêm số 0 vào cuối
    for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
        a.digits[i] = 0;
    for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
        b.digits[i] = 0;
    
    // tính toán
    carry = 0;
    for (i = 0; i <= (c.lastdigit); i++) {
        c.digits[i] = (char)((carry + a.digits[i] + b.digits[i]) % 10);
        carry = (carry + a.digits[i] + b.digits[i]) / 10;
    }
    zero_justify(c);
}

void subtract_bignum(bignum a, bignum b, bignum &c)
{
    int borrow; /* anything borrowed? */
    int v; /* placeholder digit */
    int i; /* counter */
    
    // Khởi tạo c bằng 0
    for(i=0; i<MAXDIGITS; i++) c.digits[i] = 0;
    c.lastdigit = 0;
    c.signbit = PLUS;

    if ((a.signbit == MINUS) || (b.signbit == MINUS)) {
        b.signbit = -1 * b.signbit;
        add_bignum(a, b, c);
        b.signbit = -1 * b.signbit;
        return;
    }
    
    if (compare_bignum(a, b) == PLUS) { // a < b (hàm compare trả về PLUS nếu b > a)
        subtract_bignum(b, a, c);
        c.signbit = MINUS;
        return;
    }
    
    c.signbit = PLUS; // thêm vào
    c.lastdigit = max(a.lastdigit, b.lastdigit);
    
    // điều chỉnh lại a, b: thêm số 0 vào cuối
    for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
        a.digits[i] = 0;
    for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
        b.digits[i] = 0;
    
    // tính toán
    borrow = 0;
    for (i = 0; i <= (c.lastdigit); i++) {
        v = (a.digits[i] - borrow - b.digits[i]);
        if (v < 0) {
            v = v + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        c.digits[i] = (char) v % 10;
    }
    zero_justify(c);
}