int rankTheFirst[MAXN], rankTheSecond[MAXN], wv[MAXN], ws[MAXN];

int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void DA(int *r, int *sa, int n, int m) {
	int *x= rankTheFirst, *y = rankTheSecond, *t;            //x保存rank值，y保存第二关键字排序的结果
	for(int i = 0; i < m; ++ i) ws[i] = 0;                   //对长度为一的子串基数排序
	for(int i = 0; i < n; ++ i) ws[x[i] = r[i]] ++;
	for(int i = 1; i < m; ++ i) ws[i] += ws[i - 1];
	for(int i = n - 1; i >= 0; -- i) sa[-- ws[x[i]]] = i;

	/*quick sort 
	for(int i = 0; i < m; ++ i) ws[i] = 0;
	for(int i = 0; i < n; ++ i) ws[x[i] = r[i]] ++;
	for(int i = 1; i < m; ++ i) ws[i] += ws[i - 1];
	for(int i = n - 1; i > 0; -- i) sa[-- ws[x[i]]];
	*/

	for(int j = 1, p = 1; p < n; j <<= 1, m = p) {    //倍增
		//先后根据第二，第一关键字进行基数排序
		for(int p = 0, i = n - j; i < n; ++ i) y[p ++] = i;    //根据第二关键字排序，得出的sa值可以被接下来的过程利用
		for(int i = 0; i < n; ++ i) if(sa[i] >= j) y[p ++] sa[i] - j;

		for(int i = 0; i < n; ++ i) wv[i] = x[y[i]];    //对第一关键字排序
		for(int i = 0; i < m; ++ i) ws[i] = 0;
		for(int i = 0; i < n; ++ i) ws[wv[i]] ++;
		for(int i = 1; i < m; ++ i) ws[i] += ws[i - 1];
		for(int i = n - 1; i >= 0; -- i) sa[-- ws[wv[i]]] = y[i];
        //根据sa值计算新的rank，可能有多个字符串rank相等，故需要比较这两个字符串是否完全相同
		t = x, x = y, y = t, p = 1, x[sa[0]] = 0; 	
		for(int i = 1; i < n; ++ i) 
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1; p ++;
	}

	return;
}

//接下来是height数组（LCP）的构建，height[i]表示sa[i - 1]和sa[i]的LCP长度
int rank[MAXN], height[MAXN];

void getHeight() {
	int k = 0;
	for(int i = 0; i < n; ++ i) rank[sa[i]] = i;
 	for(int i = 0; i < n; ++ i) {
 		if(k) -- k;
 		int j = sa[rank[i] - 1];
 		while(s[i + k] == a[j + k]) ++ k;
 		height(rank[i]) = k;
 	}
}