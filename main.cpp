#include <iostream>
#include <limits.h>
#include <queue>
#include <stack>

using namespace std;

//INT_MAX in limits.h
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20

//图类型
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;//有向图、网,无向图、网

//顶点元素类型
typedef char VertexType;

//邻接矩阵
//边（弧）节点
typedef struct arcCell {
    int adj;        //0，1 或 权值
    char *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//邻接矩阵图
typedef struct mGraph {
    VertexType vers[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs;                     //邻接矩阵
    int vexnum, arcnum;                 //顶点数、边数
    GraphKind kind;                     //图类型
} MGraph;

//邻接表
//边（弧）节点
typedef struct arcNode {
    int adjvex;                 //边（弧）指向的顶点的位置
    int wight;                  //权值
    struct arcNode *nextarc;
    char *info;
} ArcNode;
//顶点节点
typedef struct vNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];
//邻接表图
typedef struct alGraph {
    AdjList vertices;       //顶点向量
    int vexnum, arcnum;      //顶点数、边数
    GraphKind kind;         //图类型
} ALGraph;


//**********************************************创建邻接矩阵*****************************************************
int locateVex(MGraph g, VertexType v) {
    for (int i = 0; i < g.vexnum; ++i) {
        if (v == g.vers[i]) {
            return i;
        }
    }
    return -1;
}

void createDG(MGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        for (int j = 0; j < g.vexnum; ++j) {
            g.arcs[i][j].adj = 0;
            g.arcs[i][j].info = NULL;
        }
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vers[i];
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧（如：a b）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        cin >> v1 >> v2;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            g.arcs[i][j].adj = 1;
        }
    }

}

void createDN(MGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        for (int j = 0; j < g.vexnum; ++j) {
            g.arcs[i][j].adj = INFINITY;
            g.arcs[i][j].info = NULL;
        }
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vers[i];
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧及权值（如：a b 2）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        cin >> v1 >> v2 >> w;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            g.arcs[i][j].adj = w;
        }

    }
}

void createUDG(MGraph &g) {

    cout << "输入顶点数、边数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        for (int j = 0; j < g.vexnum; ++j) {
            g.arcs[i][j].adj = 0;
            g.arcs[i][j].info = NULL;
        }
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vers[i];
    }

    cout << "输入" << g.arcnum << "个由边附着的顶点形成的边（如：a b）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        cin >> v1 >> v2;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            g.arcs[i][j].adj = 1;
            g.arcs[j][i].adj = 1;   //双向
        }

    }
}

void createUDN(MGraph &g) {

    cout << "输入顶点数、边数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        for (int j = 0; j < g.vexnum; ++j) {
            g.arcs[i][j].adj = INFINITY;
            g.arcs[i][j].info = NULL;
        }
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vers[i];
    }

    cout << "输入" << g.arcnum << "个由边附着的顶点形成的边及权值（如：a b 5）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        cin >> v1 >> v2 >> w;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            g.arcs[i][j].adj = w;
            g.arcs[j][i].adj = w;
        }

    }
}

//**********************************************创建邻接矩阵图*****************************************************
void createGraph(MGraph &g) {
    int selectGraph;
    cout << "输入图类型选择：有向图（0）、有向网（1）、无向图（2）、无向网（3）：";
    cin >> selectGraph;
    switch (selectGraph) {
        case 0:
            g.kind = DG;
            createDG(g);
            break;
        case 1:
            g.kind = DN;
            createDN(g);
            break;
        case 2:
            g.kind = UDG;
            createUDG(g);
            break;
        case 3:
            g.kind = UDN;
            createUDN(g);
            break;
        default:
            return;
    }
}

//输出邻接矩阵
void printMGraph(MGraph g) {
    for (int i = 0; i < g.vexnum; ++i) {
        for (int j = 0; j < g.vexnum; ++j) {
            cout << g.arcs[i][j].adj << " ";
        }
        cout << endl;
    }
}


//**********************************************创建邻接表*****************************************************
int locateVex(ALGraph g, VertexType v) {
    for (int i = 0; i < g.vexnum; ++i) {
        if (v == g.vertices[i].data) {
            return i;
        }
    }
    return -1;
}

void createDG(ALGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        g.vertices[i].data = 0;
        g.vertices[i].firstarc = NULL;
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vertices[i].data;
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧（如：a b）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        cin >> v1 >> v2;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->wight = 1;

            p->nextarc = g.vertices[i].firstarc;      //此处链表使用了头插法，操作比较方便
            g.vertices[i].firstarc = p;
        }
    }

}

void createDN(ALGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        g.vertices[i].data = 0;
        g.vertices[i].firstarc = NULL;
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vertices[i].data;
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧及其权值（如：a b 5）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        cin >> v1 >> v2 >> w;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->wight = w;

            p->nextarc = g.vertices[i].firstarc;      //此处链表使用了头插法，操作比较方便
            g.vertices[i].firstarc = p;
        }
    }
}

void createUDG(ALGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        g.vertices[i].data = 0;
        g.vertices[i].firstarc = NULL;
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vertices[i].data;
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧（如：a b）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        cin >> v1 >> v2;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->wight = 1;
            p->nextarc = g.vertices[i].firstarc;
            g.vertices[i].firstarc = p;

            ArcNode *q = (ArcNode *) malloc(sizeof(ArcNode));   //双向，对称操作
            q->adjvex = i;
            q->wight = 1;
            q->nextarc = g.vertices[j].firstarc;
            g.vertices[j].firstarc = q;
        }
    }
}

void createUDN(ALGraph &g) {

    cout << "输入顶点数、弧数：";
    cin >> g.vexnum >> g.arcnum;      //此处暂不考虑info

    for (int i = 0; i < g.vexnum; ++i) {
        g.vertices[i].data = 0;
        g.vertices[i].firstarc = NULL;
    }

    cout << "输入" << g.vexnum << "个顶点：";
    for (int i = 0; i < g.vexnum; ++i) {
        cin >> g.vertices[i].data;
    }

    cout << "输入" << g.arcnum << "个由弧附着的顶点形成的弧（如：a b）：" << endl;
    for (int k = 0; k < g.arcnum; ++k) {
        VertexType v1, v2;
        int w;
        cin >> v1 >> v2 >> w;
        int i = locateVex(g, v1), j = locateVex(g, v2);
        if (i >= 0 && j >= 0) {
            ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->wight = w;
            p->nextarc = g.vertices[i].firstarc;
            g.vertices[i].firstarc = p;
            ArcNode *q = (ArcNode *) malloc(sizeof(ArcNode));   //对称操作
            q->adjvex = i;
            q->wight = w;
            q->nextarc = g.vertices[j].firstarc;
            g.vertices[j].firstarc = q;
        }
    }
}


//**********************************************创建邻接表图*****************************************************
void createGraph(ALGraph &g) {
    int selectGraph;
    cout << "输入图类型选择：有向图（0）、有向网（1）、无向图（2）、无向网（3）：";
    cin >> selectGraph;
    switch (selectGraph) {
        case 0:
            g.kind = DG;
            createDG(g);
            break;
        case 1:
            g.kind = DN;
            createDN(g);
            break;
        case 2:
            g.kind = UDG;
            createUDG(g);
            break;
        case 3:
            g.kind = UDN;
            createUDN(g);
            break;
        default:
            return;
    }
}

//输出邻接表
void printALGraph(ALGraph g) {
    for (int i = 0; i < g.vexnum; ++i) {
        cout << "顶点位置" << i << ":" << g.vertices[i].data << (g.vertices[i].firstarc != NULL ? " --> " : " ^ ");
        ArcNode *p = g.vertices[i].firstarc;
        while (p != NULL) {
            cout << p->adjvex << (p->nextarc != NULL ? " --> " : " ^ ");
            p = p->nextarc;
        }
        cout << endl;
    }
}

//********************************************邻接矩阵 DFS & BFS ******************************************************
//访问标志数组
bool visited[MAX_VERTEX_NUM];

int firstAdjVex(MGraph g, int v) {
    for (int i = 0; i < g.vexnum; ++i) {
        if (g.arcs[v][i].adj != 0 && g.arcs[v][i].adj != INFINITY) {
            return i;
        }
    }
    return -1;
}

int nextAdjVex(MGraph g, int v, int w) {
    for (int i = w + 1; i < g.vexnum; ++i) {
        if (g.arcs[v][i].adj != 0 && g.arcs[v][i].adj != INFINITY) {
            return i;
        }
    }
    return -1;
}

void DFS(MGraph g, int v) {

    visited[v] = true;
    cout << g.vers[v] << " ";
    for (int i = firstAdjVex(g, v); i >= 0; i = nextAdjVex(g, v, i)) {
        if (!visited[i]) {
            DFS(g, i);
        }
    }
}

void DFSTraverse(MGraph g) {

    for (int i = 0; i < g.vexnum; ++i) {        //初始化访问标志数组
        visited[i] = false;
    }

    for (int j = 0; j < g.vexnum; ++j) {        //深度递归遍历所有未访问顶点
        if (!visited[j]) {
            DFS(g, j);
        }
    }
}

void BFS(MGraph g) {
    queue<int> q;

    for (int i = 0; i < g.vexnum; ++i) {        //初始化访问标志数组
        visited[i] = false;
    }

    for (int j = 0; j < g.vexnum; ++j) {
        if (!visited[j]) {
            visited[j] = true;
            cout << g.vers[j] << " ";
            q.push(j);

            while (!q.empty()) {
                int t = q.front();
                q.pop();

                for (int i = firstAdjVex(g, t); i >= 0; i = nextAdjVex(g, t, i)) {
                    if (!visited[i]) {
                        visited[i] = true;
                        cout << g.vers[i] << " ";
                        q.push(i);
                    }
                }
            }
        }
    }
}

//********************************************邻接表 DFS & BFS ******************************************************
int firstAdjVex(ALGraph g, int v) {
    if (g.vertices[v].firstarc != NULL) {
        return g.vertices[v].firstarc->adjvex;
    }
    return -1;
}

int nextAdjVex(ALGraph g, int v, int w) {
    ArcNode *p = g.vertices[v].firstarc;
    while (p != NULL && p->adjvex != w) {
        p = p->nextarc;
    }
    if (p != NULL && p->nextarc != NULL) {
        return p->nextarc->adjvex;
    }
    return -1;
}

void DFS(ALGraph g, int v) {

    visited[v] = true;
    cout << g.vertices[v].data << " ";
    for (int w = firstAdjVex(g, v); w >= 0; w = nextAdjVex(g, v, w)) {
        if (!visited[w]) {
            DFS(g, w);
        }
    }
}

void DFSTraverse(ALGraph g) {
    for (int i = 0; i < g.vexnum; ++i) {
        visited[i] = false;
    }
    for (int i = 0; i < g.vexnum; ++i) {
        if (!visited[i]) {
            DFS(g, i);
        }
    }
}

void BFS(ALGraph g) {
    queue<int> q;

    for (int i = 0; i < g.vexnum; ++i) {        //初始化访问标志数组
        visited[i] = false;
    }

    for (int i = 0; i < g.vexnum; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);
            cout << g.vertices[i].data << " ";
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int w = firstAdjVex(g, v); w >= 0; w = nextAdjVex(g, v, w)) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.push(w);
                    cout << g.vertices[w].data << " ";
                }
            }

        }
    }
}

//********************************************基于邻接表的算法******************************************************
//无向图任意给定两点间是否存在长度为k的路径
int kPath(ALGraph g, int a, int b, int k) {
    if (a == b && k == 0) {
        return 1;
    } else if (k > 0) {
        visited[a]= true;
        for (ArcNode *i = g.vertices[a].firstarc; i != NULL; i = i->nextarc) {
            int temp = i->adjvex;
            if (!visited[temp] && kPath(g, temp, b, k - 1)) {
                return 1;
            }
        }
        visited[a]=false;
    }
    return 0;
}


//求所有顶点入度
void inDegreeCalc(ALGraph g,int indegree[]){
    for (int i = 0; i < g.vexnum; ++i) {
        indegree[i]=0;
    }
    for (int i = 0; i < g.vexnum; ++i) {
        for (ArcNode *p =g.vertices[i].firstarc ; p ; p=p->nextarc) {
            indegree[p->adjvex]++;
        }
    }
}

//拓扑排序
int TopologicalSort(ALGraph g){

    int indegree[g.vexnum];
    inDegreeCalc(g,indegree);

    stack<int> s;   //存放零入度节点的栈

    for (int i = 0; i < g.vexnum; ++i) {    //入度为零顶点入栈
        if (!indegree[i]){
            s.push(i);
        }
    }

    int count=0;    //计数输出的节点

    while (!s.empty()){
        //输出一个零入度节点
        int temp = s.top();
        s.pop();
        cout<<temp<<":"<<g.vertices[temp].data<<" ";
        count++;

        //该节点删除导致其指向的节点的入度减一
        for (ArcNode *p=g.vertices[temp].firstarc;p;p=p->nextarc) {
            if (!(--indegree[p->adjvex])){    //如果某节点入度减一后为零，则添加到栈中
                s.push(p->adjvex);
            }
        }
    }

    if (count<g.vexnum){    //有回路无法拓扑排序
        return 0;
    } else{                 //拓扑排序成功
        return 1;
    }
}



int main() {

//    MGraph mGraph;
//    createGraph(mGraph);
//    cout << endl << "邻接矩阵:";
//    printMGraph(mGraph);
//    cout << endl << "DFS:";
//    DFSTraverse(mGraph);
//    cout << endl << "BFS:";
//    BFS(mGraph);

    ALGraph alGraph;
    createGraph(alGraph);
    cout << endl << "邻接表: ";
    printALGraph(alGraph);
    cout << endl << "DFS: ";
    DFSTraverse(alGraph);
    cout << endl << "BFS: ";
    BFS(alGraph);
    cout << endl << "TopologicalSort: ";
    TopologicalSort(alGraph);


    return 0;
}
