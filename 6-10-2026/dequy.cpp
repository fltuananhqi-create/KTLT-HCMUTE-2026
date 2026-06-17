#include <iostream>

using namespace std;

int sumint(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + sumint(n - 1);
    }
}

int arrsum(int a[], int n) {
    if (n == 0) {
        return 0;
    } else {
        return a[n - 1] + arrsum(a, n - 1);
    }
}

int findmaxarr(int a[], int n) {
    if (n == 1) {
        return a[0];
    } else {
        int max_conlai = findmaxarr(a, n - 1);
        if (a[n - 1] > max_conlai) {
            return a[n - 1];
        } else {
            return max_conlai;
        }
    }
}

int countdigits(int n) {
    if (n / 10 == 0) {
        return 1;
    } else {
        return 1 + countdigits(n / 10);
    }
}
