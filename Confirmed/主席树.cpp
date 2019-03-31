#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAXN 100005
#define MAXM MAXN * 20

int n, m, Q, a[MAXN], b[MAXN], rt[MAXN];

inline int read() {
	static char ch;bool flag = false;while(ch = getchar(), ch < '0' || ch > '9') {if(ch == '-') flag = true;}int res = ch - '0';while(ch = getchar(), ch >= '0' && ch <= '9') {res = res * 10 + ch - '0';}return flag ? -res : res;
}

struct Node {
	int lchild, rchild, value;
} node[MAXM];

int pool = 0;

inline void nodeInit() {
	std :: sort(b + 1, b + n + 1);
	m = std :: unique(b + 1, b + m + 1) - b - 1;

	for(int i = 1; i <= n; ++ i) {
		a[i] = std :: lower_bound(b + 1, b + m + 1, a[i]) - b;
	}
}

inline void insert(const int &y, int &x, const int &l, const int &r, const int &p) {
	node[x = ++ pool] = node[y];
	++ node[x].value;

	if(l == r) return;
	int mid = (l + r) >> 1;

	if(p <= mid) insert(node[y].lchild, node[x].lchild, l ,mid, p);
	else insert(node[y].rchild, node[x].rchild, mid + 1, r, p);
}

inline int query(const int &nl, const int &nr, const int &l, const int &r, const int &k) {
	if(l == r) return l;
	int delta = node[node[nr].lchild].value - node[node[nl].lchild].value;
	int mid = (l + r) >> 1;

	if(delta >= k) return query(node[nl].lchild, node[nr].lchild, l, mid, k);
	else return query(node[nl].rchild, node[nr].rchild, mid + 1, r, k - delta);
}

inline void treeInit() {
	for(int i = 1; i <= n; ++ i) {
		insert(rt[i - 1], rt[i], 1, m, a[i]);
	}
}

int main() {
	n = read(), Q = read();
	for(int i = 1; i <= n; ++ i) {
		a[i] = b[++ m] = read();
	}

	nodeInit();
	treeInit();

	for(int i = 1; i <= Q; ++ i) {
		int l = read(), r = read(), k = read();
		printf("%d\n", b[query(rt[l - 1], rt[r], 1, m, k)]);
	}
}