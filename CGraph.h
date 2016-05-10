#include<list>
#include<iostream>
#include<vector>
#include<map>
#include"limits.h"
using namespace std;
#include"CEdge.h"
class CGraph
{
private:
    int numVertex;
    int numEdge;
    list<CEdge*> IncidentList;
    vector<vector<int> > adj;
    map<int, list<int> > nearvertexlist;
    map<int, CVertex*> mapVID_listEdge;  // 所有的顶点
    list<CVertex*> listTempMark;    //暂时标记的定点的集合
    map<int, list<CEdge*> >mapVID_listEdge;    //与定点相关联的出渡边；
    Update(int VID);
public:
    CGraph(char* inputFile);
    CGraph(list<CEdge*> listEdge);
    CGraph(CGraph &graph);
    ~CGraph();
    int getNumVertex();
    int getNumEdge();
    list<CEdge*> getEdge();
    vector<vector<int> > getAdj();
    map<int, list<int> > getnearvertexlist();
    DijkstraAlg(int VID);

};

CGraph::CGraph(list<CEdge*> listEdge)
{
  IncidentList=listEdge;

   int n=0;
   list<CEdge*>::iterator i2,i2end;
   i2end=listEdge.end();
   for(i2=listEdge.begin();i2!=i2end;i2++) n++;
   numEdge=n;
  // cout<<"num of Edge:";

   int m=0;
   int num=0;
   int t=0;
   int j=0;
   int a[1000]={0};
   list<CEdge*>::iterator i, iend;
   iend=listEdge.end();
   for(i=listEdge.begin(); i!=iend; i++)
   {
       m=(*i)->gethead();
       j=(*i)->gettail();
       a[m]++, a[j]++;
   }
   for(; t<1000; t++)
   {
       if(a[t]!=0) num++;
   }

   numVertex=num;

 //  cout<<" " << (*i);
}

CGraph::CGraph(CGraph &graph){
    numVertex = graph.getNumVertex();
    numEdge = graph.getNumEdge();
    IncidentList = graph.getEdge();

    adj=graph.getAdj();
    nearvertexlist=graph.getnearvertexlist();
}


int CGraph::getNumVertex()
{
    return numVertex;
}
int CGraph::getNumEdge()
{
    return numEdge;
}

list<CEdge*> CGraph::getEdge()
{
    return IncidentList;
}

vector<vector<int> > CGraph::getAdj()
{
    int n=numVertex;
    int a=0;
    int b=0;
    vector<vector<int> > adj1;                        //adj[][]邻接矩阵
    adj1.resize(n, vector<int>(n));
    list<CEdge*>::iterator i1, i1end;
    i1=IncidentList.begin();
    i1end=IncidentList.end();
    for(; i1!=i1end; i1++)
    {
        b=(*i1)->gethead();
        a=(*i1)->gettail();
        adj1[a][b]=(*i1)->getweight();

    }

    for(a=0;a<=n-1;a++)
    {
        for(b=0;b<=n-1;b++)
            if(adj1[a][b]==0&&a!=b) adj1[a][b]=INT_MAX;
    }
    adj=adj1;
    return adj;
}

map<int, list<int> > CGraph::getnearvertexlist()
{
    int n=numVertex;
    vector<list<int> > v;
    v.resize(n);
    int t;
    list<CEdge*>::iterator i3, i3end;
    i3end=IncidentList.end();
    for(i3=IncidentList.begin();i3!=i3end;i3++)  //遍历所有的边
        {
            if((*i3)!=NULL)
            {
                t=(*i3)->gettail();    //如果边的尾是顶点i，那么这条边的头就与顶点i邻
                v[t].push_back((*i3)->gethead());   //将这条边的头放进对应list中

            }
        }


    map<int, list<int> > m1;
    for(t=0;t<=n-1;t++)
    {
        m1.insert(make_pair(t, v[t]));
    }
    nearvertexlist=m1;
    return nearvertexlist;

}


CGraph::~CGraph()
{

}

