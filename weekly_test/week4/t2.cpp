#include <iostream>
#include <string>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int k;
    cin >> k;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int winner = 0;

    int num = 0;
    while (true)
    {
        if (arr[0] >= arr[1])
        {
            int temp = arr[1];
            for (int j = 1; j < N - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            arr[N] = temp;
            num += 1;
            if (num == k){
                break;
            }
        }
        else
        {
            int temp = arr[0];
            for (int j = 0; j < N - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            arr[N] = temp;
            num = 1;
        }
    }
    cout << arr[0] << endl;
    return 0;
}