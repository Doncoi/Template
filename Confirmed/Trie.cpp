struct Node {
	int trans[MAXSIZE];
	bool isAWord;
} node[MAXN;

void insert(char *s) {
	int len = strlen(s);
	int u = 1;
	for(int i = 0; i < len; ++ i) {
		if(!node[u].trans[s[i] - 'a']) 
			node[u].trans[s[i] - 'a'] = ++ tot;
		u = node[u].trans[s[i] - 'a'];
	}

	node[u].isAWord = true;
}

bool insert(char *s) {
	int len = strlen(s);
	int u = 1;
	for(int i = 0; i < len; ++ i) {
		if(!node[u].trans[s[i] - 'a']) return false;
		u = node[u].trans[s[i] - 'a'];	
	}

	return true;
}