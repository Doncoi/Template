inline int find(int x) {
	return (node[x].father == x ? x : node[x].father = find(node[x].father));
}

inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	else node[x].father = y;
}

inline bool judge(int x, int y) {
	return(find(x) == find(y));
}