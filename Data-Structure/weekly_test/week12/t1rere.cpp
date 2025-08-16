#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 没想到&A和A时间差这么多
int binarySearch(vector<int> &A, int target) {
    int low = 0;	
	int high = A.size() - 1; 
    while (low <= high) {
        int mid = (low + high) / 2;
        if (target <= A[mid]){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
}

int binarySearchA(vector<int> &A, int target) {
	int low = 0;	
	int high = A.size() - 1; 
	while (low <= high)	{
		int mid = (low + high) / 2;
		if (A[mid] < target) {
			low = mid + 1;
		}
		else if (A[mid] > target) { 
			high = mid - 1;	
		}
		else { 
			return mid;		
		}
	}
	return -1;
}

void binInsertionSort(vector<int> &A ,int loc) {
    int tmp = A[A.size()-1];
    for (int j = A.size() - 2; j >= loc; j--) {
        A[j + 1] = A[j];
    }
    A[loc] = tmp;
}

int main(){
    int n;
    cin >> n;
    vector<int> Store;
    int OP[n];
    int VAL[n];
    for (int i = 0; i < n; i++){
        cin >> OP[i] >> VAL[i];
    }

    for (int i = 0; i < n; i++){
        if (OP[i] == 1){
            int loc = binarySearch(Store, VAL[i]);
            Store.push_back(VAL[i]);
            binInsertionSort(Store, loc);
        }
        else if (OP[i] == 2){
            cout << binarySearchA(Store, VAL[i]) << endl;
        }
    }

    return 0;
}