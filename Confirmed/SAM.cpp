struct SAM {
	string s;
	int son[MAXN][26], pre[MAXN], step[MAXN], last, total;

	inline void pushBack(int x) {
		step[++ total] = x;
	} 

	inline void extend(int ch) {
		pushBack(step[last] + 1);
		int p = last, np = total;
		for( ; !son[p][ch]; p = pre[p]) son[p][ch] = np;
		if(!p) {
			pre[np] = 0;
		} else {
			int q = son[p][ch];
			if(step[q] != step[p] + 1) {
				pushBack(step[p] + 1);
				int nq = total;
				std :: memcpy(son[nq], son[q], sizeof(son[q]));
				pre[nq] = pre[q], pre[q] = pre[np] = nq;
				for( ; son[p][ch] == q; p = pre[p]) son[p][ch] = nq;
				else pre[np] = q;
			}
		}

		last = np;
	}

	inline void build() {
		std :: cin >> s;
		total = last = 0;
		memset(son, 0, sizeof(son));
		memset(pre, 0, sizeof(pre));
		memset(step, 0, sizeof(step));
		for(int i = 0, End = s.size(); i != End; ++ i) 
			extend(s[i] - 'A');
		visit(0, 0);
	}
}