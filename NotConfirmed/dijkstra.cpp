//dijkstra****************************************************************************************************************************************
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>

#define MAXN 2501
#define MAXEDGE 12402
#define INF 0x3f3f3f3

using namespace std;

struct Edge {
	int to, weight, next;
};

struct Dist {
	int dist, x;
	Dist(int x = 0, int dist = INF) : dist(dist), x(x) {}
	bool operator () (Dist l, Dist r) {
		return l.dist > r.dist;
	}
};

int pre[MAXN], dist[MAXN], n, m, start, end;
Edge edge[2 * MAXEDGE];

priority_queue <Dist, vector<Dist>, Dist> que;              //使用优先队列来模拟堆

void add_edge(int &num, int from, int weight, int to) {
	num++;
	edge[num].to = to;
	edge[num].weight = weight;
	edge[num].next = pre[from];
	pre[from] = num;
}

int dijistra() {
	for (int j = 1; j <= n; j++) dist[j] = INF;
	dist[start] = 0;
	que.push(Dist(start, 0));
	while (!que.empty()) {
		Dist tmp = que.
		q.top();
		que.pop();
		int x = tmp.x;
		if (tmp.dist != dist[tmp.x]) continue;
		for (int j = pre[x]; j != -1; j = edge[j].next) {
			int t = edge[j].to;
			if (dist[t] > dist[x] + edge[j].weight) {
				dist[t] = dist[x] + edge[j].weight;
				que.push(Dist(t, dist[t]));
			}
		}
	}
	return dist[end];
}


int main() {
	int i, t, f, w, num = 0;
	scanf("%d %d %d %d", &n, &m, &start, &end);
	memset(pre, -1, sizeof(pre));
	for (i = 1; i <= m; i++) {
		scanf("%d %d %d", &f, &t, &w);
		add_edge(num, f, w, t);
		add_edge(num, t, w, f);
	}
	printf("%d", dijistra());
	return 0;
}
