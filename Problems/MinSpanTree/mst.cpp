/*
    Author: William Sid (wilsi748)

    Problem solved: Minimum spanning tree problem

    Time complexity: O(|E| log |V|), where E is the number of edges and V is the number of vertices.
    
    The time complexity of kruskals algorithm is limited by sorting the edges, O(E log E), but since Union-Find is
    used to keep track of connected vertices and has a time complexity of O(log V) and since we are using edges the resulting
    time complexity is then O(E log V). Depending on the amount of edges or vertices the time complexity could be closer to O(E log E) or O(V^2 log V).
*/
#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct edge {
    int _from;
    int _to;
    int _cost;
    edge() :  _from(-1), _to(-1), _cost(inf) {};
    edge ( int from, int to, int cost) :  _from(from), _to(to), _cost(cost) {}
    bool operator < (const edge& e) const { return (_cost < e._cost); }
    string toString() { return to_string(_from) + " " + to_string(_to) + " " + to_string(_cost); } 
};

bool compare(const edge& e1, const edge& e2) {
    if(e1._from == e2._from) {
        return e1._to < e2._to;
    }
    return e1._from < e2._from; 
}

int find_root(vector<int>& parents, int i) {
    if(parents[i] != i) {
        parents[i] = find_root(parents, parents[i]);
    }
    return parents[i];
}

bool same_set(vector<int>& parents, int a, int b) {
    return find_root(parents, a) == find_root(parents, b);
}

void join(vector<int>& parents, vector<int>& childs, int a, int b) {
    int root_a = find_root(parents, a);
    int root_b = find_root(parents, b);

    if (root_a == root_b) {
        return;
    }

    if(childs[root_a] < childs[root_b]) {
        parents[root_a] = root_b;
        childs[root_b]++;
    } else {
        parents[root_b] = root_a;
        childs[root_a]++;
    }
}


// Kruskals algorithm
int kruskal(vector<edge>& edges, vector<int>& parents, vector<int>& childs, vector<edge>& tree) {
    sort(edges.begin(), edges.end()); // sort by cost
    int res = 0;
    for(edge& e : edges) {
        if(!same_set(parents, e._from, e._to)) {
            tree.push_back(e);
            res += e._cost;
            join(parents, childs, e._from, e._to);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, cost;
    while(cin >> n >> m) {
        if(n == 0 && m == 0) {
            break;
        }

        // Read in all the edges
        vector<edge> edges;
        for(int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back(edge(min(u, v), max(u, v), w)); // correct order
        }

        // If there is only 1 node, no cost reaching urself.
        if(n == 1) {
            cout << 0 << endl;
            continue;
        }
 
        // Initialise parents and childs
        vector<int> parents(n);
        vector<int> childs(n, 0);
        for(int i = 0; i < n; i++) {
            parents[i] = i;
        }

        vector<edge> tree; // resulting mst
        cost = kruskal(edges, parents, childs, tree);
        
        // check if its a mst
        if(tree.size() != n - 1) {
            cout << "Impossible" << endl;
            continue;
        }
        
        cout << cost << endl; // total cost

        sort(tree.begin(), tree.end(), compare); // lexicographic order
        for(edge& e : tree) {
            cout << e._from << " " << e._to << endl;
        }
    }
    return 0;
}