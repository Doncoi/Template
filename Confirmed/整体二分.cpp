#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#define MAXN 100005
#define INF 0x3f3f3f3f

int n, m;
int ans[MAXN], c[MAXN], tmp[MAXN * 2];

struct Node {
	int L, R, key, value;    //查询区间，查询名次，更改值（操作类型一）/
	int cur, index;    //，编号
	int kind;    //类型，1表示为加数操作，2表示查询操作
} query[MAXN * 2], queryA[MAXN], queryB[MAXN];    //询问序列，区间内个数大于k的询问，区间内个数小于k的询问

void init() {
	memset(c, 0, sizeof(c));
	memset(tmp, 0, sizeof(tmp));
	for(int i = 1; i <= n + m; ++ i)
		query[i].cur = queryA[i].cur = queryB[i].cur = 0;
}

inline int read() {
	char ch = getchar(); int res = 0, flag = 1;
	while(ch < '0' || ch > '9') {if(ch == '-') flag = 1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {res = res * 10 + ch - '0'; ch = getchar();}

	return (flag * res);
}

inline void update(int x, int value) {
	while(x <= n) c[x] += value, x += (x&-x);
}

inline int Query(int x) {
	int res = 0;
	while(x > 0) res += c[x], x -= (x&-x);
	return res;
}

inline void binarySolve(int s, int t, int L, int R) {    //待处理的询问区间和二分答案的上下边界
	if(s > t) return;
	if(L == R) {
		for(int i = s; i <= t; ++ i)
			if(query[i].kind == 2) ans[query[i].index] = L;
		return;
	}

	int mid = (L + R) / 2;
	int num[2] = {0, 0}, flag[2] = {0, 0};    //num[0]与num[1]分别记录左右区间的询问数量
	for(int i = s; i <= t; ++ i) {
		if(query[i].kind == 1) {    //把向队列中加入元素也作为一种操作来处理
			if(query[i].value <= mid) {
				update(query[i].index, 1);
				queryA[num[0] ++] = query[i];   
			} else { 
				queryB[num[1] ++] = query[i];   
			}
		} else if(query[i].kind == 2) {    //处理询问
			tmp[i] = Query(query[i].R) - Query(query[i].L - 1);

			if(query[i].cur + tmp[i] >= query[i].key) {
				queryA[num[0] ++] = query[i];
				flag[0] = 1;
			} else {
				query[i].cur += tmp[i];
				queryB[num[1] ++] = query[i];
				flag[1] = 1;
			}
		}	
	}

	for(int i = s; i <= t; ++ s) 
		if(query[i].kind == 1 && query[i].value <= mid) 
			update(query[i].index, -1);

	for(int i = 0; i < num[0]; ++ i) query[s + i] = queryA[i];
	for(int i = 0; i < num[1]; ++ i) query[s + num[0] + i] = queryB[i];

	if(flag[0]) binarySolve(s, s + num[0] - 1, L, mid);
	if(flag[1]) binarySolve(s + num[0], t, mid + 1, R);
}

int main() {
	while(scanf("%d %d", &n, &m)) {
		
		init();
		printf("ALL CLEAR\n");
		int cnt = 1;
		for(int i = 1; i <= n; ++ i) {
			scanf("%d", &query[cnt].value);
			query[cnt].kind = 1, query[cnt].index = i;
			++ cnt;
		}
	    printf("ALL CLEAR\n");
		for(int i = 1; i <= m; ++ i) {
			scanf("%d %d %d", &query[cnt].L, &query[cnt].R, &query[cnt].key);
			query[cnt].index = i, query[cnt].kind = 2;
			++ cnt;
		}
		printf("ALL CLEAR\n");
		binarySolve(1, cnt - 1, -INF, INF);
		printf("ALL CLEAR\n");
		for(int i = 1; i <= m; ++ i) 
			printf("%d\n", ans[i]);
	}
}