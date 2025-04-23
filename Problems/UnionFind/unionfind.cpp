/*
    Author: William Sid (wilsi748)

    Problem solved: Disjoint sets solved with the union find algorithm

    Time complexity: O(q log n) where q is the number of operations and n is the number of elements
*/
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    UnionFind(int n);
    void join(int a, int b);
    bool same_set(int a, int b);

private:
    void link(int a, int b);
    int find_root(int x);

    struct node {
        int value;
        int rank;
        node * parent;
    };

    vector<node> sets;
};

UnionFind::UnionFind(int n) : sets(n) {
    for(int i = 0; i < n; i++) {
        node * node = &sets[i];
        node->value = i;
        node->rank = 0;
        node->parent = node;
    }
}

void UnionFind::join(int a, int b) {
    // get the root of a and b
    const auto a_root = find_root(a);
    const auto b_root = find_root(b);
    // if they are not the same, link.
    if(a_root != b_root) {
        link(a_root, b_root);
    }
}

// Check whether a and b are in the same set.
// makes use of the find_root function to check if they have the same parent root.
bool UnionFind::same_set(int a, int b) {
    return a == b ? : find_root(a) == find_root(b);
}


void UnionFind::link(int a, int b) {
    // get the nodes corresponding to a and b
    node * _a = &sets[a];
    node * _b = &sets[b];
    // link the smaller tree to the root of the larger tree
    if(_a->rank < _b->rank) {
        _a->parent = _b;
    } else {
        _b->parent = _a;
        if(_a->rank == _b->rank) {
            _a->rank++;  // increment the rank of the root if both trees have the same rank
        }
    }
}

// Finds and returns the root of the set that contains x.
int UnionFind::find_root(int x) {
    node * parent = sets[x].parent;
    int parent_value = parent->value;
    if(parent_value != x) {
        parent = &sets[find_root(parent_value)];
    }
    return parent->value;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    UnionFind sets(n);
    char c;
    int a, b;
    stringstream output;
    for(int i = 0; i < q; i++) {
        cin >> c >> a >> b;
        if (c == '?') {
            output << (sets.same_set(a, b) ? "yes\n" : "no\n");
        } else {
            sets.join(a, b);
        }
    }
    cout << output.str();
    return 0;
}