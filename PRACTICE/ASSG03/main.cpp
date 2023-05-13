#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * @brief This function checks if the current location is safe to place the queen
 * it checks the current row, upper & lower left diagonal
 * @remarks Time Complexity O(N), space complexity O(1) -> N is size of board
 * @param board the board matrix
 * @param row current row
 * @param col current column
 * @return true if it's safe to place the queen at board[row][col]
 * @return false if it's not safe to place the queen at board[row][col]
 */
bool isSafePosition(vector<vector<bool>>& board, int row, int col) {
    int n = board.size();

    /// Check for the column
    for (int i = 0; i < n; i++) if (board[row][i] == true) return false;

    /// Check for upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) if (board[i][j] == true) return false;

    /// Check for below left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--) if (board[i][j] == true) return false;

    return true;
}

/**
 * @brief This function tries to put queen at each position to generate a perfect combination
 * @remarks Time Complexity O(N!), Space Complexity O(N^2) -> where N is board size
 * @param board square board
 * @param col current column
 * @return true if the configuration satisfies the contrain
 * @return false if the configuration doesn't satisfy the constrain
 */
bool nQueensProblem(vector<vector<bool>>& board, int col = 0){ 
    int n = board.size();

    if (col >= n) {
        return true;
    }

    for (int i = 0; i < n; i++) {
        if (isSafePosition(board, i, col)) {
            board[i][col] = true;
            if (nQueensProblem(board, col + 1)) {
                return true;
            }
            board[i][col] = false;
        }
    }

    return false;
}

/**
 * @brief This function generates a N queens board will queens placed
 * 
 * @param n size of board
 * @return vector<vector<bool>> board
 */
vector<vector<bool>> nQueensProblem(int n) {
    vector<vector<bool>> board(n, vector<bool>(n, false));
    nQueensProblem(board);
    return board;
}


int main(int argc, char const *argv[])
{
    int n; cin >> n; /// Taking board size from user
    auto startTime = high_resolution_clock::now();
    auto res = nQueensProblem(n);
    auto endTime = high_resolution_clock::now();

    cout << "EXECUTION TIME: " << duration_cast<microseconds>(endTime - startTime).count() << " microseconds\n";

    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (res[i][j] == true) {
                cout << "Q\t";
            } else {
                cout << "-\t";
            }
        }
        cout << "\n";
    }

    return 0;
}
