/*
    Author: William Sid (wilsi748)

    Problem solved: Happy Happy Prime Prime
*/
#include <bits/stdc++.h>

using namespace std;


// Check if a number is a happy number
bool isHappy(int n) {
    set<int> visited; // keep track of numbers
    // As long as n is not 1 we keep computing the sum of the squares of its digits.
    while(n != 1) {
        // if we have already seen this sum, cycle, exit, not happy.
        if(visited.count(n)) return false;
        // Add sum to set.
        visited.insert(n);
        int sum = 0;
        while(n > 0) {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        n = sum; // update n as the computed sum.
    }
    // n is 1 and is happy return true.
    return true;
}

// Check if n is a prime number
bool isPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= sqrt(n)+1; i++) {
        if(n%i==0) return false;
    }
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int p;
    cin >> p;
    p++;
    while(--p) {
        int k, m;
        cin >> k >> m;
        if(isPrime(m) && isHappy(m)) {
            cout << k << " " << m << " YES" << endl;
        } else {
            cout << k << " " << m << " NO" << endl;
        }
    }

    return 0;
}