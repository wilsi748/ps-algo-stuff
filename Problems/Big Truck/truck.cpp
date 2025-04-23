/*
    Author: William Sid (wilsi748)

    Problem solved: 
*/
#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;

struct edge {
    int _to;
    int _dist;
    edge() : _to(-1), _dist(inf) {};
    edge (int to, int dist) :  _to(to), _dist(dist) {}
};

struct node {
    int _index;
    vector<edge> _neighbours; // adjacency for lower time complexity
    int _dist;
    int _items;
    node() :  _index(0), _neighbours(0), _dist(inf), _items(0) {};
    node(int index, vector<edge> neighbours, int dist, int items) : _index(index), _neighbours(neighbours), _dist(dist), _items(items) {} 
};
bool operator > (const node& n1, const node& n2) {
    return (n1._dist > n2._dist); 
}


vector<int> get_path(int query, int start, vector<node>& nodes, vector<int>& parent_list, vector<int>& path) {
    while(true) {
        path.push_back(query);
        int prev = parent_list[query];
        if(prev == -1 && query == start) break;
        if(prev == -1) break;
        query = prev;
    }
    return path;
}

// Djikstra
int shortest_path_one(int start, vector<node>& nodes, vector<edge>& roads, vector<int>& parents, int n) {
    int items = 0;
    int best = 0;
    priority_queue<node, vector<node>, greater<node>> pq;
    nodes[start]._dist = 0;
    pq.push(nodes[start]);
    while(!pq.empty()) {
        node n = pq.top();
        pq.pop();
        for(edge& e : n._neighbours) {
            int dist = n._dist + e._dist;
            
            if(dist <= nodes[e._to]._dist) {
                nodes[e._to]._dist = dist;
                int stuff = best + n._items + nodes[e._to]._items;
                if(stuff > best) {
                    best = stuff;
                    pq.push(nodes[e._to]);
                    parents[e._to] = n._index;
                }
            }
        }
    }
    vector<int> path;
    get_path(n, 1, nodes, parents, path);
    for(int i = 0; i < path.size(); i++) {
        items += nodes[path[i]]._items;
    }
    return items;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, start, end;
    start = 1;
    while(cin>>n) {
        end = n;
        node temp;
        vector<node> nodes(n+1, temp); //locations
        for(int i = 1; i <= n; i++) {
            int t;
            cin >> t;
            nodes[i]._index = i;
            nodes[i]._items = t;
        }

        int m;
        cin >> m;
        vector<edge> roads(m);
        for(int i = 0; i < m; i++) {
            int a, b, d;
            cin >> a >> b >> d;
            if(a == b) continue;
            nodes[a]._neighbours.push_back(edge(b, d));
            nodes[b]._neighbours.push_back(edge(a, d));
            //roads.push_back(edge(a, b, d));
        }
        vector<int> parent_list(nodes.size(), -1);
        int items = shortest_path_one(start, nodes, roads, parent_list, n);
            
        if (nodes[end]._dist == inf) {
            cout << "impossible" << endl;
        }else {
            cout << nodes[end]._dist << " " << items << endl;
        }
    }
    return 0;
}