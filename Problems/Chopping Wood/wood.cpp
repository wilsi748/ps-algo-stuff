#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <iterator>
#include <vector>
#include <queue>
#include <map>
using namespace std;

template<class OutputIterator, class T>
OutputIterator iota_rng(OutputIterator first, T low, T high)
{
    return generate_n(first, high-low, [&, value = low]() mutable {return value++; });
}

int main(void) {
    int n;
    scanf("%d", &n);
    int v[n];
    vector<int> u;
    map<int, int> c;

    for (int i = 1; i <= n; i++) {
        c[i] = 0;
    }

    set<int> leafs;
    iota_rng(std::inserter(leafs, leafs.begin()), 1, n+2);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        c[v[i]] += 1;
        if (leafs.find(v[i]) != leafs.end()) {
            leafs.erase(v[i]);
        }
    }

    if(v[n-1] != n+1) {
        printf("Error");
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> a;
    
    for(int l : leafs) {
        a.push(l);
    }
    
    for(int i : v) {
        if(a.size() == 0) {
            printf("Error");
            return 0;
        }
        u.push_back(a.top());
        a.pop();
        c[i] -= 1;
        if(c[i] == 0) {
            a.push(i);
        }
    }
    for(int i = 0; i < n; i++) {
        printf("%d\n", u[i]);
    }
    return 0;
}