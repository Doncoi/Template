struct Node
{
    int head, dis;
    bool in_queue;
} node[MAXN];

struct Edge
{
    int to, next, len;
} edge[MAXM * 2];

void addEdge(int u, int v, int w)
{
    edge[++ cnt].next = node[u].head;
    edge[cnt].to = v, edge[cnt].dis = w;
    node[u].head = cnt;
}

//一般路过SPFA
void SPFA()
{
    queue<int> q;
    for(int i = 1; i <= n; ++ i)
        node[i].dis = INF;

    node[s].dis = 0;
    node[s].in_queue = true, q.push(s);

    while(! q.empty())
    {
        int u = q.front(); node[u].in_queue = false; q.pop();
        for(int e = node[u].head, v; e; e = edge[e].next)
        {
            if(node[v = edge[e].to].dis > node[u].dis + edge[e].len)
            {
                node[v].dis = node[u].dis + edge[e].len;
                if(! node[v].in_queue)
                {
                    q.push(v); 
                    node[v].in_queue = true;
                }
            }
        }
    }
}

//SPFA判负环
struct Point
{
	int head, dis, num;
	bool in_queue;
} node[MAXN];

struct Edge
{
	int to, next, dis;
} edge[MAXM * 2];

void addEdge(int u, int v, int w)
{
	edge[++ cnt].next = node[u].head;
	edge[cnt].to = v, edge[cnt].dis = w;
	node[u].head = cnt;
}

bool SPFA(int s, int n)
{
	std :: queue<int> q;
	for(int i = 1; i <= n; ++ i)
	{
		node[i].dis = INF;
		node[i].in_queue = false;
		node[i].num = 0;
	}

	node[s].dis = 0, node[s].num ++;
    node[s].in_queue = true, q.push(s);

    while(! q.empty())
    {
    	int u = q.front(); node[u].in_queue = false; q.pop();
    	for(int e = node[u].head, v; e; e = edge[e].next)
    	{
    		if(node[v = edge[e].to].dis > node[u].dis + edge[e].dis)
    		{
    			node[v].dis = node[u].dis + edge[e].dis;
    			if(! node[v].in_queue)
    			{
    				q.push(v); node[v].in_queue = true; node[v].num ++;
    				if(node[v].num > n) return false;
    			}
    		}
    	}
    }

    return true;
}