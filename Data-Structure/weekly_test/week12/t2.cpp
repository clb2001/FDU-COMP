#include <iostream>
#include <vector>
using namespace std;

int n[5001];
int m[50001];
// vector<vector<int> > G[50001];


void count(int s, int p, int n, vector<vector<int> > G){
    if (p == s){
        cout << 0 << " ";
        return;
    }
    int shortest = 0;
    bool flag = false;
    int v, w, k;

    int final[n]; //final[w] = 1表示顶点p到w的最短路径
    int D[n];// shortpathtable
    int P[n];// patharc

    for (int v = 0; v < n; v++){
        final[v] = 0;
        D[v] = G[p][v];
        P[v] = 0;
    }

    D[p] = 0;
    final[p] = 1;
    for (v = 1; v < n; v++){
        int min = 2147483647;
        for (w = 0; w < n; w++){
            if (!final[w] && D[w] <min){
                k = w;
                min = D[w];
            }
        }
        final[k] = 1;
        for (w = 0; w < n; w++){
               
        }
    }


    if (flag == true){
        cout << shortest << " ";
    }
    else {
        cout << 2147483647 << " ";
    }
}

int main(){
    // n: the num of vertex
    // m: the num of edge
    // s: the number of home
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int> > G(n, vector<int>(n, 0));
    // for (int i = 0; i < m; i++){
    //     vector<int> tmp;
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     tmp.push_back(v);
    //     tmp.push_back(w);
    //     G[u].push_back(tmp);
    // }

    for (int i = 0; i < m; i++){
        vector<int> tmp;
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = w;
    }

    for (int i = 0; i < n; i++){
        count(s, i, n, G);
    }

    return 0;
}