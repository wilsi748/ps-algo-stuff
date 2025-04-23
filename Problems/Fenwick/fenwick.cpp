/*
    Author: William Sid (wilsi748)

    Problem solved: Fenwick Tree

    Time complexity: O(q log n) where q is number of queries and n is size of tree.
*/
#include <bits/stdc++.h>

using namespace std;

template<typename T>
class FenwickTree {
public:
    FenwickTree(int n) {
        tree.assign(n, 0);
    }
    // adds delta to index i at i, i+2, i+4 and so on until end of tree
    // to determine next index to add delta to we use bitwise OR and adds 1
    // to the rightmost set bit. 
    // Ex. i = 3 (011) then next index will be 011 | 100 = 111 = 7
    void add(int i, T delta) {
        while (i < tree.size()) {
            tree[i] += delta;
            i |= (i + 1); 
        }
    }

    // returns the sum of values from the start of tree to index end.
    // end, end-2, end-4 etc.
    // uses bitwise AND operator
    // Ex. end = 7 (111) then next end will be 111 & 110 = 110 = 6 
    T sum(int end) {
        T s = 0;
        while (end >= 0) {
            s += tree[end];
            end = (end & (end + 1)) - 1; // clear the rightmost set bit
        }
        return s;
    }

private:
    vector<T> tree;
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q;
    while(cin >> n >> q) {
        FenwickTree<long long> f_tree(n);
        stringstream output;
        for(int i = 0; i < q; i++) {
            char op;
            int index;
            cin >> op;
            if(op == '+') {
                long long increment;
                cin >> index >> increment;
                f_tree.add(index, increment);
            } else {
                cin >> index;
                output << to_string(f_tree.sum(index - 1)) + "\n";
            }
        }
        cout << output.str();
    }
    return 0;
}