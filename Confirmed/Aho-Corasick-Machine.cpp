#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
#define MAXN 500000

struct Node {
	int cnt, fail;
	int next[26];
} node[MAXN];

int n, m, pos;
char s[MAXN * 20];

inline int newNode() {
	for(int i = 0; i < 26; ++ i) node[pos].next[i] = 0;
	node[pos].fail = node[pos].cnt = 0;
    return pos ++;
}

inline void insert(char *s) {
	int u = 0;
	for(int i = 0; s[i]; ++ i) {
		int k = s[i] - 'a', &x = node[u].next[k];
		u = x ? x : x = newNode();
	}

	node[u].cnt ++;
}  

inline void getNext() {
	int q[MAXN], ql = 0, qr = 0;
	q[++ qr] = 0;
	while(ql < qr) {
		int u = q[++ ql];
		node[u].cnt += node[node[u].fail].cnt;

		for(int i = 0; i < 26; ++ i) {
			int v = node[u].next[i];
			if(v == 0)
				node[u].next[i] = node[node[u].fail].next[i];
			else
				q[++ qr] = v;
			if(u && v) 
				node[v].fail = node[node[u].fail].next[i];
		}
	}
}

inline int query(char *s) {
	int res = 0, index, d = 0;
	for(int i = 0; s[i]; ++ i) {
		index = s[i] - 'a';
		d = node[d].next[index];
		res += node[d].cnt;
		node[d].cnt = 0;
	}

	return res;
}