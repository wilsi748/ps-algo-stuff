/*
    Author: William Sid (wilsi748)

    Problem solved: Suffix sort
*/
#include <bits/stdc++.h>

using namespace std;

void printVector(std::vector<int> vec) {
    std::cout << "Vector contents: ";
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}


class SuffixArray {
public:
    SuffixArray(string s) {
        n = s.size();
        temp.resize(n);
        for(int i = 0; i < n; i++) {
            temp[i] = s[i];
        }
        sa = get_suffix_array(temp);
        
    }

    /* 
    v = values to be sorted, non-negative
    p = indices of the value in the orginal order
    k = specifies the range, eg. sort in range[0, k]. 
    */
    vector<int> radix_sort(vector<int> &v, vector<int> &p, int k) {
        /*
        cnt - count number of occurences of each value of "v".
        pos - stores the starting positions of each value in "sorted".
        sorted - stores sorted values. i-th element represents the i-th smallest in "v".   */
        
        int n = v.size();
        vector<int> cnt(k, 0);
        set<int> unique_vals;
        for (int i = 0; i < n; i++) {
            cnt[v[i]]++;
            unique_vals.insert(v[i]);
        }
        int num_unique_vals = unique_vals.size();
        vector<int> sorted(num_unique_vals);

        for(int i = 1; i < k; i++) {
            cnt[i] += cnt[i-1];
        }

        for(int i = n-1; i >= 0; i--) {
            int val = v[p[i]];
            sorted[--cnt[val]] = p[i];
        }
        return sorted;
    }

    vector<int> get_suffix_array(vector<int> &v) {
        v.push_back(0);
        int n = v.size();

        /*
        sa - suffix array vector.
        rank - temporary vector which stores the rank of each suffix for sorting.
        cnt - vector for counting in radix sort.   */
        vector<int> sa(n), rank(n), tmp(n), cnt(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = v[i];
        }
        
        /*      DC3 algorithm
        Bucket sorting variant where each bucket is a substring of length k.

        1. start by sorting the suffix array by rank of the substrings of length k.
        2. update the rank for each suffix by comparing its substring of length 2k wuth the previous suffix substring.
        3. updated ranks are used for sorting in the next iteration.
        4. repeat until unique ranks for all suffixes.

        resulting suffix array is lexicographically sorted list of all suffixes of the input string. */

        for (int k = 1; k < n; k <<= 1) {
            sa = radix_sort(rank, sa, 256);
            int r = 0; 
            tmp[sa[0]] = r; // temp stores the updated ranks.
            for (int i = 1; i < n; i++) {
                if (rank[sa[i]] != rank[sa[i - 1]] || rank[sa[i] + k] != rank[sa[i - 1] + k]) r++;
                tmp[sa[i]] = r;
            }
            rank = tmp; // update the rank vector with new ranks
            if(rank[sa[n-1]] == n-1) break;
        }

        sa.erase(sa.begin());
        return sa;
    }

    int getSuffix(int i) {
        return sa[i];
    }

private:
    int n;
    vector<int> temp;
    vector<int> sa;
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string s;
    
    while(getline(cin, s)) {
        cout << "string " << s << endl;
        SuffixArray suffix(s);
        int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int q;
			cin >> q;
			cout << suffix.getSuffix(q);
		}
		cout << endl;
		getline(cin, s);
    }
    return 0;
}