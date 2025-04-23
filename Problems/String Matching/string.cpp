/*
    Author: William Sid (wilsi748)

    Problem solved: String Matching using Knuth-Morris-Pratt

    Time complexity: 
    The time complexity then for the KMP algorithm is O(n+m), text length + pattern length, because it is searching at most n characters
    and compares at most m times per character. The number of comparisons is limited to partial match table, failure / "pi" function, which 
    is made with a O(m) time complexity. This makes the algorithm linear to the input size.

*/
#include <bits/stdc++.h>

using namespace std;

// kmp string search
vector<int> string_matching(string& pattern, string& text) {
    vector<int> positions;
    vector<int> failure(pattern.size(), 0); // init to 0

    // construct partial match table 
    for(int i = 1, j = 0; i < pattern.size(); i++) {
        while(j > 0 && pattern[i] != pattern[j]) {
            j = failure[j - 1];
        }
        if(pattern[i] == pattern[j]) {
            j++;
        }
        failure[i] = j;
    }
    
    int n = text.size(), m = pattern.size(), start = 0, i = 0, j = 0;
    while (n - start >= m) {
        while (j < m && text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            positions.push_back(start);
        }
        if (j > 0 && failure[j - 1] > 0) {
            start = i - failure[j - 1];
            j = failure[j - 1];
        } else {
            if (i == start) {
                i++;
            }
            start = i;
            if (j > 0) {
                j = failure[j - 1];
            }
        }
    }
    return positions;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string pattern, text;
    while(getline(cin, pattern) && getline(cin, text)) {
        for(int pos : string_matching(pattern, text)) {
            cout << pos << " ";
        }
        cout << endl;
    }
    return 0;
}