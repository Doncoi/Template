//倍增LCA******************************************************************************************************************************************
inline void DFS(int u) {
	for(int e = node[u].head, v; e; e = edge[e].next) {
		if(node[v = edge[e].to].dis) continue;
		node[v].dis = node[u].dis + 1;
		parent[v][0] = u, DFS(v);
	}
}

inline int LCA(int x, int y) {
	int i, j;
	if(node[x].dis < node[y].dis) swap(x, y);
	for(i = 1; (1 << i) <= node[x].dis; ++ i); -- i;
	for(j = i; j >= 0; -- j) 
		if(node[x].dis - (1 << j) >= node[y].dis)
			x = parent[x][j];
	if(x == y) return x;

	for(j = i; j >= 0; -- j) 
		if(parent[x][j] != -1 && parent[x][j] != parent[y][j]) 
			x = parent[x][j], y = parent[y][j];
	//printf("All Right\n");
	return parent[x][0];
}

inline void init() {
	memset(parent, -1, sizeof(parent)); DFS(s);
	for(int j = 1; (1 << j) <= n; j ++) 
		for(int i = 1; i <= n;i ++) 
			if(parent[i][j - 1] != -1)
				parent[i][j] = parent[parent[i][j - 1]][j - 1];
}