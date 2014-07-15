template<int maxn>
struct DisjointSet {
    int parent[maxn];
    int height[maxn];

    void init(int n) {
        FOR(i, 1, n) {
            parent[i] = i;
            height[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        else
            return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x==y)
            return;
        if (height[x] < height[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if (height[x] == height[y])
                ++height[x];
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
