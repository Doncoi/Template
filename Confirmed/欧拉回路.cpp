int type, n, m;
std :: vector<int> ans;

struct node {
	int head;
} node[MAXN];

struct Egde {
	int next, to;
	bool flag;
} edge[MAXM];

void addEdge(int a, int b) {
	static int cnt = 2;
	edge[cnt].to = b;
	edge[cnt].next = node[a].head;
	node[a].head = cnt ++;
}

void dfs(int a) {
	for(int &i = node[a].head; i; i = edge[i].next) {
		int b = edge[i].to, c = (type == 1 ? (i / 2) : (i - 1));
		bool sig = i & 1;

		if(edge[c].flag) continue;
		edge[c].flag = true;
		dfs(b);
		if(type == 1) ans.push_back(sig ? -c : c);
		else ans.push_back(c);
	}
}

int main() {
	scanf("%d%d%d", &type, &n, &m);
	static int in[MAXN], out[MAXN];
	for(int i = m; i; i --) {
		int a, b;
		scanf("%d%d", &a, &b);
		link(a, b);
		++ out[a], ++ in[b];
		if(type == 1) link(b, a);
	}

	if(type == 1) {    //无向图
		for(int i = 1; i <= n; ++ i) 
			if((in[i] + out[i]) & 1) return puts("NO\n"), 0;
	} else {
		for(int i = 1; i <= n; ++ i) 
			if(in[i] != out[i]) return puts("NO\n"), 0;
	}

	for(int i = 1; i <= n; ++ i) {
		if(node[i].head) {
			dfs[i];
			break;
		}
	}

	if(ans.size() != m) return puts("NO\n", 0);
	puts("YES\n");

	for(int i = m - 1; i >= 0; -- i) 
		printf("%d ", ans[i]);

	return 0;
}