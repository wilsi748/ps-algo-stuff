#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

struct position {
    double x, y;
};

struct edge {
    int v1, v2;
    double dist;
    bool operator < (const edge& e) const { return (dist < e.dist); }
};

double getDistance(position p1, position p2) {
    return sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
}

int find(vector<int>& v, int n) {
    if(v[n] == -1) {
        return n;
    }
    return v[n] = find(v, v[n]);
}

void join(vector<int>& v, int i, int j) {
    i = find(v, i); 
    j = find(v, j);
    if(i != j) v[i] = j;
}

int main() {
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        vector<position> bridge_points(m);
        for(int j = 0; j < m; j++) {
            double x, y;
            cin >> x >> y;
            position p;
            p.x = x;
            p.y = y;
            bridge_points[j] = p;
        }
        
        vector<edge> island_dists;
        for(int j = 0; j < m; j++) {
            for(int k = j+1; k < m; k++) {
                edge e;
                e.v1 = j;
                e.v2 = k;
                e.dist = getDistance(bridge_points[j], bridge_points[k]);
                island_dists.push_back(e);
            } 
        }

        sort(island_dists.begin(), island_dists.end());
        vector<int> min_dists(m, -1);

        double res = 0;
        for(edge e : island_dists){
            if(find(min_dists, e.v1) != find(min_dists, e.v2)) {
                join(min_dists, e.v1, e.v2);
                res += e.dist;
            }
        }
        
        printf("%.4f\n", res);
    }
    return 0;
}