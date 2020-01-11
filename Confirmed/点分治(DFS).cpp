int n, m, k, ans, root, maxn, cnt, num;
int dis[MAXN];

struct Node {
	int head, size, maxv;
	bool vis;
} node[MAXN];

struct Edge {
	int to, next, length;
} edge[MAXN << 1];

inline int read() {
	char ch = getchar(); int res = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch <= '9' && ch >= '0') {
		res = res * 10 + ch - '0'; ch = getchar();
	}
	return res;
}

inline int max(int x, int y) {
	return (x > y ? x : y);
}

inline void addEdge(int from, int to, int length) {
	edge[++ cnt].to = to, edge[cnt].length = length;
	edge[cnt].next = node[from].head, node[from].head = cnt;
}

inline void getRoot(int r, int u, int pre) {
	node[u].maxv = max(node[r].size - node[u].size, node[u].maxv);
	node[u].maxv < maxn ? maxn = node[u].maxv, root = u : 0;

	for(int e = node[u].head, v; e != -1; e = edge[e].next) {
		if((v = edge[e].to) == pre || node[v].vis) continue;
		getRoot(r, v, u);
	}
}

inline void getSize(int u, int pre) {
	node[u].size = 1, node[u].maxv = 0;
	for(int e = node[u].head, v; e != -1; e = edge[e].next) {
		if((v = edge[e].to) == pre || node[v].vis) continue;

		getSize(v, u);
		node[u].size += node[v].size;
		node[u].maxv = max(node[v].size, node[u].maxv);
	}
}

inline void getDis(int u, int pre, int d) {
	dis[num ++] = d;
	for(int e = node[u].head, v; e != -1; e = edge[e].next) {
		if((v = edge[e].to) == pre || node[v].vis) continue;
		getDis(v, u, d + edge[e].length);
	} 
}

inline void init() {
	cnt = -1, ans = 0;
	for(int i = 0; i <= n; ++ i) 
		node[i].head = -1, node[i].vis = false;
}