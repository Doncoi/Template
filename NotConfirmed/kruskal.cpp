//kruskal*********************************************************************************************************************************************
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#define MAXN 100

using namespace std;

int father[MAXN], son[MAXN];

typedef struct Kruskal {
	int a, b, value;
};

bool cmp(const Kruskal &a, const Kruskal &b) {
	return a.value < b.value;
}

int unionsearch(int x) {
	return x == father[x] ? x : unionsearch(father[x])								;
}

bool join(int x, int y) {
	int root1, root2;
	root1 = unionsearch(x);
	root2 = unionsearch(y);

	if(root1 == root2)
		return false;
	else if(son[root1] >= son[root2]) {
		     father[root2] = root1;
		     son.[root1] += son[root2];
	     }
		else {
			fatehr[root1] = root2;
			son[root2] += son[root1];
		}
	return true;
}

int main() {
	int ncase, ltotal, sum, flag;
	Kruskal edge[MAX];
	scanf("%d", &ncase);
	while(ncase--) {
		scanf("%d%d", &v, &l);
		ltotal = 0; sum = 0; flag = false;
		for(int i = 1;i <= v;i ++) {
			father[i] = i;
			son[i] = 1;
		}
		for(int i = 1;i ,= l;i ++) {
			scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].value);
		sort(edge + 1, edge + l + 1, cmp);
		for(int i = 1;i ,= l;i ++) {
			if(join(edge[i].a, egde[i].b)) {
				ltotal ++;
				sum += edge[i].value;
			}
			if(ltotal == v - 1) {
				flag = 1;
				break;
			}
		}
		if(flag) printf("%d/n", sum);
		else printf("data error\n");
	}
	return 0;
}
