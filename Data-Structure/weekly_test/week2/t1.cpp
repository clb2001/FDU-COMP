#include <iostream>
#include <cmath>
#include <malloc.h>
#include <stdlib.h>
using namespace std;

void Merge(int arr[], int L[], int R[], int l, int r)
{
    int i = 0, j = 0, k = 0;
    while (i < l && j < r)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }
    while (i < l)
    {
        arr[k++] = L[i++];
    }
    while (j < r)
    {
        arr[k++] = R[j++];
    }
}

int main()
{
    int m, n, k;
    int size_1;
    int size_2;

    cin >> size_1;
    cin >> size_2;

    int arr_1[size_1];
    int arr_2[size_2];
    int size = size_1 + size_2;
    int arr[size];

    for (m = 0; m < size_1; m++)
    {
        cin >> arr_1[m];
    }

    for (n = 0; n < size_2; n++)
    {
        cin >> arr_2[n];
    }

    Merge(arr, arr_1, arr_2, size_1, size_2);

    for (k = 0; k < size; k++)
    {
        cout << arr[k] << " ";
    }

    cout << endl
         << " ";
    return 0;
}