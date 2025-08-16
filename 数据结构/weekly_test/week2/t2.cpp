#include <iostream>
#include <cmath>
#include <vector>
#include <malloc.h>
#include <stdlib.h>
using namespace std;

void Quick_Sort(int arr[], int low, int high)
{
	if (low < high)
	{
		int i = low, j = high;
		int x = arr[low];
		while (i < j)
		{
			while (i < j && arr[j] >= x)
			{
				j--;
			}
			if (i < j)
			{
				arr[i++] = arr[j];
			}
			while (i < j && arr[i] <= x)
			{
				i++;
			}
			if (i < j)
			{
				arr[j--] = arr[i];
			}
			arr[i] = x;
			Quick_Sort(arr, low, i - 1);
			Quick_Sort(arr, i + 1, high);
		}
	}
}

void Arrange(vector<int>& arr, int arr_1[], int arr_2[], int size_1, int size_2)
{
    int i = 0, j = 0, k = 0;
    while (i < size_1 && j < size_2)
    {
        if (arr_1[i] == arr_2[j])
        {
            arr.push_back(arr_1[i]);
            i++;
            j++;
            k++;
        }
        else if (arr_1[i] < arr_2[j])
        {
            i++;
        }
        else if (arr_1[i] > arr_2[j])
        {
            j++;
        }
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
    vector<int> arr;

    for (m = 0; m < size_1; m++)
    {
        cin >> arr_1[m];
    }

    for (n = 0; n < size_2; n++)
    {
        cin >> arr_2[n];
    }

    Quick_Sort(arr_1, 0, size_1 - 1);
    Quick_Sort(arr_2, 0, size_2 - 1);

    Arrange(arr, arr_1, arr_2, size_1, size_2);

    for (k = 0; k < arr.size(); k++)
    {
        cout << arr[k] << " ";
    }

    cout << endl
         << " ";
    return 0;
}