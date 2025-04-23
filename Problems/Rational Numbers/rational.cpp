/*
    Author: William Sid (wilsi748)

    Problem solved: Rational Numbers

    Makes use of the Euclidean algorithm to compute the gcd of numerator and denominator to simplify the fraction.

    Provided a small test function according to advice from course website.
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long

class Rational {
public:
    Rational() : Rational(0, 1) {}
    Rational(ll n) : Rational(n, 1) {}
    Rational(ll n, ll d) {
        if(d == 0) throw invalid_argument("denom cannot be 0");
        if(n == 0) num = 0, den = 1;
        else {
            ll div = gcd(abs(n), abs(d));
            num = n / div;
            den = d / div;
            if (den < 0) {
                num = -num;
                den = -den;
            }
        }
    }

    ll getNum() const { return num; }
    ll getDenom() const { return den; }

    // Negate, addition, subtraction, multiply, division
    Rational operator-() const { return Rational(-num, den); } 
    Rational operator+(const Rational& other) const { return Rational(num * other.den + den * other.num, den * other.den); }
    Rational operator-(const Rational& other) const { return Rational(num * other.den - den * other.num, den * other.den); }
    Rational operator*(const Rational& other) const { return Rational(num * other.num, den * other.den); }
    Rational operator/(const Rational& other) const {
        if (other.num == 0) {throw domain_error("division by zero");}
        return Rational(num * other.den, den * other.num);
    }
    // The six comparison operators, <, >, <=, >=, ==, and !=
    bool operator<(const Rational& other) const { return num * other.den < den * other.num; }
    bool operator<=(const Rational& other) const { return num * other.den <= den * other.num; }
    bool operator>(const Rational& other) const { return num * other.den > den * other.num; }
    bool operator>=(const Rational& other) const { return num * other.den >= den * other.num; }
    bool operator==(const Rational& other) const { return num == other.num && den == other.den; }
    bool operator!=(const Rational& other) const { return !(*this == other); }
    // Get the double value
    double toDouble() const { return (double)num/(double)den; }

    // for output
    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.num << " / " << r.den;
        return os;
    }

private:
    ll num;
    ll den;

    ll gcd(ll a, ll b) {
        while(b != 0) {
            ll t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
};

// Small test to check comparison
void test_rational() {
    vector<Rational> rationals = {
        Rational(1, 2),
        Rational(1, 3),
        Rational(2, 3),
        Rational(3, 4),
        Rational(4, 5),
        Rational(5, 6)
    };
    sort(rationals.begin(), rationals.end());
    for(Rational& r : rationals) cout << r.toDouble() << "   ";
    cout << endl;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int ops;
    cin >> ops;
    while(ops--) {
        ll x1, y1, x2, y2;
        char o;
        cin >> x1 >> y1 >> o >> x2 >> y2;
        Rational r1(x1, y1);
        Rational r2(x2, y2);
        if(o == '+') cout << r1 + r2 << endl;
        else if(o == '-') cout << r1 - r2 << endl;
        else if(o == '/') cout << r1 / r2 << endl;
        else if(o == '*') cout << r1 * r2 << endl;
    }
    return 0;
}