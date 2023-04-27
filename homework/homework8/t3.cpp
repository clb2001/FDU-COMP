#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void Graph ::dfs(int visited[], int indegree[], int v, int &count)
{
    count++;
    visited[v] = count;
    cout << NodeTable[v].data << endl;
    Edge *p = NodeTable[v].adj;
    while (p != NULL)
    {
        int w = p->vertex;
        indegree[w]--;
        if (visited[w] == 0 && indegree[w] == 0)
            dfs(visited, indegree, w, count);
        p = p->link;
    }
}
int i, j;
Edge *p;
float w;
cin >> NumVertices;
int *visited = new int[NumVertices + 1];
int *indegree = new int[NumVertices + 1];
for (i = 1; i <= NumVertices; i++)
{
    NodeTable[i].adj = NULL;
    cin >> NodeTable[i].data;
    cout << endl;
    visited[i] = 0;
    indegree[i] = 0;
}
int count = 0;
cin >> i >> j >> w;
cout << endl;
while (i != 0 && j != 0)
{
    p = new Edge(j, w);
    if (p == NULL)
    {
        cout << "存储分配失败！" << endl;
        exit(1);
    }
    indegree[j]++;
    p->link = NodeTable[i].adj;
    NodeTable[i].adj = p;
    NumEdges++;
    cin >> i >> j >> w;
    cout << endl;
}
for (i = 1; i <= NumVertices; i++)
    if (visited[i] == 0 && indegree[i] == 0)
        dfs(visited, indegree, i, count);
if (count < NumVertices)
    cout << "排序失败!" << endl;
else
    cout << "排序成功!" << endl;
delete[] visited;
delete[] indegree;