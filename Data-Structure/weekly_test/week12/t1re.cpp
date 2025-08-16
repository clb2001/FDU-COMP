#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int OP[100001];
int VAL[100001];

void InsertSort(vector<int> &arr){
	for (int j = 1; j < arr.size(); j++){
		int i = j;
		int num = arr[j];
		while(i > 0 && arr[i-1] > num){
			arr[i] = arr[i-1];
			i--;
		}
		arr[i] = num;
	}
}

void Merge(vector<int> &arr, vector<int> L, vector<int> R){
	int i = 0, j = 0, k = 0;
	while (i < L.size() && j < R.size()){
		if (L[i] <= R[j]){
			arr[k++] = L[i++];
		}
		else{
			arr[k++] = R[j++];
		}
	}
	while (i < L.size()){
		arr[k++] = L[i++];
	}
	while (j < R.size()){
		arr[k++] = R[j++];
	}
}

void Merge_Sort(vector<int> &arr){
	if (arr.size() > 1){
		int mid = arr.size() / 2;
        vector<int> left = vector<int>(mid, 0);
        vector<int> right = vector<int>(arr.size() - mid, 0);
		// int *left = (int*)malloc(sizeof(int)*mid);
		// int *right = (int*)malloc(sizeof(int)*(size - mid));
		for (int i = 0; i < mid; i++){
			left[i] = arr[i];
		}
		for (int j = mid; j < arr.size(); j++){
			right[j-mid] = arr[j];
		}
		Merge_Sort(left);
		Merge_Sort(right);
		Merge(arr, left, right);
	}
}

int binarySearch(vector<int>& nums, int target) {
	int low = 0;	
	int high = nums.size() - 1; 
	while (low <= high)	{
		int mid = (low + high) / 2;
		if (nums[mid] < target) {
			low = mid + 1;
		}
		else if (nums[mid] > target) { 
			high = mid - 1;	
		}
		else { 
			return mid;		
		}
	}
	return -1;
}

int main(){
    int n;
    cin >> n;
    vector<int> Store;

    for (int i = 0; i < n; i++){
        cin >> OP[i] >> VAL[i];
    }

    for (int i = 0; i < n; i++){
        if (OP[i] == 1){
            Store.push_back(VAL[i]);
            // InsertSort(Store);
            sort(Store.begin(),Store.end());
            // Merge_Sort(Store);
        }
        else if (OP[i] == 2){
            // Merge_Sort(Store);
            cout << binarySearch(Store, VAL[i]) << endl;
        }
    }

    return 0;
}