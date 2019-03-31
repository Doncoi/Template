//通过染色的方法进行判断，对于一个已染色点的邻接点，如果该点未染色，则将其染上与当前点相反的颜色；
//若该点已经被染上了与当前点相同的颜色，则可知该图不是二分图

// Node *v = egde[i]->to;
// if(v->color == -1) {
// 	v->color = !tmp->color ;
// } else if(v->color == tmp->color) {
// 	return false;
// }

int head[MAXN], link[MAXN];
bool visited[MAXN], color[MAXN];
int cnt, n, m;

struct Edge {
	int to;
	int next;
};

Edge edge;
void init() {
	cnt = 0;
	memset(head, -1, 0, sizeof(head));
	memset(color, 0, sizeof(0));
}

void addEdge(int u, int v) {
	cnt ++;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

bool setColor(int u) {
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		if(!color[v]) {
			color[v] = !color[u];
			if(!setColor(v)) {
				return false;
			} 
		} else if(color[v] == color[u]){
			return false;
		}
	}

	return true;
}

bool DFS(int u) {
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = egde[i].to;
		if(!visited[v]) {
			visited[v] = 1;
			if(link[v] == -1 || dfs(link[v])) {          //link数组用于储存点的分组
				link[v] = u;
				return true;
			}
		}
	}
}

int match() {
	int ans = 0;
	memset(link, -1, sizeof(link)) 
	for(int i = 1;i <= n; i ++) {
		memset(visited, 0 ,sizeof(visited))
		if(dfs(i)) {
			ans ++;
		}
	}

	return ans;
}
