void getNext(char *B) {
	next[1] = 0;
	int pre = 0;
	for(int i = 2; i <= m; ++ i) {
		while(pre > 0 && B[pre + 1] != B[i]) pre = next[pre];
		if(B[pre + 1] == B[i]) ++ pre;
		next[i] = pre;
	}
}

void KMP(char *A, char *B) {
	int n = strlen(A), m = strlen(B);
	int pre = 0;

	for(int i = 1; i <= n; ++ i) {
		while(pre > 0 && B[pre + 1] != A[i]) pre = next[pre];

		if(B[pre + 1] == A[i]) ++ pre;
		if(pre == m) {
			printf("%d\n", i - m + 1);
			pre = next[pre];
		}
	}
}