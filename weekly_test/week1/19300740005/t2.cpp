#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int N, T;
    int num = 0;
    int total = 0;
    cin >> N;
    cin >> T;
    int A[N];
    int B[N];
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i <N; i++)
    {
        cin >> B[i];
    }
    
    int i = 0;
    int j = 0;
    while (total < T && i < N && j < N)
    {
        if (A[i] <= B[j] && total < T)
        {
            total += A[i];
            num += 1;
            i++;
        }
        else if (A[i] > B[j] && total < T)
        {
            total += B[i];
            num += 1;
            j++;
        }
        else 
        {
            break;
        }
    }
    cout << num << endl;
    return 0;
}