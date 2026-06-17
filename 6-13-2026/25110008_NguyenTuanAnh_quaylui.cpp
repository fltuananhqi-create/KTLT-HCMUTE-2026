#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// BÀI 1: BÀI TOÁN N QUÂN HẬU

int n;
vector<int> solution_arr;
vector<bool> ok_col, ok_plus, ok_minus;
int so_cach = 0;

void print_queen_solution() {
    cout << "   Cach " << ++so_cach << ": ";
    for (int i = 1; i <= n; i++) {
        cout << "(" << i << "," << solution_arr[i] << ") ";
    }
    cout << endl;
}

// Hàm quay lui Try_row(i)
void Try_row(int i) {
    for (int j = 1; j <= n; j++) {
        // Kiểm tra ràng buộc an toàn cho cột và 2 đường chéo
        if (!ok_col[j] && !ok_plus[i + j - 1] && !ok_minus[i - j + n]) {
            solution_arr[i] = j;
            
            // Ghi nhận trạng thái (đánh dấu đã chiếm)
            ok_col[j] = true;
            ok_plus[i + j - 1] = true;
            ok_minus[i - j + n] = true;
            
            if (i < n) {
                Try_row(i + 1); // Tìm tiếp cho hàng sau
            } else {
                print_queen_solution(); // Đã xếp đủ N quân hậu
            }
            
            // Bỏ ghi nhận (Quay lui - Backtrack)
            ok_col[j] = false;
            ok_plus[i + j - 1] = false;
            ok_minus[i - j + n] = false;
        }
    }
}

void Chay_Bai_1() {
    cout << "\n================= BAI 1: N QUAN HAU =================" << endl;
    cout << "Nhap so quan hau N: ";
    cin >> n;
    
    so_cach = 0;
    solution_arr.assign(n + 1, 0);
    ok_col.assign(n + 1, false);
    ok_plus.assign(2 * n, false); 
    ok_minus.assign(2 * n, false);
    
    Try_row(1);
    
    if (so_cach == 0) {
        cout << "Khong co loi giai nao cho N = " << n << endl;
    } else {
        cout << "=> Tong cong co: " << so_cach << " cach dat." << endl;
    }
}


// BÀI 2 & 3: BÀI TOÁN MÊ CUNG

const int ROWS = 4;
const int COLS = 4;

// Hướng di chuyển: Xuống, Lên, Phải, Trái
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool visited[ROWS][COLS] = {false};
vector<pair<int, int>> current_path;

// --- CÁC BIẾN CHO BÀI 2 (MÊ CUNG KHÔNG TRỌNG SỐ) ---
int maze2[ROWS][COLS] = {
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {1, 0, 1, 0},
    {0, 0, 0, 0}
};
vector<pair<int, int>> shortest_path_maze2;
int min_steps_maze2 = 1e9;
int path_count_maze2 = 0;

// --- CÁC BIẾN CHO BÀI 3 (MÊ CUNG CÓ TRỌNG SỐ) ---
int maze3[ROWS][COLS] = {
    {1, -1,  2,  5},
    {2,  1,  3, -1},
    {-1, 4,  1,  2},
    {1,  2,  1,  1}
};
vector<pair<int, int>> optimal_path_maze3;
int current_cost_maze3 = 0;
int min_cost_maze3 = 1e9;


// Hàm hỗ trợ in đường đi ra màn hình
void printPath(const vector<pair<int, int>>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// --- THUẬT TOÁN BÀI 2 ---
bool isValid_Maze2(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze2[x][y] == 0 && !visited[x][y]);
}

void solve_Maze2(int x, int y) {
    current_path.push_back({x, y});
    visited[x][y] = true;

    // Nếu chạm đích (góc dưới cùng bên phải)
    if (x == ROWS - 1 && y == COLS - 1) {
        path_count_maze2++;
        cout << "   Duong " << path_count_maze2 << " (so buoc " << current_path.size() - 1 << "): ";
        printPath(current_path);

        // Tìm đường ngắn nhất (ít số bước nhất)
        if (current_path.size() - 1 < min_steps_maze2) {
            min_steps_maze2 = current_path.size() - 1;
            shortest_path_maze2 = current_path;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if (isValid_Maze2(next_x, next_y)) {
                solve_Maze2(next_x, next_y);
            }
        }
    }

    // Quay lui (Backtrack)
    visited[x][y] = false;
    current_path.pop_back();
}

void Chay_Bai_2() {
    cout << "\n=========== BAI 2: ME CUNG KHONG TRONG SO ===========" << endl;
    path_count_maze2 = 0;
    min_steps_maze2 = 1e9;
    shortest_path_maze2.clear();
    current_path.clear();
    for(int i=0; i<ROWS; i++) for(int j=0; j<COLS; j++) visited[i][j] = false;

    cout << "Danh sach tat ca duong di ra khoi me cung:\n";
    if (isValid_Maze2(0, 0)) {
        solve_Maze2(0, 0);
    }
    
    if (path_count_maze2 > 0) {
        cout << "\n-> DUONG DI NGAN NHAT (IT BUOC NHAT):\n   ";
        cout << "So buoc: " << min_steps_maze2 << "\n   Tuyen duong: ";
        printPath(shortest_path_maze2);
    } else {
        cout << "-> Khong co duong thoat khoi me cung!\n";
    }
}

// --- THUẬT TOÁN BÀI 3 ---
bool isValid_Maze3(int x, int y) {
    // -1 được coi là tường/vật cản
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze3[x][y] != -1 && !visited[x][y]);
}

void solve_Maze3(int x, int y) {
    current_path.push_back({x, y});
    visited[x][y] = true;
    current_cost_maze3 += maze3[x][y];

    // Nhánh và Cận (Branch and Bound): Cắt tỉa nếu chi phí hiện tại đã lớn hơn min cũ
    if (current_cost_maze3 >= min_cost_maze3) {
        current_cost_maze3 -= maze3[x][y];
        visited[x][y] = false;
        current_path.pop_back();
        return;
    }

    // Nếu chạm đích
    if (x == ROWS - 1 && y == COLS - 1) {
        if (current_cost_maze3 < min_cost_maze3) {
            min_cost_maze3 = current_cost_maze3;
            optimal_path_maze3 = current_path;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if (isValid_Maze3(next_x, next_y)) {
                solve_Maze3(next_x, next_y);
            }
        }
    }

    // Quay lui (Backtrack)
    current_cost_maze3 -= maze3[x][y];
    visited[x][y] = false;
    current_path.pop_back();
}

void Chay_Bai_3() {
    cout << "\n============ BAI 3: ME CUNG CO TRONG SO ============" << endl;
    min_cost_maze3 = 1e9;
    current_cost_maze3 = 0;
    optimal_path_maze3.clear();
    current_path.clear();
    for(int i=0; i<ROWS; i++) for(int j=0; j<COLS; j++) visited[i][j] = false;

    if (isValid_Maze3(0, 0)) {
        solve_Maze3(0, 0);
    }
    
    if (min_cost_maze3 != 1e9) {
        cout << "-> DUONG DI TOI UU (TONG TRONG SO NHO NHAT):\n   ";
        cout << "Tong chi phi (trong so): " << min_cost_maze3 << "\n   Tuyen duong: ";
        printPath(optimal_path_maze3);
    } else {
        cout << "-> Khong co duong thoat khoi me cung!\n";
    }
}


int main() {
    int lua_chon;
    do {
        cout << "\n==================== MENU BAI TAP ====================" << endl;
        cout << "1. Chay Bai 1: Dat N quan hau (In tat ca cac cach)" << endl;
        cout << "2. Chay Bai 2: Me cung KHONG trong so (In het duong di + Tim ngan nhat)" << endl;
        cout << "3. Chay Bai 3: Me cung CO trong so (Tim duong chi phi nho nhat)" << endl;
        cout << "4. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon cua ban (1-4): ";
        cin >> lua_chon;
        
        switch(lua_chon) {
            case 1:
                Chay_Bai_1();
                break;
            case 2:
                Chay_Bai_2();
                break;
            case 3:
                Chay_Bai_3();
                break;
            case 4:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
        }
        cout << "\n======================================================" << endl;
    } while(lua_chon != 4);
    
    return 0;
}