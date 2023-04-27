#include <iostream>
#include <cmath>

using namespace std;
int main()
{
    int n;
    long nn = 1;
    long mm = 1e+9 + 7;
    cin >> n;
    for (int i = 1; i < n + 1; i++)
    {
        nn = i * nn;
    }
    cout << nn%mm << endl;
}

// #include <bits/stdc++.h>
// #include <iostream>
// using namespace std;

// const long long mod = 1000000007;

// int main()
// {
//     long N;
//     long long a = 1;
//     cin >> N;
//     for (long i = 1; i < N + 1; i++){
//         a = (i * a) % mod;
//     }
//     cout << a << endl;
//     return 0;
// }