/*
    Author: William Sid (wilsi748)

    Problem solved: Cudak
*/
#include <bits/stdc++.h>

using namespace std;

long long dp[20][136];

long long count_numbers(long long n, int S)
{
    // if s is negative, there are no valid numbers
    if (S < 0)
    {
        return 0;
    }
    // if n = 0 and s = 0, only 1 is a valid number.
    if (n == 0 && S == 0)
    {
        return 1;
    }
    // if only n = 0, no valid numbers.
    if (n == 0)
    {
        return 0;
    }

    long long sum = 0, num = n;
    int last_digit, n_digits = 0;
    while (num)
    {
        last_digit = num % 10;
        num /= 10;
        n_digits++;
    }
    // if n has only one digit
    if (n_digits == 1)
    {
        // if the digit sum S is less than or equal to n,
        // then there is 1 valid number
        if (S <= n)
        {
            return 1;
        }
        // otherwise no valid numbers
        else
        {
            return 0;
        }
    }
    // for numbers with multiple digits, we count the number of valid numbers recursively
    for (int i = 0; i < last_digit && S - i >= 0; i++)
    {
        sum += dp[n_digits - 1][S - i];
    }
    long long factor = 1;
    while (factor * 10 <= n)
    {
        factor *= 10;
    }
    return (sum + count_numbers(n - last_digit * (long long)factor, S - last_digit));
}

long long find_smallest(long long A, long long B, int S)
{
    // binary search
    // find the smallest number in the range [A, B] whose digits sum to S.
    long long left = A, right = B, mid;
    while (left != right)
    {
        // find middle of search range, add 1 to round up.
        mid = (left + right + 1) / 2;
        // Check for valid number
        // greater than 0 means there is valid number in right side so continue search there,
        // otherwise continue in left.
        if ((count_numbers(mid, S) - count_numbers(left, S)) > 0)
        {
            right = mid - 1;
        }
        else
        {
            left = mid;
        }
    }
    return left + 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Precompute valid numbers for every digit sum and number of digits.
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < 10; i++)
    {
        dp[1][i] = 1;
    }
    for (int i = 2; i < 20; i++)
    {
        for (int j = 0; j <= 135; j++)
        {
            for (int k = 0; k < 10 && j - k >= 0; k++)
            {
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }

    long long A, B;
    int S;
    cin >> A >> B >> S;

    cout << count_numbers(B, S) - count_numbers(A - 1, S) << endl;
    cout << find_smallest(A, B, S) << endl;

    return 0;
}