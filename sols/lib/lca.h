template<int maxn>
struct LCA {
    Edge map[maxn+1];
    int child[maxn+1], parent[maxn+1];
    bool visited[maxn+1];
    int n;
    int cnt;

    void insert(int x, int y) {
        cnt++;
        child[x] = cnt;
    }

    void init(int n) {
        this->n = n;
        cnt = 0;
        CLRN(child, n + 1);
        CLRN(visited, n + 1);
        memset(parent, -1, sizeof(parent[0])*(n+1));
    }

    int findSet(int x) {
        if (parent[x] == x) return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void mergeSet(int x, int y) {
        int fx = findSet(x);
        parent[y] = fx;
    }

    int tarjan(int x, int qx, int qy) {
        for (int t = child[x]; t; t = map[t].next) {
            int ans = tarjan(map[t].y, qx, qy);
            if (ans >= 0) return ans;
            mergeSet(x, map[t].y);
            visited[map[t].y] = true;
        }
        if (qx == x && visited[qy])
            return findSet(qy);
        if (qy == x && visited[qx])
            return findSet(qx);
        return -1;
    }
};

LCA<maxn> lca;
