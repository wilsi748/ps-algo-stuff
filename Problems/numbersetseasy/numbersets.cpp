#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

set<int> primefactors(int n) {
    set<int> primes;
    for(int i = 2; i <= sqrt(n); i++) {
        while(n % i == 0) {
            primes.insert(i);
            n /= i;
        }
    }
    if(n > 1) {
        primes.insert(n);
    }
    return primes;
}

int find(vector<int>& v, int n) {
    //find set that n belongs to.
    if(v[n] == -1) {
        return n;
    }
    return v[n] = find(v, v[n]);
}

void merge(vector<int>& sets, int i, int j) {
    i = find(sets, i); 
    j = find(sets, j);
    if(i != j) sets[i] = j;
}

int calcSets(int a, int b, int p) {
    vector<int> sets(b+1, -1);
    
    for(int i = a; i < b+1; i++) {
        for(int j = i+1; j < b+1; j++) {
            set<int> primef_i = primefactors(i);
            set<int> primef_j = primefactors(j);
            for(int n : primef_i) {
                if(n >= p && primef_j.count(n) > 0) {
                    merge(sets, i, j);
                }
            }
        }
    }
    int count = 0;
    for(int i = a; i < b+1; i++) {
        if(sets[i] == -1) count++;
    }
    return count;
}


int main() {
    int n;
    cin >> n;
    int a, b, p;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> p; 
        cout << "Case #" << i+1 << ": " << calcSets(a, b, p) << endl;
    }
    return 0;
}