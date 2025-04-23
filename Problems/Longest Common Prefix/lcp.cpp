/*
    Author: William Sid (wilsi748)

    Problem solved: 
*/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 2e5 +5;

class SuffixArray {
public:
    SuffixArray(const string& str) : n(str.length()), s(str) {
        get_suffix_array();
    }

    int operator[](int i) const {
        return sa[i];
    }

    int size() const {
        return n;
    }


private:
    int n;
    string s;
    int sa[MAX], rank[MAX], count[MAX], x[MAX], y[MAX];

    void get_suffix_array() {
        cout << "yoyo" << endl;
        /*
        int max_ascii = 128;
        int *x = rank, *y = count;
        // count chars in string
        for (int i = 1; i <= n; i++) {
            count[x[i] = s[i]]++;
        }
        //
        for (int i = 1; i <= max_ascii; i++) {
            count[i] += count[i-1];
        }
        //
        for (int i = n; i; i--) {
            sa[count[x[i]]--] = i;
        }
        // Loop through the power of 2 from 1 to n. 
        // k is the current size of the substring being compared
        for(int k = 1; k <= n; k <<=1) {
            int num = 0; // store amount of unique ranks
            for(int i = n - k + 1; i <= n; i++) {
                y[num++] = i; // suffixes with less rank than k store in y
            }
            for(int i = 1; i <= n; i++) {
                if(sa[i] > k) y[num++] = sa[i] - k; // suffixes with greater rank than k store in y
            }
            for(int i = 1; i <= max_ascii; i++){
                count[i] = 0; // reset count array;
            }
            for (int i = 1; i <= n; i++) {
                count[x[i]]++; // count frequency of ranks
            }
            for(int i = 2; i <= max_ascii; i++) {
                count[i] += count[i-1];
            }
            // Sort the suffixes based on the new rank array.
            for(int i = n; i; i--) {
                sa[count[x[y[i]]]--] = y[i];
                y[i] = 0;
            }
            swap(x, y); // swap rank and count arrays
            x[sa[1]] = 1, num = 1; // set rnak of the first suffix to 1 and the nubmer of unique ranks to 1;
            for ( int i = 2; i <= n; i++) {
                //Update the rank array based on the new order of suffixes 
                x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1] + k]) ? num : ++num; 
            }
            
            // if the number of unique ranks is equal to 
            if(num >= n) break; 
            max_ascii = num;
        }
        */
    }
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int len;
    string s;
    cin >> len >> s;
    cout << " s " << s << endl;
    SuffixArray sa(s);
    for(int i = 0; i < sa.size(); i++) {
        cout << sa[i] << " ";
    }
    cout << endl;

    return 0;
}