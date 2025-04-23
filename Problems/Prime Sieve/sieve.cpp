/*
    Author: William Sid (wilsi748)

    Problem solved: Erathostenes sieve algorithm

    Time complexity: Loops over all primes numbers up to sqrt(n), which is a time complexity of O(sqrt(n) log log n), 
    but the number of primes is approx n/(log n) so the overall time complexity will be O(n log log n).
*/
#include <bits/stdc++.h>

using namespace std;

class Sieve {
public:
    Sieve(int n) {
        // assign all values except 0, 1 to true
        is_prime.assign(n + 1, true); 
        is_prime[0] = is_prime[1] = false;
        // Mark all multiples of "i" as not prime, 
        // like the Eratosthenes sieve algorithm crosses out composite numbers.
        for (int i = 2; i <= sqrt(n); i++) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    // constant time queries
    bool isPrime(int x) {
        return is_prime[x];
    }

    int countPrimes() {
        return count(is_prime.begin(), is_prime.end(), true);
    }

private:
    vector<bool> is_prime;
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, q, x;
    cin >> n >> q;
    Sieve sieve(n);
    cout << sieve.countPrimes() << endl;
    while(q--) {
        cin >> x;
        
        if(sieve.isPrime(x)) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}