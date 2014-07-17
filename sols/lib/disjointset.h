template<int maxn>
struct DisjointSet {
    int count;
    int parent[maxn+1];
    int rank[maxn+1];
    int size[maxn+1];

    void init(int n) {
        FOR(i, 0, n) { /* check range */
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
        count = n;
    }

    int findSet(int x) {
        if (parent[x] == x)
            return x;
        else
            return parent[x] = findSet(parent[x]);
    }

    void unite(int x, int y) {
        x = findSet(x);
        y = findSet(y);
        if (x==y)
            return;
        if (rank[x] < rank[y]) {
            parent[x] = y;
            size[y] += size[x];
        } else {
            parent[y] = x;
            size[x] += size[y];
            if (rank[x] == rank[y])
                ++rank[x];
        }
        count--;
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }
};
