//写法1 邻接表
struct Node
{
	int head, color;
	int dfn, low;
	bool in_stack;
} node[MAXN];

struct Edge
{
	int to, next;
} edge[MAXM];

int n, m, tmp;
//分别记录边数，连通块数，深度
int cnt, sum, deep;
//模拟栈
int top, stack[MAXN << 1];

void addEdge(int u, int v)
{
	edge[++ cnt].to = v;
	edge[cnt].next = node[u].head;
	node[u].head = cnt; 
}

void Tarjan(int u)
{
	node[u].dfn = node[u].low = ++ deep;
	node[u].in_stack = true, stack[++ top] = u;

	for(int e = node[u].head, v; e; e = edge[e].next)
	{
		if(!node[v = edge[e].to].dfn)
		{
			Tarjan(v);
			node[u].low = min(node[u].low, node[v].low);
		}
		else
		{
			if(node[v].in_stack)
				node[u].low = min(node[u].low, node[v].dfn);
		}
	}

	if(node[u].dfn == node[u].low)
	{
		++ sum;
		do
		{
			node[tmp = stack[top --]].in_stack = false;
			node[tmp].color = sum;		
		} while(tmp != u);
	}
}

//写法2 
int n, m, ans;
int deep, top, sum;
int color[MAXN], in_stack[MAXN], cnt[MAXN];
int dfn[MAXN << 1], low[MAXN << 1], stack[MAXN << 1]; 

vector<int> g[MAXN];


void Tarjan(int u)
{
	dfn[u] = low[u] = ++ deep;
	in_stack[u] = 1, stack[++ top] = u;
	int size = g[u].size();

	for(int i = 0, v; i < size; ++ i)
	{
		if(! dfn[v = g[u][i]])
		{
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else
		{
			if(in_stack[v])
				low[u] = min(low[u], dfn[v]);
		}
	}

	if(dfn[u] == low[u])
	{
		color[u] = ++ sum, in_stack[u] = 0;
		while(stack[top] != u)
		{
			color[stack[top]] = sum;
			in_stack[stack[top --]] = 0;
		}

		-- top;
	}
}

for(int i = 1; i <= m; ++ i)
{
	int x, y;
	cin >> x >> y;
	g[x].push_back(y);
}
for(int i = 1; i <= n; ++ i)
{
	if(! dfn[i]) Tarjan(i);
}