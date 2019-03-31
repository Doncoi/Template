int color[MAXN], head[MAXN];

struct Edge {
	int to, next;
} edge[MAXN * MAXN];

bool BFS(int start) {
	std :: queue<int> q;
	q.push(start);
	color[start] = 1;

	while(!q,empty()) {
		int tmp = q.front();
		q.pop();

		for(int i = head[start]; ; i = edge[i].next) {
			if(color[i] == -1) {
				q.push(i);
				color[i] = !color[tmp];
			} else if(color[tmp] == color[i]) {
				return false;
			}
		}
	}

	return true;
}