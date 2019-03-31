struct Node {
	Node *lchild, *rhcild;
	int dist, size, value;
	long long sum;

	Node() {}
	Node(const int &v) {
		lc = NULL, rc = NULL;
		dist = 0, size = 1, value = sum = v;
	}

	inline Node *Update() {
		size = (lchild ? lchild->size : 0) + (rchild ? rchild->size : 0) + 1;
		sum = (lchild ? lchild->sum : 0) + (rchild ? rchild->sum : 0) + value;
		return this;
	}
} *tree[MAXN];

Node *Merge(Node *x, Node *y) {
	if(!x) return y;
	if(!y) return x;
	if(x->value < y->value) std :: swap(x, y);
	x->rchild = Merge(x->rchild, y);    //将较小堆与较大堆的极右子树合并

	if(!x->lchild || x->lchild->dist < x->rchild->dist) std :: swap(x->lchild, x->rchild);    //使用交换左右子树的方法调整左右子树距离大小关系
	x->dist = x->rchild ? x->rchild->dist + 1 : 0;
	return x->Update();
}

inline void Balance(Node *&x) {
	while(x->sum > m) 
		x = Merge(x->lchild, x->rchild);
}

inline void Relax(long long &x, const long long &y) {
	if(x < y) x = y;
}