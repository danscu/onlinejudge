/* trie */
/* poj 2418 */

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#ifdef BENCH
#define DBG 0 // modify this for enabling/disable debug
#else
#define DBG 0
#endif // BENCH

#define D(...) do { if (DBG) fprintf(stderr, __VA_ARGS__); } while (0)

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
	typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++

struct Trie {
	struct TrieNode {
		TrieNode *child[256];
		int count;
	};

	int n;

	TrieNode *init() {
		n = 0;
		return new TrieNode();
	}

	void insert(TrieNode *u, char *word) {
		if (!word) return;
		n++;
		TrieNode *v;
		char *p;
		v = u;
		for (p = word; *p; p++) {
			if (v->child[*p] == 0)
				v->child[*p] = new TrieNode();
			v = v->child[*p];
		}
		v->count++;
	}

	void dfs(TrieNode *root) {
		static char dump[31];
		static int pos;

		if (root->count) {
			dump[pos] = '\0';
			if (dump[0])
				printf("%s %0.4f\n", dump, (float)root->count*100/n);
		}

		REP(i, 256) {
			if (root->child[i]) {
				dump[pos++] = i;
				dfs(root->child[i]);
				pos--;
			}
		}
	}
};

Trie trie;

int main() {
#if BENCH
	freopen("files/poj2418_trie_hardwood.txt","r",stdin);
#endif
	char w[31];
	Trie::TrieNode *root = trie.init();
	while (gets(w))
		trie.insert(root, w);
	trie.dfs(root);
	return 0;
}
