#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Define the puzzle size
const int N = 3;

// Structure to represent a puzzle state
struct PuzzleState
{
    int puzzle[N][N];
    int zeroRow, zeroCol;
    int g;
    int h;

    bool operator<(const PuzzleState &other) const
    {
        return (g + h) > (other.g + other.h);
    }
};

void printPuzzle(const PuzzleState &state)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << state.puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----\n";
}

bool isEqual(const PuzzleState &state1, const PuzzleState &state2) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (state1.puzzle[i][j] != state2.puzzle[i][j]) 
                return false;
        }
    }
    return true;
}

int calculateManhattanDistance(const PuzzleState &state) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value = state.puzzle[i][j];
            if (value != 0) {
                int targetRow = (value - 1) / N;
                int targetCol = (value - 1) % N;
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return distance;
}

bool isValid(int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N);
}

vector<PuzzleState> generateNextStates(const PuzzleState &currentState) {
    vector<PuzzleState> nextStates;
    const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Left, Right, Up, Down

    for (int k = 0; k < 4; k++) {
        int nextZeroRow = currentState.zeroRow + moves[k][0];
        int nextZeroCol = currentState.zeroCol + moves[k][1];

        if (isValid(nextZeroRow, nextZeroCol)) {
            PuzzleState nextState = currentState;
            swap(nextState.puzzle[currentState.zeroRow][currentState.zeroCol],
                 nextState.puzzle[nextZeroRow][nextZeroCol]);
            nextState.zeroRow = nextZeroRow;
            nextState.zeroCol = nextZeroCol;
            nextState.g = currentState.g + 1;
            nextState.h = calculateManhattanDistance(nextState);
            nextStates.push_back(nextState);
        }
    }

    return nextStates;
}

void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState) {
    priority_queue<PuzzleState> pq;
    unordered_set<int> visited;

    pq.push(initialState);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        cout << "Current State:\n";
        printPuzzle(current);
        cout << "Number of moves: " << current.g << endl;
        cout << "Heuristic cost: " << current.h << endl;
        cout << "-------------------\n";

        if (isEqual(current, finalState)) {
            cout << "Goal State Reached!\n";
            cout << "Number of moves: " << current.g << endl;
            cout << "Heuristic cost: " << current.h << endl;
            break;
        }

        vector<PuzzleState> nextStates = generateNextStates(current);

        for (const PuzzleState &nextState : nextStates) {
            int hash = 0;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    hash = hash * 10 + nextState.puzzle[i][j];

            if (visited.find(hash) == visited.end()) {
                pq.push(nextState);
                visited.insert(hash);
            }
        }
    }
}

PuzzleState getPuzzleState(const string &prompt) {
    PuzzleState state;

    cout << prompt << " (0 represents the empty tile):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> state.puzzle[i][j];

            if (state.puzzle[i][j] == 0)
            {
                state.zeroRow = i;
                state.zeroCol = j;
            }
        }
    }

    state.g = 0;
    state.h = calculateManhattanDistance(state);

    return state;
}

int main()
{
    PuzzleState initialState = getPuzzleState("Enter the initial state of the puzzle");
    PuzzleState finalState = getPuzzleState("Enter the final state of the puzzle");

    cout << "Initial State:\n";
    printPuzzle(initialState);

    aStarSearch(initialState, finalState);

    return 0;
}

/*
Enter the initial state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 0
Enter value at position (0, 1): 1
Enter value at position (0, 2): 2
Enter value at position (1, 0): 4
Enter value at position (1, 1): 6
Enter value at position (1, 2): 3
Enter value at position (2, 0): 7
Enter value at position (2, 1): 5
Enter value at position (2, 2): 8
Enter the final state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 1
Enter value at position (0, 1): 2
Enter value at position (0, 2): 3
Enter value at position (1, 0): 4
Enter value at position (1, 1): 5
Enter value at position (1, 2): 6
Enter value at position (2, 0): 7
Enter value at position (2, 1): 8
Enter value at position (2, 2): 0
Initial State:
0 1 2
4 6 3
7 5 8
-----
Current State:
0 1 2
4 6 3
7 5 8
-----
Number of moves: 0
Heuristic cost: 6
-------------------
Current State:
1 0 2
4 6 3
7 5 8
-----
Number of moves: 1
Heuristic cost: 5
-------------------
Current State:
1 2 0
4 6 3
7 5 8
-----
Number of moves: 2
Heuristic cost: 4
-------------------
Current State:
1 2 3
4 6 0
7 5 8
-----
Number of moves: 3
Heuristic cost: 3
-------------------
Current State:
1 2 3
4 0 6
7 5 8
-----
Number of moves: 4
Heuristic cost: 2
-------------------
Current State:
1 2 3
4 5 6
7 0 8
-----
Number of moves: 5
Heuristic cost: 1
-------------------
Current State:
1 2 3
4 5 6
7 8 0
-----
Number of moves: 6
Heuristic cost: 0
-------------------
Goal State Reached!
Number of moves: 6
Heuristic cost: 0
*/
