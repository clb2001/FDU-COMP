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