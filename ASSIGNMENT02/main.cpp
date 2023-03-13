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
 * @brief Function performs 0/1 Knapsack Using Recursion
 * @param weights weights of knapsack
 * @param profits profit associated with weights
 * @param W capacity of bag
 * @return int 
 */
int knapSackRecursive(vector<int>& weights, vector<int>& profits, int W, int i = -1) {
    if (i == weights.size() || W == 0) {
        return 0;
    }

    if (weights[i] > W) {
        return knapSackRecursive(weights, profits, W, i + 1);
    }

    return max(profits[i] + knapSackRecursive(weights, profits, W - weights[i], i + 1), knapSackRecursive(weights, profits, W, i + 1));
}

/**
 * @brief Function performs 0/1 Knapsack Using Dynamic Programming
 * 
 * @param weights weights of knapsack
 * @param profits profits associated with weights
 * @param W capacity of bag
 * @return int 
 */
int knapSackDynamicProgramming(vector<int>& weights, vector<int>& profits, int W) {
    int n = weights.size();
    vector<vector<int> > dp(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main(int argc, char const *argv[])
{
    int W, n; cin >> W >> n;

    Array weights(n);
    Array profits(n);

    for (int i = 0; i < n; i++) cin >> weights[i];
    for (int i = 0; i < n; i++) cin >> profits[i];
    
    TimePoint start = DateTimeNow();
    int ans = knapSackDynamicProgramming(weights, profits, W);
    TimePoint end = DateTimeNow();
    cout << "RESULT:\t" << ans << "\n";
    cout << "EXEC TIME:\t" << duration_cast<microseconds>(end - start).count() << " ms\n";

    return 0;
}