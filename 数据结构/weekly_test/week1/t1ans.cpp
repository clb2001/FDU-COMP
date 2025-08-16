#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;

int main(){
    int n;
    cin >> n;
    long long ans = 1;
    for (int i = 1; i <= n; i++){
        ans = (ans * i) %mod;
    }
    cout << ans << endl;
    return 0;
}