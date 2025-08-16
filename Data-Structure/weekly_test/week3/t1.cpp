#include <iostream>
#include <cmath>
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

int main()
{
	int i, j, m;
	int n, w;
	
	cin >> n;
    cin >> w;
	int arr[n];
    int vec[n-w+1];
	int sli[w];

    for (m = 0; m < n; m++)
	{
		cin >> arr[m];
	}
	
	for (i = 0; i < n-w+1; i++)
    {
        for (j = 0; j < w; j++)
        {
            sli[j] = arr[i+j];
        }
        Quick_Sort(sli, 0, w-1);
        vec[i] = sli[w-1];
    }
	
	for (m = 0; m < n-w+1; m++)
	{
		cout << vec[m] << " ";
	}
	
	return 0;
}