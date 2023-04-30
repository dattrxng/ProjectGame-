#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_SIZE = 100;

int M, N;
char grid[MAX_SIZE][MAX_SIZE];

bool isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

bool searchWord(int x, int y, string word, int dx, int dy, int& x1, int& y1, int& x2, int& y2) {
    int len = word.length();
    for (int i = 0; i < len; i++) {
        if (!isValid(x, y) || grid[x][y] != word[i]) {
            return false;
        }
        if (i == 0) {
            x1 = x;
            y1 = y;
        }
        if (i == len - 1) {
            x2 = x;
            y2 = y;
        }
        x += dx;
        y += dy;
    }
    return true;
}

bool findWord(string word, int& x1, int& y1, int& x2, int& y2) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (searchWord(i, j, word, 1, 0, x1, y1, x2, y2) ||
                searchWord(i, j, word, 0, 1, x1, y1, x2, y2) ||
                searchWord(i, j, word, 1, 1, x1, y1, x2, y2) ||
                searchWord(i, j, word, -1, 1, x1, y1, x2, y2)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin >> M >> N;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    int K;
    cin >> K;

    for (
