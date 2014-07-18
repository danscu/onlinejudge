template<int maxw>
struct KMP {
	int wlen, tlen;
	int fail[maxw];
	char *w, *t;

	// Pre-process the pattern
	// next[i]: Let pre[i] denote the prefix of pattern of length i
	//          fail[i] is -1 + the length of the longest suffix ending at i which is also a prefix of pre[i].
	void buildFailureFunction() {
		int i, j = -1;
		fail[0] = -1;
		for (i = 1; i <= wlen; i++) {
			while (j > -1 && w[j + 1] != w[i])
				j = fail[j];
			if (w[j + 1] == w[i]) j++;
			fail[i] = j;
		}
	}

	int kmp(char *w, char *t) {
		int cnt = 0;
		this->w = w, this->t = t;
		wlen = strlen(w);
		tlen = strlen(t);

		int i, j = -1;
		buildFailureFunction();

		for (i = 0; i < tlen; i++) {
			while (j != -1 && w[j + 1] != t[i])
				j = fail[j];
			if (w[j+1] == t[i])
				j++;
			if (j == wlen - 1)
				cnt++;
		}

		return cnt;
	}
};
