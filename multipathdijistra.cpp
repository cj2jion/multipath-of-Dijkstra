#include <cstdio>
#include<vector>
#include<iostream>
#include<list>
#include <cstdlib>
#include"CGraph.h"
#include"limits.h"
#include<map>
#include <cstring>

using namespace std;


string itoa(int num) {
    char str[20];
    sprintf(str, "%d", num);
    return string(str);
}

int main()
{
    CEdge* e1=new CEdge(1,0,2,1);
    CEdge* e2=new CEdge(2,1,1,1);
    CEdge* e3=new CEdge(3,0,1,1);
    CEdge* e4=new CEdge(1,3,1,1);
    CEdge* e5=new CEdge(2,3,1,1);
    list<CEdge*> listedge;
    listedge.push_back(e1);
    listedge.push_back(e2);
    listedge.push_back(e3);
    listedge.push_back(e4);
    listedge.push_back(e5);
    CGraph g(listedge);
    cout<<"num of vertex:"<<g.getNumVertex()<<endl;   //输出顶点数
    cout<<"num of edge:"<<g.getNumEdge()<<endl;       //输出边数
    int n=g.getNumVertex();
    int m=g.getNumEdge();

    /*   求adj    */
    vector<vector<int> > adj;                        //adj[][]邻接矩阵
    adj.resize(n, vector<int>(n));
    adj=g.getAdj();

    map<int, list<int> > m1;                        //邻接链表
    m1=g.getnearvertexlist();


    vector<int> iminpathnum;                         //iminpathnum[]最小路径数目
    iminpathnum.resize(n);

    vector<vector<vector<int> > > sminpath;               //sminpath[][]最小路径
    sminpath.resize(n);

    vector<int> iprevertexnum;                      //iprevertexnum[]前置邻接点数目
    iprevertexnum.resize(n);

    vector<vector<int> > iprevertexid;               //iprevertexid[n][n]前置邻接点
    iprevertexid.resize(n,vector<int>(n));

    vector<int> dist;                                //dist[]距离标记
    dist.resize(n);

    vector<bool> final;
    final.resize(n);

    int a[n];
    memset(a, 0, sizeof(a));
    int i;
    int j;
    for(i=0;i<=n-1;i++) {
        iminpathnum[i] = 0;
        iprevertexnum[i] = 0;
        dist[i] = adj[0][i];
        final[i] = false;
        if (i != 0 && dist[i] != INT_MAX) {
            iminpathnum[i] = 1;
            vector<int> v1;
            v1.push_back(0);
            v1.push_back(i);
            sminpath[i].push_back(v1);
            iprevertexnum[i] = 1;
            iprevertexid[i][0] = 0;
            a[i]++;
        }
    }
        final[0]=true;
        iminpathnum[0]=1;
        vector<int> v2;
        v2.push_back(0);
        sminpath[0].push_back(v2);
        iprevertexnum[0]=0;


    for(i=1;i<=n-1;i++) {
        /* find(min(dist[v]))&&!final[v];*/
        int c, v;
        multimap<int, int> m2;
        for (c = 1; c < n; c++) {
            if (!final[c]) {
                m2.insert(make_pair(dist[c], c));
            }
        }
        /*找到m2中dist最小的*/
        v = (*(m2.begin())).second;
        //cout << "min_v:" << v <<" ";
        //cout << "dist[v]:" << dist[v] << endl;

        if (dist[v] == INT_MAX) break;
        final[v] = true;
        map<int, list<int> >::iterator f;
        f = m1.find(v);
        list<int>::iterator i12, i12end;
        i12 = (*f).second.begin();
        i12end = (*f).second.end();
        for(; i12!=i12end;i12++)
             {
                 j=(*i12);
                 if (!final[j] && dist[v] + adj[v][j] < dist[j])
                     {
                         dist[j] = dist[v] + adj[v][j];
                         iminpathnum[j] = iminpathnum[v];
                         sminpath[j] = sminpath[v];    //？？？应该是在v的所有最短路径后面添上j
                         for (int k = 0; k < sminpath[j].size(); k++) {
                             sminpath[j][k].push_back(j);
                         }
                         iprevertexnum[j] = 1;
                         iprevertexid[j][0] = v;           //前邻接节点为v，且要把其他的清除
                         a[j]=1;
                         int t;
                         for(t=1;t<n;t++)
                         {
                             iprevertexid[j][t]=0;
                         }


                     }
                 else if (!final[j] && dist[v] + adj[v][j] == dist[j])
                     {
                         iminpathnum[j] = iminpathnum[j] + iminpathnum[v];
                         //sminpath[j]=sminpath[j]+(sminpath[v]+j);//???应该实现的是将顶点v的每条路径连接顶点j所构成的字符串作为一条新的最短路径加入到j的最短路径集中
                         for (int k = 0; k < sminpath[v].size(); k++) {
                             sminpath[v][k].push_back(j);
                             sminpath[j].push_back(sminpath[v][k]);
                             sminpath[v][k].erase(sminpath[v][k].end()-1);


                         }
                         iprevertexnum[j]++;
                         iprevertexid[j][a[j]]=v;
                         a[j]++;
                     }
             }
        cout<<endl;

    }




   /* return dist[];*/
    vector<int>::iterator i2, i2end;
    i2=dist.begin();
    i2end=dist.end();
    cout<<"dist[]:";
    for(; i2!=i2end;i2++)
    {

        cout<<(*i2)<<" ";
    }
    cout<<endl;



  vector<int>::iterator i3, i3end;
    i3=iminpathnum.begin();
    i3end=iminpathnum.end();
    cout<<"iminpathnum[]:";
    for(; i3!=i3end;i3++) {

        cout<<(*i3)<<" ";
    }
    cout<<endl;

    /*  return iprevertexnum[];*/

    vector<int>::iterator i6, i6end;
    i6=iprevertexnum.begin();
    i6end=iprevertexnum.end();
    cout<<"iprevertexnum:";
    for(; i6!=i6end;i6++)
    {
        cout<<(*i6)<<" ";
    }
    cout<<endl;

    vector<vector<int> >::iterator i7, i7end;
    i7=iprevertexid.begin();
    i7end=iprevertexid.end();
    cout<<"iprevertexid:"<<endl;
    for(; i7!=i7end;i7++)
    {
        vector<int>::iterator i8, i8end;
        i8=(*i7).begin();
        i8end=(*i7).end();
        for(; i8!=i8end;i8++)
            cout<<(*i8)<<" ";
            cout<<endl;
    }
    cout<<endl;

    vector<vector<vector<int> > >::iterator i4, i4end;
    i4=sminpath.begin();
    i4end=sminpath.end();
    cout<<"sminpath:";
    cout<<endl;
    for(; i4!=i4end;i4++)
    {
        vector<vector<int> >::iterator i5, i5end;
        i5=(*i4).begin();
        i5end=(*i4).end();
        for(; i5!=i5end;i5++)
        {
            vector<int>::iterator i9, i9end;
            i9=(*i5).begin();
            i9end=(*i5).end();
            for(; i9!=i9end; i9++)
            {
                cout<<(*i9)<<" ";

            }

            cout<<";";
        }
        cout<<endl;
    }
    cout<<endl;

    system("pause");

    return 0;
}

