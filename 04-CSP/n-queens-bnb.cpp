#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isSafe(int row, int col, const vector<int>& placement) {
    for (int i = 0; i < row; ++i) {
        if (col == placement[i] || abs(row - i) == abs(col - placement[i])) {
            return false;
        }
    }
    return true;
}

bool solveNQueens(int row, int n, vector<int>& placement, int& count) {
    if (row == n) {
        ++count;
        return true;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, placement)) {
            placement[row] = col;
            if (solveNQueens(row + 1, n, placement, count)) {
                return true;
            }
            // Backtrack
            placement[row] = -1;
        }
    }

    return false;
}

void printSolution(const vector<int>& placement) {
    int n = placement.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (placement[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void solveNQueens(int n) {
    vector<int> placement(n, -1);
    int count = 0;
    solveNQueens(0, n, placement, count);
    if (count == 0) {
        cout << "No solution exists" << endl;
    }
}

int main() {
    int n;
    cout << "Enter the board size (n): ";
    cin >> n;

    solveNQueens(n);

    return 0;
}
