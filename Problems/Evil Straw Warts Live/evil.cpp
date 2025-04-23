/*
    Author: William Sid (wilsi748)

    Problem solved: 
*/
#include <bits/stdc++.h>

using namespace std;


bool check_palindrome(string s) {
    int odd = 0;
    map<char, int> um;
    // count the amount of occurrences of character c in the string
    for(char c : s) {
        um[c]++;
    }

    // for each character, is there more then 1 occurrences of odd characters
    for(auto& i : um) {
        if (i.second % 2 == 1) odd++;
    }
    if(odd > 1) {
        return false;
    } else {
        return true;
    }
}

int palindrome_swaps(string s) {
    int swaps = 0, left = 0, right = s.size() - 1;
    
    if(!check_palindrome(s)) return -1;
    
    while(left < right) {
        int l = left, r = right;

        // find a character that is the same.
        while(s[l] != s[r]) r--;
        
        // if the characted that is the same is in the same spot it means that this is the odd character,
        // therefore we move it to the middle of the string.
        if(l == r) {
            swap(s[r], s[r+1]);
            swaps++;
            continue;
        }else{
            // not odd so we move to character found at the index of "r" until it reaches the index of "right".
            while(r < right) {
                swap(s[r], s[r + 1]);
                swaps++;
                r++;
            }
        }
        left++, right--;
    }
    return swaps;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    while(cin >> n) {
        string s;
        for(int i = 0; i < n; i++) {
            cin >> s;
            int res = palindrome_swaps(s);
            if (res != -1) {
                cout << res << endl;
            } else {
                cout << "Impossible" << endl;
            }
        }
    }

    return 0;
}