#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

/**
 * @brief The function calculates maximum profit for 0/1 knapsack using greedy
 * @remark Space Complexity O(N * W) + O(N), Time Complexity O(N * W)
 * @param weights the weight of items
 * @param profits the profit of items
 * @param capacity the total capacity the sack can have
 * @param i current item
 * @return int - maximum possible profit
 */
int knapsackUsingGreedy(vector<int> &weights, vector<int> &profits, int capacity) {
    int n = weights.size(), res = 0;
    
    vector<pair<int, int>> item(n);

    for (int i = 0; i < n; i++) item[i] = make_pair(weights[i], profits[i]);

    auto compareItem = [&](pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second;
    };

    sort(item.begin(), item.end(), compareItem);

    for (int i = 0; i < n; i++) {
        if (capacity >= item[i].first) {
            res += item[i].second;
            capacity -= item[i].first;
        }
    }

    return res;
}


/**
 * @brief The function calculates maximum profit for 0/1 knapsack using recursion
 * @remark Space Complexity O(N * W) + O(N), Time Complexity O(N * W)
 * @param weights the weight of items
 * @param profits the profit of items
 * @param capacity the total capacity the sack can have
 * @param i current item
 * @return int - maximum possible profit
 */
int knapsackUsingRecursion(vector<int> &weights, vector<int> &profits, int capacity, int i = 0)
{
    if (i == weights.size() || capacity == 0)
    {
        /// If the sack has been full or all the items are considered then returns 0
        return 0;
    }

    if (weights[i] > capacity)
    {
        /// If the current item can't be put in the sack then we move to next item
        return knapsackUsingRecursion(weights, profits, capacity, i + 1);
    }

    /// Returns maximum out of selecting the current item or skipping the current item
    return max(profits[i] + knapsackUsingRecursion(weights, profits, capacity - weights[i], i + 1), knapsackUsingRecursion(weights, profits, capacity, i + 1));
}





/**
 * @brief The function calculates maximum profit for 0/1 knapsack using dynamic programming
 * @remark Space Complexity O(N * W), Time Complexity O(N * W) -> N is number of items, W is capacity
 * @param weights the weight of items
 * @param profits the profit of items
 * @param capacity the total capacity the sack can have
 * @param i current item
 * @return int - maximum possible profit
 */
int knapsackUsingDynamicPrgramming(vector<int> &weights, vector<int> &profits, int capacity)
{
    vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, 0)); /// Creating of memoisation table

    /// Bottom up filling of the memoisation table
    for (int i = 0; i <= weights.size(); i++)
    {

        for (int j = 0; j <= capacity; j++)
        {

            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (weights[i - 1] <= j)
                /// If the current item can be added into sack then we check total profit by adding this item & also consider profits by filling remaining weight
                dp[i][j] = max(profits[i - 1] + dp[i - 1][capacity - weights[i - 1]], dp[i - 1][j]);
            else
                /// If it's quite impossible to put the current item, then we select the previous row item
                dp[i][j] = dp[i - 1][j];
        }

    }
    return dp[weights.size()][capacity];
}


int main(int argc, char const *argv[])
{
    int n; cin >> n; /// take number of items
    int cap; cin >> cap; // take capacity of sack
    vector<int> weights(n); vector<int> profits(n);

    for (int i = 0; i < n; i++) {
        cin >> weights[i] >> profits[i];
    }

    int res;


    auto startTime = std::chrono::high_resolution_clock::now();
    res = knapsackUsingGreedy(weights, profits, cap);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Code execution time for Greedy: " << duration << " microseconds" << std::endl;


    startTime = std::chrono::high_resolution_clock::now();
    res = knapsackUsingRecursion(weights, profits, cap);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Code execution time for Recursion: " << duration << " microseconds" << std::endl;


    startTime = std::chrono::high_resolution_clock::now();
    res = knapsackUsingDynamicPrgramming(weights, profits, cap);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Code execution time for Dynamic Programming: " << duration << " microseconds" << std::endl;



    // auto startTime = std::chrono::high_resolution_clock::now();
    // int res = knapsackUsingGreedy(weights, profits, cap);
    // cout << "GREEDY\t" << res << "\n";
    // auto endTime = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    // std::cout << "Code execution time for Greedy: " << duration << " microseconds" << std::endl;

    

    return 0;
}
