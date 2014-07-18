/* Aho-Corasick */
template<int maxn, int maxm>
struct ACAuto {
	int next[maxn][maxm], fail[maxn], data[maxn], size;
	int que[maxn], head, tail;

	int code(char c) {
		return c - 'a';
	}

	void clear(int x) {
		CLRV(next[x], -1);
		fail[x] = -1; data[x] = 0;
	}

	void init() {
		clear(0);
		size = 1;
	}

	void insert(const char *str) {
		int p = 0, idx;
		while (*str) {
			idx = code(*str);
			if (next[p][idx] == -1) {
				clear(size);
				next[p][idx] = size++;
			}
			p = next[p][idx];
			str++;
		}
		data[p]++;
	}

	void buildAC() {
		int p, pp, fp, fpp;
		head = tail = 0;
		que[tail++] = 0;
		while (head < tail) {
			p = que[head++];
			for (int i = 0; i < maxm; i++) {
				if ((pp = next[p][i]) != -1) {
					for (fp = fail[p]; fp != -1; fp = fail[fp]) {
						if ((fpp = next[fp][i]) != -1) {
							fail[pp] = fpp;
							break;
						}
					}
					if (fp == -1) fail[pp] = 0;
					que[tail++] = pp;
				} else {    // next?
					if (p == 0) next[p][i] = 0;
					else next[p][i] = next[fail[p]][i];
				}
			}
		}
	}

	int query(char *str) {
		int p = 0, ret = 0, idx, pp;
		while (*str) {
			idx = code(*str);
			p = next[p][idx];
			for (pp = p; pp != -1 && data[pp] != -1; pp = fail[pp]) {
				ret += data[pp];
				data[pp] = -1;
			}
			++str;
		}
		return ret;
	}
};
