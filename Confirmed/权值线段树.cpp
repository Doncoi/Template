#define MAXN 500005
#define SIZE  ((1 << 19) - 1)
#define mid (l + r) >> 1

int Q, n, type, L, R, K, cnt, size;
int q[MAXN], qn;

struct Node {
	int size, lchild, rchild;

	#define size(x) node[x].size
	#define lc(x) node[x].lchild
	#define rc(x) node[x].rchild
} node[MAXN * 20];

//区间线段树合并
inline int modify(int y, int l, int r, int k) {
	int x = ++ cnt;
	node[x] = node[y], ++ size(x);
	if(l == r) return x;
	if(key <= mid) lc(x) = modify(lc(y), l, mid, k);
	else rc(x) = modify(rc(y), mid + 1, r, k);
	return x;
}

//查询区间(x, y)内与k异或和最大的元素
inline int queryXor(int x, int y, int l, int r, int k, int len) {
	if(l == r) return l;

	//从最高位开始贪心
	if(k & len) {
		if(size(lc(y)) - size(lc(x))) return queryXor(lc(x), lc(y), l, mid, k, (len >> 1));
		else return queryXor(rc(x), rc(y), mid + 1, r, k, (len >> 1));
	} else {
		if(size(rc(y)) - size(rc(x))) return queryXor(rc(x), rx(y), mid + 1, r, k, (len >> 1));
		else return queryXor(lc(x), lc(y), l, mid, k, (len >> 1));
	}
}

//查询区间(x, y)内比k小的元素的个数
inline int querySize(int x, int y, int l, int r, int k) {
	//在区间线段树上，若r小于k，则可知(l, r)间的元素全部小于k
	if(r <= k) return size(y) - size(x);
	if(size(y) == size(x)) return 0;

	//向左子树查询
	if(k <= mid) return querySize(lc(x), lc(y), l, mid, k);
	//计算左子树的贡献并向右查询
	else return size(lc(y)) - size(lc(x)) + querySize(rc(x), rc(y), mid + 1, r, k);
}

//查询区间(x, y)内的第k大值
inline int query(int x, int y, int l, int r, int k) {
	if(l == r) return l;
	int res = size(lc(y)) - size(lc(x));
	if(k <= res) return query(lc(x), lc(y), l, mid, k);
	else return query(rc(x), rc(y), mid + 1, r, k - res);
}

//以下是调用接口
inline void insert(int x) {
	q[++ qn] = modify(q[qn - 1], 0, SIZE, x);
}

inline int queryXor(int l, int r, int k) {
	return queryXor(q[L - 1], q[R], 0, SIZE, k, (1 << 18));
}

inline int querySize(int l, int r, int k) {
	return querySize(q[L - 1], q[R], 0, SIZE, k);
}

inline int query(int l, int r, int k) {
	return query(q[L - 1], q[R], 0, SIZE, k);
}