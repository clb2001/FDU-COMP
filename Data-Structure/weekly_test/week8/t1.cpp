#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int m;
    cin >> m;

    int size = pow (2, m) - 1;
    int arr[size];
    for (int i = 0; i < size; i++){
        cin >> arr[i];
    }

    int i = 0;
    while (i < size){
        if (i > (size / 2 - 2) && i < size && arr[i] == -1){
            i--;
        }
        else if (arr[i] != -1 && i < size){
            cout << arr[i] << ' ';
            i = 2 * i + 2;
        }
    }
    cout << endl;
}