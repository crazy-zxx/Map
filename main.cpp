#include <iostream>

using namespace std;

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20

typedef enum {
    DG, DN, UDG, UDN
} GraphKind;//有向、无向，图、网

//邻接矩阵
typedef char VertexType ;
typedef struct arcCell {        //边 或 弧
    int adj;        //0，1 或 权值
    char *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct mGraph {
    VertexType vers[MAX_VERTEX_NUM];   //顶点
    AdjMatrix arcs;             //邻接矩阵
    int vexnum, arcnum;
    GraphKind kind;
} MGraph;

int locateVex(MGraph g,VertexType v){
    for (int i = 0; i <g.vexnum ; ++i) {
        if (v==g.vers[i]){
            return i;
        }
    }
}

void createDG(MGraph &g){

    cout<<"输入顶点数、弧数：";
    cin>>g.vexnum>>g.arcnum;      //此处暂不考虑info

    for (int i = 0; i <g.vexnum ; ++i) {
        for (int j = 0; j <g.vexnum ; ++j) {
            g.arcs[i][j].adj=0;
            g.arcs[i][j].info=NULL;
        }
    }

    cout<<"输入"<<g.vexnum<<"个顶点：";
    for (int i = 0; i <g.vexnum ; ++i) {
        cin>>g.vers[i];
    }

    cout<<"输入"<<g.arcnum<<"个由弧附着的顶点形成的弧（如：a b）："<<endl;
    for (int k = 0; k <g.arcnum ; ++k) {
        VertexType v1,v2;
        cin>>v1>>v2;
        int i=locateVex(g,v1),j=locateVex(g,v2);
        g.arcs[i][j].adj=1;

    }

}
void createDN(MGraph &g){

    cout<<"输入顶点数、弧数：";
    cin>>g.vexnum>>g.arcnum;      //此处暂不考虑info

    for (int i = 0; i <g.vexnum ; ++i) {
        for (int j = 0; j <g.vexnum ; ++j) {
            g.arcs[i][j].adj=INFINITY;
            g.arcs[i][j].info=NULL;
        }
    }

    cout<<"输入"<<g.vexnum<<"个顶点：";
    for (int i = 0; i <g.vexnum ; ++i) {
        cin>>g.vers[i];
    }

    cout<<"输入"<<g.arcnum<<"个由弧附着的顶点形成的弧（如：a b）："<<endl;
    for (int k = 0; k <g.arcnum ; ++k) {
        VertexType v1,v2;
        int w;
        cin>>v1>>v2>>w;
        int i=locateVex(g,v1),j=locateVex(g,v2);
        g.arcs[i][j].adj=w;

    }
}
void createUDG(MGraph &g){

    cout<<"输入顶点数、边数：";
    cin>>g.vexnum>>g.arcnum;      //此处暂不考虑info

    for (int i = 0; i <g.vexnum ; ++i) {
        for (int j = 0; j <g.vexnum ; ++j) {
            g.arcs[i][j].adj=0;
            g.arcs[i][j].info=NULL;
        }
    }

    cout<<"输入"<<g.vexnum<<"个顶点：";
    for (int i = 0; i <g.vexnum ; ++i) {
        cin>>g.vers[i];
    }

    cout<<"输入"<<g.arcnum<<"个由边附着的顶点形成的边（如：a b）："<<endl;
    for (int k = 0; k <g.arcnum ; ++k) {
        VertexType v1,v2;
        cin>>v1>>v2;
        int i=locateVex(g,v1),j=locateVex(g,v2);
        g.arcs[i][j].adj=1;
        g.arcs[j][i].adj=1;

    }
}
void createUDN(MGraph &g){

    cout<<"输入顶点数、边数：";
    cin>>g.vexnum>>g.arcnum;      //此处暂不考虑info

    for (int i = 0; i <g.vexnum ; ++i) {
        for (int j = 0; j <g.vexnum ; ++j) {
            g.arcs[i][j].adj=INFINITY;
            g.arcs[i][j].info=NULL;
        }
    }

    cout<<"输入"<<g.vexnum<<"个顶点：";
    for (int i = 0; i <g.vexnum ; ++i) {
        cin>>g.vers[i];
    }

    cout<<"输入"<<g.arcnum<<"个由边附着的顶点形成的边（如：a b）："<<endl;
    for (int k = 0; k <g.arcnum ; ++k) {
        VertexType v1,v2;
        int w;
        cin>>v1>>v2>>w;
        int i=locateVex(g,v1),j=locateVex(g,v2);
        g.arcs[i][j].adj=w;
        g.arcs[j][i].adj=w;

    }
}

void createGraph(MGraph &g) {
    int select;
    cout<<"输入类型选择：有向图（0）、有向网（1）、无向图（2）、无向网（3）：";
    cin>>select;
    switch (select) {
        case 0:g.kind=DG;createDG(g);
            break;
        case 1:g.kind=DN;createDN(g);
            break;
        case 2:g.kind=UDG;createUDG(g);
            break;
        case 3:g.kind=UDN;createUDN(g);
            break;
        default:
            return;
    }
}

void printMgraph(MGraph g){
    for (int i = 0; i <g.vexnum ; ++i) {
        for (int j = 0; j <g.vexnum ; ++j) {
            cout<<g.arcs[i][j].adj<<" ";
        }
        cout<<endl;
    }
}

int main() {

    MGraph g;
    createGraph(g);
    printMgraph(g);

    return 0;
}
