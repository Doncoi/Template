//埃氏筛法优化*****************************************************************************************************************************
void prime() {
	memset(prime, true, sizeof(prime));
	for(int j = 4;j <= n;j += 2) 
		prime[j] = 0;

	for(int i = 3;i <= n;i += 2) {
		if(!prime[i]) continue;
		for(int j = i * 2;j <= n;j += i * 2)
			prime[j] = 0;
	}
}

//线性筛***************************************************************************************************************************************
#include <cstdio>
#include <climits>                                                                

int prime[INT_MAX / 100], vis[INT_MAX / 100];
int tot = 0;

inline void euler(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) prime[++tot] = i;
		for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int main() {
	int l, r, ans = 0;
	scanf("%d %d", &l, &r);
	euler(r);
	for (int i = 1; i <= tot; i++) {
		if (prime[i] >= l) 	ans++;
	}
	
	printf("%d", ans);
	return 0;
}

//GCD******************************************************************************************************************************************
int gcd(int x, int y) {                                            
	return x % y ? gcd(y, x % y) : y;
}

//扩展欧几里得*********************************************************************************************************************************
int ExGcd(int a, int b, int &x, int &y) {
    if (b==0) {
        x = 1; y = 0;
        return a;
    }
    int ans = ExGcd(b, a%b, y, x);
    y -= x*(a/b);
    return ans;
}

//快速幂***************************************************************************************************************************************
int quick_pow(int a, int b, int p)
{
	int ans = 1;
	for( ; b; a = (a * a) % p, b >>= 1) 
	{
		if(b & 1) ans = (ans * a) % p;
	}
	return ans;
}