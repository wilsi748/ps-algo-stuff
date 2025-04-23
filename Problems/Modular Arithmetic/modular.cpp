/*
    Author: William Sid (wilsi748)

    Problem solved: Modular Arithmetic
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll mod(ll a, ll n) {
    return ((a % n) + n) % n;
}

ll add_mod(ll a, ll b, ll n) {
    return mod((a + b), n);
}

ll sub_mod(ll a, ll b, ll n) {
    return mod((a - b), n);
}

/* 
binary exponentiation - Fast calculation of a^n => a^(2n) => a^(2n+1) ...
Iterates over the binary digits of b, for each digit, if it is 1, update res by adding a mod n.
Then update a by squaring it modulo n and right shift b for next digit.
Time complexity: O(log2(b))
*/ 
ll mul_mod(ll a, ll b, ll n) {
    ll res = 0;
    while(b > 0) {
        if (b % 2) res = add_mod(res, a, n);
        a = add_mod(a, a, n);
        b >>= 1;
    }
    return res;
}


/*
Inverse mod: a * b ≡ 1 (mod n)
Extended Euclidean Algorithm to find it
r and t to represent remainder and coefficient of a and n.
when new_r == 0 it stops and the mod inv of a is t.
Time complexity: O(log n) where n is the input integer.
*/
ll inv_mod(ll a, ll n) {
    ll t = 0, new_t = 1;
    ll r = n, new_r = a;
    while(new_r != 0) {
        ll q = r / new_r;
        ll temp = t;
        t = new_t;
        new_t = temp - q * new_t;
        temp = r;
        r = new_r;
        new_r = temp - q * new_r;
    }
    if(t < 0) { // make positive.
        t += n;
    }
    return t;
}

ll gcd(ll a, ll b) {
    while(b != 0) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    while(true) {
        ll n;
        int t;
        cin >> n >> t;
        if(n == 0 && t == 0) break;
        while(t--) {
            ll x, y;
            char o;
            cin >> x >> o >> y;
            if(o == '+') cout << add_mod(x, y, n) << endl;
            else if(o == '-') cout << sub_mod(x, y, n) << endl;
            else if(o == '/') {
                if (n == 1) {
                    if (y == 1) cout << 1 << endl;
                    else cout << -1 << endl;
                } else if (gcd(y, n) != 1) {
                    cout << -1 << endl;
                } else {
                    cout << mul_mod(x, inv_mod(y, n), n) << endl;
                }
            } else if(o == '*') cout << mul_mod(x, y, n) << endl;
        }
    }
    return 0;
}