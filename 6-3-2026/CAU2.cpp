// Nguyen Tuan Anh
// 25110008
// 23/10/2007
// 25110FIE2

#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

#define MAX 52

typedef struct CARD {
    int kind;
    int number;
};

CARD deck[52];

int Random(int n) {
    return rand() % n;
}

void Swap(CARD &a, CARD &b) {
    CARD t = a;
    a = b;
    b = t;
}

void CreateDeck(CARD deck[52]) {
    int n = 0;
    for (int kind = 1; kind <= 4; kind++) {
        for (int num = 1; num <= 13; num++) {
            deck[n].kind = kind;
            deck[n].number = num;
            n++;
        }
    }
}

void ShuffleDeck(CARD deck[52]) {
    int no = 30 + Random(23);
    for (int i = 0; i < no; i++) {
        int v1 = Random(52);
        int v2 = Random(52);
        if (v1 != v2) Swap(deck[v1], deck[v2]);
    }
}

void DealCards(CARD deck[52], CARD hands[MAX][MAX], int n, int k) {
    int v = 0;
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++) {
            hands[i][j] = deck[v++];
        }
    }
}

bool checkAbsoluteWin(CARD hand[], int k = 6) {
    bool has[5][14] = {false};
    int aces = 0;

    for (int i = 0; i < k; i++) {
        has[hand[i].kind][hand[i].number] = true;
        if (hand[i].number == 1) aces++;
    }

    if (aces == 4) return true;

    if (aces == 3) {
        for (int c = 1; c <= 4; c++) {
            if (has[c][1] && has[c][13]) return true;
        }
    }

    int ak_pairs = 0;
    for (int c = 1; c <= 4; c++) {
        if (has[c][1] && has[c][13]) ak_pairs++;
    }
    if (ak_pairs == 2) return true;

    for (int c = 1; c <= 4; c++) {
        if (has[c][12] && has[c][13] && has[c][1] && aces >= 2) return true;
    }

    for (int c = 1; c <= 4; c++) {
        if (has[c][11] && has[c][12] && has[c][13] && has[c][1]) return true;
    }

    return false;
}

int main() {
    CARD hands[MAX][MAX];
    int n = 4, k = 6;
    
    srand((unsigned)time(NULL));
    
    CreateDeck(deck);
    ShuffleDeck(deck);
    DealCards(deck, hands, n, k);

    bool foundWinner = false;
    for (int i = 0; i < n; i++) {
        if (checkAbsoluteWin(hands[i], k)) {
            cout << "Player " << i + 1 << " gains an absolute win!" << endl;
            foundWinner = true;
        }
    }

    if (!foundWinner) {
        cout << "No player gains an absolute win." << endl;
    }

    return 0;
}