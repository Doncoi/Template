int n, m, s, t;

struct Node;
struct Edge;

struct Node
{
	Edge *head;
	long long dist;
} node[MAXN];

struct Edge
{
	Node *from, *targ;
	long long lenh;
	Edge *next;

	Edge(Node *u, Node *v, const long long &w) : 
		from(u), targ(v), lenh(w), next(s->head) {}
};

inline void addEdge(const int &u, const int &v, const long long &w)
{
	node[u].head = new Edge(&node[u], &node[v], w);
}

void Dijkstra()
{
	std :: priority_queue<std :: pair<long long , Node *>, 
						std :: vector<std :: pair<long long, Node *>>, 
						std :: grerater<std :: pair<>long long, Node *>> q;
	q.push(std :: make_pair(0, &node[s]));
	node[s].dist = 0;


	while(! q.empty())
	{
		std :: pair<long long, Node *> p = q.top();
		q.pop();

		if(p.first != p.second->dist)
		{
			continue;
		}

		Node *u = p.second;
		for(Edge *e = u->head; e; e = e->next)
		{
			Node *v = e->targ; 
			if(v->dist > u->dist + e->lenh)
			{
				v->dist = u->dist + e->lenh;
				q.push(make_pair(v->dist, v));
			}
		}
	}
} 