#include <iostream>
#include <vector>
using namespace std;

int OP[100001];
int VAL[100001];

struct BSNode{
    int key;
    BSNode* left;
    BSNode* right;
    BSNode* parent;

    BSNode(int value, BSNode* p, BSNode* r, BSNode* l):
    key(value), parent(p), left(l), right(r){}

    BSNode(){
        left = NULL;
        right = NULL;
        parent = NULL;
    };
};

struct BSTree{
    BSNode* mRoot;

    BSTree(){
        mRoot = NULL;
    };
    
    ~BSTree(){}
};

void Insert(BSTree* &tree, int k){
    BSNode *x = tree->mRoot;
    BSNode *y = NULL;
    BSNode *z = new BSNode();
    z->key = k;
    // 这一步是将z插到x的下面
    while (x != NULL) {
        y = x;
        if (z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL){
        tree->mRoot = z;
    }
    // 确定z是左节点还是右节点
    else if (z->key < y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
}

void inOrder(BSNode *x, int &count, int e, bool &flag) {
    if (x != NULL){
        inOrder(x->left, count, e, flag);
        if (x->key == e){
            cout << count << endl;
            flag = true;
            return;
        }
        count++;
        inOrder(x->right, count, e, flag);
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> Store;
    BSTree *tree = new BSTree();

    for (int i = 0; i < n; i++){
        cin >> OP[i] >> VAL[i];
    }

    for (int i = 0; i < n; i++){
        if (OP[i] == 1){
            Store.push_back(VAL[i]);
            Insert(tree, Store[Store.size()-1]);
        }
        else if (OP[i] == 2){
            int count = 0;
            bool flag = false;
            inOrder(tree->mRoot, count, VAL[i], flag);
            if (flag == false){
                cout << -1 << endl;
            }
        }
    }

    return 0;
}

// void max_heapify(vector<int> &arr, int start, int end){
//     int dad = start;
//     int son = dad * 2 + 1;
//     while (son <= end){
//         if (son + 1 <= end && arr[son] < arr[son + 1])
//             son++;
//         if (arr[dad] > arr[son])
//             return;
//         else{ 
//             swap(arr[dad], arr[son]);
//             dad = son;
//             son = dad * 2 + 1;
//         }
//     }
// }

// void Build(vector<int> &store){
//     for (int i = store.size() / 2 - 1; i >= 0; i--){
//         max_heapify(store, i, store.size() - 1);
//     }
//     for (int i = store.size() - 1; i > 0; i--){
//         swap(store[0], store[i]);
//         max_heapify(store, 0, i - 1);
//     }
// }

// void Search(vector<int> store, int e){
//     int i = 0;
//     for (i = 0; i < store.size(); i++){
//         if (store[i] == e){
//             cout << i << endl;
//             return;
//         }
//     }
//     if (i == store.size()){
//         cout << -1 << endl;
//     }
// }

// void Search(BSTree *tree, int e){
//     int i = 0;
//     BSNode* cur = tree->mRoot;
// 	while (cur){
// 		if (e < cur->key){
// 			cur = cur->left;
//             i = 2 * i - 1;
// 		}
// 		else if (e > cur->key){
// 			cur = cur->right;
//             i = 2 * i;
// 		}
// 		else{
// 			cout << i << endl;
// 		}
// 	}
// 	cout << -1 << endl;
// }