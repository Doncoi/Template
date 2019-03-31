#include <cstdio>
#include <algorithm>
#include <cstring>

int n, maxn;
int a[1005];
int f[1005];

int main() {
	scanf("%d", &n);
	for(int i = 1;i <= n;i ++) 
		scanf("%d", &a[i]);

	memset(f, 0, sizeof(f));
	f[1] = 1;    maxn = 1;
	for(int i = 2;i <= n;i ++) 
		for(int j = 1;j <= i;j ++) 
			if(a[j] < a[i] && f[j]) {
				f[i] = std :: max(f[i], f[j] + 1);		
				maxn = std :: max(maxn, f[i]);
			}

	printf("%d", maxn);
}
