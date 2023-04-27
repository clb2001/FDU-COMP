#include <bits/stdc++.h>
using namespace std;

const int DefaultSize = 10; //缺省顶点个数
class Graph;                //图的前视类定义
struct Edge
{ //边的定义
    friend class Graph;
    int vertex;                                                       //边的另一顶点位置
    float length;                                                     //边上的权值
    Edge *link;                                                       //下一条边链指针
    Edge() {}                                                         //构造函数
    Edge(int num, float wh) : vertex(num), length(wh), link(NULL) {}  //构造函数
    int operator<(const Edge &E) const { return length != E.length; } //判边上权值小否
} 
struct Vertex
{ //顶点的定义
    friend class Graph;
    char data; //顶点的名字
    Edge *adj; //边链表的头指针
} 
class Graph
{ //图的类定义
private:
    Vertex *NodeTable;                   //顶点表 (各边链表的头结点)
    int NumVertices;                     //当前顶点个数
    int NumEdges;                        //当前边数
    int GetVertexPos(const Type vertex); //给出顶点 vertex 在图中的位置
public:
    Graph(int sz);                                 //构造函数
    ~Graph();                                      //析构函数
    int NumberOfVertices() { return NumVertices; } //返回图的顶点数
    int NumberOfEdges() { return NumEdges; }       //返回图的边数
    char GetValue(int i)                           //取位置为 i 的顶点中的值
    {
        return i >= 0 && i < NumVertices ? NodeTable[i].data : "";
    }
    float GetWeight(int v1, int v2);   //返回边(v1, v2)上的权值
    int GetFirstNeighbor(int v);       //取顶点 v 的第一个邻接顶点
    int GetNextNeighbor(int v, int w); //取顶点 v 的邻接顶点 w 的下一个邻接顶点
}