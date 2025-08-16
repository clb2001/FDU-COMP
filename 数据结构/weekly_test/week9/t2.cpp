#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

void invalidArr(const char *a, int next[]){
    next[0] = -1;
    int k = -1;
    int i = 0;
    if(strlen(a) > 1){
        while (i < strlen(a)){
            if (k == -1 || a[i] == a[k]){
                i++;
                k++;
                next[i] = k;
            }
            else{
                k = next[k];
            }
        }
    }
}

// 从b字符串的第k个位置开始匹配
int KMP(const char *a, const char *b, int next[], int k){
    int i = k;
    while (i < strlen(b)){
        int mat = 0;
        while (a[mat] == b[i] && i < strlen(b)){
            mat++;
            i++;
            if (i == strlen(b)){
                return (i - mat);
            }
        }
        if (mat == strlen(a) && i + strlen(a) < strlen(b)){
            i++;
        }
        i -= next[mat];
    }
    return strlen(b);
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    const char *a = NULL;
    const char *b = NULL;
    a = s1.c_str();
    b = s2.c_str(); 

    int next[strlen(b)];
    invalidArr(b, next);
    int tmp = KMP(b, a, next, 0);

    for (int i = 0; i < tmp; i++){
        cout << s1[i];
    }
    cout << s2;
    return 0;
}