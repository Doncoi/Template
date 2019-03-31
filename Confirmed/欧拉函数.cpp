//type 1    计算x的φ值
long long phi(long long x) {    
	long long a = x;
	for(long long i = 2; i <= m; ++ i) {
		if(x % i == 0) {                  //找到了一个因数
			a = a / i * (i - 1);          //φ基本计算公式
			while(x % i == 0) {           //去除所有包含因数i的因数
				x /= i;
			}
		}
	}

	if(x > 1) a = a / x * (x - 1);        //处理最后一个因数
	return a;
}

//type 2    预处理φ数组的前缀和
long long p[MAXN], phi[MAXN], prime[MAXN];

void init() {
	phi[1] = 1;
	for(int i = 2; i <= n; ++ i) {
		if(!p[i]) {
			prime[++ prime[0]] = i;
			phi[i] = i - 1;
		}

		for(int j = 1; j <= prime[0] && prime[j] <= n; ++ j) {
			p[i * prime[j]] = 1;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j ] - 1);
			}
		}

		phi[i] += phi[i - 1];
	}
}