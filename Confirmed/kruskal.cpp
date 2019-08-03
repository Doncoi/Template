#include <iostream>  
#include <algorithm>  
using namespace std;  
  
#define  MAX_N 110   
#define  MAX_E  11000  
  
static int N;  
static struct Edge  
{  
    int from;  
    int to;  
    int cost;  
}edge[MAX_E];  
static int E;  
  
static int cmp(Edge&ls,Edge&rs)  
{  
    return ls.cost<rs.cost;  
}  
  
static int par[MAX_N];  
static void init()  
{  
    for (int i=0;i<MAX_N;++i)  
     par[i] = i;  
}  
  
static int getParent(int u)  
{  
    if (par[u]!=u)  
      par[u] = getParent(par[u]);  
    return par[u];  
}  
  
static void merge(int u,int v)  
{  
    int p1 = getParent(u);  
    int p2 = getParent(v);  
    if (p1==p2)  
     return;  
    par[p1] = p2;  
}  
  
static bool same(int u,int v)  
{  
    int p1 = getParent(u);  
    int p2 = getParent(v);  
    if (p1==p2)  
     return true;  
    return false;  
}  
  
static int kruskal()  
{  
    int res = 0;  
    sort(edge,edge+E,cmp);  
    for (int i=0;i<E;++i)  
    {  
        int u = edge[i].from;  
        int v = edge[i].to;  
        if (!same(u,v))  
        {  
            merge(u,v);  
            res+=edge[i].cost;  
        }  
    }  
    return res;  
}  
  
int main()  
{  
    scanf("%d",&N);  
    int cnt = 0;  
    int u,v;  
    for(int i=1;i<=N;++i)  
        for (int j=1;j<=N;++j)  
        {  
            scanf("%d",&u);  
            if (u!=0){  
             edge[cnt].from = i;  
             edge[cnt].to = j;  
             edge[cnt].cost = u;  
             cnt++;  
            }  
        }  
    init();  
    E = cnt;  
    int Q;  
    scanf("%d",&Q);  
    for (int i=0;i<Q;++i)  
    {  
        scanf("%d %d",&u,&v);  
        merge(u,v);  
    }  
    printf("%d\n",kruskal());  
    return 0;  
}  