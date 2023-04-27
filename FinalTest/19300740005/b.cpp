#include <iostream>
#include <vector>
using namespace std;

struct Dis {
    int value;
    bool visit;
    void dis() {
        visit = false;
        value = 0;
    }
};

void shortest_root(Dis* dis, int n, int s, vector<vector<int> > G, vector<int> &tmp){
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
            tmp[i] = dis[i].value;
        }
        else{
            tmp[i] = 2147483647;
        }
    }
}

int main(){
    // n: the num of vertex
    // m: the num of edge
    int n, m;
    cin >> n >> m;
    vector<vector<int> > G(n, vector<int>(n, 0));
    Dis* dis_M = new Dis[n];
    Dis* dis_W = new Dis[n];

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

    vector<int> M = vector<int>(n, 0);
    vector<int> W = vector<int>(n, 0);
    shortest_root(dis_M, n, 1, G, M);
    shortest_root(dis_W, n, n, G, W);

    int min = 2147483647;
    for (int i = 1; i < n - 1; i++){
        if (M[i] < 2147483647 && W[i] < 2147483647 && (M[i] + W[i] < min)){
            min = M[i] + W[i];
        }
    }

    if (min == 2147483647){
        cout << -1 << endl;
    }
    else{
        cout << min << endl;
    }

    return 0;
}