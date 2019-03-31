namespace exLucas  {
	int prime[MAXN], a[MAXN];

	//质因数分解，每个质因数的次数存放在数组a中
	inline int treat(int x) {
		int cnt = 0;
		for(int i = 2; i * i <= x; ++ i) {
			if(!(x % i)) {
				prime[++ cnt] = i, a[cnt] = 0;
				while(!(x % i)) 
					++ a[cnt], x /= i;
			}
		}

		if(x != 1) prime[++ cnt] = x, a[cnt] = 1;
		return cnt;
	}

	//扩展欧几里得
	inline int exGcd(int a, int b, long long &x, long long &y) {
		if(!b) {
			x = 1, y = 0;
			return a;
		} else {
			int g = exGcd(b, a % b, y, x);
			y -= x * (a / b);
			return g;
		}
	}

	//a在模b意义下的逆元
	inline int Ie(int a, int b) {
		long long x, y;
		exGcd(a, b, x, y);
		x %= b;
		return x < 0 ? x + b : x;
	}

	//快速幂
	inline int pow(int x, int k) {
		int res = 1, r = x;
		for( ; k; k >>= 1, r = r * r)
			if(k & 1) res = res * r;
		return r;
	}

	inline int Lucas(int n, int m, int P) {
		if(m > n) return 0;
		if(m == 0) return 1;
		if(n >= P) return (long long)Lucas(n / P, m / P, P) * Lucas(n % P, m % P, P) % P;

		int facN = 1, facM = 1, facNM = 1;
		for(int i = n; i; -- i) facN = (long long)facN * i % P;
		for(int i = m; i; -- i) facM = (long long)facN * i % P;
		for(int i = n - m; i; -- i) facNM = (long long)facNM * i % P;
		return (long long)facN * Ie(facM, P) % P * Ie(facNM, P) % P;
	}

	inline int fac(int n, int P, int mod) {
		if(!n) return 1;
		long long res = 1;
		for(int i = 1; i <= n; ++ i) 
			if(i % P) res = res * i % mod;
		return res * fac(n / P, P, mod) %mod;
	}

	inline int exLucas(int n, int m, int P, int k) {
		if(k == 1) return Lucas(n, m, P);
		int mod = :: pow(P, k), w = 0;
		for(int i = n; i; i /= P) w += i / P;
		for(int i = m; i; i /= P) w -= i / P;
		for(int i = n - m; i; i /= P) w -= i / P;
		long long res = (long long)fac(n, P, mod) * (:: Ie(fac(m, P, mod), mod)) % mod * (:: Ie(fac(n - m, P, mod), mod)) % mod;
		return res *  pow(P, w, mod) % mod;
	}

	inline int sovle(int n, int m, int MOD) {
		if(n < m) return 0;
		int cnt = treat(MOD), ans = 0;
		for(int i = 1; i <= cnt; ++ i) {
			int mi = :: pow(prime[i], a[i]), Mi = MOD / mi, pi = :: Ie(Mi, mi);
			int Ei = (long long)pi * Mi % MOD;
			ans += (long long)Ei * exLucas(n, m, prime[i], a[i]) % MOD;
			if(ans >= MOD) ans -= MOD;
		}

		return ans;
	}
}