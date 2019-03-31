struct hashTable {
	static const int HASHSIZE = 30001;

	struct Node {
		long long start, value;
		Node *next;

		Node() {}
		Node(long long start, long long value, Node *next) : start(start), value(value), next(next) {}
	} *head[HASHSIZE], node[HASHSIZE], *_end;

	int time[HASHSIZE], curr;

	hashTable() {
		curr = 0, clear();
	}

	void clear() {
		curr ++, _end = node;
	}


	int hash(long long start) {
		return start % HASHSIZE;
	}

	Node *begin() {
		return node;
	}

	Node *end() {
		return _end;
	}

	void push(long long start, long long value) {
		int i = hash(start);
		if(time[i] != curr) time[i] = curr, head[i] = NULL;
		for(Node *e = head[i]; e; e = e->next) {
			if(v->start == start)
				return (void)(v->value += value);
			head[i] = new(_end++) Node(start, value, head[i]);
		}
	}
};