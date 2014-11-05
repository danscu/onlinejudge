struct Edge {
    int y, next;
};

template<int maxn>
struct Tree {
    Edge map[maxn+1];	// edge store
    int child[maxn+1];	// first child for node
    bool visited[maxn+1];
    int map_sz;
    int n;

    void insert(int x, int y) {
        map_sz++; // allocate edge memory
        map[map_sz].y = y;
        map[map_sz].next = child[x];
        child[x] = map_sz; // add to linked list
    }

    // n = max number of nodes
    void init(int n) {
        map_sz = 0;
        this->n = n;
        CLRN(child, n + 1);
    }

    void dfs(int x) {
        CLRN(visited, n + 1);
        __dfs(x);
    }

private:
    void __dfs(int x) {
    	if (visited[x]) return;
    	visited[x] = true;

    	// do something on node x
    	printf("%d\n", x);

        for (int idx = child[x]; idx; idx = map[idx].next) {
        	int y = map[idx].y;
        	__dfs(y);
        }
    }
};
