/*
    Author: William Sid (wilsi748)

    Problem solved: Knapsack solved using dynamic programming.

    Time complexity: O(n*capacity)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


vector<int> knapsack(int capacity, vector<pair<int, int>> items) {
    int n = items.size();
    // init dp with 0s
    vector<vector<int>> dp(n+1, vector<int>(capacity+1, 0));
    // dp[i][j] will represent the max value that can be obtained using i items
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j<= capacity; j++) {
            // i-1 items and a knapsack with capacity j.
            // dp[i-1][j] is the max value when not including the ith item.
            // dp[i-1][j-items[i-1].second] + items[i-1].first is the max value including the ith value.
            // and we check which ever is greater.
            // if statement checks if the ith items weight is greater or equal to the remaining capacity.
            if(items[i-1].second <= j) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-items[i-1].second] + items[i-1].first);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    vector<int> res;
    int j = capacity;
    // iterate through dp reverse
    // checks whether the max value was obtained with current item.
    for(int i = n; i > 0 && j > 0; i--) {
        if(dp[i][j] != dp[i-1][j]) {
            // if it was, add the index to it.
            res.push_back(i-1);
            // subtract the weight from capacity.
            j -= items[i-1].second;
        }
    }
    // reverse the list to get the indicies in correct order since we iterate backwards with j to get the list.
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    int c, n;
    while(cin >> c >> n) {
        int v, w;
        vector<pair<int, int>> items;
        for (int i = 0; i < n; i++) {
            cin >> v >> w;
            items.push_back({v, w});
        }
        vector<int> indices = knapsack(c, items);
        cout << indices.size() << endl;
        for(auto& i : indices) cout << i << " ";
        cout << endl;
    }
    return 0;
}