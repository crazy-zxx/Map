#include <iostream>

using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20

//图类型
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;//有向、无向，图、网

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
        g.arcs[i][j].adj = 1;

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
        g.arcs[i][j].adj = w;

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
        g.arcs[i][j].adj = 1;
        g.arcs[j][i].adj = 1;

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
        g.arcs[i][j].adj = w;
        g.arcs[j][i].adj = w;

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
        ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->wight = 1;
        p->nextarc = g.vertices[i].firstarc;      //此处链表使用了头插法，操作比较方便
        g.vertices[i].firstarc = p;
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
        ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->wight = w;
        p->nextarc = g.vertices[i].firstarc;      //此处链表使用了头插法，操作比较方便
        g.vertices[i].firstarc = p;
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
        ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->wight = 1;
        p->nextarc = g.vertices[i].firstarc;
        g.vertices[i].firstarc = p;
        ArcNode *q = (ArcNode *) malloc(sizeof(ArcNode));   //对称操作
        q->adjvex = i;
        q->wight = 1;
        q->nextarc = g.vertices[j].firstarc;
        g.vertices[j].firstarc = q;
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



int main() {

    MGraph mGraph;
    createGraph(mGraph);
    printMGraph(mGraph);

    ALGraph alGraph;
    createGraph(alGraph);
    printALGraph(alGraph);

    return 0;
}
