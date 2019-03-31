#include <cstdio>
#include <cstring>
#define MAXN 1000000 + 5

struct Edge
{
	int to, next, len;
} edge[MAXN];

struct Node
{
	int dis, head;
	bool vis;
} node[MAXN];

int n, m, s, t;
int cnt, minn, k;
int x, y, z; 

inline void addEdge(int u, int v, int w)
{
	edge[++ cnt].to = v, edge[cnt].len = w;
	edge[cnt].next = node[u].head, node[u].head = cnt;
}

inline int read()
{
	char ch = getchar(); int res = 0, flag = 1;
	while(ch < '0' || ch > '9') {if(ch == '-') flag = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0') {res = res * 10 + ch - '0'; ch = getchar();}
	return (res * flag);
}

void init()
{
	n = read(), m = read(), s = read(), t = read();
	for(int i = 1; i <= m; ++ i)
	{
		x = read(), y = read(), z = read();
		addEdge(x, y, z), addEdge(y, x, z);
	}

	for(int i = 1; i <= n; ++ i)
	{
		node[i].dis = MAXN;
	}
}

void solve()
{
	node[s].dis = 0;
	for(int i = 1; i <= n; ++ i)
	{
		minn = MAXN, k = 0;
		for(int j = 1; j <= n; ++ j)
		{
			if(!node[j].vis && minn > node[j].dis)
			{
				minn = node[j].dis;
				k = j;
			}
		}

		node[k].vis = true;
		for(int e = node[k].head, v; e; e = edge[e].next)
		{
			if(!node[v = edge[e].to].vis && node[v].dis > node[k].dis + edge[e].len)
			{
				node[v].dis = node[k].dis + edge[e].len;
			}
		}
	}

	printf("%d\n", node[t].dis);
}

int main()
{	
	init();
	solve();
}