#include <iostream>
#include <vector>
using namespace std;

// vector<vector<int> > G[50001];

struct Dis {
    int value;
    bool visit;
    void dis() {
        visit = false;
        value = 0;
    }
};

int main(){
    // n: the num of vertex
    // m: the num of edge
    // s: the number of home
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int> > G(n, vector<int>(n, 0));
    Dis *dis = new Dis[n];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            G[i][j] = 2147483647;
        }
    }

    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        if (w < G[u-1][v-1]){
            G[u-1][v-1] = w;
        }
    }

    for (int i = 0; i < n; i++){
        dis[i].value = G[s-1][i];
    }

    dis[s-1].value = 0;
    dis[s-1].visit = true;

    int count = 1;

    while(count != n){
        int tmp = 0;
        int min = 2147483647;
        for (int i = 0; i < n; i++){
            if (!dis[i].visit && dis[i].value < min){
                min = dis[i].value;
                tmp = i;
            }
        }
        dis[tmp].visit = true;
        count++;
        for (int i = 0; i < n; i++){
            if ((!dis[i].visit) && (G[tmp][i] != 2147483647) && (dis[tmp].value != 2147483647) \
            && ((dis[tmp].value + G[tmp][i]) < dis[i].value)) {
                dis[i].value = dis[tmp].value + G[tmp][i];
            }
        }
    }

    for (int i = 0; i < n; i++){
        if (dis[i].value != 2147483647){
            cout << dis[i].value << " ";
        }
        else{
            cout << 2147483647 << " ";
        }
    }
    cout << endl;

    return 0;
}