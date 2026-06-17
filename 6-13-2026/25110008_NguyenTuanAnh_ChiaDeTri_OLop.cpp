#include <iostream>
using namespace std;

// 1. BINARY SEARCH (MẢNG GIẢM DẦN)

int BINARY_SEARCH_DESC(int A[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (key == A[mid]) {
            return mid; 
        } 
        else if (key > A[mid]) { 
            right = mid - 1; // Số lớn hơn nằm bên trái
        } 
        else { 
            left = mid + 1;  // Số nhỏ hơn nằm bên phải
        }
    }
    return -1; 
}

// 2. MERGE SORT (ĐỆ QUY THEO SLIDE)

void MERGE(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MERGE_SORT(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MERGE_SORT(A, p, q);
        MERGE_SORT(A, q + 1, r);
        MERGE(A, p, q, r);
    }
}

// 3. QUICK SORT (MẢNG PHỤ THEO SLIDE)

void QUICKSORT(int A[], int p, int r) {
    if (p < r) {
        int pivot = A[r]; // Chọn phần tử cuối làm chốt
        
        int size = r - p + 1;
        int* L = new int[size];
        int* R = new int[size];
        int n1 = 0, n2 = 0;

        for (int i = p; i < r; i++) {
            if (A[i] <= pivot) {
                L[n1++] = A[i];
            } else {
                R[n2++] = A[i];
            }
        }

        int q = p + n1; 

        for (int i = 0; i < n1; i++) A[p + i] = L[i];
        A[q] = pivot;
        for (int i = 0; i < n2; i++) A[q + 1 + i] = R[i];

        delete[] L;
        delete[] R;

        QUICKSORT(A, p, q - 1); 
        QUICKSORT(A, q + 1, r); 
    }
}

// HÀM MAIN ĐỂ CHẠY THỬ VÀ KIỂM TRA

int main() {
    // 1. Kiểm tra Binary Search (Mảng giảm dần)
    cout << "--- 1. KIEM TRA BINARY SEARCH (GIAM DAN) ---" << endl;
    int arr_desc[] = {90, 75, 60, 45, 30, 15, 5};
    int n_desc = sizeof(arr_desc) / sizeof(arr_desc[0]);
    int key = 45;
    
    int pos = BINARY_SEARCH_DESC(arr_desc, n_desc, key);
    if (pos != -1)
        cout << "Tim thay " << key << " tai vi tri index: " << pos << endl;
    else
        cout << "Khong tim thay " << key << endl;
    cout << endl;

    // 2. Kiểm tra Merge Sort
    cout << "--- 2. KIEM TRA MERGE SORT ---" << endl;
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    MERGE_SORT(arr1, 0, n1 - 1);
    cout << "Mang sau khi Merge Sort: ";
    for (int i = 0; i < n1; i++) cout << arr1[i] << " ";
    cout << "\n\n";

    // 3. Kiểm tra Quick Sort
    cout << "--- 3. KIEM TRA QUICK SORT (MANG PHU) ---" << endl;
    int arr2[] = {12, 7, 11, 5, 2, 9, 8, 6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    QUICKSORT(arr2, 0, n2 - 1);
    cout << "Mang sau khi Quick Sort: ";
    for (int i = 0; i < n2; i++) cout << arr2[i] << " ";
    cout << "\n";

    return 0;
}