#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int n;
    cin >> n;
    int index[n];

    string source_storage[n];
    string target_storage[n];

    for (int i = 0; i < n; i++){
        cin >> index[i];
        cin >> source_storage[i];
        cin >> target_storage[i];
    }

    for (int i = n-1; i >= 0; i--){
        if (s.find(source_storage[i]) == index[i]){
            s.replace(index[i], source_storage[i].size(), target_storage[i]);
        }
    }

    cout << s << endl;    
    return 0;
}