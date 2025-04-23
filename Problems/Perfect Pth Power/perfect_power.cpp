#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

/*
vector<int> calculate_primes(int n) 
{
    vector<int> primes;
    bool a[n + 1];
    memset(a, true, sizeof(a));

    for(int p = 2; p * p <= n; p++) {
        if (a[p] == true) {
            for (int i = p * p; i <= n; i+=p) {
                a[i] = false;
            }
        }
    }
    for(int p = 2; p <= n; p++) {
        if(a[p]) primes.push_back(p);
    }

    return primes;
}*/

int pth(long long int x) 
{
    bool neg = x < 0;
    x = abs(x);
    int b = 2;
    int p;
    
    for(int b = 2; b <= sqrt(x); b++) {
        p = (int)floor(log(x) / log(b));
        if(!neg) {
            if(pow(b, p) == x) return p;
        }else{
            if(fmod(p, 2) == 0.0) {
                continue;
            }else{
                if(pow(b, p) == x) return p;
            }
        }
    }
    return 1;
}

int main () {
    long long int x;
    while(cin >> x) 
    {
        if(x==0) break;
        if(x==1) printf("%d\n", 1);
        printf("%d\n", pth(x));
    }
    return 0;
}   