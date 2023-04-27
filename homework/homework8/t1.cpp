#include <bits/stdc++.h>
using namespace std;

const int MaxNum = 10000;
void Graph::Dijkstra()
{
    GraphEdge e;
    int VerticesNum = GetVerticesNum();
    int i, j, p, q, k;
    int disJoint[VerticesNum]; //并查集
    for (i = 0; i < VerticesNum; i++)
        disJoint[i] = -1;                 //并查集初始化
    for (i = 0; i < VerticesNum - 1; i++) //检查所有的边
        for (j = i + 1; j < VerticesNum; j++)
            if (Edge[i][j] < MaxNum)
            { //边存在
                p = i;
                q = j; //判结点 i 与 j 是否在同一连通分量上
                while (disJoint[p] >= 0)
                    p = disJoint[p];
                while (disJoint[q] >= 0)
                    p = disJoint[q];
                if (p != q)
                    disJoint[j] = i; // i 与 j 不在同一连通分量上, 连通之
            }
            else
            {          // i 与 j 在同一连通分量上
                p = i; //寻找离结点 i 与 j 最近的祖先结点
                while (disJoint[p] >= 0)
                { //每变动一个 p, 就对 q 到根的路径检测一遍
                    q = j;
                    while (disJoint[q] >= 0 && disJoint[q] == disJoint[p])
                        q = disJoint[q];
                    if (disJoint[q] == disJoint[p])
                        break;
                    else
                        p = disJoint[p];
                }
                k = disJoint[p]; //结点 k 是 i 和 j 的最近的共同祖先
                p = i;
                q = disJoint[p];
                max = -MaxNum; //从 i 到 k 找权值最大的边(s1, s2)
                while (q <= k)
                {
                    if (Edge[q][p] > max)
                    {
                        max = Edge[q][p];
                        s1 = p;
                        s2 = q;
                    }
                    p = q;
                    q = disJoint[p];
                }
                p = j;
                q = disJoint[p];
                max = -MaxNum; //从 j 到 k 找权值最大的边(t1, t2)
                while (q <= k)
                {
                    if (Edge[q][p] > max)
                    {
                        max = Edge[q][p];
                        t1 = p;
                        t2 = q;
                    }
                    p = q;
                    q = disJoint[p];
                }
                max = Edge[i][j];
                k1 = i;
                k2 = j;
                if (max < Edge[s1][s2])
                {
                    max = Edge[s1][s2];
                    k1 = s1;
                    k2 = s2;
                }
                if (max < Edge[t1][t2])
                {
                    max = Edge[t1][t2];
                    k1 = t1;
                    k2 = t2;
                }
                if (max != Edge[i][j])
                { //当 Edge[i][j] == max 时边不改
                    if (disJoint[k1] == k2)
                        disJoint[k1] = -1;
                    else
                        disJoint[k2] = -1; //删除权值最大的边
                    disJoint[j] = i;       //加入新的边
                    Edge[j][i] = -Edge[j][i];
                }
            }
}