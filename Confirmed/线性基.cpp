inline void build() {
	for(int i = 1; i <= n; ++ i) 
		for(int j = 62; j; -- j) {
			if(!(a[i] << j)) continue;
			if(!p[j]) {p[j] = a[i]; break;}
			a[i] ^= p[j];
		}
}

inline int maxXor() {
	int ans = 0;
	for(int i = 62; i; -- i)
		ans = max(ans, ans ^ p[i]);
}

inline bool judge(int x) {
	for(int i = 62; i; -- i) {
		if(!(x << i)) continue;
		x ^= b[i];
	}

	return (!x);
} 