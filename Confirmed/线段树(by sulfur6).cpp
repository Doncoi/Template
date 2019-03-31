#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

typedef long long ll;

const int MAXN = 200000;

int n, q;
ll a[MAXN + 1];

struct Segt {
#define mid (this->l + (this->r - this->l) / 2)
	int l, r;
	Segt *lc, *rc;
	ll sum, tag;

	Segt(int l, int r, Segt *lc, Segt *rc) : l(l), r(r), lc(lc), rc(rc), sum(0), tag(0) {}

	void cover(ll x) {
		sum += x * (r - l + 1);
		tag += x;
	}

	void pushDown() {
		if (tag) {
			lc->cover(tag);
			rc->cover(tag);
			tag = 0;
		}
	}

	void update() {
		sum = lc->sum + rc->sum;
	}

	void modify(int l, int r, ll x) {
		if (l == this->l && r == this->r) cover(x);
		else {
			pushDown();
			if (r <= mid) lc->modify(l, r, x);
			else if (l > mid) rc->modify(l, r, x);
			else {
				lc->modify(l, mid, x);
				rc->modify(mid + 1, r, x);
			}
			update();
		}
	}

	ll query(int l, int r) {
		if (l == this->l && r == this->r) return sum;
		else {
			pushDown();
			if (r <= mid) return lc->query(l, r);
			else if (l > mid) return rc->query(l, r);
			else return lc->query(l, mid) + rc->query(mid + 1, r);
		}
	}
#undef mid

	static Segt *build(int l, int r) {
		if (l == r) {
			Segt *v = new Segt(l, r, NULL, NULL);
			v->sum = a[l];
			return v;
		} else {
			int mid = l + (r - l) / 2;
			Segt *v = new Segt(l, r, build(l, mid), build(mid + 1, r));
			v->update();
			return v;
		}
	}
} *segt;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	segt = Segt::build(1, n);
	scanf("%d", &q);
	for (int cmd, l, r; q--; ) {
		scanf("%d %d %d", &cmd, &l, &r);
		if (cmd == 1) {
			ll x;
			scanf("%lld", &x);
			segt->modify(l, r, x);
		} else if (cmd == 2) {
			printf("%lld\n", segt->query(l, r));
		} else throw "%%% LYX";
	}
	return 0;
}
