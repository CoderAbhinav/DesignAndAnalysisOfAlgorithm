#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#define Array vector<int>
#define TimePoint chrono::steady_clock::time_point
#define DateTimeNow high_resolution_clock::now
#define DurationInMS chrono::microseconds

using namespace std;
using namespace std::chrono;

/**
 * @brief returns if the current position of the queen will be attacked or not
 * 
 * @param board board of size n * n
 * @param row the row number of position
 * @param col the column number of position
 * @return true if the position is safe
 * @return false if the position can be attacked
 */
bool isSafePlace(vector<vector<bool> >& board, int row, int col) {
    int N = board.size();

    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--){
        if (board[i][j]) return false;
    } 

    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}

/**
 * @brief this function performs the actual logic for n queens problem backtracking
 * 
 * @param board the board of size n * n
 * @param col the column in which  queen to be placed
 * @return true if can be placed in the given column
 * @return false if can't be placed in the given column
 */
bool nQueensProblemUtility(vector<vector<bool> >& board, int col) {
    int N = board.size();
    if (col >= N) {
        return true;
    }

    for (int i = 0; i < N; i++) {
        if (isSafePlace(board, i, col)) {
            board[i][col] = true;
            if (nQueensProblemUtility(board, col + 1)) {
                return true;
            }
            board[i][col] = false;
        }
    }

    return false;
}

/**
 * @brief This function solves n queens problem using backtracking
 * @param boardSize the size of board
 * @return vector<vector<bool> > 
 */
vector<vector<bool> > nQueensProblem(int boardSize) {
    vector<vector<bool> > board(boardSize, vector<bool>(boardSize, false));

    nQueensProblemUtility(board, 0);

    return board;
}

/**
 * @brief Functions acts as intermediate drive code between logic & user
 * @param caseNo 
 */
void solve(int caseNo) {
    int boardSize; cin >> boardSize;

    TimePoint start = DateTimeNow();
    vector<vector<bool> > board = nQueensProblem(boardSize);
    TimePoint end = DateTimeNow();

    cout << "case no\t\t\t: " << caseNo << endl;
    cout << "board size\t\t: " << boardSize << " x " << boardSize << endl;
    cout << "execution time\t: " << duration_cast<microseconds>(end - start).count() << " ms" << endl;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == false){ 
                cout << "▢\t";
            } else {
                cout << "◼\t";
            }
        }

        cout << '\n';
    }


    cout << '\n';
}

int main(int argc, char const *argv[])
{   
    int testCases; cin >> testCases;
    for (int i = 0; i < testCases; i++) solve(i + 1);
    return 0;
}
