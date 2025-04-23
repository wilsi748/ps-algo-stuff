/*
    Author: William Sid (wilsi748)

    Problem solved: Factovisors
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long

unordered_map<ll, ll> primes;

// Calculate the number of occurences of each prime factor in n.
void prime_factors(ll n, unordered_map<ll, ll> &primes) {
    for (ll i = 2; i <= sqrt(n)+1; i++) {
        while (n % i == 0) {
            primes[i]++;
            n /= i;
        }
    }
    if (n > 1) {
        primes[n]++;
    }
}

ll highestPower(ll n, ll p) {
    ll res = 0;
    while (n > 0) {
        n /= p;
        res += n;
    }
    return res;
}

bool factovisor(ll n, ll m) {
    primes.clear();
    prime_factors(m, primes);
    
    // Check if m divides n!
    for (auto& [prime, power] : primes) {
        if (highestPower(n, prime) < power) {
            return false;
        }
    }
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll n, m;
    while(cin >> n >> m) {
        
        if(m == 0) {
            cout << m << " does not divide " << n << "!" << endl;
            continue;
        } else if (m == 1) {
            cout << m  << " divides " << n << "!" << endl;
            continue;
        }
        
        if(factovisor(n, m)) {
            cout << m  << " divides " << n << "!" << endl;
        } else {
            cout << m << " does not divide " << n << "!" << endl;
        }
    }
    return 0;
}