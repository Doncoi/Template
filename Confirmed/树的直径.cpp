int cnt, ans, s, t, tmp;
int q[MAXN], ql, qr;

struct Node {
	int head, dis;
	bool vis;
} node[MAXN]

struct Edge {
	int from, to, next, lenth;
} edge[MAXN << 1];

inline void init() {
	cnt = 0;
	for(int i = 0; i < MAXN; ++ i)
		node[i].head = -1;
}

inline void addEdge(int from ,int to, int length) {
	edge[++ cnt].from = from, edge[cnt].to = to, edge[cnt].length = length;
	edge[cnt].next = node[from].head, node[from].head = cnt;
}

//首先对任意一点搜索一边，再对得到的端点tmp搜索一遍
inline void BFS(int s) {
	ans = 0;
	for(int i = 0; i < MAXN; ++ i) 
		node[i].dis = 0, node[i].vis = false;
	ql = qr = 0, q[++ qr] = s, node[s].vis = true;

	while(ql < qr) {
		int u = q[++ ql];
		for(int e = node[u].head, v; e != -1; e = edge[e].next) {
			if(node[v = edge[e].to].vis || node[v].dis < node[u].dis + edge[e].length) 
				continue;
			node[v].dis = node[u].dis + edge[e].length;
			if(ans < node[v].dis) {ans = node[v].dis; tmp = v;}
			node[v].vis = true, q[++ qr] = v;
		}
	}
}

inline int solve() {
	BFS(1);
	BFS(tmp);
	return ans;
}