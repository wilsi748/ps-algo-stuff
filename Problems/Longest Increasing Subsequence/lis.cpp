/*
    Author: William Sid (wilsi748)

    Problem solved: Longest Increasing Subsequence

    Time complexity: O(n log n) where n is the length of the input sequence and O(log n) is the time complexity for binary search.
*/
#include <bits/stdc++.h>

using namespace std;


// Sorting done with patience sorting
vector<int> lis(vector<int>& nums) {
    // piles stores the cards in the the piles
    // prev stores the previous card in the longest increasing subsequence and ends with the current card.
    // indicies stores the index of the last card in the pile.
    vector<int> piles, prev(nums.size()), indices(nums.size());

    // iterate through each card of the input
    for (int i = 0; i < nums.size(); ++i) {
        int card = nums[i];
        // then we use binary search to find the pile "idx" where we place the current card.
        auto it = lower_bound(piles.begin(), piles.end(), card);
        int idx = it - piles.begin();
        // if there is no pile for the card we create a new pile.
        if (it == piles.end()) piles.push_back(card);
        else piles[idx] = card;
        // update prev and indicies base on the index of the previous card of the 
        // longest increasing subsequence ending in the current card.
        indices[idx] = i;
        prev[i] = idx ? indices[idx-1] : -1;
        // if the card is the same as the top card of the previous pile
        // we merge the piles.
        if (idx > 0 && piles[idx-1] == card) {
            indices[idx] = indices[idx-1];
            prev[i] = idx > 1 ? indices[idx-2] : -1;
        }
    }
    // after going through all the piles we construct the longest increasing subsequence.
    int len = piles.size(), cur = indices[len-1];
    vector<int> res(len);
    while (cur != -1) {
        res[--len] = cur;
        cur = prev[cur];
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    while(cin >> n) {
        vector<int> seq(n);
        for(int i = 0; i < n; i++) {
            cin >> seq[i];
        }
        vector<int> res = lis(seq);
        cout << res.size() << endl;
        for(int i = 0; i < res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << endl;
    }
    return 0;
}