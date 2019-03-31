/倍增LCA******************************************************************************************************************************************
inline void dfs(int x) {
	for(int i = head[x]; i != -1; i = next[i]) {
		if(!deep][to[i]]) {
			deep[to][i] = deep[x] + 1;
			p[to[i]][o] = u;
			dfs(to[i]);
		}
	}
}

void init() {
	for(int j = 1; (1 << j) <= n; j ++) 
		for(int i = 1;i <= n;i ++) 
			if(p[i][j - 1] != -1)
				p[i][j] = p[p[i][j - 1]][j - 1];
}

int lca(int a, b) {
	int i, j;
	if(deep[a] < deep[b]) swap(a, b);
	for(i = 1;(1 << i) <= deep[a]; i++);
	i --;
	for(j = i;j >= 0;j --) 
		if(deep[a] - (1 << j) >= deep[b]) 
			a = p[a][j];
	if(a == b) return;

	for(j = i;j >= 0;j --) 
		if(p[a][j] != -1 && p[a][j] != p[b][j]) {
			a = p[a][j];
			b = p[b][j];
		}
	return p[a][0];
}