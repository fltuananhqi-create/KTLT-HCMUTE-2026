// Nguyen Tuan Anh
// 25110008
// 23/10/2007
// 25110FIE2

#include <iostream>
#include <stdio.h>

#define MAX 100

using namespace std;

void docfile(char filename[], int a[][MAX], int &N) {
    FILE* f = fopen(filename, "rt");
    if (f == NULL) {
        return;
    }
    if (fscanf(f, "%d", &N) != 1) {
        fclose(f);
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }
    fclose(f);   
}

bool kiemtrarange(int a[][MAX], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (a[i][j] < 1 || a[i][j] > N * N) {
                return false;
            }
        }
    }
    return true;
}

bool kiemtratrung(int a[][MAX], int N) {
    bool count[MAX * MAX + 1] = {false}; 
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = a[i][j];
            if (x >= 0 && x <= MAX * MAX) {
                if (count[x]) return true;
                count[x] = true;
            } 
            else {
                for (int r = 0; r <= i; r++) {
                    int max_c = (r == i) ? j : N;
                    for (int c = 0; c < max_c; c++) {
                        if (a[r][c] == x) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool kiemtramagical(int a[][MAX], int N) {
    if (!kiemtrarange(a, N) || kiemtratrung(a, N)) {
        return false;
    }

    int sum = 0;
    for (int j = 0; j < N; j++) {
        sum += a[0][j];
    }
    
    for (int i = 1; i < N; i++) {
        int sumrow = 0;
        for (int j = 0; j < N; j++) {
            sumrow += a[i][j];
        }
        if (sumrow != sum) return false;
    }
    
    for (int j = 0; j < N; j++) {
        int sumcol = 0;
        for (int i = 0; i < N; i++) {
            sumcol += a[i][j];
        }
        if (sumcol != sum) return false;
    }
    
    int sumdiag1 = 0, sumdiag2 = 0;
    for (int i = 0; i < N; i++) {
        sumdiag1 += a[i][i];
        sumdiag2 += a[i][N - 1 - i];
    }
    if (sumdiag1 != sum || sumdiag2 != sum) return false;
    
    return true;
}

int main() {
    int a[MAX][MAX], N = 0;

    docfile("INPUT.TXT", a, N);

    if (kiemtrarange(a, N)) cout << "TRUE" << endl;
    else cout << "FALSE" << endl;
    
    if (kiemtratrung(a, N)) cout << "TRUE" << endl; 
    else cout << "FALSE" << endl;
    
    if (kiemtramagical(a, N)) cout << "TRUE" << endl;
    else cout << "FALSE" << endl;
    
    return 0;
}